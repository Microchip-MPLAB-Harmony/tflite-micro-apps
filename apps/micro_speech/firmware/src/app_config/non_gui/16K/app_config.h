/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_config.h

  Summary:
    This header file provides prototypes and definitions for the application,
    specific to this configuration.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/
#include "osal/osal.h"

#ifndef APP_CONFIG_H
#define APP_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END
                                   
#define INIT_VOLUME_IDX           3
    
#define VOLUME_STEPS              4 

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
typedef struct 
{
    /* Left channel data */
    int32_t leftData;

    /* Right channel data */
    int32_t rightData;

} DRV_I2S_DATA32m;

#define DRV_I2S_DATA DRV_I2S_DATA32m


// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	APP_AUDIO_STATE_INIT=0,
            
    /* TODO: Define states used by the application state machine. */
    APP_AUDIO_STATE_CODEC_OPEN,
    APP_AUDIO_STATE_CODEC_SET_BUFFER_HANDLER,
    APP_AUDIO_STATE_CODEC_ADD_BUFFER,
    APP_AUDIO_STATE_CODEC_WAIT_FOR_BUFFER_COMPLETE,                 
} APP_AUDIO_STATES;      

typedef enum
{
    BUTTON_STATE_IDLE=0,
    BUTTON_STATE_PRESSED,
    BUTTON_STATE_BUTTON0_PRESSED,                   
    BUTTON_STATE_WAIT_FOR_RELEASE    
} BUTTON_STATES;

// *****************************************************************************
// CODEC Data
//
//  Summary:
//    Holds codec data
//
//  Description:
//    This structure holds the codec's data.
//
//  Remarks:
// *****************************************************************************
typedef struct
{
    DRV_HANDLE handle;
    DRV_CODEC_BUFFER_HANDLE writeBufHandle;
    DRV_CODEC_BUFFER_EVENT_HANDLER bufferHandler;
    uintptr_t context;
    uint8_t *txbufferObject;
    uint8_t *rxbufferObject;
    size_t bufferSize;
} AUDIO_CODEC_DATA;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
   /* The application's current state */
    APP_AUDIO_STATES state;
    
    /* handle to opened timer */
    DRV_HANDLE tmrHandle;
    
    uint8_t volume;

    AUDIO_CODEC_DATA codecData;

    uint16_t txBufferIdx, rxBufferIdx;
    
 
    
    uint32_t buttonDelay;
    
    BUTTON_STATES buttonState;
       
    uint8_t volumeIndex;
       
    OSAL_SEM_DECLARE (rxTransferDone);

    int32_t audio_timestamp;

} APP_AUDIO_DATA;



//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* APP_CONFIG_H */
