/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
int tf_main ( void );

#ifdef __cplusplus
}
#endif


#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "model.h"


extern const float INPUT_RANGE = 2.f * 3.14159265359f;
const uint16_t INFERENCE_PER_CYCLE = 70;

void handle_output(tflite::ErrorReporter* error_reporter, float x_value, float y_value);

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

volatile int counter = 0;

int tf_main ( void )
{
    static tflite::MicroErrorReporter micro_error_reporter;
    tflite::ErrorReporter* error_reporter = &micro_error_reporter;

    // Load a model from an array of bytes
    const tflite::Model* model = tflite::GetModel(sine_model);

    if(model->version() != TFLITE_SCHEMA_VERSION)
    {
        TF_LITE_REPORT_ERROR(error_reporter, "Model provided is schema version %d not equal to supported version %d.",
                             model->version(), TFLITE_SCHEMA_VERSION);
        return 0;
    }


    // Pull in only the operation implementations we need.
    // This relies on a complete list of all the ops needed by this graph.
    // An easier approach is to just use the AllOpsResolver, but this will
    // incur some penalty in code space for op implementations that are not
    // needed by this graph.
    //
    // tflite::AllOpsResolver resolver;
    tflite::MicroMutableOpResolver<3> micro_op_resolver;
    micro_op_resolver.AddFullyConnected();
    micro_op_resolver.AddRelu();
    micro_op_resolver.AddReshape();

    // Create an area of memory to use for input, output, and intermediate arrays.
    const int tensor_arena_size = 10000;
    uint8_t tensor_arena[tensor_arena_size] __ALIGNED(16);

    // Build an interpreter to run the model with.
    tflite::MicroInterpreter interpreter(model, micro_op_resolver, tensor_arena,
                                        tensor_arena_size,
                                        &micro_error_reporter);
    interpreter.AllocateTensors();

    // Obtain pointers to the model's input and output tensors.
    TfLiteTensor* input = interpreter.input(0);
    TfLiteTensor* output = interpreter.output(0);

    // We are dividing the whole input range with the number of inference
    // per cycle we want to show to get the unit value. We will then multiply
    // the unit value with the current position of the inference
    float unitValuePerDevision = INPUT_RANGE / static_cast<float>(INFERENCE_PER_CYCLE);



        // Calculate an x value to feed into the model
    for(uint16_t inferenceCount = 0; inferenceCount <= INFERENCE_PER_CYCLE; inferenceCount++)
    {

        float x_val = static_cast<float>(inferenceCount) * unitValuePerDevision;

        // Place our calculated x value in the model's input tensor
        input->data.f[0] = x_val;

        // Run inference, and report any error
        TEST1_Set();
        TfLiteStatus invoke_status = interpreter.Invoke();
        TEST1_Clear();

        if (invoke_status != kTfLiteOk) {
            TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x_val: %f\n",static_cast<double>(x_val));
            return 0;
        }

        // Read the predicted y value from the model's output tensor
        float y_val = output->data.f[0];

        // Do something with the results
        handle_output(error_reporter, x_val, y_val);

    }

    while ( true )
    {
        counter++;
    }

    return ( EXIT_FAILURE );
}

void handle_output(tflite::ErrorReporter* error_reporter, float x_value, float y_value)
{
    // Log the current X and Y values
    TF_LITE_REPORT_ERROR(error_reporter, "x_value: %f, y_value: %f\n", x_value, y_value);

    // A custom function can be implemented and used here to do something with the x and y values.
    // In my case I will be plotting sine wave on an LCD.
//  LCD_Output(x_value, y_value);
}





/*******************************************************************************
 End of File
*/

