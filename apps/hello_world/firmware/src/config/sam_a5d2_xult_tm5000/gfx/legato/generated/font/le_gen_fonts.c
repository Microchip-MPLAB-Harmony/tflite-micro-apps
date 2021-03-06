#include "gfx/legato/generated/le_gen_assets.h"

/*********************************
 * Legato Font Asset
 * Name:         NotoSans_16
 * Height:       17
 * Baseline:     12
 * Style:        Antialias
 * Glyph Count:  10
 * Range Count:  10
 * Glyph Ranges: 0x20
                 0x44
                 0x53
                 0x61
                 0x67
                 0x69
                 0x6E
                 0x72
                 0x74
                 0x77
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
    0x0A,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x00,0x0A,0x00,0x0C,0x00,0x0C,0x00,
    0x01,0x00,0x0C,0x00,0x00,0x00,0x0A,0x00,0x00,0x00,0x00,0x00,0x53,0x00,0x09,0x00,
    0x0C,0x00,0x09,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x09,0x00,0x78,0x00,0x00,0x00,
    0x61,0x00,0x08,0x00,0x09,0x00,0x09,0x00,0x00,0x00,0x09,0x00,0x00,0x00,0x08,0x00,
    0xE4,0x00,0x00,0x00,0x67,0x00,0x09,0x00,0x0D,0x00,0x0A,0x00,0x00,0x00,0x09,0x00,
    0x00,0x00,0x09,0x00,0x2C,0x01,0x00,0x00,0x69,0x00,0x02,0x00,0x0C,0x00,0x04,0x00,
    0x01,0x00,0x0C,0x00,0x00,0x00,0x02,0x00,0xA4,0x01,0x00,0x00,0x6E,0x00,0x08,0x00,
    0x09,0x00,0x0A,0x00,0x01,0x00,0x09,0x00,0x00,0x00,0x08,0x00,0xBC,0x01,0x00,0x00,
    0x72,0x00,0x06,0x00,0x09,0x00,0x07,0x00,0x01,0x00,0x09,0x00,0x00,0x00,0x06,0x00,
    0x04,0x02,0x00,0x00,0x74,0x00,0x06,0x00,0x0B,0x00,0x06,0x00,0x00,0x00,0x0B,0x00,
    0x00,0x00,0x06,0x00,0x3C,0x02,0x00,0x00,0x77,0x00,0x0D,0x00,0x09,0x00,0x0D,0x00,
    0x00,0x00,0x09,0x00,0x00,0x00,0x0D,0x00,0x80,0x02,0x00,0x00,
};

/*********************************
 * raw font glyph data
 ********************************/
const uint8_t NotoSans_16_glyphs[760] =
{
    0x74,0xFF,0xFF,0xFF,0xF4,0xD5,0x87,0x16,0x00,0x00,0x74,0xFC,0x34,0x34,0x41,0x74,
    0xE0,0xE7,0x30,0x00,0x74,0xFC,0x00,0x00,0x00,0x00,0x0F,0xCD,0xDA,0x06,0x74,0xFC,
    0x00,0x00,0x00,0x00,0x00,0x3D,0xFF,0x50,0x74,0xFC,0x00,0x00,0x00,0x00,0x00,0x02,
    0xF2,0x91,0x74,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0xD7,0xAA,0x74,0xFC,0x00,0x00,
    0x00,0x00,0x00,0x00,0xDA,0xA8,0x74,0xFC,0x00,0x00,0x00,0x00,0x00,0x04,0xF6,0x8C,
    0x74,0xFC,0x00,0x00,0x00,0x00,0x00,0x4B,0xFF,0x4B,0x74,0xFC,0x00,0x00,0x00,0x00,
    0x18,0xDB,0xD3,0x02,0x74,0xFC,0x34,0x35,0x47,0x81,0xEA,0xE0,0x26,0x00,0x74,0xFF,
    0xFF,0xFF,0xF3,0xCC,0x7D,0x10,0x00,0x00,0x00,0x05,0x80,0xDD,0xF9,0xE8,0xC3,0x5C,
    0x00,0x00,0x96,0xF1,0x6A,0x3D,0x58,0x9C,0x6A,0x00,0x02,0xF7,0x83,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0xF7,0x8F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB0,0xF5,0x5D,
    0x02,0x00,0x00,0x00,0x00,0x00,0x18,0xC3,0xFF,0xDD,0x73,0x0B,0x00,0x00,0x00,0x00,
    0x01,0x4B,0xBB,0xFF,0xE2,0x2D,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0xE8,0xCC,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xFD,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x8F,
    0xEA,0x00,0x28,0xA2,0x61,0x42,0x41,0x81,0xFA,0x78,0x00,0x19,0xB7,0xE5,0xF7,0xEE,
    0xC6,0x56,0x00,0x00,0x00,0x14,0x8E,0xD6,0xF6,0xE1,0x84,0x01,0x00,0x14,0xC4,0x66,
    0x3F,0x82,0xFF,0x61,0x00,0x00,0x00,0x00,0x00,0x00,0xD4,0x9E,0x00,0x00,0x00,0x00,
    0x01,0x04,0xB7,0xB0,0x00,0x29,0xAE,0xEA,0xFE,0xFF,0xFF,0xB0,0x0A,0xE8,0xCE,0x59,
    0x3A,0x30,0xC6,0xB0,0x36,0xFF,0x40,0x00,0x00,0x04,0xE0,0xB0,0x16,0xF9,0xAA,0x3D,
    0x4D,0xB7,0xDF,0xB0,0x00,0x54,0xD8,0xF9,0xDC,0x61,0x70,0xB0,0x00,0x00,0x66,0xDD,
    0xF9,0xCF,0x45,0xB6,0x7C,0x00,0x50,0xFF,0x96,0x42,0x62,0xDF,0xF0,0x7C,0x00,0xCB,
    0xBD,0x00,0x00,0x00,0x44,0xFF,0x7C,0x04,0xFC,0x72,0x00,0x00,0x00,0x02,0xFB,0x7C,
    0x18,0xFF,0x5E,0x00,0x00,0x00,0x00,0xE7,0x7C,0x04,0xFC,0x71,0x00,0x00,0x00,0x00,
    0xF6,0x7C,0x00,0xD0,0xB8,0x00,0x00,0x00,0x33,0xFF,0x7C,0x00,0x57,0xFF,0x91,0x41,
    0x5B,0xD3,0xF4,0x7C,0x00,0x00,0x6D,0xDF,0xF9,0xD1,0x45,0xE5,0x7C,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xF4,0x6E,0x00,0x00,0x00,0x00,0x00,0x00,0x39,0xFF,0x49,0x00,
    0x62,0x91,0x54,0x3C,0x5D,0xE1,0xD6,0x04,0x00,0x3C,0xBC,0xE9,0xFA,0xEE,0xAD,0x22,
    0x00,0x00,0x00,0x00,0x94,0xB7,0x77,0x93,0x00,0x00,0xA4,0xC4,0xA4,0xC4,0xA4,0xC4,
    0xA4,0xC4,0xA4,0xC4,0xA4,0xC4,0xA4,0xC4,0xA4,0xC4,0xA4,0xC4,0xA4,0x92,0x5B,0xD6,
    0xF7,0xD8,0x63,0x00,0xA4,0xE8,0xD3,0x57,0x40,0x9E,0xFF,0x39,0xA4,0xFD,0x21,0x00,
    0x00,0x04,0xEB,0x7E,0xA4,0xDB,0x00,0x00,0x00,0x00,0xCD,0x96,0xA4,0xC6,0x00,0x00,
    0x00,0x00,0xCC,0x98,0xA4,0xC4,0x00,0x00,0x00,0x00,0xCC,0x98,0xA4,0xC4,0x00,0x00,
    0x00,0x00,0xCC,0x98,0xA4,0xC4,0x00,0x00,0x00,0x00,0xCC,0x98,0xA4,0xC4,0x00,0x00,
    0x00,0x00,0xCC,0x98,0xA4,0x8F,0x39,0xD1,0xF9,0x47,0xA4,0xCB,0xD8,0x61,0x3B,0x10,
    0xA4,0xFF,0x39,0x00,0x00,0x00,0xA4,0xDA,0x00,0x00,0x00,0x00,0xA4,0xC4,0x00,0x00,
    0x00,0x00,0xA4,0xC4,0x00,0x00,0x00,0x00,0xA4,0xC4,0x00,0x00,0x00,0x00,0xA4,0xC4,
    0x00,0x00,0x00,0x00,0xA4,0xC4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0xDF,0x00,
    0x00,0x00,0x00,0x69,0xE0,0x00,0x00,0x00,0x87,0xFC,0xFF,0xFF,0xFF,0x5C,0x27,0xA0,
    0xE6,0x34,0x34,0x12,0x00,0x88,0xE0,0x00,0x00,0x00,0x00,0x88,0xE0,0x00,0x00,0x00,
    0x00,0x88,0xE0,0x00,0x00,0x00,0x00,0x88,0xE0,0x00,0x00,0x00,0x00,0x82,0xEA,0x00,
    0x00,0x00,0x00,0x57,0xFF,0x78,0x3A,0x25,0x00,0x03,0x96,0xE8,0xF4,0x57,0x00,0x00,
    0xB2,0xBF,0x00,0x00,0x00,0x9E,0xFF,0x38,0x00,0x00,0x2C,0xFF,0x46,0x6F,0xF7,0x07,
    0x00,0x01,0xE9,0xF0,0x82,0x00,0x00,0x6B,0xF8,0x09,0x2C,0xFF,0x3D,0x00,0x37,0xFD,
    0x8E,0xCC,0x00,0x00,0xAA,0xBE,0x00,0x00,0xE8,0x7C,0x00,0x83,0xC9,0x3B,0xFE,0x17,
    0x00,0xE8,0x7A,0x00,0x00,0xA6,0xBB,0x00,0xCF,0x7E,0x04,0xEF,0x60,0x28,0xFF,0x36,
    0x00,0x00,0x63,0xF3,0x1B,0xFF,0x30,0x00,0xA8,0xA6,0x67,0xEF,0x02,0x00,0x00,0x20,
    0xFF,0x85,0xE1,0x00,0x00,0x5C,0xE6,0xA3,0xAE,0x00,0x00,0x00,0x00,0xDD,0xEA,0x94,
    0x00,0x00,0x14,0xFD,0xEC,0x6A,0x00,0x00,0x00,0x00,0x9A,0xFF,0x46,0x00,0x00,0x00,
    0xC6,0xFF,0x26,0x00,0x00,0x00,0x00,0x00,
};

leRasterFont NotoSans_16 =
{
    {
        {
            LE_STREAM_LOCATION_ID_INTERNAL, // data location id
            (void*)NotoSans_16_glyphs, // glyph table variable pointer
            760, // data size
        },
        LE_RASTER_FONT,
    },
    17,
    12,
    LE_FONT_BPP_8, // bits per pixel
    NotoSans_16_data, // kerning table
};

