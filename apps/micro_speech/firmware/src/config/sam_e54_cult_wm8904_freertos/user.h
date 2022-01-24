/*******************************************************************************
  User Configuration Header

  File Name:
    user.h

  Summary:
    Build-time configuration header for the user defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    It only provides macro definitions for build-time configuration options

*******************************************************************************/

#ifndef USER_H
#define USER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: User Configuration macros
// *****************************************************************************
// *****************************************************************************

#define AUDIO_SAMPLING_FREQUENCY    16000
#define AUDIO_DATA_WIDTH            32
#define AUDIO_DATA_TYPE             int32_t
#define AUDIO_BUFFER_SIZE           480   // 30 ms of audio at 16,000 samples/second    
#define AUDIO_NUM_OF_BUFFERS        2     // Two buffers used for ping-pong


#define SWITCH_STATE_PRESSED      0
#define SWITCH_Get                SWITCH1_Get
    
#define LED_YES_On                LED1_Clear
#define LED_YES_Off               LED1_Set
#define LED_YES_Toggle            LED1_Toggle

#define LED_NO_On                 LED2_Clear
#define LED_NO_Off                LED2_Set
#define LED_NO_Toggle             LED2_Toggle    
 
    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // USER_H
/*******************************************************************************
 End of File
*/
