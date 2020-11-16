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
#include "tensorflow/lite/micro/testing/micro_test.h"
#include "sample.h"
#include "model.h"



// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
// Make sure that the expected "Yes" score is higher than the other classes.
uint8_t silence_score = 0;
uint8_t unknown_score = 0;
uint8_t yes_score = 0;
uint8_t no_score = 0;

// There are four possible classes in the output, each with a score.
const int kSilenceIndex = 0;
const int kUnknownIndex = 1;
const int kYesIndex = 2;
const int kNoIndex = 3;    

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
	//
	// tflite::AllOpsResolver resolver;
	tflite::MicroMutableOpResolver<4> micro_op_resolver;
	micro_op_resolver.AddDepthwiseConv2D();
	micro_op_resolver.AddFullyConnected();
	micro_op_resolver.AddReshape();
	micro_op_resolver.AddSoftmax();
	
	// Create an area of memory to use for input, output, and intermediate arrays.
	const int tensor_arena_size = 10 * 1024;
	uint8_t tensor_arena[tensor_arena_size] __ALIGNED(16);
	
	// Build an interpreter to run the model with.
	tflite::MicroInterpreter interpreter(model, micro_op_resolver, tensor_arena,
										tensor_arena_size,
										&micro_error_reporter);
	interpreter.AllocateTensors();
	
	// Get information about the memory area to use for the model's input.
	TfLiteTensor* input = interpreter.input(0);
	
	
	// Copy a spectrogram created from a .wav audio file of someone saying "Yes",
	// into the memory area used for the input.
	const int8_t* yes_features_data = g_yes_data;
	for (size_t i = 0; i < input->bytes; ++i) {
	input->data.int8[i] = yes_features_data[i];
	}
	
	// Run the model on this input and make sure it succeeds.
    TEST1_Set();
	TfLiteStatus invoke_status = interpreter.Invoke();
    TEST1_Clear();

	if (invoke_status != kTfLiteOk) {
	TF_LITE_REPORT_ERROR(&micro_error_reporter, "Invoke failed\n");
	}
	
	// Get the output from the model, and make sure it's the expected size and
	// type.
	TfLiteTensor* output = interpreter.output(0);


	
	// Make sure that the expected "Yes" score is higher than the other classes.
	yes_score = output->data.int8[kYesIndex] + 128;
	no_score = output->data.int8[kNoIndex] + 128;
	silence_score = output->data.uint8[kSilenceIndex] + 128;
	unknown_score = output->data.uint8[kUnknownIndex] + 128;
	
	// Now test with a different input, from a recording of "No".
	const int8_t* no_features_data = g_no_data;
	for (size_t i = 0; i < input->bytes; ++i) {
	input->data.int8[i] = no_features_data[i];
	}
	TEST1_Set();
	// Run the model on this "No" input.
	invoke_status = interpreter.Invoke();
    TEST1_Clear();
    
	if (invoke_status != kTfLiteOk) {
	TF_LITE_REPORT_ERROR(&micro_error_reporter, "Invoke failed\n");
	}
	
	// Get the output from the model, and make sure it's the expected size and
	// type.
	output = interpreter.output(0);

	
	// Make sure that the expected "No" score is higher than the other classes.
	yes_score = output->data.int8[kYesIndex] + 128;
	no_score = output->data.int8[kNoIndex] + 128;	
    silence_score = output->data.int8[kSilenceIndex] + 128;
	unknown_score = output->data.int8[kUnknownIndex] + 128;


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

