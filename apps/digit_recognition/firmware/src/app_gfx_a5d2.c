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

#include "definitions.h"
#include "app_a5d2.h"
#include "app_ml.h"
#include <stdio.h>
#include <string.h>

#define APP_MGSCRN_PRINTF(...) printf(__VA_ARGS__)

#define GEST_IMG_SHOW_POS_X 300
#define GEST_IMG_HIDE_POS_X 800

#define TOUCH_POINT_SIZE 2
#define IMAGE_SIZE  784
uint8_t imageData[IMAGE_SIZE];
bool imageReady=false;

typedef enum
{
    MG_SCRN_STATE_INIT,
    MG_SCRN_STATE_WAIT_FOR_READY,
    MG_SCRN_STATE_READY,
    MG_SCRN_STATE_IDLE,
    MG_SCRN_STATE_ACTIVE,
    MG_SCRN_STATE_DONE,
    MG_SCRN_STATE_EXIT,
} MG_SCRN_STATE;

typedef enum
{
    MG_SCRN_TOUCH_NONE,
    MG_SCRN_TOUCH_DOWN,
    MG_SCRN_TOUCH_MOVE,
    MG_SCRN_TOUCH_UP,
} MG_SCRN_TOUCH_CMD;

static MG_SCRN_STATE mgState = MG_SCRN_STATE_INIT;
static MG_SCRN_TOUCH_CMD touchCmd = MG_SCRN_TOUCH_NONE;


static bool clearImage=false;
static bool touchActive[2];
static int32_t totalTouchPoints=0;
static int32_t prevX[2], prevY[2];
static int32_t lastX[2], lastY[2];

static leBool DrawSurface_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);

static leWidgetEventFilter DrawSurface_eventFilter =
{
    DrawSurface_filterEvent,
    NULL
};

//The images in the array should match the enum APP_GESTURE_CMD
static leImage * digitImages[10] = 
{
    &zero,
    &one,
    &two,            
    &three,
    &four, 
    &five,
    &six,
    &seven,            
    &eight,
    &nine,
};

static leBool DrawSurface_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{    
    leBool retval = LE_FALSE;
    int32_t touchID;
    int8_t x,y;
        
    TEST2_Set();

    switch(evt->id)
    {
        case LE_EVENT_TOUCH_DOWN:
        {
            //Clear the widget
            touchID = ((leWidgetEvent_TouchDown *) evt)->touchID;
            if (touchID < 2)
            {
                lastX[touchID] = ((leWidgetEvent_TouchDown *) evt)->x;
                lastY[touchID] = ((leWidgetEvent_TouchDown *) evt)->y;
                prevX[touchID] = lastX[touchID];
                prevY[touchID] = lastY[touchID];
                touchActive[touchID] = true;
            
                if (touchID == 0)
                {
                    touchCmd = MG_SCRN_TOUCH_DOWN;
                }
            
                // Clear image buffer
                for(int i=0; i<IMAGE_SIZE; i++)
                    imageData[i]=-128;   
   
                totalTouchPoints=0;  
            }
            
            evt->accepted = LE_TRUE;
            evt->owner = target;
            
            retval = LE_TRUE;
            

            
            break;
        }   
        case LE_EVENT_TOUCH_MOVE:            
        {
            touchID = ((leWidgetEvent_TouchMove *) evt)->touchID;
            if (touchID < 2)
            {            
                prevX[touchID] = lastX[touchID];
                prevY[touchID] = lastY[touchID];

                lastX[touchID] = ((leWidgetEvent_TouchMove *) evt)->x;
                lastY[touchID] = ((leWidgetEvent_TouchMove *) evt)->y;

                touchCmd = MG_SCRN_TOUCH_MOVE;

                // Fill the image buffer (28 x 28) for digit recognition
                x=(lastX[touchID]-300)>>4;
                y=(lastY[touchID]-16)>>4;
                
                if(x<0)
                    x=0;
                else if (x >= 28)
                    x=27;
                
                if(y<0)
                    y=0;
                else if (y >= 28)
                    y=27;
                                
                totalTouchPoints++;   
                imageData[y*28+x]=100;
                printf("(x,y): %d, %d \n\r",x,y);
                
            }
            
            evt->accepted = LE_TRUE;
                    
            retval = LE_TRUE;
            
           
            break;
        }
        case LE_EVENT_TOUCH_UP:
        {
            touchID = ((leWidgetEvent_TouchUp *) evt)->touchID;
            touchActive[touchID] = false;
            
            touchCmd = MG_SCRN_TOUCH_UP;
            evt->accepted = LE_TRUE;                  
            retval = LE_TRUE;
            
            /* Perform inference only if we have minimum num of touch points */
            if(totalTouchPoints>5)
                imageReady = true;  
            
            break;
        }
        default:
            break;
    }
    TEST2_Clear();

   return retval;
}


static void DisplayDigit(void)
{
    int8_t digit = APP_ML_GetRecognisedDigit();

    if(digit>=0)
    {
        APP_MGSCRN_PRINTF("xxxxx Done -> show digit %d \n\r", digit);
        MGScrn_GestureImageWidget->fn->setImage
                                (MGScrn_GestureImageWidget, digitImages[digit]);
        MGScrn_GestureImageWidget->fn->setX
                                (MGScrn_GestureImageWidget, GEST_IMG_SHOW_POS_X);

        APP_ML_ClearRecognisedDigit();     
    } else
    {
        APP_MGSCRN_PRINTF("Failed to recognize the digit \n\r");

        MGScrn_GestureImageWidget->fn->setImage
                                (MGScrn_GestureImageWidget, &failed);
        MGScrn_GestureImageWidget->fn->setX
                                (MGScrn_GestureImageWidget, GEST_IMG_SHOW_POS_X);     
    }
}

void MGScrn_ClearImage(void)
{
    clearImage = true;                  
}

leBool event_MGScrn_DrawSurfaceWidget0_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    leBool retval = LE_TRUE;
    return retval;
}

void MGScrn_OnShow(void)
{
    MGScrn_DrawSurfaceWidget0->fn->installEventFilter(MGScrn_DrawSurfaceWidget0, DrawSurface_eventFilter);    
    mgState = MG_SCRN_STATE_INIT;
}

void MGScrn_OnUpdate(void)
{
    switch (mgState)
    {
        case MG_SCRN_STATE_INIT:
        {
                mgState = MG_SCRN_STATE_IDLE;
                break;
        }
        

        case MG_SCRN_STATE_IDLE:
        {
            if(clearImage==true)
            {           
                MGScrn_GestureImageWidget->fn->setImage(MGScrn_GestureImageWidget, &clear);
                MGScrn_GestureImageWidget->fn->setX(MGScrn_GestureImageWidget, GEST_IMG_SHOW_POS_X);  
                clearImage=false;
            }

            switch(touchCmd)
            {
                case MG_SCRN_TOUCH_DOWN:
                {
                    APP_MGSCRN_PRINTF("**** idle -> down -> start \n\r");
                    mgState = MG_SCRN_STATE_ACTIVE;                    
                    break;
                }
                default:
                {
                    break;
                }
            }
            
            touchCmd = MG_SCRN_TOUCH_NONE;

            break;
        }
        case MG_SCRN_STATE_ACTIVE:
        {
            switch(touchCmd)
            {
                case MG_SCRN_TOUCH_MOVE:
                {
                    APP_MGSCRN_PRINTF("===== active -> move \n\r");
                    
                    break;
                }
                case MG_SCRN_TOUCH_UP:
                {
                    APP_MGSCRN_PRINTF("===== active -> up -> Done \n\r");
                    mgState = MG_SCRN_STATE_DONE;
                    break;
                }
                default:
                {
                    break;
                }
            }
                      
            touchCmd = MG_SCRN_TOUCH_NONE;

            break;
        }
        case MG_SCRN_STATE_DONE:
        {
            if(totalTouchPoints>5)
                DisplayDigit();
            
            mgState = MG_SCRN_STATE_IDLE;
            break;
        }
        default:
            break;
    }   
}