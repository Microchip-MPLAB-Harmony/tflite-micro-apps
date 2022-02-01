/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    non_gui.c

  Summary:
    This file contains the source code for the non-GUI versions of the application.

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

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

uint16_t volumeLevels[VOLUME_STEPS] =
{
#ifdef DRV_AK4954_VOLUME
    0 /* off */, 192, 208, 224          // if using AK4954, use narrower range  
#else            
    0 /* off */, 128, 192, 255
#endif  
};

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

// called every millisecond from App_TimerCallback
void KeyRepeatTask()
{
    if (app_audioData.buttonDelay)
    {      
        app_audioData.buttonDelay--;
    }    
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

void APP_AUDIO_Initialize_sub ( void )
{
    uint16_t i,j;

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */   
    app_audioData.state = APP_AUDIO_STATE_INIT;
    
    app_audioData.buttonDelay = 0;
    
    app_audioData.volumeIndex = INIT_VOLUME_IDX;
    app_audioData.volume = volumeLevels[app_audioData.volumeIndex];         
  
    for (i=0; i < AUDIO_NUM_OF_BUFFERS; i++)
    {
        for (j=0; j < AUDIO_BUFFER_SIZE; j++)
        {
            micBuffer[i][j].leftData = 0;
            micBuffer[i][j].rightData = 0;
        }
    }
    
    
    app_audioData.txBufferIdx = 0;
    app_audioData.rxBufferIdx = 1;          

    app_audioData.codecData.txbufferObject = (uint8_t *) micBuffer[app_audioData.txBufferIdx];
    app_audioData.codecData.rxbufferObject = (uint8_t *) micBuffer[app_audioData.rxBufferIdx];     
}

/******************************************************************************
  Function:
    void APP_Tasks_sub ( void )

  Remarks:
    called from APP_Tasks
 */

#define BUTTON_DEBOUNCE 50

void APP_AUDIO_Tasks_sub()
{
   //BUTTON PROCESSING
    /* Check the buttons' current state. */      
    switch ( app_audioData.buttonState )
    {
        case BUTTON_STATE_IDLE:
        {
            if ( (app_audioData.buttonDelay==0)&&
                 (SWITCH_Get()==SWITCH_STATE_PRESSED))                
            {
                app_audioData.buttonDelay=BUTTON_DEBOUNCE;       
                app_audioData.buttonState=BUTTON_STATE_PRESSED;               
            }
        }
        break;
        
        case BUTTON_STATE_PRESSED:
        { 
            if (app_audioData.buttonDelay>0)
            {
                break;      // still debouncing
            }
            app_audioData.buttonState=BUTTON_STATE_BUTTON0_PRESSED;                  
        }
        break;
          
        case BUTTON_STATE_BUTTON0_PRESSED:
        {
            if ((SWITCH_Get()!=SWITCH_STATE_PRESSED))     // SW01 pressed and released
            {
                uint8_t oldVolumeIndex;
                    
                oldVolumeIndex = app_audioData.volumeIndex;
                app_audioData.volumeIndex++;
                if (app_audioData.volumeIndex >= VOLUME_STEPS)
                {
                    app_audioData.volumeIndex = 0;    
                }
                    
                app_audioData.volume = volumeLevels[app_audioData.volumeIndex];
                    
                if (0==app_audioData.volume)
                {
                    DRV_CODEC_MuteOn(app_audioData.codecData.handle);                       
                }
                else
                {
                    DRV_CODEC_VolumeSet(app_audioData.codecData.handle,
                      DRV_CODEC_CHANNEL_LEFT_RIGHT, app_audioData.volume);                                      
                    if (0==volumeLevels[oldVolumeIndex])
                    {
                        // if volume was 0, unmute codec
                        DRV_CODEC_MuteOff(app_audioData.codecData.handle);                     
                    }
                }                             

                app_audioData.buttonDelay=BUTTON_DEBOUNCE;                
                app_audioData.buttonState=BUTTON_STATE_IDLE;              
            }             
        } 
        break;
        
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
