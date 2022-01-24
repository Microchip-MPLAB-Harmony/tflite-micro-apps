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
#define AUDIO_DATA_WIDTH            16
#define AUDIO_DATA_TYPE             int16_t
#define AUDIO_BUFFER_SIZE           480   // 30 ms of audio at 160,000 samples/second    
#define AUDIO_NUM_OF_BUFFERS        2     // Two buffers used for ping-pong

    

#define LED_YES_On                LED2_On
#define LED_YES_Off               LED2_Off
#define LED_YES_Toggle            LED2_Toggle

#define LED_NO_On                 LED1_On
#define LED_NO_Off                LED1_Off
#define LED_NO_Toggle             LED1_Toggle

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // USER_H
/*******************************************************************************
 End of File
*/
