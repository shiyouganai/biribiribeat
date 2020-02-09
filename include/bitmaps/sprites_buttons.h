/**
 * \file
 * \author originator: tytydraco, derivatives by: shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring small button and arrow sprites.
 */
#ifndef SPRITES_BUTTONS_H
#define SPRITES_BUTTONS_H

#include <Arduino.h>

#define SMALL_BUTTON_SPRITE_HEIGHT 13
#define SMALL_BUTTON_SPRITE_WIDTH  13

extern const uint8_t PROGMEM upArrow[];
extern const uint8_t PROGMEM upArrowFilled[];
extern const uint8_t PROGMEM downArrow[];
extern const uint8_t PROGMEM downArrowFilled[];
extern const uint8_t PROGMEM leftArrow[];
extern const uint8_t PROGMEM leftArrowFilled[];
extern const uint8_t PROGMEM rightArrow[];
extern const uint8_t PROGMEM rightArrowFilled[];
extern const uint8_t PROGMEM aTile[];
extern const uint8_t PROGMEM aTileFilled[];
extern const uint8_t PROGMEM bTile[];
extern const uint8_t PROGMEM bTileFilled[];
extern const uint8_t PROGMEM abTileMask[];

#endif