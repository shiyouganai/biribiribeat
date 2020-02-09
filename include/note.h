/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring note class.
 */
#ifndef NOTE_H
#define NOTE_H

#include "entity.h"
#include "rhythm_manager.h"

class note: public entity
{
    private:
        uint16_t hit_tick;
    public:
        note();
        void init(int16_t x_pos, int16_t y_pos, uint16_t hit_tick,
                  uint8_t button);
        void draw() override;
        void update(uint16_t ticks_delta, uint8_t pixels_per_tick) override;
        int16_t get_ticks_to_hit(uint16_t ticks_curr);
        timing_e grade;
        uint8_t button;
};

#endif