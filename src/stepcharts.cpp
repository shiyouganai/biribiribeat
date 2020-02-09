/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining the game's step charts (player inputs).
 */
#include "Arduboy2.h"
#include "audio/stepcharts.h"
#include "audio/melodys.h"

/* FULL CHART EASY */
const uint8_t PROGMEM steps_easy_00[] = 
{
    UP_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON, PEOM, //QUARTERS
    UP_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON, PEOM, //QUARTERS
    UP_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON, PEOM, //QUARTERS
    UP_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_00 =
{
    &steps_easy_00[0]
};

const uint8_t PROGMEM steps_easy_01[] = 
{
    DOWN_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON,
    RIGHT_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON,
    A_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON,
    RIGHT_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_01 =
{
    &steps_easy_01[0]
};

const uint8_t PROGMEM steps_easy_02[] = 
{
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    RIGHT_BUTTON | B_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_02 =
{
    &steps_easy_02[0]
};

const uint8_t PROGMEM steps_easy_03[] = 
{
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON | A_BUTTON,
    RIGHT_BUTTON | A_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_03 =
{
    &steps_easy_03[0]
};

const uint8_t PROGMEM steps_easy_04[] = 
{
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    RIGHT_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    LEFT_BUTTON,
    A_BUTTON,
    LEFT_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_04 =
{
    &steps_easy_04[0]
};

const uint8_t PROGMEM steps_easy_05[] = 
{
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    RIGHT_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    LEFT_BUTTON | B_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_05 =
{
    &steps_easy_05[0]
};

const uint8_t PROGMEM steps_easy_06[] = 
{
    LEFT_BUTTON | B_BUTTON,
    DOWN_BUTTON | A_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    DOWN_BUTTON | A_BUTTON, PEOM, //QUARTERS
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON,
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON | A_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON,
    DOWN_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON | A_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON,
    DOWN_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_06 =
{
    &steps_easy_06[0]
};

const uint8_t PROGMEM steps_easy_07[] = 
{
    LEFT_BUTTON | B_BUTTON,
    DOWN_BUTTON | A_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    DOWN_BUTTON | A_BUTTON, PEOM, //QUARTERS
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON,
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON | A_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON,
    DOWN_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON | B_BUTTON,
    LEFT_BUTTON | B_BUTTON, PEOM, //HALVES
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_easy_07 =
{
    &steps_easy_07[0]
};

/* FULL CHART MEDI */
const uint8_t PROGMEM steps_medi_00[] = 
{
    UP_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    UP_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON, PEOM, //QUARTERS
    UP_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    UP_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    B_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_medi_00 =
{
    &steps_medi_00[0]
};

const uint8_t PROGMEM steps_medi_01[] = 
{
    DOWN_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    DOWN_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON,
    A_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    DOWN_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    B_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_medi_01 =
{
    &steps_medi_01[0]
};

const uint8_t PROGMEM steps_medi_02[] = 
{
    LEFT_BUTTON,
    A_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, 
    UP_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, 
    UP_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    RIGHT_BUTTON | B_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_medi_02 =
{
    &steps_medi_02[0]
};

const uint8_t PROGMEM steps_medi_03[] = 
{
    LEFT_BUTTON,
    A_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, 
    UP_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    LEFT_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    A_BUTTON,
    DOWN_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, 
    UP_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    RIGHT_BUTTON | B_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    UP_BUTTON | A_BUTTON,
    UP_BUTTON | A_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_medi_03 =
{
    &steps_medi_03[0]
};

const uint8_t PROGMEM steps_medi_04[] = 
{
    LEFT_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    A_BUTTON,
    UP_BUTTON,
    A_BUTTON, PEOM, //EIGHTHS
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    B_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    LEFT_BUTTON,
    A_BUTTON,
    LEFT_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_medi_04 =
{
    &steps_medi_04[0]
};

const uint8_t PROGMEM steps_medi_05[] = 
{
    LEFT_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    A_BUTTON,
    UP_BUTTON,
    A_BUTTON, PEOM, //EIGHTHS
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    B_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    LEFT_BUTTON | B_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_medi_05 =
{
    &steps_medi_05[0]
};

/* FULL CHART HARD */
const uint8_t PROGMEM steps_hard_00[] = 
{
    UP_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //SIXTEENTHS
    UP_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON, PEOM, //QUARTERS
    UP_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    UP_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    B_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_00 =
{
    &steps_hard_00[0]
};

const uint8_t PROGMEM steps_hard_01[] = 
{
    DOWN_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //SIXTEENTHS
    DOWN_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON,
    A_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    DOWN_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    B_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_01 =
{
    &steps_hard_01[0]
};

const uint8_t PROGMEM steps_hard_02_00[] = 
{
    LEFT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    B_BUTTON, 
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    B_BUTTON,
    B_BUTTON, PEOM, //SIXTEENTHS
    LEFT_BUTTON,
    UP_BUTTON | A_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    DOWN_BUTTON | B_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    B_BUTTON, 
    NO_BUTTON,
    UP_BUTTON,
    NO_BUTTON,
    B_BUTTON,
    B_BUTTON, PEOM, //SIXTEENTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_02_00 =
{
    &steps_hard_02_00[0]
};

const uint8_t PROGMEM steps_hard_02_01[] = 
{
    LEFT_BUTTON,
    A_BUTTON,
    LEFT_BUTTON | A_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    B_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    B_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_02_01 =
{
    &steps_hard_02_01[0]
};

const uint8_t PROGMEM steps_hard_03[] = 
{
    RIGHT_BUTTON | B_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    UP_BUTTON | A_BUTTON,
    UP_BUTTON | A_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_03 =
{
    &steps_hard_03[0]
};

const uint8_t PROGMEM steps_hard_04_00[] = 
{
    LEFT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    LEFT_BUTTON,
    A_BUTTON,
    DOWN_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    NO_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    RIGHT_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    NO_BUTTON, PEOM, //SIXTEENTHS
    DOWN_BUTTON,
    A_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    NO_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON,
    UP_BUTTON, PEOM, //SIXTEENTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_04_00 =
{
    &steps_hard_04_00[0]
};

const uint8_t PROGMEM steps_hard_04_01[] = 
{
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    NO_BUTTON,
    RIGHT_BUTTON,
    NO_BUTTON,
    A_BUTTON,
    LEFT_BUTTON,
    A_BUTTON,
    LEFT_BUTTON, PEOM, //EIGHTHS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_04_01 =
{
    &steps_hard_04_01[0]
};

const uint8_t PROGMEM steps_hard_05[] = 
{
    LEFT_BUTTON,
    UP_BUTTON,
    A_BUTTON,
    B_BUTTON, PEOM, //QUARTERS
    DOWN_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    LEFT_BUTTON | B_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_05 =
{
    &steps_hard_05[0]
};

const uint8_t PROGMEM steps_hard_06[] = 
{
    LEFT_BUTTON | B_BUTTON,
    UP_BUTTON,
    DOWN_BUTTON | A_BUTTON,
    UP_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON | A_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON,
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON | A_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON,
    DOWN_BUTTON,
    LEFT_BUTTON | A_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON,
    DOWN_BUTTON, PEOM, //EIGHTS
    LEFT_BUTTON | B_BUTTON,
    DOWN_BUTTON,
    RIGHT_BUTTON,
    UP_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    DOWN_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    UP_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_06 =
{
    &steps_hard_06[0]
};

const uint8_t PROGMEM steps_hard_07[] = 
{
    LEFT_BUTTON | B_BUTTON,
    UP_BUTTON,
    DOWN_BUTTON | A_BUTTON,
    UP_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    NO_BUTTON,
    DOWN_BUTTON | A_BUTTON,
    NO_BUTTON, PEOM, //EIGHTHS
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON,
    UP_BUTTON | DOWN_BUTTON,
    LEFT_BUTTON | RIGHT_BUTTON, PEOM, //QUARTERS
    LEFT_BUTTON | A_BUTTON,
    UP_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON,
    RIGHT_BUTTON | A_BUTTON,
    UP_BUTTON,
    LEFT_BUTTON,
    DOWN_BUTTON, PEOM, //EIGHTS
    RIGHT_BUTTON | B_BUTTON,
    DOWN_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON | B_BUTTON,
    DOWN_BUTTON,
    LEFT_BUTTON | B_BUTTON,
    UP_BUTTON, PEOM, //QUARTERS
    PEOF, PEOF
};

const PROGMEM step_pattern_t pattern_hard_07 =
{
    &steps_hard_07[0]
};

/* DIFFICULTY LIBRARIES */
const PROGMEM step_pattern_t *const __attribute((used)) patterns_easy[14] =
   {&pattern_easy_00,
    &pattern_easy_01,
    &pattern_easy_02,
    &pattern_easy_03,
    &pattern_easy_04,
    &pattern_easy_05,
    &pattern_easy_06,
    &pattern_easy_07,
    &pattern_easy_06,
    &pattern_easy_07,
    &pattern_easy_04,
    &pattern_easy_05,
    &pattern_easy_02,
    &pattern_easy_03};

const PROGMEM step_pattern_library_t library_easy =
{
    (sizeof(patterns_easy)/sizeof(*patterns_easy[0])),
    &patterns_easy[0]
};

const PROGMEM step_pattern_t *const __attribute((used)) patterns_medi[14] =
   {&pattern_medi_00,
    &pattern_medi_01,
    &pattern_medi_02,
    &pattern_medi_03,
    &pattern_medi_04,
    &pattern_medi_05,
    &pattern_easy_06,
    &pattern_easy_07,
    &pattern_easy_06,
    &pattern_easy_07,
    &pattern_medi_04,
    &pattern_medi_05,
    &pattern_medi_02,
    &pattern_medi_03};

const PROGMEM step_pattern_library_t library_medi =
{
    (sizeof(patterns_medi)/sizeof(*patterns_medi[0])),
    &patterns_medi[0]
};

const PROGMEM step_pattern_t *const __attribute((used)) patterns_hard[22] =
   {&pattern_hard_00, 
    &pattern_hard_01, 
    &pattern_hard_02_00, &pattern_hard_02_01, 
    &pattern_hard_02_00, &pattern_hard_03,
    &pattern_hard_04_00, &pattern_hard_04_01,
    &pattern_hard_04_00, &pattern_hard_05, 
    &pattern_hard_06,
    &pattern_hard_07,
    &pattern_hard_06,
    &pattern_hard_07, 
    &pattern_hard_04_00, &pattern_hard_04_01,
    &pattern_hard_04_00, &pattern_hard_05, 
    &pattern_hard_02_00, &pattern_hard_02_01, 
    &pattern_hard_02_00, &pattern_hard_03};

const PROGMEM step_pattern_library_t library_hard =
{
    (sizeof(patterns_hard)/sizeof(*patterns_hard[0])),
    &patterns_hard[0]
};

/* SONGS */
const PROGMEM playable_song_t playable_music_level =
{
    "DOING_IT",
    6,
    &music_level[0],
    {&library_easy, &library_medi, &library_hard},
};


