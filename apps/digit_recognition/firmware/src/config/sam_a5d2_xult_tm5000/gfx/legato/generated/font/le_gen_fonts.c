#include "gfx/legato/generated/le_gen_assets.h"

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
 *********************************/
/*********************************
 * font glyph kerning table description
 *
 * unsigned int - number of glyphs
 * for each glyph:
 *     unsigned short - codepoint         * the glyph's codepoint
 *     short          - width             * the glyph's width in pixels
 *     short          - height            * the glyph's height in pixels
 *     short          - advance           * the glyph's advance value in pixels
 *     short          - bearingX          * the glyph's bearing value in pixels on the X axis
 *     short          - bearingY          * the glyph's bearing value in pixels on the Y axis
 *     unsigned short - flags             * status flags for this glyph
 *     unsigned short - data row width    * the size of a row of glyph data in bytes
 *     unsigned int   - data table offset * the offset into the corresponding font data table
 ********************************/
const uint8_t NotoSans_16_data[204] =
{
    0x0A,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x00,0x0D,0x00,0x0E,0x00,0x0F,0x00,
    0x01,0x00,0x0E,0x00,0x00,0x00,0x0D,0x00,0x00,0x00,0x00,0x00,0x52,0x00,0x0C,0x00,
    0x0E,0x00,0x0C,0x00,0x01,0x00,0x0E,0x00,0x00,0x00,0x0C,0x00,0xB8,0x00,0x00,0x00,
    0x63,0x00,0x08,0x00,0x0B,0x00,0x0A,0x00,0x01,0x00,0x0B,0x00,0x00,0x00,0x08,0x00,
    0x60,0x01,0x00,0x00,0x65,0x00,0x0A,0x00,0x0B,0x00,0x0B,0x00,0x01,0x00,0x0B,0x00,
    0x00,0x00,0x0A,0x00,0xB8,0x01,0x00,0x00,0x67,0x00,0x0A,0x00,0x10,0x00,0x0C,0x00,
    0x01,0x00,0x0B,0x00,0x00,0x00,0x0A,0x00,0x28,0x02,0x00,0x00,0x69,0x00,0x03,0x00,
    0x0F,0x00,0x05,0x00,0x01,0x00,0x0F,0x00,0x00,0x00,0x03,0x00,0xC8,0x02,0x00,0x00,
    0x6E,0x00,0x0A,0x00,0x0B,0x00,0x0C,0x00,0x01,0x00,0x0B,0x00,0x00,0x00,0x0A,0x00,
    0xF8,0x02,0x00,0x00,0x6F,0x00,0x0B,0x00,0x0B,0x00,0x0C,0x00,0x01,0x00,0x0B,0x00,
    0x00,0x00,0x0B,0x00,0x68,0x03,0x00,0x00,0x74,0x00,0x07,0x00,0x0E,0x00,0x07,0x00,
    0x00,0x00,0x0E,0x00,0x00,0x00,0x07,0x00,0xE4,0x03,0x00,0x00,
};

/*********************************
 * raw font glyph data
 ********************************/
const uint8_t NotoSans_16_glyphs[1096] =
{
    0x10,0xFF,0xFF,0xFF,0xFF,0xFA,0xE2,0xBC,0x68,0x0C,0x00,0x00,0x00,0x10,0xFF,0xDA,
    0x74,0x74,0x7B,0x98,0xDB,0xFF,0xDD,0x37,0x00,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,
    0x00,0x01,0x60,0xF7,0xED,0x20,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,
    0x62,0xFF,0xAA,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xE2,0xF8,
    0x11,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA5,0xFF,0x3B,0x10,0xFF,
    0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8B,0xFF,0x55,0x10,0xFF,0xBC,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x8F,0xFF,0x53,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xAC,0xFF,0x3B,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xEB,
    0xF8,0x08,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0xFF,0x9D,0x00,0x10,
    0xFF,0xBC,0x00,0x00,0x00,0x00,0x06,0x76,0xFC,0xE5,0x1A,0x00,0x10,0xFF,0xDA,0x74,
    0x74,0x81,0xA4,0xE8,0xFF,0xD4,0x29,0x00,0x00,0x10,0xFF,0xFF,0xFF,0xFF,0xF6,0xE1,
    0xAE,0x5A,0x05,0x00,0x00,0x00,0x00,0x00,0x10,0xFF,0xFF,0xFF,0xFF,0xF7,0xDD,0xA2,
    0x30,0x00,0x00,0x00,0x10,0xFF,0xDA,0x74,0x74,0x87,0xB4,0xFD,0xFA,0x44,0x00,0x00,
    0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x4A,0xFF,0xD0,0x00,0x00,0x10,0xFF,0xBC,0x00,
    0x00,0x00,0x00,0x00,0xE2,0xFF,0x07,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,
    0xDA,0xFF,0x08,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x29,0xFC,0xD0,0x00,0x00,
    0x10,0xFF,0xC5,0x24,0x24,0x36,0x66,0xE1,0xF8,0x41,0x00,0x00,0x10,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xBB,0x30,0x00,0x00,0x00,0x10,0xFF,0xD1,0x50,0x50,0x75,0xFF,0xA2,
    0x00,0x00,0x00,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,0xB3,0xFF,0x45,0x00,0x00,0x00,
    0x10,0xFF,0xBC,0x00,0x00,0x00,0x20,0xF6,0xDE,0x0A,0x00,0x00,0x10,0xFF,0xBC,0x00,
    0x00,0x00,0x00,0x7B,0xFF,0x8B,0x00,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x06,
    0xD8,0xFC,0x32,0x00,0x10,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,0x43,0xFF,0xCE,0x03,
    0x00,0x00,0x59,0xC1,0xEE,0xF4,0xD7,0x88,0x00,0x94,0xFF,0xD3,0x84,0x85,0xBA,0x96,
    0x44,0xFF,0xB8,0x04,0x00,0x00,0x00,0x00,0xA3,0xFF,0x35,0x00,0x00,0x00,0x00,0x00,
    0xCF,0xFA,0x03,0x00,0x00,0x00,0x00,0x00,0xE2,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
    0xD2,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0xAA,0xFF,0x3C,0x00,0x00,0x00,0x00,0x00,
    0x4F,0xFF,0xB9,0x02,0x00,0x00,0x00,0x02,0x00,0xA5,0xFF,0xCE,0x80,0x82,0xA7,0xB6,
    0x00,0x01,0x6A,0xCB,0xF3,0xFA,0xDA,0x72,0x00,0x00,0x5E,0xCA,0xF3,0xED,0xB7,0x3D,
    0x00,0x00,0x00,0x8C,0xFF,0xBD,0x80,0x8D,0xE5,0xFC,0x50,0x00,0x3A,0xFF,0x86,0x00,
    0x00,0x00,0x14,0xEB,0xE2,0x02,0x9B,0xFF,0x35,0x24,0x24,0x24,0x24,0xB3,0xFF,0x2B,
    0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x42,0xE2,0xF9,0x50,0x50,0x50,0x50,
    0x50,0x50,0x50,0x15,0xD1,0xFF,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA1,0xFF,
    0x5A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3D,0xFF,0xDB,0x13,0x00,0x00,0x00,0x00,
    0x1F,0x00,0x00,0x84,0xFF,0xE8,0x90,0x7B,0x97,0xD0,0xC8,0x00,0x00,0x00,0x4F,0xBA,
    0xEB,0xFC,0xED,0xBB,0x5A,0x00,0x00,0x00,0x00,0x07,0x81,0xDF,0xF9,0xDE,0x81,0x07,
    0xDF,0x98,0x00,0xB0,0xFF,0xC7,0x7D,0x95,0xE3,0xB8,0xFD,0x98,0x50,0xFF,0xB7,0x01,
    0x00,0x00,0x12,0xD2,0xFF,0x98,0xA9,0xFF,0x3C,0x00,0x00,0x00,0x00,0x61,0xFF,0x98,
    0xD7,0xFF,0x08,0x00,0x00,0x00,0x00,0x31,0xFF,0x98,0xE4,0xF2,0x00,0x00,0x00,0x00,
    0x00,0x21,0xFF,0x98,0xD8,0xFE,0x06,0x00,0x00,0x00,0x00,0x28,0xFF,0x98,0xAD,0xFF,
    0x38,0x00,0x00,0x00,0x00,0x50,0xFF,0x98,0x58,0xFF,0xAF,0x00,0x00,0x00,0x08,0xBF,
    0xFF,0x98,0x02,0xBB,0xFF,0xC3,0x7C,0x8F,0xDA,0xCA,0xFF,0x98,0x00,0x0A,0x87,0xE0,
    0xFA,0xE2,0x88,0x2C,0xFF,0x98,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2E,0xFF,0x92,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5A,0xFF,0x79,0x05,0x28,0x00,0x00,0x00,0x00,
    0x0E,0xD4,0xFF,0x35,0x10,0xFF,0xC7,0x99,0x7F,0x8E,0xE0,0xFF,0xA5,0x00,0x05,0x85,
    0xC9,0xE7,0xF9,0xF4,0xCD,0x70,0x03,0x00,0x3F,0xF2,0x67,0x51,0xFF,0x7F,0x00,0x12,
    0x00,0x00,0x00,0x00,0x4C,0xFF,0x74,0x4C,0xFF,0x74,0x4C,0xFF,0x74,0x4C,0xFF,0x74,
    0x4C,0xFF,0x74,0x4C,0xFF,0x74,0x4C,0xFF,0x74,0x4C,0xFF,0x74,0x4C,0xFF,0x74,0x4C,
    0xFF,0x74,0x4C,0xFF,0x74,0x00,0x00,0x00,0x4C,0xFF,0x33,0x53,0xC6,0xF5,0xE8,0xB8,
    0x33,0x00,0x4C,0xFF,0xB6,0xF2,0x99,0x7B,0xA0,0xFB,0xF8,0x2A,0x4C,0xFF,0xFD,0x2E,
    0x00,0x00,0x00,0x64,0xFF,0x8E,0x4C,0xFF,0xB7,0x00,0x00,0x00,0x00,0x14,0xFF,0xB4,
    0x4C,0xFF,0x8A,0x00,0x00,0x00,0x00,0x00,0xFF,0xBC,0x4C,0xFF,0x75,0x00,0x00,0x00,
    0x00,0x00,0xFF,0xBC,0x4C,0xFF,0x74,0x00,0x00,0x00,0x00,0x00,0xFF,0xBC,0x4C,0xFF,
    0x74,0x00,0x00,0x00,0x00,0x00,0xFF,0xBC,0x4C,0xFF,0x74,0x00,0x00,0x00,0x00,0x00,
    0xFF,0xBC,0x4C,0xFF,0x74,0x00,0x00,0x00,0x00,0x00,0xFF,0xBC,0x4C,0xFF,0x74,0x00,
    0x00,0x00,0x00,0x00,0xFF,0xBC,0x00,0x00,0x00,0x00,0x5F,0xC7,0xF3,0xF3,0xC9,0x63,
    0x00,0x00,0x00,0x00,0x98,0xFF,0xD0,0x83,0x7F,0xC7,0xFF,0xA3,0x00,0x00,0x48,0xFF,
    0xB9,0x03,0x00,0x00,0x00,0xA4,0xFF,0x58,0x00,0xA7,0xFF,0x3D,0x00,0x00,0x00,0x00,
    0x22,0xFE,0xBB,0x00,0xD6,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0xE9,0xEB,0x00,0xE2,
    0xF3,0x00,0x00,0x00,0x00,0x00,0x00,0xD3,0xFD,0x00,0xCE,0xFF,0x09,0x00,0x00,0x00,
    0x00,0x00,0xEA,0xF0,0x00,0x9B,0xFF,0x43,0x00,0x00,0x00,0x00,0x26,0xFF,0xBE,0x00,
    0x38,0xFE,0xBE,0x04,0x00,0x00,0x00,0xA6,0xFF,0x5C,0x00,0x00,0x81,0xFF,0xD2,0x82,
    0x7E,0xC6,0xFF,0xA8,0x00,0x00,0x00,0x00,0x52,0xC1,0xF1,0xF6,0xCC,0x69,0x02,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x4C,0x00,0x00,0x00,0x00,0x00,0xBD,0x98,0x00,
    0x00,0x00,0x00,0x14,0xFA,0x98,0x00,0x00,0x00,0x69,0xEF,0xFF,0xFF,0xFF,0xFF,0xB4,
    0x4F,0x89,0xFF,0xC7,0x74,0x74,0x51,0x00,0x28,0xFF,0x98,0x00,0x00,0x00,0x00,0x28,
    0xFF,0x98,0x00,0x00,0x00,0x00,0x28,0xFF,0x98,0x00,0x00,0x00,0x00,0x28,0xFF,0x98,
    0x00,0x00,0x00,0x00,0x28,0xFF,0x98,0x00,0x00,0x00,0x00,0x26,0xFF,0x9A,0x00,0x00,
    0x00,0x00,0x13,0xFF,0xC5,0x00,0x00,0x00,0x00,0x00,0xC7,0xFF,0xAD,0x7A,0x74,0x00,
    0x00,0x1F,0xB5,0xF4,0xF5,0xA0,0x00,0x00,
};

leRasterFont NotoSans_16 =
{
    {
        {
            LE_STREAM_LOCATION_ID_INTERNAL, // data location id
            (void*)NotoSans_16_glyphs, // glyph table variable pointer
            1096, // data size
        },
        LE_RASTER_FONT,
    },
    21,
    15,
    LE_FONT_BPP_8, // bits per pixel
    NotoSans_16_data, // kerning table
};

