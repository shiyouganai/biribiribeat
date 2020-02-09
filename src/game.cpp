/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining the main game class.
 */
#include "game.h"
#include "Arduino.h"

#if 0
#define DEBUG_SERIAL
#endif

game::game()
{
    state_curr                          = RUN_INIT;
    state_next                          = RUN_INIT;
    state_table[RUN_INIT]               = &state_run_init;
    state_table[RUN_PLAYING]            = &state_run_playing;
    state_table[MENU_MAIN]              = &state_menu_main;
    state_table[MENU_CONFIG]            = &state_menu_config;
    state_table[MENU_MANUAL]            = &state_menu_manual;
    state_table[MENU_SELECT_MODE]       = &state_menu_select_mode;
    state_table[MENU_SELECT_DIFFICULTY] = &state_menu_select_difficulty;
    state_table[MENU_RESULT]            = &state_menu_result;

    /* first run kick off */
    /* entry logic */
    state_table[state_next]->on_entry();
    return;
}

game::~game()
{
}

/* the current game logic is an EXTENDED STATE MACHINE
 * next state is determined by current state + state context variables + player input
 * maybe in future try a heirarchical state machine
 */
void game::loop()
{
    for(;;) {
        if(!state_table[state_curr]->next_frame()) {
            /* if it's not time to advance a frame, do nothing */
            continue;
        }
        
        /* advance game state and render frame
         * yes, game state is locked to frame rate for now */
        #ifdef DEBUG_SERIAL
        Serial.println(state_curr);
        Serial.println(state_next);
        #endif

        /* entry logic */
        if(state_next != state_curr) {
            state_table[state_next]->on_entry();
            state_curr = state_next;
        }

        /* loop logic */
        state_next = state_table[state_curr]->on_loop();
        #ifdef DEBUG_SERIAL
        Serial.println(state_curr);
        Serial.println(state_next);
        #endif

        /* exit logic */
        if(state_next != state_curr) {
            state_table[state_curr]->on_exit();
        }
    }
}