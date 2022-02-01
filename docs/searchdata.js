var SearchFiles = ["GUID-64C4C60D-2C4B-4E01-BCC9-D6E17F16F1DE.html",
							"GUID-CA8858A6-EC72-42D5-8A59-8B9794E16C66.html",
							"GUID-0F3CD544-58EB-44C0-BB29-1A012E01C1B1.html",
							"GUID-984FB84C-4725-4AA2-A70C-A884D01311AB.html",
							"GUID-1073FCEB-AA0D-4DED-B13C-728191CCA55B.html",
							"GUID-22D72BA8-E33F-48CE-8AD7-9D5B4221D2A1.html",
							"GUID-03CB631F-1D98-46BA-AEDA-43AA5C83CF21.html",
							"GUID-DAB76DB4-BD3F-4333-8865-97CB13B28834.html",
							"GUID-45E127EA-AAD5-43DE-8456-D6843606BAF6.html",
							"GUID-1A54C1AF-D42B-4750-A5F2-C8E1CC52E767.html",
							"GUID-18F432ED-65E7-4A5B-A662-1BA75CF70D3C.html",
							"GUID-DF0BF0FD-784B-48A8-9C86-58CCD0F15E41.html",
							"GUID-85C71EF8-14CC-4BC7-814C-1248E7D2D6B6.html",
							"GUID-F2F8B90C-C322-4646-9017-C0BF6059C8EF.html",
							"GUID-5040A5F5-7EEE-4A90-BD82-BAF0C39B7F80.html"];

var SearchTitles = ["MPLAB® Harmony TensorFlow Lite Configurations and Application examples for Microchip Microcontrollers",
"Digit Recognition example",
"Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit",
"Building and Running the Application on SAM E51 Integrated Graphics and Touch Development Board",
"Building and Running the Application on SAM A5D2 Xplained Ultra",
"Hello World example",
"Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit",
"Building and Running the Application SAM E51 Integrated Graphics and Touch Development Board",
"Building and Running the Application on SAM A5D2 Xplained Ultra",
"Magic Wand example",
"Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit",
"Building and Running the Application on SAM E54 Curiosity Ultra Development Board",
"Micro Speech example",
"Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit",
"Building and Running the Application on SAM E54 Curiosity Ultra Development Board"];

var SearchInfo = [" MPLAB® Harmony TensorFlow Lite Configurations and Application examples for Microchip Microcontrollers This distribution package contains scripts to represent TensorFlow Lite for Microcontrollers as a component for easier configuration and example applications to demonstrate the usage as part of Harmony framwork Google Colaboratory notebook is provided to create Convolutional Neural Network (CNN) and train with MNIST dataset to classify handwritten digit Refer to Digit Recognition example application for more details Introduction TensorFlow is an end-to-end open-source platform for machine learning Tensorflow bundles together Machine Learning and Deep Learning models and algorithms TensorFlow can be used for both network training and inference whereas TensorFlow Lite for Microcontroller (TFLM) is specifically designed to deploy a pre-trained deep learning model on embedded devices with limited compute and memory resources The process of creating and deploying machine learning model on Microcontroller using TFLM is given below Select and train a model using TensorFlow Convert the model to TensorFlow Lite format using TensorFlow Lite Converter Deploy the converted model for inferencing on Microcontrollers with TFLM run time engine ml flow TensorFlow Lite converter takes a TensorFlow model and generates a TensorFlow Lite model (an optimized FlatBuffer format identified by the tflite file extension) You can quantize the model to reduce model size and improve execution performance Refer to post-training quantization for more details Google Colab or \"Colaboratory\" allows you to write and execute Python in your browser to create models and evaluate these models Refer to the following information to get started with TensorFlow and Google Colaboratory Welcome to Colaboratory TensorFlow 2 quickstart for beginners TensorFlow Lite for Microcontroller (TFLM) Configurations The following figure shows the configuration option for TFLM component tflite_configuration Use CMSIS-NN Library CMSIS-NN provides optimized kernels to maximize the performance and minimize the memory for Cortex-M4 and Cortex-M7 based Microcontrollers TensorFlow Lite uses optimized kernels (integer) when available The reference kernels (float) are used as the fallback option Use Audio Frontend Library This is required to run the micro_speech example with TFLM Use FFT library This is required to run the micro_speech example with TFLM TFLM makes use of following third-party library FlatBuffers library Low Precision Matrix Multiplication library RUY Matrix Multiplication Library Application examples The following applications are provided to demonstrate the typical or interesting usage models for TensorFlow Lite Name Description Digit Recognition Demonstrates handwritten digit recognition hello world Demonstrate the absolute basics of using TensorFlow Lite for Microcontroller magic wand Demonstrates how to use accelerometer to recognize gestures micro speech Demonstrates how to recognize keywords from speech data ",
							" Digit Recognition example This example demonstrates handwritten digit recognition using TensorFlow Lite for Microchip 32-bit Microcontrollers The neural network model is created and trained with MNIST dataset to classify a given image of handwritten digit into one of 10 classses (0-9) Google Colaboratory notebook is provided to create Convolutional Neural Network (CNN) and train with MNIST dataset to classify handwritten digit Open the notebook in google Colab Press ctrl+F9 or go to runtime menu on top and click run all option and all cells run at a time Generated model is converted to TensorFlow Lite FlatBuffer format ( model_int8_full tflite ) with full integer quantization to reduce model size and improve execution performance The easiest way to use a model in your project is to include it as a C array Hence the flatbuffer is converted to C array ( \"model_int8_full cpp\" and \"model_int8_full h\" ) tflite model MPLAB X project includes the generated model file to perform inferencing on Microcontroller using TFLM runtime engine c array model Development Kits The following list provides links to documentation on how to build and run the demo on different development kits ",
							" Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit Downloading and building the application Path of the application within the repository is apps/digit_recognition/firmware To build the application refer to the following table and open the project in MPLAB X IDE Project Name Board Configuration sam_e70_xult_tm4301b_ssd1963 X SAM E70 Xplained Ultra Evaluation Kit with SSD1963 LCD Controller Graphics Card driving High-Performance WQVGA Display Module with maXTouch® Technology Setting up the hardware Setup hardware to drive the WQVGA display using SSD1963 external graphics controller digit_recognition_sam_e70_xult_tm4301b_ssd1963 Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Open the Terminal application (Ex :Tera term) on the computer Connect to the EDBG Virtual COM port and configure the serial settings as follows: Baud : 115200 Data : 8 Bits Parity : None Stop : 1 Bit Flow Control : None Build and Program the application Write a digit (0 to 9) on the display as shown below digit_recognition_sam_e70_xult_tm4301b_ssd1963_writedigit Recognised digit is displayed as shown below digit_recognition_sam_e70_xult_tm4301b_ssd1963_recogniseddigit The array of scores corresponding to the 10 classes are displayed in the terminal The highest scores 2 in this case will be displayed as the predicted digit digit_recognition_teraterm ",
							" Building and Running the Application on SAM E51 Integrated Graphics and Touch Development Board Downloading and building the application Path of the application within the repository is apps/digit_recognition/firmware To build the application refer to the following table and open the project using its IDE Project Name Board Configuration sam_e51_igat X SAM E51 Integrated Graphics and Touch Development Board Setting up the hardware Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Open the Terminal application (Ex :Tera term) on the computer Connect to the EDBG Virtual COM port and configure the serial settings as follows: Baud : 115200 Data : 8 Bits Parity : None Stop : 1 Bit Flow Control : None Build and Program the application Write a digit (0 to 9) on the display as shown below digit_recognition_sam_e51_igat_writedigit Recognised digit is displayed as shown below digit_recognition_sam_e51_igat_recogniseddigit The array of scores corresponding to the 10 classes are displayed in the terminal The highest scores 2 in this case will be displayed as the predicted digit digit_recognition_teraterm ",
							" Building and Running the Application on SAM A5D2 Xplained Ultra Downloading and building the application Path of the application within the repository is apps/digit_recognition/firmware To build the application refer to the following table and open the project using its IDE Project Name Board Configuration sam_a5d2_xult_tm5000 X SAM A5D2 Xplained Ultra with High-Performance WVGA Display Module with maXTouch® Technology Setting up the hardware Take an SD Card formatted with FAT32 file system and copy the boot bin binary file from this location Also copy the harmony bin file you generated from the \"Building the Application\" section Connect the ribbon cable from the display to the LCD connector on the SAM A5D2 Xplained Ultra board digit_recognition_sam_a5d2_xult_tm5000 Insert the SD card to J19 of the SAM A5D2 Xplained Ultra board Connect the Debug USB port (J14) on the board to the computer using a micro USB cable Running the Application Open the Terminal application (Ex :Tera term) on the computer Connect to the EDBG Virtual COM port and configure the serial settings as follows: Baud : 115200 Data : 8 Bits Parity : None Stop : 1 Bit Flow Control : None Build and Program the application Write a digit (0 to 9) on the display and the Recognised digit is displayed as shown below digit_recognition_sam_a5d2_xult_tm5000_recogniseddigit The array of scores corresponding to the 10 classes are displayed in the terminal The highest scores 2 in this case will be displayed as the predicted digit digit_recognition_teraterm ",
							" Hello World example This is \"hello world\" demo of TensorFlow Lite This example is designed to demonstrate the absolute basics of using TensorFlow Lite for Microcontroller It uses pretrained ML model to predict the sin of an input In a real-world application if you needed the sine of x you could just calculate it directly However by training a model to approximate the result we can demonstrate the basics of machine learning Development Kits The following list provides links to documentation on how to build and run the demo on different development kits ",
							" Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit Downloading and building the application Path of the application within the repository is apps/hello_world/firmware To build the application refer to the following table and open the project in MPLAB X IDE Project Name Board Configuration sam_e70_xult_tm4301b_ssd1963 X SAM E70 Xplained Ultra Evaluation Kit with SSD1963 LCD Controller Graphics Card driving High-Performance WQVGA Display Module with maXTouch® Technology Setting up the hardware Setup hardware to drive the WQVGA display using SSD1963 external graphics controller hello_world_sam_e70_xult_tm4301b_ssd1963 Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Build and Program the application Sin wave is displayed as shown below hello_world_sam_e70_xult_tm4301b_ssd1963_sinoutput ",
							" Building and Running the Application SAM E51 Integrated Graphics and Touch Development Board Downloading and building the application Path of the application within the repository is apps/hello_world/firmware To build the application refer to the following table and open the project using its IDE Project Name Board Configuration sam_e51_igat X SAM E51 Integrated Graphics and Touch Development Board Setting up the hardware Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Build and Program the application Sin wave is displayed as shown below hello_world_sam_e51_igat_sinoutput ",
							" Building and Running the Application on SAM A5D2 Xplained Ultra Downloading and building the application Path of the application within the repository is apps/hello_wrold/firmware To build the application refer to the following table and open the project using its IDE Project Name Board Configuration sam_a5d2_xult_tm5000 X SAM A5D2 Xplained Ultra with High-Performance WVGA Display Module with maXTouch® Technology Setting up the hardware Take an SD Card formatted with FAT32 file system and copy the boot bin binary file from this location Also copy the harmony bin file you generated from the \"Building the Application\" section Connect the ribbon cable from the display to the LCD connector on the SAM A5D2 Xplained Ultra board hello_world_sam_a5d2_xult_tm5000 Insert the SD card to J19 of the SAM A5D2 Xplained Ultra board Connect the Debug USB port (J14) on the board to the computer using a micro USB cable Running the Application Build and Program the application Sin wave is displayed as shown below hello_world_sam_a5d2_xult_tm5000_sinoutput ",
							" Magic Wand example This is \"magic wand\" demo of TensorFlow Lite This example shows how to run neural network model using Tensorflow Lite for microcontroller runtime engine to recognize the \"ring\" \"wing\" and \"slop\" gestures with an accelerometer Development Kits The following list provides links to documentation on how to build and run the demo on different development kits ",
							" Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit Downloading and building the application Path of the application within the repository is apps/magic_wand/firmware To build the application refer to the following table and open the project in MPLAB X IDE Project Name Board Configuration sam_e70_xult_imu2 X SAM E70 Xplained Ultra Evaluation Kit with 6DOF IMU 2 Click Setting up the hardware Plug an IMU 2 Click board into the MikroBus socket Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Open the Terminal application (Ex :Tera term) on the computer Connect to the EDBG Virtual COM port and configure the serial settings as follows: Baud : 115200 Data : 8 Bits Parity : None Stop : 1 Bit Flow Control : None Build and Program the application Hold the board as shown below Proper board orientation is required to infer the gestures correctly magic_wand_sam_e70_xult_imu2_orientation Perform the wing gesture magic_wand_wing_gesture The detected gesture is displayed on the terminal magic_wand_terminal_output ",
							" Building and Running the Application on SAM E54 Curiosity Ultra Development Board Downloading and building the application Path of the application within the repository is apps/magic_wand/firmware To build the application refer to the following table and open the project using its IDE Project Name Board Configuration sam_e54_cult_imu2 X SAM E54 Curiosity Ultra Development Board with 6DOF IMU 2 Click Setting up the hardware Plug an IMU 2 Click board into the MikroBus socket Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Open the Terminal application (Ex :Tera term) on the computer Connect to the EDBG Virtual COM port and configure the serial settings as follows: Baud : 115200 Data : 8 Bits Parity : None Stop : 1 Bit Flow Control : None Build and Program the application Hold the board as shown below Proper board orientation is required to infer the gestures correctly magic_wand_sam_e54_cult_imu2_orientation Perform the wing gesture magic_wand_wing_gesture The detected gesture is displayed on the terminal magic_wand_terminal_output ",
							" Micro Speech example This is \"micro speech\" demo of TensorFlow Lite This example shows how to run neural network model using Tensorflow Lite for microcontroller runtime engine to recognize 2 keywords \"yes\" and \"no\" from speech data The application listens to its surroundings with a microphone and indicates when it has detected a the keyword by lighting an LED or displaying data on a terminal Development Kits The following list provides links to documentation on how to build and run the demo on different development kits ",
							" Building and Running the Application on SAM E70 Xplained Ultra Evaluation Kit Downloading and building the application Path of the application within the repository is apps/micro_speech/firmware To build the application refer to the following table and open the project in MPLAB X IDE Project Name Board Configuration sam_e70_xult_wm8904_i2sc_freertos X SAM E70 Xplained Ultra Evaluation Kit with PIC32 Audio Codec Daughter Card with WM8904 stereo codec Setting up the hardware Hardware is setup as shown below micro_speech_sam_e70_cult_wm8904_setup Plugin Audio codec daugter board into the set of X32 connectors Set the jumpers on the audio codec board as shown below Each jumper should be connected to the two right-most pins on the board when viewed from the perspective of the audio jack micro_speech_wm8904_jumpers_right Connect headphones to the green HP OUT jack of the Codec Daughter Board Connect your microphone to pink MIC IN jack of the Codec Daughter Board micro_speech_omnimic_3 5mm Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Open the Terminal application (Ex :Tera term) on the computer Connect to the EDBG Virtual COM port and configure the serial settings as follows: Baud : 115200 Data : 8 Bits Parity : None Stop : 1 Bit Flow Control : None Build and Program the application Press Switch (SW1) to cycles through four volume levels (one muted) The LEDs will light up selectively based on which keyword is detected | Event | LED indication | |:------------------|:---------------------| | “YES” keyword detected | LED2 is turned on for 4 seconds| | “NO” keyword detected | LED1 is turned on for 4 seconds| The score corresponding to four classes are displayed on the terminal The highest scores \"Yes\" in this case is the detected keyword micro_speech_terminal_output ",
							" Building and Running the Application on SAM E54 Curiosity Ultra Development Board Downloading and building the application Path of the application within the repository is apps/micro_speech/firmware To build the application refer to the following table and open the project using its IDE Project Name Board Configuration sam_e54_cult_wm8904_freertos X SAM E54 Curiosity Ultra Development Board with PIC32 Audio Codec Daughter Card with WM8904 stereo codec Setting up the hardware Hardware is setup as shown below micro_speech_sam_e54_cult_wm8904_setup Plugin Audio codec daugter board into the set of X32 connectors Set the jumpers on the audio codec board as shown below Each jumper should be connected to the two left-most pins on the board when viewed from the perspective of the audio jack micro_speech_wm8904-jumpers_left Set the CLK SELECT jumper (J401) so that it connects the MCLK and PA17 pins on the board as shown below This pin configuration lets the WM8904 act as the clock master to the SAME54’s I2S peripheral micro_speech_E54-J401-PA17 Connect headphones to the green HP OUT jack of the Codec Daughter Board Connect your microphone to pink MIC IN jack of the Codec Daughter Board micro_speech_omnimic_3 5mm Connect the Debug USB port on the board to the computer using a micro USB cable Running the Application Open the Terminal application (Ex :Tera term) on the computer Connect to the EDBG Virtual COM port and configure the serial settings as follows: Baud : 115200 Data : 8 Bits Parity : None Stop : 1 Bit Flow Control : None Build and Program the application Press Switch (SW1) to cycle through four volume levels (one muted) The LEDs will light up selectively based on which keyword is detected Event LED indication “YES” keyword detected LED1 is turned on for 4 seconds “NO” keyword detected LED2 is turned on for 4 seconds The score corresponding to four classes are displayed on the terminal The highest scores \"Yes\" in this case is the detected keyword micro_speech_terminal_output "];
