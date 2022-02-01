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
#include "app_e70.h"
#include "app_ml.h"
#include <stdio.h>
#include <string.h>

#define APP_MGSCRN_PRINTF(...) printf(__VA_ARGS__)

#define GEST_IMG_SHOW_POS_X 200
#define GEST_IMG_HIDE_POS_X 480

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

typedef enum
{
    MG_SCRN_DRAW_NONE,
    MG_SCRN_DRAW_CLEAR,
    MG_SCRN_DRAW_POINT,
} MG_SCRN_DRAW_CMD;

static MG_SCRN_STATE mgState = MG_SCRN_STATE_INIT;
static MG_SCRN_TOUCH_CMD touchCmd = MG_SCRN_TOUCH_NONE;
static MG_SCRN_DRAW_CMD drawCmd = MG_SCRN_DRAW_NONE;


static bool touchActive[2];
static int32_t totalTouchPoints=0;
static int32_t prevX[2], prevY[2];
static int32_t lastX[2], lastY[2];
static int inputIdx = -1;

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
                x=(lastX[touchID]-200)>>3;
                y=(lastY[touchID]-30)>>3;
                
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
        drawCmd = MG_SCRN_DRAW_CLEAR;

        APP_ML_ClearRecognisedDigit();     
    } else
    {
        APP_MGSCRN_PRINTF("Failed to recognize the digit \n\r");

        MGScrn_GestureImageWidget->fn->setImage
                                (MGScrn_GestureImageWidget, &failed);
        MGScrn_GestureImageWidget->fn->setX
                                (MGScrn_GestureImageWidget, GEST_IMG_SHOW_POS_X);     
        drawCmd = MG_SCRN_DRAW_CLEAR;
    }
}


leBool event_MGScrn_DrawSurfaceWidget0_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    leBool retval = LE_TRUE;
    
    switch(drawCmd)
    {
        case MG_SCRN_DRAW_CLEAR:
        {
            APP_MGSCRN_PRINTF("++++ clear %d \n\r", touchCmd);
            leRenderer_FillArea(sfc->widget.rect.x,
                                    sfc->widget.rect.y,
                                    sfc->widget.rect.width,
                                    sfc->widget.rect.height,
                                    leScheme_GetRenderColor(sfc->widget.scheme, LE_SCHM_BASE),
                                    255);
            
            break;
        }
        case MG_SCRN_DRAW_POINT:
        {
            APP_MGSCRN_PRINTF("++++ drawPoint \n\r");
            if (touchActive[0] == true)
            {
                leRenderer_FillArea(lastX[0] - TOUCH_POINT_SIZE,
                                    lastY[0] - TOUCH_POINT_SIZE,
                                    TOUCH_POINT_SIZE * 2,
                                    TOUCH_POINT_SIZE * 2,
                                    leScheme_GetRenderColor(sfc->widget.scheme, LE_SCHM_FOREGROUND),
                                    255);
                
                leRenderer_DrawLine(lastX[0],
                                    lastY[0],
                                    prevX[0],
                                    prevY[0],
                                    leScheme_GetRenderColor(sfc->widget.scheme, LE_SCHM_FOREGROUND),
                                    255);
            }
    

            break;
        }
        default:
        {
            break;
        }
    }
    
    return retval;
}




void MGScrn_OnShow(void)
{
    MGScrn_DrawSurfaceWidget0->fn->installEventFilter(MGScrn_DrawSurfaceWidget0, DrawSurface_eventFilter);    
    
    MGScrn_GestureImageWidget->fn->setX(MGScrn_GestureImageWidget, GEST_IMG_SHOW_POS_X);
    
    
    GFX_DISP_INTF_PIN_BACKLIGHT_Clear();

    mgState = MG_SCRN_STATE_INIT;
    
    legato_showScreen(screenID_MGScrn);
    
}

void MGScrn_OnHide(void)
{
    MGScrn_DrawSurfaceWidget0->fn->removeEventFilter(MGScrn_DrawSurfaceWidget0, DrawSurface_eventFilter); 
    
    SYS_INP_RemoveListener(inputIdx);
       
}

void MGScrn_OnUpdate(void)
{
    switch (mgState)
    {
        case MG_SCRN_STATE_INIT:
        {
            
            if(leGetRenderState()->frameState != LE_FRAME_READY || 
               leEvent_GetCount() != 0 ||
               isDisplayReady() != true)
                break;
            
            leRenderer_FillArea(MGScrn_DrawSurfaceWidget0->widget.rect.x,
                                    MGScrn_DrawSurfaceWidget0->widget.rect.y,
                                    MGScrn_DrawSurfaceWidget0->widget.rect.width,
                                    MGScrn_DrawSurfaceWidget0->widget.rect.height,
                                    leScheme_GetRenderColor(MGScrn_DrawSurfaceWidget0->widget.scheme, LE_SCHM_BASE),
                                    255);
            
            touchCmd = MG_SCRN_TOUCH_NONE;            
            
            mgState = MG_SCRN_STATE_WAIT_FOR_READY;
            break;
        }
        case MG_SCRN_STATE_WAIT_FOR_READY:
        {
            if(leGetRenderState()->frameState != LE_FRAME_READY || 
               leEvent_GetCount() != 0 ||
               isDisplayReady() != true)
                break;
                  

            GFX_DISP_INTF_PIN_BACKLIGHT_Set();            
            mgState = MG_SCRN_STATE_READY;
            
            break;
        }
        case MG_SCRN_STATE_READY:
        {
            if (touchCmd == MG_SCRN_TOUCH_DOWN)
                mgState = MG_SCRN_STATE_IDLE;
                       
            break;
        }
        case MG_SCRN_STATE_IDLE:
        {
            switch(touchCmd)
            {
                case MG_SCRN_TOUCH_DOWN:
                {
                    APP_MGSCRN_PRINTF("**** idle -> down -> start \n\r");
                    MGScrn_DrawInstructionLabel->fn->setX(MGScrn_DrawInstructionLabel,GEST_IMG_HIDE_POS_X);
                    MGScrn_GestureImageWidget->fn->setX(MGScrn_GestureImageWidget,GEST_IMG_HIDE_POS_X);
                    MGScrn_DrawSurfaceWidget0->fn->invalidate(MGScrn_DrawSurfaceWidget0);
                    
                    drawCmd = MG_SCRN_DRAW_CLEAR;
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
                    //APP_MGSCRN_PRINTF("===== active -> move \n\r");
                    MGScrn_DrawSurfaceWidget0->fn->invalidate(MGScrn_DrawSurfaceWidget0);
                    drawCmd = MG_SCRN_DRAW_POINT;
                    
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