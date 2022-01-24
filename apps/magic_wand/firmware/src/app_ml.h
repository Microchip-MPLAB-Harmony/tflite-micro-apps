/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ml.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_ML_Initialize" and "APP_ML_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_ML_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_ML_H
#define _APP_ML_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

extern bool tflite_runInference(void);
extern void tflite_setup(void);


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_ML_H */

/*******************************************************************************
 End of File
 */

