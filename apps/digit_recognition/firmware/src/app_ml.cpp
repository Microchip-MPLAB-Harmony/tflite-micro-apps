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
    app_ml.c

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

#include "app_ml.h"
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "model.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_ML_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_ML_DATA app_mlData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/
int8_t recognisedDigit=-1;
int8_t recognitionThreshold=20;

void handle_output(tflite::ErrorReporter* error_reporter, float x_value, float y_value)
{
    // Log the current X and Y values
    TF_LITE_REPORT_ERROR(error_reporter, "x_value: %f, y_value: %f\n", x_value, y_value);

    // A custom function can be implemented and used here to do something with the x and y values.
    // In my case I will be plotting sine wave on an LCD.
//  LCD_Output(x_value, y_value);
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

const tflite::Model* model = nullptr;
tflite::ErrorReporter* error_reporter = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;


// Create an area of memory to use for input, output, and intermediate arrays.
// The size of this will depend on the model you're using, and may need to be
// determined by experimentation.
constexpr int kTensorArenaSize = 25000;
uint8_t tensor_arena[kTensorArenaSize] __ALIGNED(16);;

void tflite_setup(void)
{

    static tflite::MicroErrorReporter micro_error_reporter;  
    error_reporter = &micro_error_reporter;

    // Load a model from an array of bytes
    model = tflite::GetModel(g_model);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
      TF_LITE_REPORT_ERROR(error_reporter,
                           "Model provided is schema version %d not equal "
                           "to supported version %d.",
                           model->version(), TFLITE_SCHEMA_VERSION);
      return;
    }

    // Pull in only the operation implementations we need.
    // This relies on a complete list of all the ops needed by this graph.
    // An easier approach is to just use the AllOpsResolver, but this will
    // incur some penalty in code space for op implementations that are not
    // needed by this graph.
    static tflite::MicroMutableOpResolver<5> micro_op_resolver;  // NOLINT
    micro_op_resolver.AddConv2D();
    micro_op_resolver.AddFullyConnected();
    micro_op_resolver.AddMaxPool2D();
    micro_op_resolver.AddSoftmax();
    micro_op_resolver.AddReshape();

    // Build an interpreter to run the model with.
    static tflite::MicroInterpreter static_interpreter(
        model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
      TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
      return;
    }
}
extern int8_t imageData[];
extern bool imageReady;
int number[10];

bool tflite_runInference(void)
{
    int8_t maxValue=-128;
    int8_t numberValue=-1;
    
    // Obtain pointers to the model's input and output tensors.
    TfLiteTensor* input = interpreter->input(0);
    TfLiteTensor* output = interpreter->output(0);

    TF_LITE_REPORT_ERROR(error_reporter, "%d", input->bytes);
    for (int i = 0; i < input->bytes; i++) {
        input->data.int8[i] = imageData[i];
    }
    
    // Run inference, and report any error
    TfLiteStatus invoke_status = interpreter->Invoke();    
    
    if (invoke_status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed ");
        return false;
    }

    // Print the score in terminal and find the maximum score
    for (int i = 0; i < 10; i++) {
        number[i]=output->data.int8[i];
        printf("Score for Index %d is %d\n\r",i,number[i]);
        
        if(number[i]>recognitionThreshold)
        {
            if (number[i]>maxValue)
            {
                numberValue=i;
                maxValue=number[i];
            }
        }
    }
    recognisedDigit=numberValue;
    printf("Recognised Digit is %d \n\r",recognisedDigit);

    return true;
}




// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_ML_Initialize ( void )

  Remarks:
    See prototype in app_ml.h.
 */

void APP_ML_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_mlData.state = APP_ML_STATE_INIT;

    tflite_setup();

}


/******************************************************************************
  Function:
    void APP_ML_Tasks ( void )

  Remarks:
    See prototype in app_ml.h.
 */

void APP_ML_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_mlData.state )
    {
        /* Application's initial state. */
        case APP_ML_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                app_mlData.state = APP_ML_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_ML_STATE_SERVICE_TASKS:
        {
            if(imageReady==true)
            {            
                tflite_runInference();
                imageReady=false;
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

int8_t APP_ML_GetRecognisedDigit(void)
{
    return recognisedDigit;
}

void APP_ML_ClearRecognisedDigit(void)
{
    recognisedDigit = -1;
}
/*******************************************************************************
 End of File
 */
