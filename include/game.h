/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring the main game class.
 */
#ifndef GAME_H
#define GAME_H

#include "gamestates.h"

/**
 * \brief The main game class.
 * 
 * This class contains all the game's procedural logic to run, as well as an
 * invocation point for the main game loop.
 */
class game
{
private:
    gamestate_e                 state_next, state_curr;          /**< Used to store state machine metadata. */
    base_state                 *state_table[END_OF_GAMESTATE_E]; /**< A table of pointers to each discrete state class. */
    game_run_init               state_run_init;                  /**< Member variable for run_init state */
    game_run_playing            state_run_playing;               /**< Member variable for run_playing state */
    game_menu_main              state_menu_main;                 /**< Member variable for menu_main state */
    game_menu_config            state_menu_config;               /**< Member variable for menu_config state */
    game_menu_manual            state_menu_manual;               /**< Member variable for menu_manual state */
    game_menu_select_mode       state_menu_select_mode;          /**< Member variable for menu_select_mode state */
    game_menu_select_difficulty state_menu_select_difficulty;    /**< Member variable for menu_select_difficulty state */
    game_menu_result            state_menu_result;               /**< Member variable for menu_result state */

public:
    game();
    ~game();

    /**
     * \brief Run the game.
     * 
     * This function runs the game, and should be called when all non-game setup is complete by the main program.
     * \warning _This function does not return!_
     */
    void loop();
};

#endif