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
 * Legato Graphics Asset Location IDs
 *****************************************************************************/

/*****************************************************************************
 * Legato Graphics Image Assets
 *****************************************************************************/
/*********************************
 * Legato Image Asset
 * Name:   Microchip_logo_150x30
 * Size:   150x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Microchip_logo_150x30;

/*********************************
 * Legato Image Asset
 * Name:   TouchML
 * Size:   89x100 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage TouchML;

/*********************************
 * Legato Image Asset
 * Name:   one
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage one;

/*********************************
 * Legato Image Asset
 * Name:   two
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage two;

/*********************************
 * Legato Image Asset
 * Name:   three
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage three;

/*********************************
 * Legato Image Asset
 * Name:   four
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage four;

/*********************************
 * Legato Image Asset
 * Name:   five
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage five;

/*********************************
 * Legato Image Asset
 * Name:   six
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage six;

/*********************************
 * Legato Image Asset
 * Name:   seven
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage seven;

/*********************************
 * Legato Image Asset
 * Name:   eight
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage eight;

/*********************************
 * Legato Image Asset
 * Name:   nine
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage nine;

/*********************************
 * Legato Image Asset
 * Name:   zero
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage zero;

/*********************************
 * Legato Image Asset
 * Name:   failed
 * Size:   102x150 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage failed;

/*****************************************************************************
 * Legato Graphics Font Assets
 *****************************************************************************/
/*********************************
 * Legato Font Asset
 * Name:         TitleFont
 * Height:       21
 * Baseline:     13
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  13
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont TitleFont;

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   2
 *****************************************************************************/

// language IDs
#define language_default    0

// string IDs
#define stringID_StartDrawing    0
#define stringID_TouchTitle    1

extern const leStringTable stringTable;


// string list
extern leTableString string_StartDrawing;
extern leTableString string_TouchTitle;

void initializeStrings(void);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* LE_GEN_ASSETS_H */
