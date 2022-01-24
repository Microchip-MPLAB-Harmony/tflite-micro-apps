/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_audio.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app_audio.h"        
#include "app_ml.h"
#include "osal/osal.h"
#include "micro_model_settings.h"
#include "app_config.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

DRV_I2S_DATA __attribute__ ((aligned (32))) micBuffer[AUDIO_NUM_OF_BUFFERS][AUDIO_BUFFER_SIZE];
AUDIO_DATA_TYPE micCaptureBuffer[kMicCaptureBufferSize];
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_AUDIO_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_AUDIO_DATA app_audioData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/// *****************************************************************************
 /*
  Function:
        static void WM8904_TimerCallback
        (
            uintptr_t context
        )

  Summary:
    Implements the handler for timer callback function.

  Description:
    Called every 1 ms by timer services.  It then decrements WM8904Delay if
    non-zero.

  Parameters:
    context      - Contains index into driver's instance object array

  Remarks:
    None
*/
static void App_TimerCallback( uintptr_t context)
{
    KeyRepeatTask();    // used to debounce button or touch events
    APP_ML_DelayTick();
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

void _audioCodecDataInitialize (AUDIO_CODEC_DATA* codecData)
{
    codecData->handle = DRV_HANDLE_INVALID;
    codecData->context = 0;
    codecData->bufferHandler = 
           (DRV_CODEC_BUFFER_EVENT_HANDLER) Audio_Codec_BufferEventHandler;
    codecData->txbufferObject = (uint8_t *) micBuffer[0];
    codecData->rxbufferObject = (uint8_t *) micBuffer[1];
    codecData->bufferSize = sizeof(micBuffer[0]);
    
}
/*******************************************************************************
  Function:
    void APP_AUDIO_Initialize ( void )

  Remarks:
    See prototype in app_audio.h.
 */

void APP_AUDIO_Initialize ( void )
{
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */   
    app_audioData.state = APP_AUDIO_STATE_INIT;
    app_audioData.audio_timestamp = 0;
    
    _audioCodecDataInitialize (&app_audioData.codecData);
    
    OSAL_SEM_Create(&app_audioData.rxTransferDone, OSAL_SEM_TYPE_BINARY, 0, 0);

    APP_AUDIO_Initialize_sub();        // do specific gui/non-gui initialization    
}


/******************************************************************************
  Function:
    void APP_AUDIO_Tasks ( void )

  Remarks:
    See prototype in app_audio.h.
 */
DRV_HANDLE tmrHandle;

void APP_AUDIO_Tasks ( void )
{   
    APP_AUDIO_Tasks_sub();        // do specific gui/non-gui processing    
    
    /* Check the application's current state. */
    switch ( app_audioData.state )
    {       
        /* Application's initial state. */
        case APP_AUDIO_STATE_INIT:
        {
            /* Open the timer Driver */
            tmrHandle = SYS_TIME_CallbackRegisterMS(App_TimerCallback, 
                    (uintptr_t)0, 1/*ms*/, SYS_TIME_PERIODIC);

            if ( SYS_TIME_HANDLE_INVALID != tmrHandle )
            {
               app_audioData.state = APP_AUDIO_STATE_CODEC_OPEN;
            }            
        }
        break;
        
        case APP_AUDIO_STATE_CODEC_OPEN:
        {
            // see if codec is done initializing
            SYS_STATUS status = DRV_CODEC_Status(sysObjdrvCodec0);           
            if (SYS_STATUS_READY == status)
            {
                // This means the driver can now be be opened.
                /* A client opens the driver object to get an Handle */
                app_audioData.codecData.handle = DRV_CODEC_Open(DRV_CODEC_INDEX_0, 
                    (DRV_IO_INTENT)(DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_EXCLUSIVE));       
                if(app_audioData.codecData.handle != DRV_HANDLE_INVALID)
                {
                    DRV_CODEC_VolumeSet(app_audioData.codecData.handle,
                        DRV_CODEC_CHANNEL_LEFT_RIGHT, app_audioData.volume);
                                          
                    app_audioData.state = APP_AUDIO_STATE_CODEC_SET_BUFFER_HANDLER;
                }            
            }
        }
        break;
        
        /* Set a handler for the audio buffer completion event */
        case APP_AUDIO_STATE_CODEC_SET_BUFFER_HANDLER:
        {
            DRV_CODEC_BufferEventHandlerSet(app_audioData.codecData.handle, 
                                            app_audioData.codecData.bufferHandler, 
                                            app_audioData.codecData.context);                                          
            
            app_audioData.state = APP_AUDIO_STATE_CODEC_ADD_BUFFER;           
        }
        break;
       
        case APP_AUDIO_STATE_CODEC_ADD_BUFFER:
        {
            DRV_CODEC_BufferAddWriteRead(app_audioData.codecData.handle,
                    &app_audioData.codecData.writeBufHandle,
                    app_audioData.codecData.txbufferObject, app_audioData.codecData.rxbufferObject,
                    app_audioData.codecData.bufferSize);
            
            if(app_audioData.codecData.writeBufHandle != DRV_CODEC_BUFFER_HANDLE_INVALID)
            {
                app_audioData.txBufferIdx = 1 - app_audioData.txBufferIdx;      // swap between 0 and 1
                app_audioData.rxBufferIdx = 1 - app_audioData.txBufferIdx;
                
                app_audioData.codecData.txbufferObject = (uint8_t *) micBuffer[app_audioData.txBufferIdx];
                app_audioData.codecData.rxbufferObject = (uint8_t *) micBuffer[app_audioData.rxBufferIdx];                
        
                app_audioData.state = APP_AUDIO_STATE_CODEC_WAIT_FOR_BUFFER_COMPLETE;
            }
            
            const int32_t start_sample_offset = app_audioData.audio_timestamp * (kAudioSampleFrequency / 1000);
 
            for (int i = 0; i < AUDIO_BUFFER_SIZE; ++i) {
                const int capture_index = (start_sample_offset + i) % kMicCaptureBufferSize;
                micCaptureBuffer[capture_index] = micBuffer[app_audioData.txBufferIdx][i].leftData/2 + micBuffer[app_audioData.txBufferIdx][i].rightData/2;
            }
            
            app_audioData.audio_timestamp = app_audioData.audio_timestamp + (AUDIO_BUFFER_SIZE / (kAudioSampleFrequency / 1000));
            
        }
        break;

        /* Audio data Transmission under process */
        case APP_AUDIO_STATE_CODEC_WAIT_FOR_BUFFER_COMPLETE:
        {

            
            /* Wait for transfer to complete */
            if (OSAL_SEM_Pend(&app_audioData.rxTransferDone, OSAL_WAIT_FOREVER) == OSAL_RESULT_TRUE)
            {
                    
            }
                        
        }
        break;
         
        default:
        {
            /* TODO: Handle error in application's state machine. */
        }
        break;             
    }
}

//******************************************************************************
// 
// Audio_Codec_TxBufferComplete() - Set APP_Tasks Next state to buffer complete.
//
// NOTE: Called from APP_CODECBufferEventHandler().
//
// TODO: Put the app_audioData instance pointer in the AUDIO_CODEC_DATA instance on
//       initialization of codecData and let the audio_codec instance change
//       the codec data and state. CAL
//
//******************************************************************************
void Audio_Codec_BufferEventHandler(DRV_CODEC_BUFFER_EVENT event,
    DRV_CODEC_BUFFER_HANDLE handle, uintptr_t context)
{
    switch(event)
    {
        case DRV_CODEC_BUFFER_EVENT_COMPLETE:
        {

            app_audioData.state = APP_AUDIO_STATE_CODEC_ADD_BUFFER; 
            TEST1_Toggle();
            //Signal to APP that Tx is complete. 
            OSAL_SEM_PostISR(&app_audioData.rxTransferDone);
            // OSAL_SEM_PostISR(&app_mlData.processML);
        }        
        break;

        case DRV_CODEC_BUFFER_EVENT_ERROR:
        {
        } 
        break;

        case DRV_CODEC_BUFFER_EVENT_ABORT:
        {
        } 
        break;
    }
}

