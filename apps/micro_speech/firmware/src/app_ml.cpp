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
#include "definitions.h"                // SYS function prototypes

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/testing/micro_test.h"
#include "audio_provider.h"
#include "recognize_commands.h"
#include "feature_provider.h"
#include "command_responder.h"
#include "micro_model_settings.h"
#include "model.h"
#include "osal/osal.h"
#include "app_audio.h"
#include "micro_model_settings.h"

extern int16_t micCaptureBuffer[];

APP_ML_DATA app_mlData;

void APP_ML_DelayTick()
{
    if (app_mlData.mlDelayTick)
    {      
        app_mlData.mlDelayTick--;
    } else
    {
        app_mlData.mlDelayTick=50;
//        OSAL_SEM_PostISR(&app_mlData.processML);
    }
}


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
// Make sure that the expected "Yes" score is higher than the other classes.
uint8_t silence_score = 0;
uint8_t unknown_score = 0;
uint8_t yes_score = 0;
uint8_t no_score = 0;




tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* model_input = nullptr;
FeatureProvider* feature_provider = nullptr;
RecognizeCommands* recognizer = nullptr;
int32_t previous_time = 0;


// Create an area of memory to use for input, output, and intermediate arrays.
// The size of this will depend on the model you're using, and may need to be
// determined by experimentation.
constexpr int kTensorArenaSize = 10 * 1024;
uint8_t tensor_arena[kTensorArenaSize] __ALIGNED(16);;
int8_t feature_buffer[kFeatureElementCount];
int8_t* model_input_buffer = nullptr;


void tflite_setup(void)
{
    // Set up logging. Google style is to avoid globals or statics because of
    // lifetime uncertainty, but since this has a trivial destructor it's okay.
    static tflite::MicroErrorReporter micro_error_reporter;  // NOLINT
    error_reporter = &micro_error_reporter;

    // Map the model into a usable data structure. This doesn't involve any
    // copying or parsing, it's a very lightweight operation.
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
	micro_op_resolver.AddDepthwiseConv2D();
	micro_op_resolver.AddFullyConnected();
	micro_op_resolver.AddReshape();
	micro_op_resolver.AddSoftmax();

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

    // Get information about the memory area to use for the model's input.
    model_input = interpreter->input(0);
    model_input_buffer = model_input->data.int8;
    
    // Prepare to access the audio spectrograms from a microphone or other source
    // that will provide the inputs to the neural network.
    // NOLINTNEXTLINE(runtime-global-variables)
    static FeatureProvider static_feature_provider(kFeatureElementCount,
                                                 feature_buffer);
    feature_provider = &static_feature_provider;
  
    static RecognizeCommands static_recognizer(error_reporter);
    recognizer = &static_recognizer;
}
static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;

static void Timer_Callback ( uintptr_t context)
{  
    LED_YES_Off();
    LED_NO_Off();
    
}
void tflite_task(void)
{
    const int32_t current_time = LatestAudioTimestamp();
    int how_many_new_slices = 0;
   
//    TF_LITE_REPORT_ERROR(error_reporter, "previous time (%d) current time (%d)", previous_time, current_time);
        
    TfLiteStatus feature_status = feature_provider->PopulateFeatureData(
        error_reporter, previous_time, current_time, &how_many_new_slices);
    if (feature_status != kTfLiteOk) {
      TF_LITE_REPORT_ERROR(error_reporter, "Feature generation failed");
      return;
    }

    previous_time = current_time;
    // If no new audio samples have been received since last time, don't bother
    // running the network model.
    if (how_many_new_slices == 0) {
        return;
    }
    
    TEST2_Set();
    // Copy feature buffer to input tensor
    for (int i = 0; i < kFeatureElementCount; i++) {
        model_input_buffer[i] = feature_buffer[i];
    }
        
    // Run the model on the spectrogram input and make sure it succeeds.
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
      TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed");
      return;
    }
   
    // Obtain a pointer to the output tensor
    TfLiteTensor* output = interpreter->output(0);
    
   
  // Determine whether a command was recognized based on the output of inference
    const char* found_command = nullptr;
    uint8_t score = 0;
    bool is_new_command = false;
    TfLiteStatus process_status = recognizer->ProcessLatestResults(
        output, current_time, &found_command, &score, &is_new_command);
    if (process_status != kTfLiteOk) {
      TF_LITE_REPORT_ERROR(error_reporter,
                           "RecognizeCommands::ProcessLatestResults() failed");
      return;
    }    
    
    // Indicate the recognized command.
    if (is_new_command) {

        // Detected keyword "Yes"
        if(memcmp(found_command,kCategoryLabels[2],3) == 0)
        {
            LED_YES_On();
            timer = SYS_TIME_CallbackRegisterMS(Timer_Callback, 1, 4000, SYS_TIME_SINGLE);            
            RespondToCommand(error_reporter, current_time, found_command, score,is_new_command);
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[2],output->data.int8[2]);
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[3],output->data.int8[3]);
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[1],output->data.int8[1]); 
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[0],output->data.int8[0]); 
        }

        // Detected keyword "No"
        if(memcmp(found_command,kCategoryLabels[3],2) == 0)
        {
            LED_NO_On();
            timer = SYS_TIME_CallbackRegisterMS(Timer_Callback, 1, 4000, SYS_TIME_SINGLE);            
            RespondToCommand(error_reporter, current_time, found_command, score,is_new_command);
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[2],output->data.int8[2]);
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[3],output->data.int8[3]);
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[1],output->data.int8[1]);  
            printf("Score for keyword %s is %d\n\r",kCategoryLabels[0],output->data.int8[0]); 
        }
        
        

    }
    
    TEST2_Clear();

    
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
    OSAL_SEM_Create(&app_mlData.processML, OSAL_SEM_TYPE_BINARY, 0, 0);

    tflite_setup();


    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
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
            app_mlData.mlDelayTick=20;


            if (appInitialized)
            {

                app_mlData.state = APP_ML_STATE_CALC;
            }
            break;
        }

        case APP_ML_STATE_WAIT:
            if (OSAL_SEM_Pend(&app_mlData.processML, OSAL_WAIT_FOREVER) == OSAL_RESULT_TRUE)
            {
                    
            }       
            app_mlData.state = APP_ML_STATE_CALC;

        case APP_ML_STATE_CALC:
        {
            /* Wait for transfer to complete */
            tflite_task();
            app_mlData.state = APP_ML_STATE_CALC;
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
