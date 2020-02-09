/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining all game menu objects.
 */
#include "menus.h"

/* Title screen menu */
#define MENU_TITLE_ENTRIES 3

const uint8_t PROGMEM title_text_1[] = "PLAY";
const uint8_t PROGMEM title_text_2[] = "OPTIONS";
const uint8_t PROGMEM title_text_3[] = "MANUAL";

entry_data title_entries[MENU_TITLE_ENTRIES] =
{
    {
        .length_text = sizeof(title_text_1) - 1U,
        .length_desc = 0U,
        .text        = (char *)&title_text_1[0],
        .desc        = NULL
    },
    {
        .length_text = sizeof(title_text_2) - 1U,
        .length_desc = 0U,
        .text        = (char *)&title_text_2[0],
        .desc        = NULL
    },
    {
        .length_text = sizeof(title_text_3) - 1U,
        .length_desc = 0U,
        .text        = (char *)&title_text_3[0],
        .desc        = NULL
    }
};

menu_data menu_title
{
    .orientation = HORIZONTAL,
    .x_start     = 9U,
    .y_start     = 57U,
    .num_entries = MENU_TITLE_ENTRIES,
    .entries     = &title_entries[0],
    .curr_entry  = 0
};

/* config screen menu */
#define MENU_CONFIG_ENTRIES 3

const uint8_t PROGMEM config_text_1[] = "SOUND";
const uint8_t PROGMEM config_text_2[] = "NOTE SPEED";
const uint8_t PROGMEM config_text_3[] = "ERASE SCORES";
const uint8_t PROGMEM config_desc_1[] = "ENABLE\nGAME AUDIO.";
const uint8_t PROGMEM config_desc_2[] = "SET NOTE\nSCROLL SPEED.";
const uint8_t PROGMEM config_desc_3[] = "ERASE ALL\nHIGH SCORES!!";

entry_data config_entries[MENU_TITLE_ENTRIES] =
{
    {
        .length_text = sizeof(config_text_1) - 1U,
        .length_desc = sizeof(config_desc_1) - 1U,
        .text        = (char *)&config_text_1[0],
        .desc        = (char *)&config_desc_1[0]
    },
    {
        .length_text = sizeof(config_text_2) - 1U,
        .length_desc = sizeof(config_desc_2) - 1U,
        .text        = (char *)&config_text_2[0],
        .desc        = (char *)&config_desc_2[0]
    },
    {
        .length_text = sizeof(config_text_3) - 1U,
        .length_desc = sizeof(config_desc_3) - 1U,
        .text        = (char *)&config_text_3[0],
        .desc        = (char *)&config_desc_3[0]
    }
};

menu_data menu_config
{
    .orientation = VERTICAL,
    .x_start     = SELECT_INFO_X,
    .y_start     = SELECT_INFO_Y,
    .num_entries = MENU_CONFIG_ENTRIES,
    .entries     = &config_entries[0],
    .curr_entry  = 0
};

/* Mode select screen menu */
#define MENU_MODE_ENTRIES 2

const uint8_t PROGMEM mode_text_1[] = "NORMAL MODE";
const uint8_t PROGMEM mode_text_2[] = "CHAOS  MODE";
const uint8_t PROGMEM mode_desc_1[] = "STANDARD\nRHYTHM\nGAMEPLAY!";
const uint8_t PROGMEM mode_desc_2[] = "FUN RANDOMLY\nGENERATED\nCHARTS!";

entry_data mode_entries[MENU_MODE_ENTRIES] =
{
    {
        .length_text = sizeof(mode_text_1) - 1U,
        .length_desc = sizeof(mode_desc_1) - 1U,
        .text        = (char *)&mode_text_1[0],
        .desc        = (char *)&mode_desc_1[0]
    },
    {
        .length_text = sizeof(mode_text_2) - 1U,
        .length_desc = sizeof(mode_desc_2) - 1U,
        .text        = (char *)&mode_text_2[0],
        .desc        = (char *)&mode_desc_2[0]
    }
};

menu_data menu_mode
{
    .orientation = VERTICAL,
    .x_start     = SELECT_INFO_X,
    .y_start     = SELECT_INFO_Y,
    .num_entries = MENU_MODE_ENTRIES,
    .entries     = &mode_entries[0],
    .curr_entry  = 0
};

/* Difficulty select screen menu */
#define MENU_DIFF_ENTRIES 3

const uint8_t PROGMEM diff_text_1[] = "EASY";
const uint8_t PROGMEM diff_text_2[] = "MEDIUM";
const uint8_t PROGMEM diff_text_3[] = "HARD";
const uint8_t PROGMEM diff_desc_hs[] = "HIGH SCORE:\n";
#if 0
const uint8_t PROGMEM diff_desc_1[] = "GOOD FOR\nBABY GAMERS.";
const uint8_t PROGMEM diff_desc_2[] = "GOOD FOR\nBASIC GAMERS.";
const uint8_t PROGMEM diff_desc_3[] = "GOOD FOR\nEPIC GAMERS!!";
#endif

entry_data diff_entries[MENU_DIFF_ENTRIES] =
{
    {
        .length_text = sizeof(diff_text_1) - 1U,
        .length_desc = sizeof(diff_desc_hs) - 1U,
        .text        = (char *)&diff_text_1[0],
        .desc        = (char *)&diff_desc_hs[0]
    },
    {
        .length_text = sizeof(diff_text_2) - 1U,
        .length_desc = sizeof(diff_desc_hs) - 1U,
        .text        = (char *)&diff_text_2[0],
        .desc        = (char *)&diff_desc_hs[0]
    },
    {
        .length_text = sizeof(diff_text_3) - 1U,
        .length_desc = sizeof(diff_desc_hs) - 1U,
        .text        = (char *)&diff_text_3[0],
        .desc        = (char *)&diff_desc_hs[0]
    }
};

menu_data menu_diff
{
    .orientation = VERTICAL,
    .x_start     = SELECT_INFO_X,
    .y_start     = SELECT_INFO_Y,
    .num_entries = MENU_DIFF_ENTRIES,
    .entries     = &diff_entries[0],
    .curr_entry  = 0
};