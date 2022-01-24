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

extern const float INPUT_RANGE = 2.f * 3.14159265359f;

float ml_output[SAMPLES_PER_SIN_CYCLE];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/
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
constexpr int kTensorArenaSize = 10 * 1024;
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
    static tflite::MicroMutableOpResolver<3> micro_op_resolver;  // NOLINT
    micro_op_resolver.AddFullyConnected();
    micro_op_resolver.AddRelu();
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
    
bool tflite_task(void)
{
    // Obtain pointers to the model's input and output tensors.
    TfLiteTensor* input = interpreter->input(0);
    TfLiteTensor* output = interpreter->output(0);

    // We are dividing the whole input range with the number of inference
    // per cycle we want to show to get the unit value. We will then multiply
    // the unit value with the current position of the inference
    float unitValuePerDevision = INPUT_RANGE / static_cast<float>(SAMPLES_PER_SIN_CYCLE);
    
        // Calculate an x value to feed into the model
    for(uint16_t inferenceCount = 0; inferenceCount < SAMPLES_PER_SIN_CYCLE; inferenceCount++)
    {

        float x_val = (float)(inferenceCount) * unitValuePerDevision;

        // Place our calculated x value in the model's input tensor
        input->data.f[0] = x_val;

        // Run inference, and report any error
        TfLiteStatus invoke_status = interpreter->Invoke();

        if (invoke_status != kTfLiteOk) {
            TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x_val: %f\n",static_cast<double>(x_val));
            return false;
        }

        // Read the predicted y value from the model's output tensor
        float y_val = output->data.f[0];

        ml_output[inferenceCount]=y_val;
        
        // handle_output(error_reporter, x_val, y_val);

    }    
    
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
            tflite_task();
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
