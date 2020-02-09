/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring class for game menus.
 */
#ifndef MENU_H
#define MENU_H

#include "entity.h"
#include "bitmaps/sprites_main.h"

/**
 * \brief Vertical and horizontal menus are supported.
 */
enum menu_orientation_e
{
    VERTICAL,
    HORIZONTAL
};

/**
 * \brief Structure containing data of one menu entry.
 */
struct entry_data
{
    uint8_t length_text;
    uint8_t length_desc;
    char *text;
    char *desc;
};

/**
 * \brief Structure containing data of one full menu.
 */
struct menu_data
{
    menu_orientation_e orientation;
    int8_t x_start;
    int8_t y_start;
    uint8_t num_entries;
    entry_data *entries;
    uint8_t curr_entry;
};

/**
 * \brief Class for manipulating and displaying game menus.
 */
class menu_selector: public entity
{
    private:
        int8_t x_pos_start;
        int8_t x_pos_curr;
        int8_t x_pos_sel;
        int8_t y_pos_start;
        int8_t y_pos_curr;
        int8_t y_pos_sel;
        uint8_t num_entries;
        uint8_t curr_entry;
        #ifdef CURSOR_MEMORY
        bool cursor_memory;
        #endif
        menu_orientation_e orientation;
        menu_data *menu_data_curr;
        entry_data *entry_data_curr;
        entry_data *entry_data_base;

    public:
        menu_selector();

        /**
         * \brief Set which menu data to handle.
         * 
         * The menu selector works with one menu data object at a time, this
         * function is used to set which menu to work with.
         * 
         * \param[in,out] data The menu_data object to handle.
         */
        void set_data(menu_data *data);

        #ifdef CURSOR_MEMORY
        /**
         * \brief Set whether to remember cursor position.
         * 
         * The menu selector can record the user's cursor position in the
         * menu_data object. Otherwise, the cursor position defaults to
         * the first position in the current menu when menu's change.
         * 
         * \param[in] cursor_memory Whether to store the cursor position.
         */
        void set_cursor_memory(bool cursor_memory);

        /**
         * \brief Get whether the selector remembers cursor position.
         * 
         * The menu selector can record the user's cursor position in the
         * menu_data object. Otherwise, the cursor position defaults to
         * the first position in the current menu when menu's change.
         * 
         * \return Whether the selector is storing the cursor position.
         */
        bool get_cursor_memory();
        #endif

        /**
         * \brief Move the cursor to the next menu entry.
         * 
         * If the current entry is the last entry, the cursor will wrap
         * around.
         */
        void move_next();

        /**
         * \brief Move the cursor to the previous menu entry.
         * 
         * If the current entry is the first tnery, the cursor will wrap
         * around.
         */
        void move_previous();

        /**
         * \brief Select the current menu entry.
         * 
         * The menu selector will, when select is called, return the numerical
         * value of the entry that the cursor is currently on. For example, if
         * the cursor is on entry 3, and select is called, 3 will be returned.
         * 
         * \return The entry the cursor is currently selecting.
         */
        uint8_t select();

        /**
         * \brief Draw the current menu into the framebuffer.
         */
        void draw() override;

        /**
         * \brief Update menu animations.
         * 
         * The menu selector can animate, if desired.
         * 
         * \warning This functionality is currently unimplemented.
         * 
         * \param[in] ticks_delta     The number of ticks since last update.
         * \param[in] pixels_per_tick The number of pixels steps move per tick.
         */
        void update(uint16_t ticks_delta, uint8_t pixels_per_tick) override;
};

#endif