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

#include "sine_model.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

// Create an area of memory to use for input, output, and intermediate arrays.
// Minimum arena size, at the time of writing. After allocating tensors
// you can retrieve this value by invoking interpreter.arena_used_bytes().
const int kModelArenaSize = 2468;
// Extra headroom for model + alignment + future interpreter changes.
const int kExtraArenaSize = 560 + 16 + 100;
const int kTensorArenaSize = kModelArenaSize + kExtraArenaSize;
uint8_t tensor_arena[kTensorArenaSize] __ALIGNED(16);
}  // namespace

// This constant represents the range of x values our model was trained on,
// which is from 0 to (2 * Pi). We approximate Pi to avoid requiring
// additional libraries.
extern const float INPUT_RANGE = 2.f * 3.14159265359f;
// NOTE: extern is used because lcd.c also uses this variable.

// This constant determines the number of inferences to perform across the range
// of x values defined above. Since each inference takes time, the higher this
// number, the more time it will take to run through the entire range. The value
// of this constant can be tuned so that one full cycle takes a desired amount
// of time. Since different devices take different amounts of time to perform
// inference, this value should be defined per-device.
// A larger number than the default to make the animation smoother
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
  	error_reporter = &micro_error_reporter;

  	// Map the model into a usable data structure. This doesn't involve any
  	// copying or parsing, it's a very lightweight operation.
    model = tflite::GetModel(sine_model);

  	if(model->version() != TFLITE_SCHEMA_VERSION)
  	{
  		TF_LITE_REPORT_ERROR(error_reporter,
  	                         "Model provided is schema version %d not equal "
  	                         "to supported version %d.",
  	                         model->version(), TFLITE_SCHEMA_VERSION);
  	    return 0;
  	}


    // This pulls in all the operation implementations we need.
    // NOLINTNEXTLINE(runtime-global-variables)
    static tflite::AllOpsResolver resolver;

    // Build an interpreter to run the model with.
    static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
        return 0;
    }

    // Obtain pointers to the model's input and output tensors.
    input = interpreter->input(0);
    output = interpreter->output(0);

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
        TfLiteStatus invoke_status = interpreter->Invoke();
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
//	LCD_Output(x_value, y_value);
}





/*******************************************************************************
 End of File
*/

