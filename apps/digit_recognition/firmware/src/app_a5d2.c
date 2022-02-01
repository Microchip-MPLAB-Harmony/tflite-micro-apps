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
    app_a5d2.c

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

#include "app_a5d2.h"
#include "app_ml.h"
#include "definitions.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_PRINTF(...) //printf(__VA_ARGS__)
static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_A5D2_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_A5D2_DATA app_A5D2Data;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
extern void MGScrn_ClearImage(void);
extern bool imageReady;

static void Timer_Callback ( uintptr_t context)
{  
   MGScrn_ClearImage(); 
}

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
    void APP_A5D2_Initialize ( void )

  Remarks:
    See prototype in app_A5D2.h.
 */

void APP_A5D2_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_A5D2Data.state = APP_A5D2_STATE_INIT;


    APP_ML_Initialize();

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_A5D2_Tasks ( void )

  Remarks:
    See prototype in app_A5D2.h.
 */

void APP_A5D2_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_A5D2Data.state )
    {
        /* Application's initial state. */
        case APP_A5D2_STATE_INIT:
        {
            bool appInitialized = true;
            

            if (appInitialized)
            {
                app_A5D2Data.state = APP_A5D2_STATE_SERVICE_TASKS;
//                GFX_DISP_INTF_PIN_BACKLIGHT_Set();
            }
            break;
        }
        
        case APP_A5D2_STATE_SERVICE_TASKS:
        {            
            if(imageReady==true)
            {   
                timer = SYS_TIME_CallbackRegisterMS(Timer_Callback, 1, 4000, SYS_TIME_SINGLE);            
            }
            
            TEST1_Set();
            APP_ML_Tasks( );
            TEST1_Clear();

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
