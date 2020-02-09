/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring classes for game states.
 */
#ifndef GAMESTATES_H
#define GAMESTATES_H

/* Framerates defined as ms per frame. */
#define FD_15PT625FPS 64U /**< 15.625 FPS is 64ms/frame */
#define FD_31PT250FPS 32U /**< 31.250 FPS is 32ms/frame */
#define FD_62PT500FPS 16U /**< 62.500 FPS is 16ms/frame */
#define FD_66PT667FPS 15U /**< 66.667 FPS is 15ms/frame */

/**
 * \brief Enumerate the discrete game states.
 */
enum gamestate_e
{
    RUN_INIT,
    RUN_PLAYING,
    MENU_MAIN,
    MENU_CONFIG,
    MENU_MANUAL,
    MENU_SELECT_MODE,
    MENU_SELECT_DIFFICULTY,
    MENU_RESULT,
    END_OF_GAMESTATE_E
};

/**
 * \brief Abstract base state class.
 * 
 * This base class implements a heirarchical state machine, with each
 * state having three methods: entry, loop, and exit.
 * 
 * Whenever a state is transitioned into, its entry method should be called.
 * The loop method of the current state should be called every game loop, and
 * will return the next state based on its runtime calculations.
 * 
 * When a transition is determined necessary by the loop method, i.e. the
 * next state is not equal to the current state, the current state's
 * exit method should be called and the next state saved.
 * 
 * When no transition is necessary, simply loop again.
 */
class base_state
{
    private:

    public:
        /**
         * \brief Determines if it's time to draw the next frame.
         * 
         * In this engine, the state machine runs to completion once per frame.
         * 
         * This function is a frame timekeeping function. It internally
         * measures the time between frames, and will return whether enough
         * time has elapsed since the last frame to draw a new one.
         * 
         * \return True when it is time to draw the next frame.
         *         False when more time must pass before drawing the next frame.
         */
        virtual bool next_frame();

        /**
         * \brief The entry function of a state.
         * 
         * This function is part of the enter->loop->exit method of handling
         * states and transitions. It should be run when entering a new state
         * before calling the looping method.
         */
        virtual void on_entry() = 0;

        /**
         * \brief The exit function of a state.
         * 
         * This function is part of the enter->loop->exit method of handling
         * states and transitions. It should be run when exiting a current state
         * before entering a different state.
         */
        virtual void on_exit() = 0;

        /**
         * \brief The loop function of a state.
         * 
         * This function is part of the enter->loop->exit method of handling
         * states and transitions. It should be run for the current state every
         * game loop.
         * 
         * \return The next state for the subsequent run of the game loop.
         *         Can be the same as the current state (no transition), or
         *         different (state transition necessary).
         */
        virtual gamestate_e on_loop() = 0;
};

/**
 * \brief A class for the state in which the game initializes itself.
 */
class game_run_init: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

/**
 * \brief A class for the state in which the main gameplay occurs.
 */
class game_run_playing: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

/**
 * \brief A class for the state in which the game displays the main menu.
 */
class game_menu_main: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

/**
 * \brief A class for the state in which the game displays the config menu.
 */
class game_menu_config: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

/**
 * \brief A class for the state in which the game displays the game manual.
 */
class game_menu_manual: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

/**
 * \brief A class for the state in which the game displays the mode select menu.
 */
class game_menu_select_mode: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

/**
 * \brief A class for the state in which the game displays the difficulty select
 *        menu.
 */
class game_menu_select_difficulty: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

/**
 * \brief A class for the state in which the game displays the gameplay results
 *        menu.
 */
class game_menu_result: public base_state
{
    private:

    public:
        virtual void on_entry() override;
        virtual void on_exit() override;
        virtual gamestate_e on_loop() override;
};

#endif