/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_e70.c

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

#include "app_e70.h"
#include "definitions.h"
#include "app_ml.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_PRINTF(...) //printf(__VA_ARGS__)

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_E70_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_E70_DATA app_e70Data;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

bool isDisplayReady(void)
{
    gfxIOCTLArg_Value val;
    
    gfxDriverInterface.ioctl(GFX_IOCTL_GET_STATUS, &val);
    
    return  (val.value.v_uint == 0);
}
/*******************************************************************************
  Function:
    void APP_E70_Initialize ( void )

  Remarks:
    See prototype in app_e70.h.
 */

void APP_E70_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_e70Data.state = APP_E70_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
	 
    APP_ML_Initialize();	 
}


/******************************************************************************
  Function:
    void APP_E70_Tasks ( void )

  Remarks:
    See prototype in app_e70.h.
 */

void APP_E70_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_e70Data.state )
    {
        /* Application's initial state. */
        case APP_E70_STATE_INIT:
        {
            bool appInitialized = true;
            
            if (appInitialized)
            {
                app_e70Data.state = APP_E70_STATE_SERVICE_TASKS;
                GFX_DISP_INTF_PIN_BACKLIGHT_Set();
            }
            break;
        }
        
        case APP_E70_STATE_SERVICE_TASKS:
        {
            APP_ML_Tasks( );

            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
