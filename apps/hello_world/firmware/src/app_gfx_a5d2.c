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
    app_gfx_a5d2.c

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

#include "app_gfx_a5d2.h"
#include "user.h"
#include "definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define X_AXIS_ORIGIN   100
#define Y_AXIS_ORIGIN   80
#define Y_HIGHT         380
#define X_WIDTH         600
#define Y_MAX           (Y_AXIS_ORIGIN+Y_HIGHT)
#define WAVE_PIXEL_SIZE 1

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_GFX_A5D2_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_GFX_A5D2_DATA app_gfxData;
SYS_TIME_HANDLE graph_custom_sys_time_handle;

extern float ml_output[];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void Graph_Custom_Draw_Rectangle(int16_t x, int16_t y,int16_t size, leColor color)
{
    leRect rec;
    
    rec.height = size;
    rec.width = size;
    rec.x = x;
    rec.y = y;
    
  leRenderer_RectFill(&rec,color,0xff);  
}

leBool event_Screen0_DrawSurfaceWidget0_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    
    int i;
    static bool first_call = 1;
    static int offset = 0;
    int index;
    TEST2_Set();
    if(first_call == 1)
    {
        first_call = 0;
        app_gfxData.size_to_send = X_WIDTH;
        return LE_TRUE;
    }
    
    for(i = 0; i < app_gfxData.size_to_send; i++)
    {
        index = (offset + i)%(app_gfxData.size_to_send);
        app_gfxData.x_coord = (X_AXIS_ORIGIN + i);
        app_gfxData.y_coord = (int32_t)(Y_MAX-(ml_output[index]*0.9*(Y_HIGHT/2) + (Y_HIGHT/2)));
        Graph_Custom_Draw_Rectangle(app_gfxData.x_coord,app_gfxData.y_coord, WAVE_PIXEL_SIZE,RGBA_8888_GREEN_MASK);    
    }
       
    offset=offset+10;
    
    if(offset >= (app_gfxData.size_to_send - 1))
    {
       
       offset = offset %10;
    }

    TEST2_Clear();
    return LE_TRUE;
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

void Graph_Custom_Timer_Callback ( uintptr_t context)
{
  app_gfxData.graph_custom_update_flag = 1;
  TEST1_Toggle();
}

/*******************************************************************************
  Function:
    void APP_GFX_Initialize ( void )

  Remarks:
    See prototype in app_gfx.h.
 */

void APP_GFX_A5D2_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_gfxData.state = APP_GFX_A5D2_STATE_INIT;


  app_gfxData.graph_custom_update_flag = 0;
  
  graph_custom_sys_time_handle = SYS_TIME_TimerCreate(0, SYS_TIME_MSToCount(50), &Graph_Custom_Timer_Callback, (uintptr_t)NULL, SYS_TIME_PERIODIC);
  
    if (graph_custom_sys_time_handle != SYS_TIME_HANDLE_INVALID)
    {
        //timer is created successfully.
    }
    
    SYS_TIME_TimerStart(graph_custom_sys_time_handle);
    
}


/******************************************************************************
  Function:
    void APP_GFX_A5D2_Tasks ( void )

  Remarks:
    See prototype in app_gfx_a5d2.h.
 */

void APP_GFX_A5D2_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_gfxData.state )
    {
        /* Application's initial state. */
        case APP_GFX_A5D2_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                app_gfxData.state = APP_GFX_A5D2_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_GFX_A5D2_STATE_SERVICE_TASKS:
        {
            if(app_gfxData.graph_custom_update_flag == 1)
            {
                app_gfxData.graph_custom_update_flag = 0;
                GRAPH_CUSTOM->fn->invalidate(GRAPH_CUSTOM);
            }
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
