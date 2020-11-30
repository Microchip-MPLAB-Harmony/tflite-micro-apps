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


#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/testing/micro_test.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "sample.h"
#include "model.h"



// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int number[10];
int tf_main ( void )
{
    static tflite::MicroErrorReporter micro_error_reporter;
  	tflite::ErrorReporter* error_reporter = &micro_error_reporter;

  	// Load a model from an array of bytes
    const tflite::Model* model = tflite::GetModel(g_model);

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
    static tflite::MicroMutableOpResolver<5> micro_op_resolver;  // NOLINT
    micro_op_resolver.AddConv2D();
    micro_op_resolver.AddFullyConnected();
    micro_op_resolver.AddMaxPool2D();
    micro_op_resolver.AddSoftmax();
    micro_op_resolver.AddReshape();

    // Create an area of memory to use for input, output, and intermediate arrays.
    // Finding the minimum value for your model may require some trial and error.
    const int tensor_arena_size = 20000;
	uint8_t tensor_arena[tensor_arena_size] __ALIGNED(16);
	
    // Build an interpreter to run the model with
    tflite::MicroInterpreter interpreter(model, micro_op_resolver, tensor_arena,
                                       tensor_arena_size, error_reporter);

    // Allocate memory from the tensor_arena for the model's tensors
    interpreter.AllocateTensors();

    // Obtain a pointer to the model's input and output tensor
    TfLiteTensor* input = interpreter.input(0);
    TfLiteTensor* output = interpreter.output(0);
	
    // Provide input image for "7"
    const int8_t* mnist_data = number_7;
    TF_LITE_REPORT_ERROR(error_reporter, "%d", input->bytes);
    for (int i = 0; i < input->bytes; i++) {
        input->data.int8[i] = mnist_data[i];
    }
	
	// Run the model on this input and make sure it succeeds.
    TEST1_Set();
	TfLiteStatus invoke_status = interpreter.Invoke();
    TEST1_Clear();

	if (invoke_status != kTfLiteOk) {
	TF_LITE_REPORT_ERROR(&micro_error_reporter, "Invoke failed\n");
	}
	
    // Make sure that the expected score is higher than the other
    // classes for number[7]
    for (int i = 0; i < 10; i++) {
        number[i]=output->data.int8[i];
    }

    // Provide an input image for "2"
    mnist_data = number_2;
    TF_LITE_REPORT_ERROR(error_reporter, "%d", input->bytes);
    for (int i = 0; i < input->bytes; i++) {
        input->data.int8[i] = mnist_data[i];
    }
	
	// Run the model on this input and make sure it succeeds.
    TEST1_Set();
	invoke_status = interpreter.Invoke();
    TEST1_Clear();

	if (invoke_status != kTfLiteOk) {
	TF_LITE_REPORT_ERROR(&micro_error_reporter, "Invoke failed\n");
	}
	
    // Make sure that the expected score is higher than the other
    // classes for number[7]
    for (int i = 0; i < 10; i++) {
        number[i]=output->data.int8[i];
    }
	TF_LITE_REPORT_ERROR(&micro_error_reporter, "Ran successfully\n");
	
    while(1) {}
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

