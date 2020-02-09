/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining class for game menus.
 */
#include "menu.h"
#include "Arduboy2.h"
#include "fonts/Font4x6.h"
#include "bitmaps/sprites_main.h"

/* global variables */
extern Sprites sprites;
extern Font4x6 font;
extern Arduboy2Base arduboy;

menu_selector::menu_selector()
{
    x_pos_sel = 0;
    y_pos_sel = 0;
    x_pos_curr = 0;
    y_pos_curr = 0;
    x_pos_start = 0;
    y_pos_start = 0;
    num_entries = 0;
    curr_entry = 0;
    orientation = VERTICAL;
    menu_data_curr = NULL;
    entry_data_curr = NULL;
    entry_data_base = NULL;
    #ifdef CURSOR_MEMORY
    cursor_memory = true;
    #endif
}

void menu_selector::set_data(menu_data *data)
{
    if(NULL != data) {
        this->menu_data_curr = data;

        num_entries = menu_data_curr->num_entries;
        orientation = menu_data_curr->orientation;
        x_pos_start = menu_data_curr->x_start;
        x_pos_curr  = x_pos_start;
        x_pos_sel   = x_pos_start;
        y_pos_start = menu_data_curr->y_start;
        y_pos_curr  = y_pos_start;
        y_pos_sel   = y_pos_start;
        if(NULL != data->entries) {
            entry_data_base = data->entries;
            entry_data_curr = entry_data_base;
            curr_entry = 0U;

            #ifdef CURSOR_MEMORY
            if(cursor_memory) {
                uint8_t mem_entry = menu_data_curr->curr_entry;
                while(mem_entry != curr_entry) {
                    move_next();
                }
            }
            #else
            uint8_t mem_entry = menu_data_curr->curr_entry;
            while(mem_entry != curr_entry) {
                move_next();
            }
            #endif
        }
    }
}

#ifdef CURSOR_MEMORY
void menu_selector::set_cursor_memory(bool cursor_memory)
{
    this->cursor_memory = cursor_memory;
}

bool menu_selector::get_cursor_memory(void)
{
    return this->cursor_memory;
}
#endif

void menu_selector::move_next(void)
{
    if(num_entries == (++curr_entry)) {
        curr_entry = 0U;
        x_pos_sel = x_pos_start;
        y_pos_sel = y_pos_start;
    } else {
        if(HORIZONTAL == orientation) {
            x_pos_sel += (entry_data_curr->length_text + (uint8_t)2U) * (uint8_t)FONT4x6_CHAR_WIDTH;
        } else if (VERTICAL == orientation) {
            y_pos_sel += (uint8_t)FONT4x6_LINE_HEIGHT;
        }
    }
    entry_data_curr = &entry_data_base[curr_entry];
    menu_data_curr->curr_entry = curr_entry;
}

void menu_selector::move_previous(void)
{
    if(UINT8_MAX == (--curr_entry)) {
        curr_entry = num_entries - (uint8_t)1U;
        if(HORIZONTAL == orientation) {
            for(uint8_t ctr = 0U; ctr < (num_entries - (uint8_t)1U); ctr++) {
                x_pos_sel += (entry_data_base[ctr].length_text + (uint8_t)2U) * (uint8_t)FONT4x6_CHAR_WIDTH;
            }
            y_pos_sel = y_pos_start;
        } else if (VERTICAL == orientation) {
            x_pos_sel = x_pos_start;
            y_pos_sel = y_pos_start + (curr_entry * (uint8_t)FONT4x6_LINE_HEIGHT);
        }
    } else {
        if(HORIZONTAL == orientation) {
            x_pos_sel -= (entry_data_base[curr_entry].length_text + (uint8_t)2U) * (uint8_t)FONT4x6_CHAR_WIDTH;
        } else if (VERTICAL == orientation) {
            y_pos_sel -= (uint8_t)FONT4x6_LINE_HEIGHT;
        }
    }
    entry_data_curr = &entry_data_base[curr_entry];
    menu_data_curr->curr_entry = curr_entry;
}

uint8_t menu_selector::select(void)
{
    return curr_entry;
}

void menu_selector::draw(void)
{
    x_pos_curr = x_pos_start;
    y_pos_curr = y_pos_start;
    font.setCursor(0,0);
    #if 0
    font.print(curr_entry);
    font.print(entry_data_curr->length_text);
    #endif
    font.setCursor(x_pos_start + (uint8_t)FONT4x6_CHAR_WIDTH, y_pos_start);
    for(uint8_t ctr = 0U; ctr < num_entries; ctr++) {
        font.print(reinterpret_cast<const __FlashStringHelper *>(entry_data_base[ctr].text));
        if(HORIZONTAL == orientation) {
            x_pos_curr += (entry_data_base[ctr].length_text + (uint8_t)2U) * (uint8_t)FONT4x6_CHAR_WIDTH;
        } else if (VERTICAL == orientation) {
            y_pos_curr += (uint8_t)FONT4x6_LINE_HEIGHT;
        }
        font.setCursor(x_pos_curr + (uint8_t)FONT4x6_CHAR_WIDTH, y_pos_curr);
    }
    sprites.drawSelfMasked(x_pos_sel, y_pos_sel + FONT4x6_LETTER_SPACING, menuSelect, 0U);
    if(HORIZONTAL == orientation) {
        sprites.drawSelfMasked(x_pos_sel + ((entry_data_base[curr_entry].length_text + 1U) * FONT4x6_CHAR_WIDTH),
                               y_pos_sel + FONT4x6_LETTER_SPACING, menuSelectMirror, 0U);
    } else {
        x_pos_curr = x_pos_start - 3U;
        y_pos_curr = y_pos_start - 2U;

        arduboy.drawRect(x_pos_curr, y_pos_curr, 70U, num_entries * FONT4x6_LINE_HEIGHT + 4U, WHITE);

        if(NULL != entry_data_curr->desc)
        {
            x_pos_curr = x_pos_start - 3U;
            y_pos_curr += num_entries * FONT4x6_LINE_HEIGHT + 6U;

            uint8_t lines = 1U;
            char *desc_curr = entry_data_curr->desc;
            for(uint8_t cnt = 0U; cnt < entry_data_curr->length_desc; cnt++) {
                if('\n' == pgm_read_byte((desc_curr)++)) {
                    lines++;
                }
            }

            arduboy.drawRect(x_pos_curr, y_pos_curr, 70U, lines * FONT4x6_LINE_HEIGHT + 4U, WHITE);

            x_pos_curr = x_pos_start;
            y_pos_curr = y_pos_start + num_entries * FONT4x6_LINE_HEIGHT + 6U;

            font.setCursor(x_pos_curr, y_pos_curr);
            font.print(reinterpret_cast<const __FlashStringHelper *>(entry_data_curr->desc));
        }
    }
}

void menu_selector::update(uint16_t a, uint8_t b)
{
    /* if we ever want to do frame-by-frame animated menu things, this is where we'd do them */
}