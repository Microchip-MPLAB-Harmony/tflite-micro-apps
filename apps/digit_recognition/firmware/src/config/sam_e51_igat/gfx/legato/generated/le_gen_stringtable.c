#include "gfx/legato/generated/le_gen_assets.h"

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   2
 *****************************************************************************/

/*****************************************************************************
 * string table data
 * 
 * this table contains the raw character data for each string
 * 
 * unsigned short - number of indices in the table
 * unsigned short - number of languages in the table
 * 
 * index array (size = number of indices * number of languages
 * 
 * for each index in the array:
 *   unsigned byte - the font ID for the index
 *   unsigned byte[3] - the offset of the string codepoint data in
 *                      the table
 * 
 * string data is found by jumping to the index offset from the start
 * of the table
 * 
 * string data entry:
 *     unsigned short - length of the string in bytes (encoding dependent)
 *     codepoint data - the string data
 ****************************************************************************/

const uint8_t stringTable_data[48] =
{
    0x02,0x00,0x01,0x00,0x00,0x0C,0x00,0x00,0x00,0x1C,0x00,0x00,0x0D,0x00,0x53,0x74,
    0x61,0x72,0x74,0x20,0x44,0x72,0x61,0x77,0x69,0x6E,0x67,0x00,0x11,0x00,0x44,0x69,
    0x67,0x69,0x74,0x20,0x52,0x65,0x63,0x6F,0x67,0x6E,0x69,0x74,0x69,0x6F,0x6E,0x00,
};

/* font asset pointer list */
leFont* fontList[1] =
{
    (leFont*)&TitleFont,
};

const leStringTable stringTable =
{
    {
        LE_STREAM_LOCATION_ID_INTERNAL, // data location id
        (void*)stringTable_data, // data address pointer
        48, // data size
    },
    (void*)stringTable_data, // string table data
    fontList, // font lookup table
    LE_STRING_ENCODING_ASCII // encoding standard
};


// string list
leTableString string_StartDrawing;
leTableString string_TouchTitle;

void initializeStrings(void)
{
    leTableString_Constructor(&string_StartDrawing, stringID_StartDrawing);
    leTableString_Constructor(&string_TouchTitle, stringID_TouchTitle);
}
