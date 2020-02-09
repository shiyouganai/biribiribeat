/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring navigator class.
 */
#ifndef NAVI_H
#define NAVI_H

#include "entity.h"
#include "bitmaps/sprites_navi.h"

#define NAVI_NUM_EXPRESSIONS 6

enum navi_expression_e
{
    MENU_NEUTRAL,
    MENU_POSITIVE,
    MENU_NEGATIVE,
    PLAYING_NEUTRAL,
    PLAYING_POSITIVE,
    PLAYING_NEGATIVE,
    END_OF_NAVI_EXPRESSION_E
};

class navi: public entity
{
    private:
        const uint8_t *const bgsprite_table[NAVI_NUM_EXPRESSIONS] = 
                {&naviMenuBgNeutral[0],
                 &naviMenuBgGood[0],
                 &naviMenuBgBad[0],
                 &naviPlayBgNeutral[0],
                 &naviPlayBgNeutral[0],
                 &naviPlayBgNeutral[0]};
        const uint8_t *const anisprite_table[NAVI_NUM_EXPRESSIONS] = 
                {&naviMenuAnimNeutral[0],
                 &naviMenuAnimGood[0],
                 &naviMenuAnimBad[0],
                 &naviPlayAnimNeutral[0],
                 &naviPlayAnimGood[0],
                 &naviPlayAnimBad[0]};
        const coord_2d bg_offset_table[NAVI_NUM_EXPRESSIONS] =
                {{0, 0},
                 {-5, 0},
                 {0, 0},
                 {0, 32},
                 {0, 32},
                 {0, 32}};
        const coord_2d ani_offset_table[NAVI_NUM_EXPRESSIONS] =
                {{NAVIMENUANIMNEUTRAL_XOFF, NAVIMENUANIMNEUTRAL_YOFF},
                 {NAVIMENUANIMGOOD_XOFF,    NAVIMENUANIMGOOD_YOFF   },
                 {NAVIMENUANIMBAD_XOFF,     NAVIMENUANIMBAD_YOFF    },
                 {NAVIPLAYANIMNEUTRAL_XOFF, NAVIPLAYANIMNEUTRAL_YOFF},
                 {NAVIPLAYANIMGOOD_XOFF,    NAVIPLAYANIMGOOD_YOFF   },
                 {NAVIPLAYANIMBAD_XOFF,     NAVIPLAYANIMBAD_YOFF    }};
        const uint8_t frame_count_table[NAVI_NUM_EXPRESSIONS] =
                {2U,
                 2U,
                 2U,
                 2U,
                 2U,
                 2U};
        navi_expression_e expression;
        uint8_t           frame_curr;
        int16_t           ticks_until_change;

    public:
        navi();
        void              change_expression(navi_expression_e new_expression);
        navi_expression_e get_expression();
        void              init(int8_t x_pos, int8_t y_pos, navi_expression_e expression);
        void              init(int8_t x_pos, int8_t y_pos, navi_expression_e expression, uint8_t ticks_per_beat);
        void              draw() override;
        void              update(uint16_t ticks_delta, uint8_t ticks_per_beat) override;
};

#endif
