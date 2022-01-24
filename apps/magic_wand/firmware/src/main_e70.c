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

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdint.h>
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>
#include "ringbuffer.h"
#include "sensor.h"
#include "app_config.h"
#include "app_ml.h"

// *****************************************************************************
// *****************************************************************************
// Section: Platform specific includes
// *****************************************************************************
// *****************************************************************************
#include "definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global variables
// *****************************************************************************
// *****************************************************************************
// 128 samples of 3-axis acceleration data
#define   ACC_RING_BUFFER_SIZE      256
#define   ACC_ML_INPUT_BUFFER_SIZE  128
float accData[ACC_ML_INPUT_BUFFER_SIZE][3];
float accDataBuffer[ACC_RING_BUFFER_SIZE][3];
int16_t accIndex=0;

bool accDataReady=false;
bool waitForInitData=true;

static volatile uint32_t tickcounter = 0;

static struct sensor_device_t sensor;
static snsr_data_t _snsr_buffer_data[SNSR_BUF_LEN][SNSR_NUM_AXES];
static ringbuffer_t snsr_buffer;
static volatile bool snsr_buffer_overrun = false;

// *****************************************************************************
// *****************************************************************************
// Section: Generic stub definitions
// *****************************************************************************
// *****************************************************************************

static void Null_Handler(PIO_PIN pin, uintptr_t context) {
    // Do nothing
}

// Take 128 samples of acceleration in 3-axis at 25Hz (128 x 3-axis = 384)
// Sensor data in m/s^2 = [data / (2^15/range)] * 9.8
// Eg., range = 16g     = (data/2048)*9.8  -> Unit is m/s^2
// Eg., range = 16g     = (data/2048)  -> Unit is g

static void SNSR_ISR_HANDLER(PIO_PIN pin, uintptr_t context) {
    
    TEST1_Toggle();

    /* Check if any errors we've flagged have been acknowledged */
    if ((sensor.status != SNSR_STATUS_OK) || snsr_buffer_overrun)
        return;
    
    ringbuffer_size_t wrcnt;
    snsr_data_t *ptr = ringbuffer_get_write_buffer(&snsr_buffer, &wrcnt);
    
    if (wrcnt == 0)
        snsr_buffer_overrun = true;
    else if ((sensor.status = sensor_read(&sensor, ptr)) == SNSR_STATUS_OK)
        ringbuffer_advance_write_index(&snsr_buffer, 1);
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    int8_t app_failed = 0;

    /* Initialize all modules */
    SYS_Initialize ( NULL );
    MIKRO_INT_Disable();
    SYSTICK_TimerStart();
    
    /* Initialize the sensor data buffer */
    if (ringbuffer_init(&snsr_buffer, _snsr_buffer_data, sizeof(_snsr_buffer_data) / sizeof(_snsr_buffer_data[0]), sizeof(_snsr_buffer_data[0])))
    {        
        app_failed = 1;
    }
   
    /* Init and configure sensor */
    if (sensor_init(&sensor) != SNSR_STATUS_OK) {
        printf("ERROR: sensor init result = %d\n\r", sensor.status);
        app_failed = 1;
    }

    if (sensor_set_config(&sensor) != SNSR_STATUS_OK) {
        printf("ERROR: sensor configuration result = %d\n\r", sensor.status);
        app_failed = 1;
    }

    printf("sensor type is %s\n\r", SNSR_NAME);
    printf("sensor sample rate set at %dHz\n\r", SNSR_SAMPLE_RATE);
    
    #if SNSR_USE_ACCEL
        printf("Accelerometer axes %s%s%s enabled with range set at +/-%dGs\n\r", SNSR_USE_ACCEL_X ? "x" : "", SNSR_USE_ACCEL_Y ? "y" : "", SNSR_USE_ACCEL_Z ? "z" : "", SNSR_ACCEL_RANGE);
    #else
        printf("Accelerometer disabled\n\r");
    #endif

    #if SNSR_USE_GYRO
        printf("Gyrometer axes %s%s%s enabled with range set at %dDPS\n\r", SNSR_USE_GYRO_X ? "x" : "", SNSR_USE_GYRO_Y ? "y" : "", SNSR_USE_GYRO_Z ? "z" : "", SNSR_GYRO_RANGE);
    #else
        printf("Gyrometer disabled\n\r");
    #endif

    if (!app_failed)
    {
       tflite_setup();
       MIKRO_INT_CallbackRegister(SNSR_ISR_HANDLER);
       MIKRO_INT_Enable();
    }
        
    while (!app_failed)
    {
        /* Maintain state machines of all system modules. */
        SYS_Tasks ( );
        
        if (sensor.status != SNSR_STATUS_OK) {
            printf("ERROR: Got a bad sensor status: %d\n", sensor.status);
            break;
        } 
        else if (snsr_buffer_overrun == true) {
            printf("\n\n\nOverrun!\n\n\n");

            /* STATE CHANGE - buffer overflow */
            SNSR_SLEEP_MS(5000U);

            // Clear OVERFLOW
            MIKRO_INT_CallbackRegister(Null_Handler);
            ringbuffer_reset(&snsr_buffer);
            snsr_buffer_overrun = false;
            MIKRO_INT_CallbackRegister(SNSR_ISR_HANDLER);
        } else
        {
            ringbuffer_size_t rdcnt;
            SNSR_DATA_TYPE const *ptr = ringbuffer_get_read_buffer(&snsr_buffer, &rdcnt);
            while (rdcnt--) {

                float x = *ptr++;
                float y = *ptr++;
                float z = *ptr++;
                
                ringbuffer_advance_read_index(&snsr_buffer, 1);

               
                float norm_x=-z/8192;
                float norm_y=-x/8192;
                float norm_z=-y/8192;   

               
                accDataBuffer[accIndex][0]= norm_x*1000;
                accDataBuffer[accIndex][1]= norm_y*1000;
                accDataBuffer[accIndex][2]= norm_z*1000;
  
                accIndex++;
                
                if (accIndex >= ACC_RING_BUFFER_SIZE) {
                    accIndex=0;
                }
                
                // Wait for initial data
                if(waitForInitData==true && accIndex>=200)
                    waitForInitData=false;
                
                if(waitForInitData==false)
                    accDataReady=true;
            }
            
            if (accDataReady)
            {
                // Read last 128 samples
                for (int i = 0; i < ACC_ML_INPUT_BUFFER_SIZE; ++i) {
                    int index=accIndex-ACC_ML_INPUT_BUFFER_SIZE+i;
                    
                    if(index<0)
                        index= index+ACC_RING_BUFFER_SIZE;
                    
                    accData[i][0]=accDataBuffer[index][0];
                    accData[i][1]=accDataBuffer[index][1];
                    accData[i][2]=accDataBuffer[index][2];                    
                }
                
                accDataReady=false;
                tflite_runInference();
            }
        }
    }

    /* Loop forever on error */
    while (1) {};

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/
