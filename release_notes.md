![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Harmony TensorFlow Lite for Micrcontroller (TFLM) Solutions v1.0.0 Release

### New Features
This release introduces Harmony support for TensorFlow Lite for Microcontroller (TFM). It includes the following
- Harmony 3 component to easily configure and generate code for TFLM runtime engine
- Example scripts to create Neural Network model with Google Colaboratory for digit recognition and covert the model to TensorFlow Lite format using TensorFlow Lite Converter
- Example applications to demonstrate how to deploy TensorFlow Lite model for inferencing on Microcontrollers with TFLM run time engine

| Application        | Description  | [SAM E70 XULT](https://www.microchip.com/en-us/development-tool/DM320113) | [SAM E51 IGaT](https://www.microchip.com/en-us/development-tool/EV14C17A) | [SAM E54 CULT](https://www.microchip.com/en-us/development-tool/DM320210) | [SAM A5D2 XULT](https://www.microchip.com/en-us/development-tool/ATSAMA5D2C-XULT)
| -------------------| ------------ |  ----------- |------------- | ------------ | -------------
| Micro Speech       | This example classifies speech input into one of 4 classes ('yes', 'no’, ‘silence’, ‘unknown’) 				| Yes | -   | Yes | -  |
| Magic Wand  		 | This example classifies accelerometer data into one of 4 classes of gestures (Wing, Ring, Slop, unknown)  	| Yes | -   | Yes | -  |
| Digit Recognition  | This example demonstrates handwritten digit recognition with the model trained using MNIST dataset 			| Yes   | Yes | -   | Yes|
| Hello World      	 | This example demonstrates end to end workflow of creating and deploying model to predict sin function output| Yes   | Yes | -   | Yes|


### Known Issues
- None 

### Development Tools
* [MPLAB X IDE v6.0](https://www.microchip.com/mplabx-ide-windows-installer)
* [MPLAB XC32 C/C++ Compiler v4.0](https://www.microchip.com/mplab/compilers)
* MPLAB X IDE plug-ins: 
    * MPLAB Code Configurator (MCC) v5.1.2
