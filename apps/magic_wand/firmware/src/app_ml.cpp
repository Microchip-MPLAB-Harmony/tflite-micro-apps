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
#include "gesture_predictor.h"
#include "constants.h"
#include "sample.h"


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

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

void handle_output(tflite::ErrorReporter* error_reporter, int index)
{
    // Log the current X and Y values
    TF_LITE_REPORT_ERROR(error_reporter, "gesture index: %d\n", index);

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
__attribute__((__aligned__(16))) uint8_t tensor_arena[kTensorArenaSize];

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
    static tflite::MicroMutableOpResolver<6> micro_op_resolver;  // NOLINT
    micro_op_resolver.AddConv2D();
    micro_op_resolver.AddFullyConnected();
    micro_op_resolver.AddMaxPool2D();
    micro_op_resolver.AddSoftmax();
    micro_op_resolver.AddReshape();
    micro_op_resolver.AddDepthwiseConv2D();

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
extern float accData[];
int inferenceCount=0;

bool tflite_runInference(void)
{

    // Obtain pointers to the model's input and output tensors.
    TfLiteTensor* input = interpreter->input(0);
    TfLiteTensor* output = interpreter->output(0);

    for (int i = 0; i < 384; i++) {
        input->data.f[i] = accData[i];
    }
    
    // Run inference, and report any error
    TfLiteStatus invoke_status = interpreter->Invoke();    


    // printf("Score: %f, %f, %f, %f, %d\r",interpreter->output(0)->data.f[0],interpreter->output(0)->data.f[1],interpreter->output(0)->data.f[2],interpreter->output(0)->data.f[3], inferenceCount++);
        
    // Analyze the results to obtain a prediction
    int gesture_index = PredictGesture(interpreter->output(0)->data.f);

    if (gesture_index!=kNoGesture)
    {
        switch (gesture_index)
        {
            case kWingGesture: 
                printf("WING Gesture			\n\r");
                printf("\n\r");
                printf("*         *         *	\n\r");
                printf(" *       * *       *	\n\r");
                printf("  *     *   *     *		\n\r");
                printf("   *   *     *   *		\n\r");
                printf("    * *       * *		\n\r");
                printf("     *         *		\n\r");
                printf("\n\r");
                break;
                
            case kRingGesture: 
                printf("RING Gesture			\n\r");
                printf("\n\r");
                printf("          *				\n\r");
                printf("       *     *			\n\r");
                printf("     *         *		\n\r");
                printf("    *           *		\n\r");
                printf("     *         *		\n\r");
                printf("       *     *			\n\r");
                printf("          *				\n\r");
                printf("\n\r");
                break;
                
            case kSlopeGesture: 
                printf("SLOPE Gesture 			\n\r");
                printf("\n\r");
                printf("        *				\n\r");
                printf("       *				\n\r");
                printf("      *					\n\r");
                printf("     *					\n\r");
                printf("    *					\n\r");
                printf("   *					\n\r");
                printf("  *						\n\r");
                printf(" * * * * * * * *		\n\r");
                printf("\n\r");                
                break;        
                
            default: 
                break;
        } 
    }
   
    if (invoke_status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed ");
        return false;
    }


    return true;
}



