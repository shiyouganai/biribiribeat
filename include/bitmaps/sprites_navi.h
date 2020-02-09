/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring Navi's sprites.
 */
#ifndef SPRITES_NAVI_H
#define SPRITES_NAVI_H

#include <Arduino.h>

#define MENU_NAVI_X 6
#define MENU_NAVI_Y 13
#define PLAY_NAVI_X 2
#define PLAY_NAVI_Y 17

#define NAVIMENUANIMNEUTRAL_XOFF 18
#define NAVIMENUANIMNEUTRAL_YOFF 31

#define NAVIMENUANIMGOOD_XOFF    11
#define NAVIMENUANIMGOOD_YOFF    20

#define NAVIMENUANIMBAD_XOFF     25
#define NAVIMENUANIMBAD_YOFF     10

#define NAVIPLAYANIMNEUTRAL_XOFF  3
#define NAVIPLAYANIMNEUTRAL_YOFF  0

#define NAVIPLAYANIMGOOD_XOFF  3
#define NAVIPLAYANIMGOOD_YOFF  0

#define NAVIPLAYANIMBAD_XOFF -2
#define NAVIPLAYANIMBAD_YOFF -8

/* uncompressed bitmaps */
extern const uint8_t PROGMEM naviMenuBgNeutral[];
extern const uint8_t PROGMEM naviMenuBgGood[];
extern const uint8_t PROGMEM naviMenuBgBad[];

extern const uint8_t PROGMEM naviPlayBgNeutral[];

extern const uint8_t PROGMEM naviMenuAnimNeutral[];
extern const uint8_t PROGMEM naviMenuAnimGood[];
extern const uint8_t PROGMEM naviMenuAnimBad[];

extern const uint8_t PROGMEM naviPlayAnimNeutral[];
extern const uint8_t PROGMEM naviPlayAnimGood[];
extern const uint8_t PROGMEM naviPlayAnimBad[];

#endif