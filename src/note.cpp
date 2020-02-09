/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining note class.
 */
#include "note.h"
#include "Arduboy2.h"
#include "bitmaps/sprites_buttons.h"

/* global variables */
extern Sprites sprites;

note::note(void)
{
    x_pos = 0;
    y_pos = 0;
    hit_tick = 0;
    grade = UNGRADED;
    button = 0;
}

void note::draw(void)
{
    const unsigned char *sprite = NULL;
    const unsigned char *mask = NULL;
    switch (button)
    {
    case UP_BUTTON:
        sprite = upArrowFilled;
        break;
    case DOWN_BUTTON:
        sprite = downArrowFilled;
        break;
    case LEFT_BUTTON:
        sprite = leftArrowFilled;
        break;
    case RIGHT_BUTTON:
        sprite = rightArrowFilled;
        break;
    case A_BUTTON:
        sprite = aTileFilled;
        mask = abTileMask;
        break;
    case B_BUTTON:
        sprite = bTileFilled;
        mask = abTileMask;
        /* code */
        break;
    default:
        break;
    }
    /* if note should be visible */
    if(sprite != NULL) {
        /* draw us */
        if(mask != NULL) {
            sprites.drawExternalMask(x_pos, y_pos, sprite, mask, 0, 0);
        }
        sprites.drawSelfMasked(x_pos, y_pos, sprite, 0);
    }
}

void note::init(int16_t x_pos, int16_t y_pos, uint16_t hit_tick, uint8_t button)
{
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->hit_tick = hit_tick;
    this->grade = UNGRADED;
    this->button = button;
}

void note::update(uint16_t ticks_delta, uint8_t pixels_per_tick)
{
    y_pos -= pixels_per_tick * ticks_delta;
    //x_pos += pixels_per_tick * ticks_delta;
}

int16_t note::get_ticks_to_hit(uint16_t ticks_curr)
{
    return (hit_tick - (int16_t)ticks_curr);
}