/*******************************************************************************
 Module for Microchip Legato Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    le_gen_assets.h

  Summary:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.


  Description:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.

*******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C)  Microchip Technology Inc. and its subsidiaries.
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
*******************************************************************************/

// DOM-IGNORE-END

#ifndef LE_GEN_ASSETS_H
#define LE_GEN_ASSETS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

#include "gfx/legato/legato.h"

extern const lePalette leGlobalPalette;

/*****************************************************************************
 * Legato Graphics Image Assets
 *****************************************************************************/
/*********************************
 * Legato Image Asset
 * Name:   mchpLogo_light
 * Size:   152x40 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage mchpLogo_light;

/*********************************
 * Legato Image Asset
 * Name:   nine
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage nine;

/*********************************
 * Legato Image Asset
 * Name:   eight
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage eight;

/*********************************
 * Legato Image Asset
 * Name:   seven
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage seven;

/*********************************
 * Legato Image Asset
 * Name:   six
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage six;

/*********************************
 * Legato Image Asset
 * Name:   five
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage five;

/*********************************
 * Legato Image Asset
 * Name:   four
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage four;

/*********************************
 * Legato Image Asset
 * Name:   three
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage three;

/*********************************
 * Legato Image Asset
 * Name:   two
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage two;

/*********************************
 * Legato Image Asset
 * Name:   one
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage one;

/*********************************
 * Legato Image Asset
 * Name:   zero
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage zero;

/*********************************
 * Legato Image Asset
 * Name:   failed
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage failed;

/*********************************
 * Legato Image Asset
 * Name:   MLlogo
 * Size:   92x105 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage MLlogo;

/*********************************
 * Legato Image Asset
 * Name:   clear
 * Size:   448x448 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage clear;

/*****************************************************************************
 * Legato Graphics Font Assets
 *****************************************************************************/
/*********************************
 * Legato Font Asset
 * Name:         NotoSans_16
 * Height:       21
 * Baseline:     15
 * Style:        Antialias
 * Glyph Count:  10
 * Range Count:  9
 * Glyph Ranges: 0x20
                 0x44
                 0x52
                 0x63
                 0x65
                 0x67
                 0x69
                 0x6E-0x6F
                 0x74
***********************************/
extern leRasterFont NotoSans_16;

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   1
 *****************************************************************************/

// language IDs
#define language_English    0

// string IDs
#define stringID_DigitRecognition    0

extern const leStringTable stringTable;


// string list
extern leTableString string_DigitRecognition;

void initializeStrings(void);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* LE_GEN_ASSETS_H */
