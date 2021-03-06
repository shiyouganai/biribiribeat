/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining small button and arrow sprites.
 */
#include "bitmaps/sprites_buttons.h"

const unsigned char PROGMEM upArrow[] =
{
// width, height,
13, 16,
0x00, 0xc0, 0x60, 0x30, 0x98, 0x8c, 0x06, 0x06, 0x8c, 0x98, 0x30, 0x60, 0xc0, 
0x00, 0x01, 0x03, 0x01, 0x00, 0x1f, 0x10, 0x10, 0x1f, 0x00, 0x01, 0x03, 0x01, 
};

const unsigned char PROGMEM upArrowFilled[] =
{
// width, height,
13, 16,
0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 
0x00, 0x01, 0x03, 0x01, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x01, 0x03, 0x01, 
};

const unsigned char PROGMEM downArrow[] =
{
// width, height,
13, 16,
0x00, 0xe0, 0xb0, 0x20, 0x40, 0x7e, 0x02, 0x02, 0x7e, 0x40, 0x20, 0xb0, 0xe0, 
0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 
};

const unsigned char PROGMEM downArrowFilled[] =
{
// width, height,
13, 16,
0x00, 0xe0, 0xf0, 0xe0, 0xc0, 0xfe, 0xfe, 0xfe, 0xfe, 0xc0, 0xe0, 0xf0, 0xe0, 
0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 
};

const unsigned char PROGMEM leftArrow[] =
{
// width, height,
13, 16,
0x00, 0xc0, 0xe0, 0x30, 0x18, 0x0c, 0x06, 0x32, 0x2e, 0x24, 0x20, 0x20, 0xe0, 
0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x13, 0x1d, 0x09, 0x01, 0x01, 0x01, 
};

const unsigned char PROGMEM leftArrowFilled[] =
{
// width, height,
13, 16,
0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0xee, 0xe4, 0xe0, 0xe0, 0xe0, 
0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x1d, 0x09, 0x01, 0x01, 0x01, 
};

const unsigned char PROGMEM rightArrow[] =
{
// width, height,
13, 16,
0x00, 0xe0, 0x20, 0x20, 0x24, 0x2e, 0x32, 0x06, 0x0c, 0x18, 0x30, 0xe0, 0xc0, 
0x00, 0x01, 0x01, 0x01, 0x09, 0x1d, 0x13, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 
};

const unsigned char PROGMEM rightArrowFilled[] =
{
// width, height,
13, 16,
0x00, 0xe0, 0xe0, 0xe0, 0xe4, 0xee, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 
0x00, 0x01, 0x01, 0x01, 0x09, 0x1d, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 
};

const unsigned char PROGMEM aTile[] =
{
// width, height,
13, 16,
0x00, 0xfc, 0x02, 0x02, 0xfa, 0xfa, 0x9a, 0x9a, 0xfa, 0xfa, 0x02, 0x02, 0xfc, 
0x00, 0x0f, 0x10, 0x10, 0x17, 0x17, 0x10, 0x10, 0x17, 0x17, 0x10, 0x10, 0x0f, 
};

const unsigned char PROGMEM aTileFilled[] =
{
// width, height,
13, 16,
0x00, 0xfc, 0xfe, 0xfe, 0x06, 0x06, 0x66, 0x66, 0x06, 0x06, 0xfe, 0xfe, 0xfc, 
0x00, 0x0f, 0x1f, 0x1f, 0x18, 0x18, 0x1f, 0x1f, 0x18, 0x18, 0x1f, 0x1f, 0x0f, 
};

const unsigned char PROGMEM bTile[] =
{
// width, height,
13, 16,
0x00, 0xfc, 0x02, 0x02, 0xfa, 0xfa, 0x9a, 0x9a, 0xfa, 0x72, 0x02, 0x02, 0xfc, 
0x00, 0x0f, 0x10, 0x10, 0x17, 0x17, 0x14, 0x14, 0x17, 0x13, 0x10, 0x10, 0x0f, 
};

const unsigned char PROGMEM bTileFilled[] =
{
// width, height,
13, 16,
0x00, 0xfc, 0xfe, 0xfe, 0x06, 0x06, 0x66, 0x66, 0x06, 0x8e, 0xfe, 0xfe, 0xfc, 
0x00, 0x0f, 0x1f, 0x1f, 0x18, 0x18, 0x1b, 0x1b, 0x18, 0x1c, 0x1f, 0x1f, 0x0f, 
};

const unsigned char PROGMEM abTileMask[] =
{
0x00, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 
0x00, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 
};