    # coding: utf-8
"""*****************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************"""

import os
import time
from xml.sax.saxutils import quoteattr as xml_quoteattr
import xml.etree.ElementTree as ET

TFLITE_MICRO_FILE_LIST ="config/filelist/tflite_micro_files.xml"
TFLITE_FILE_LIST ="config/filelist/tflite_files.xml"

XML_ATTRIB_NAME = "name"
XML_ATTRIB_DIR  = "dir"
XML_ATTRIB_FILE  = "file"
XML_ATTRIB_CMSIS = "cmsis"
XML_ATTRIB_MODULE = "module"

def genCmsisMacro(symbol, event):
    symbol.setEnabled(event["value"])

def genFixedPointMacro(symbol, event):
    if( event["value"] == True):
        symbol.setValue("FIXED_POINT=16")
        symbol.getComponent().getSymbolByID("USE_KISSFFT_LIBRARY").setValue(True)
    else:
        symbol.setValue("")
        symbol.getComponent().getSymbolByID("USE_KISSFFT_LIBRARY").setValue(False)


#Instatntiate FreeRTOS Component
def instantiateComponent(tflite):
    Log.writeInfoMessage("Running TensorFlow Lite")
    global CMSIS_NN_Enable

############################################################################
#### Code Generation ####
############################################################################
    deviceArch = tflite.createStringSymbol("DEVICE_ARCHITECTURE", None)
    deviceArch.setVisible(False)
    deviceArch.setDefaultValue(ATDF.getNode("/avr-tools-device-file/devices/device").getAttribute("architecture"))

    CMSIS_NN_Enable = tflite.createBooleanSymbol("TFLITE_USES_CMSIS_NN", None)
    CMSIS_NN_Enable.setLabel("Use CMSIS-NN Library")

    if deviceArch.getValue() == "CORTEX-M4" or deviceArch.getValue() == "CORTEX-M7":
        CMSIS_NN_Enable.setDefaultValue(True)
        CMSIS_NN_Enable.setVisible(True)
    else:
        CMSIS_NN_Enable.setDefaultValue(False)
        CMSIS_NN_Enable.setVisible(False)

    preProcessingMenu = tflite.createMenuSymbol("TFLITE_PRE_PROCESSING", None)
    preProcessingMenu.setLabel("Pre-processing Library")

    microFrontEnd = tflite.createBooleanSymbol("USE_MICROFRONTEND_LIBRARY", preProcessingMenu)
    microFrontEnd.setLabel("Use Audio Frontend Library")
    microFrontEnd.setDefaultValue(False)

    thirdPartyMenu = tflite.createMenuSymbol("TFLITE_THIRD_PARTY", None)
    thirdPartyMenu.setLabel("Third Party Library")

    kissFFT = tflite.createBooleanSymbol("USE_KISSFFT_LIBRARY", thirdPartyMenu)
    kissFFT.setLabel("Use FFT Library")
    kissFFT.setDefaultValue(False)

    flatBuffers = tflite.createBooleanSymbol("USE_FLATBUFFERS_LIBRARY", thirdPartyMenu)
    flatBuffers.setLabel("Use FlatBuffers Library")
    flatBuffers.setDescription("Memory Efficient Serialization Library")
    flatBuffers.setDefaultValue(True)
    flatBuffers.setReadOnly(True)

    gemmLibrary = tflite.createBooleanSymbol("USE_GEMMLOWP_LIBRARY", thirdPartyMenu)
    gemmLibrary.setLabel("Use Low Precision Matrix Multiplication Library")
    gemmLibrary.setDescription("Low-Precision General Matrix Multiplication")
    gemmLibrary.setDefaultValue(True)
    gemmLibrary.setReadOnly(True)

    ruyLibrary = tflite.createBooleanSymbol("USE_RUY_LIBRARY", thirdPartyMenu)
    ruyLibrary.setLabel("Use RUY Matrix Multiplication Library")
    ruyLibrary.setDescription("RUY Matrix Multiplication Library")
    ruyLibrary.setDefaultValue(True)
    ruyLibrary.setReadOnly(True)

    tfliteMacro = tflite.createSettingSymbol("XC32_TFLITE_MACRO", None)
    tfliteMacro.setCategory("C32")
    tfliteMacro.setKey("preprocessor-macros")
    tfliteMacro.setValue("TF_LITE_STATIC_MEMORY")
    tfliteMacro.setAppend(True, ";=")

    tfliteCmsisMacro = tflite.createSettingSymbol("XC32_TFLITE_CMSIS_NN_MACRO", None)
    tfliteCmsisMacro.setCategory("C32")
    tfliteCmsisMacro.setKey("preprocessor-macros")
    tfliteCmsisMacro.setValue("CMSIS_NN")
    tfliteCmsisMacro.setAppend(True, ";=")
    tfliteCmsisMacro.setEnabled(CMSIS_NN_Enable.getValue() == True)
    tfliteCmsisMacro.setDependencies(genCmsisMacro, ["TFLITE_USES_CMSIS_NN"])

    tfliteCppMacro = tflite.createSettingSymbol("XC32CPP_TFLITE_MACRO", None)
    tfliteCppMacro.setCategory("C32CPP")
    tfliteCppMacro.setKey("preprocessor-macros")
    tfliteCppMacro.setValue("TF_LITE_STATIC_MEMORY")
    tfliteCppMacro.setAppend(True, ";=")

    tfliteCppCmsisMacro = tflite.createSettingSymbol("XC32CPP_TFLITE_CMSIS_NN_MACRO", None)
    tfliteCppCmsisMacro.setCategory("C32CPP")
    tfliteCppCmsisMacro.setKey("preprocessor-macros")
    tfliteCppCmsisMacro.setValue("CMSIS_NN")
    tfliteCppCmsisMacro.setAppend(True, ";=")
    tfliteCppCmsisMacro.setEnabled(CMSIS_NN_Enable.getValue() == True)
    tfliteCppCmsisMacro.setDependencies(genCmsisMacro, ["TFLITE_USES_CMSIS_NN"])


    tfliteFixedPointMacro = tflite.createSettingSymbol("XC32_TFLITE_FIXED_POINT_MACRO", None)
    tfliteFixedPointMacro.setCategory("C32")
    tfliteFixedPointMacro.setKey("preprocessor-macros")
    tfliteFixedPointMacro.setAppend(True, ";=")
    tfliteFixedPointMacro.setDependencies(genFixedPointMacro, ["USE_MICROFRONTEND_LIBRARY"])

    tfliteFixedPointCppMacro = tflite.createSettingSymbol("XC32CPP_TFLITE_FIXED_POINT_MACRO", None)
    tfliteFixedPointCppMacro.setCategory("C32CPP")
    tfliteFixedPointCppMacro.setKey("preprocessor-macros")
    tfliteFixedPointCppMacro.setValue("TF_LITE_STATIC_MEMORY")
    tfliteFixedPointCppMacro.setAppend(True, ";=")
    tfliteFixedPointCppMacro.setDependencies(genFixedPointMacro, ["USE_MICROFRONTEND_LIBRARY"])


    configName =    Variables.get( "__CONFIGURATION_NAME" )

    tfliteIncludePath = tflite.createSettingSymbol("XC32_TFLITE_INCLUDE_DIRS", None)
    tfliteIncludePath.setCategory("C32")
    tfliteIncludePath.setKey("extra-include-directories")
    tfliteIncludePath.setValue( "../src/third_party/tflite-micro/"
                        + ";../src/third_party/tflite-micro/third_party/flatbuffers/include/"
                        + ";../src/third_party/tflite-micro/third_party/gemmlowp/"
                        + ";../src/third_party/tflite-micro/third_party/ruy/"
                        + ";../src/third_party/tflite-micro/third_party/kissfft/"
                        + ";../src/packs/"
                        )
    tfliteIncludePath.setAppend(True, ";")

    tfliteCppIncludePath = tflite.createSettingSymbol("XC32CPP_TFLITE_INCLUDE_DIRS", None)
    tfliteCppIncludePath.setCategory("C32CPP")
    tfliteCppIncludePath.setKey("extra-include-directories")
    tfliteCppIncludePath.setValue(tfliteIncludePath.getValue())
    tfliteCppIncludePath.setAppend(True, ";")

    projectPath="third_party"

    # Add TensorFlow Lite files
    AddTfliteMicroFile(tflite, "..", projectPath,Module.getPath()+TFLITE_MICRO_FILE_LIST)
    AddTfliteFile(tflite, "..", projectPath,Module.getPath()+TFLITE_FILE_LIST)

    # Add datalog file
    dataLogFile = tflite.createFileSymbol("TFLITE_DATALOG", None)
    dataLogFile.setSourcePath("/src/debug_log.c")
    dataLogFile.setOutputName("debug_log.c")
    dataLogFile.setDestPath("")
    dataLogFile.setProjectPath("")
    dataLogFile.setType("SOURCE")
    dataLogFile.setMarkup(False)
    dataLogFile.setOverwrite(False)

#############################################################
### Add files
#############################################################

def enableCMSISfiles(symbol, event):
    symbol.setEnabled(event["value"])

def enableTFLITEfiles(symbol, event):
    symbol.setEnabled(not event["value"])

def enable_KISSFFT_files(symbol, event):
    symbol.setEnabled(event["value"])

def enable_FLATBUFFERS_files(symbol, event):
    symbol.setEnabled(event["value"])

def enable_GEMMLOWP_files(symbol, event):
    symbol.setEnabled(event["value"])

def enable_RUY_files(symbol, event):
    symbol.setEnabled(event["value"])

def enable_MICROFRONTEND_files(symbol, event):
    symbol.setEnabled(event["value"])


# Add File
def AddFile(child,component, strPath, strFileName, strDestPath, strProjectPath, bOverWrite=True,strType="SOURCE",bMarkup=False):
    global CMSIS_NN_Enable
    tfliteAddFile = component.createFileSymbol(strPath.upper(), None)
    tfliteAddFile.setSourcePath(strPath)
    tfliteAddFile.setOverwrite(bOverWrite)
    tfliteAddFile.setOutputName(strFileName.replace(".cc", ".cpp"))
    tfliteAddFile.setDestPath(strDestPath)
    tfliteAddFile.setProjectPath(strProjectPath)
    tfliteAddFile.setType(strType)
    tfliteAddFile.setMarkup(bMarkup)


    if(".h" in strFileName):
        tfliteAddFile.setType("HEADER")
    else:
        tfliteAddFile.setType("SOURCE")

    # Optimised CMSIS-NN kernal files are not generated for MIPS.
    if XML_ATTRIB_CMSIS in child.attrib and child.attrib[XML_ATTRIB_CMSIS] == "YES":
        if CMSIS_NN_Enable.getValue() == True:
            tfliteAddFile.setEnabled(True)
        else:
            tfliteAddFile.setEnabled(False)
        tfliteAddFile.setDependencies(enableCMSISfiles, ["TFLITE_USES_CMSIS_NN"])

    # Default TensorFlow Lite kernel files are generated for MIPS devices
    if XML_ATTRIB_CMSIS in child.attrib and child.attrib[XML_ATTRIB_CMSIS] == "NO":
        if CMSIS_NN_Enable.getValue() == False:
            tfliteAddFile.setEnabled(True)
        else:
            tfliteAddFile.setEnabled(False)
        tfliteAddFile.setDependencies(enableTFLITEfiles, ["TFLITE_USES_CMSIS_NN"])

    if XML_ATTRIB_MODULE in child.attrib and child.attrib[XML_ATTRIB_MODULE] == "KISSFFT":
        tfliteAddFile.setEnabled(False)
        tfliteAddFile.setDependencies(enable_KISSFFT_files, ["USE_KISSFFT_LIBRARY"])

    if XML_ATTRIB_MODULE in child.attrib and child.attrib[XML_ATTRIB_MODULE] == "FLATBUFFERS":
        tfliteAddFile.setEnabled(True)
        tfliteAddFile.setDependencies(enable_FLATBUFFERS_files, ["USE_FLATBUFFERS_LIBRARY"])

    if XML_ATTRIB_MODULE in child.attrib and child.attrib[XML_ATTRIB_MODULE] == "GEMMLOWP":
        tfliteAddFile.setEnabled(True)
        tfliteAddFile.setDependencies(enable_GEMMLOWP_files, ["USE_GEMMLOWP_LIBRARY"])

    if XML_ATTRIB_MODULE in child.attrib and child.attrib[XML_ATTRIB_MODULE] == "RUY":
        tfliteAddFile.setEnabled(True)
        tfliteAddFile.setDependencies(enable_RUY_files, ["USE_RUY_LIBRARY"])

    if XML_ATTRIB_MODULE in child.attrib and child.attrib[XML_ATTRIB_MODULE] == "MICROFRONTEND":
        tfliteAddFile.setEnabled(False)
        tfliteAddFile.setDependencies(enable_MICROFRONTEND_files, ["USE_MICROFRONTEND_LIBRARY"])

def AddDir(root,component,strPath, strRelativeFilePath,strProjectPath):
    for child in root:
        NewstrPath = strPath + "/" + str(child.attrib[XML_ATTRIB_NAME])
        if child.tag == XML_ATTRIB_DIR:
            NewstrRelativeFilePath = strRelativeFilePath +  "/" + str(child.attrib[XML_ATTRIB_NAME])
            NewstrProjectPath = strProjectPath +  "/" + str(child.attrib[XML_ATTRIB_NAME])
            AddDir(child,component,NewstrPath, NewstrRelativeFilePath ,NewstrProjectPath)
        if child.tag == XML_ATTRIB_FILE:
            AddFile(child, component,NewstrPath, str(child.attrib[XML_ATTRIB_NAME]), strRelativeFilePath ,strProjectPath)

def AddTfliteMicroFile(component,strPath, projectPath, strXmlFile):
    tree = ET.parse(strXmlFile)
    root = tree.getroot()
    for child in root:
        NewstrPath = strPath + "/" + str(child.attrib[XML_ATTRIB_NAME])
        if child.tag == XML_ATTRIB_DIR:
            AddDir(child,component,NewstrPath, "../../third_party/" + str(child.attrib[XML_ATTRIB_NAME]),projectPath +  "/" + str(child.attrib[XML_ATTRIB_NAME]))
        if child.tag == XML_ATTRIB_FILE:
            AddFile(child,component,NewstrPath, str(child.attrib[XML_ATTRIB_NAME]), "../../third_party/" + str(child.attrib[XML_ATTRIB_NAME]), projectPath + "/" + str(child.attrib[XML_ATTRIB_NAME]))

def AddTfliteFile(component,strPath, projectPath, strXmlFile):
    tree = ET.parse(strXmlFile)
    root = tree.getroot()
    for child in root:
        if child.tag == "loc":
            NewstrPath = strPath + "/" + str(child.attrib["srcpath"])
            AddDir(child,component,NewstrPath, "../../third_party/" + str(child.attrib["dstpath"]),projectPath +  "/" + str(child.attrib["dstpath"]))
        else:
            NewstrPath = strPath + "/" + str(child.attrib[XML_ATTRIB_NAME])
            if child.tag == XML_ATTRIB_DIR:
                AddDir(child,component,NewstrPath, "../../third_party/" + str(child.attrib[XML_ATTRIB_NAME]),projectPath +  "/" + str(child.attrib[XML_ATTRIB_NAME]))
            if child.tag == XML_ATTRIB_FILE:
                AddFile(child,component,NewstrPath, str(child.attrib[XML_ATTRIB_NAME]), "../../third_party/" + str(child.attrib[XML_ATTRIB_NAME]), projectPath + "/" + str(child.attrib[XML_ATTRIB_NAME]))
