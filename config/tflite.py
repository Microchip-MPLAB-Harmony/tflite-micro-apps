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

FILE_LIST ="config/filelist/tflite_files.xml"
XML_ATTRIB_NAME = "name"
XML_ATTRIB_DIR  = "dir"
XML_ATTRIB_FILE  = "file"
XML_ATTRIB_CMSIS = "cmsis"


#Instatntiate FreeRTOS Component
def instantiateComponent(tflite):
    Log.writeInfoMessage("Running TensorFlow Lite")

############################################################################
#### Code Generation ####
############################################################################
    CMSIS_NN_Enable = tflite.createBooleanSymbol("TFLITE_USES_CMSIS_NN", None)
    CMSIS_NN_Enable.setLabel("Use CMSIS-NN Library")
    CMSIS_NN_Enable.setDefaultValue(True)

    tfliteMacro = tflite.createSettingSymbol("XC32_TFLITE_MACRO", None)
    tfliteMacro.setCategory("C32")
    tfliteMacro.setKey("preprocessor-macros")
    tfliteMacro.setValue("TF_LITE_STATIC_MEMORY")
    tfliteMacro.setAppend(True, ";")

    tfliteCppMacro = tflite.createSettingSymbol("XC32CPP_TFLITE_MACRO", None)
    tfliteCppMacro.setCategory("C32CPP")
    tfliteCppMacro.setKey("preprocessor-macros")
    tfliteCppMacro.setValue("TF_LITE_STATIC_MEMORY")
    tfliteCppMacro.setAppend(True, ";")

    configName =    Variables.get( "__CONFIGURATION_NAME" )

    tfliteIncludePath = tflite.createSettingSymbol("XC32_TFLITE_INCLUDE_DIRS", None)
    tfliteIncludePath.setCategory("C32")
    tfliteIncludePath.setKey("extra-include-directories")
    tfliteIncludePath.setValue( "../src/config/"+configName+"/tensorflow/"
                        + ";../src/config/"+configName+"/tensorflow/third_party/flatbuffers/include/"
                        + ";../src/config/"+configName+"/tensorflow/third_party/gemmlowp/"
                        + ";../src/config/"+configName+"/tensorflow/third_party/ruy/"
                        + ";../src/packs/"
                        )
    tfliteIncludePath.setAppend(True, ";")

    tfliteCppIncludePath = tflite.createSettingSymbol("XC32CPP_TFLITE_INCLUDE_DIRS", None)
    tfliteCppIncludePath.setCategory("C32CPP")
    tfliteCppIncludePath.setKey("extra-include-directories")
    tfliteCppIncludePath.setValue(tfliteIncludePath.getValue())
    tfliteCppIncludePath.setAppend(True, ";")

#    xc32cppGnuStd = tflite.createSettingSymbol("XC32CPP_GNU_STD", None)
#    xc32cppGnuStd.setCategory("C32CPP")
#    xc32cppGnuStd.setKey("appendMe")
#    xc32cppGnuStd.setValue("-std=gnu++11")
#    xc32cppGnuStd.setAppend(True, " ")

    configName = Variables.get("__CONFIGURATION_NAME")
    projectPath="/config/"+configName+"/"

    # Add TensorFlow Lite files
    AddTfliteFile(tflite, "..", projectPath,Module.getPath()+FILE_LIST)

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

# Add File
def AddFile(child,component, strPath, strFileName, strDestPath, strProjectPath, bOverWrite=True,strType="SOURCE",bMarkup=False):
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

    if XML_ATTRIB_CMSIS in child.attrib and child.attrib[XML_ATTRIB_CMSIS] == "YES":
        tfliteAddFile.setDependencies(enableCMSISfiles, ["TFLITE_USES_CMSIS_NN"])
    if XML_ATTRIB_CMSIS in child.attrib and child.attrib[XML_ATTRIB_CMSIS] == "NO":
        tfliteAddFile.setEnabled(False)
        tfliteAddFile.setDependencies(enableTFLITEfiles, ["TFLITE_USES_CMSIS_NN"])

def AddDir(root,component,strPath, strRelativeFilePath,strProjectPath):
    for child in root:
        NewstrPath = strPath + "/" + str(child.attrib[XML_ATTRIB_NAME])
        if child.tag == XML_ATTRIB_DIR:
            NewstrRelativeFilePath = strRelativeFilePath +  "/" + str(child.attrib[XML_ATTRIB_NAME])
            NewstrProjectPath = strProjectPath +  "/" + str(child.attrib[XML_ATTRIB_NAME])
            AddDir(child,component,NewstrPath, NewstrRelativeFilePath ,NewstrProjectPath)
        if child.tag == XML_ATTRIB_FILE:
            AddFile(child, component,NewstrPath, str(child.attrib[XML_ATTRIB_NAME]), strRelativeFilePath ,strProjectPath)

def AddTfliteFile(component,strPath, projectPath, strXmlFile):
    tree = ET.parse(strXmlFile)
    root = tree.getroot()
    for child in root:
        NewstrPath = strPath + "/" + str(child.attrib[XML_ATTRIB_NAME])
        if child.tag == XML_ATTRIB_DIR:
            AddDir(child,component,NewstrPath, "/" + str(child.attrib[XML_ATTRIB_NAME]),projectPath +  "/" + str(child.attrib[XML_ATTRIB_NAME]))
        if child.tag == XML_ATTRIB_FILE:
            AddFile(child,component,NewstrPath, str(child.attrib[XML_ATTRIB_NAME]), "/" + str(child.attrib[XML_ATTRIB_NAME]), projectPath + "/" + str(child.attrib[XML_ATTRIB_NAME]))


