/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining navigator class.
 */
#include "navi.h"
#include "Arduboy2.h"

/* global variables */
extern Sprites sprites;
extern Arduboy2Base arduboy;

navi::navi(void)
{
    x_pos = 0;
    y_pos = 0;
    expression = MENU_NEUTRAL;
    frame_curr = 0;
    ticks_until_change = 0;
}

void navi::change_expression(navi_expression_e new_expression)
{
    this->expression = new_expression;
}

navi_expression_e navi::get_expression()
{
    return this->expression;
}

void navi::init(int8_t x_pos, int8_t y_pos, navi_expression_e expression, uint8_t ticks_per_beat)
{
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->expression = expression;
    this->ticks_until_change = (int16_t)ticks_per_beat;
    this->frame_curr = 0;
}

void navi::draw(void)
{
    if(NULL != bgsprite_table[expression])
    {
        sprites.drawSelfMasked(x_pos + bg_offset_table[expression].x,
                               y_pos + bg_offset_table[expression].y,
                               bgsprite_table[expression],
                               0U);
    }

    if(NULL != anisprite_table[expression])
    {
        /* special handling for playing navigators, because the 'frames'
         * are just moving the sprite's coords and not actually using a
         * multi-frame spritesheet (to save ROM) */
        if((PLAYING_NEUTRAL  == expression) ||
           (PLAYING_POSITIVE == expression) ||
           (PLAYING_NEGATIVE == expression))
        {
            sprites.drawSelfMasked(x_pos + ani_offset_table[expression].x,
                                   y_pos + ani_offset_table[expression].y + frame_curr,
                                   anisprite_table[expression],
                                   0U);
        } else
        {
            sprites.drawSelfMasked(x_pos + ani_offset_table[expression].x,
                                   y_pos + ani_offset_table[expression].y,
                                   anisprite_table[expression],
                                   frame_curr);
        }
    }
}

void navi::update(uint16_t ticks_delta, uint8_t ticks_per_beat)
{
    ticks_until_change = ticks_until_change - (int16_t)ticks_delta;
    if(0 >= ticks_until_change)
    {
        frame_curr++;
        if(frame_count_table[expression] == frame_curr) {
            frame_curr = 0;
        }
        ticks_until_change = ticks_per_beat + ticks_until_change;
    }
}