/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining classes for game states.
 */
#include "Arduboy2.h"
#include "Squawk.h"
#include "squawk_defines.h"
#include "gamestates.h"
#include "rhythm_manager.h"
#include "navi.h"
#include "bitmaps/sprites_main.h"
#include "audio/stepcharts.h"
#include "audio/melodys.h"
#include "fonts/Font4x6.h"
#include "menus.h"

#define GAME_VERSION "1.0.0"

/* debug defines, uncomment if needed */
#if 0
#define DEBUG_HUD
#endif

/* synth ISR macro define */
SQUAWK_CONSTRUCT_ISR(SQUAWK_PWM_ARDUBOY);

/* global variables shared throughout program */
Arduboy2Base arduboy;
Sprites sprites;
SquawkSynth squawk;
Font4x6 font;

/* static variables shared between states */
static rhythm_manager otoge;
static menu_selector menu;
bool muted = false;
uint16_t erase_timer = 0U;

/* EEPROM layout */
#define EEPROM_MAGIC_WORD_ADDRESS EEPROM_STORAGE_SPACE_START
static uint32_t EEPROM_magic_word = 0xBABACAFE;
#define EEPROM_SCORE_OFFSET EEPROM_STORAGE_SPACE_START + sizeof(EEPROM_magic_word)
static uint8_t EEPROM_addresses[NUM_MODES][NUM_DIFFICULTIES] =
  {{EEPROM_SCORE_OFFSET,
    EEPROM_SCORE_OFFSET +  sizeof(uint32_t),
    EEPROM_SCORE_OFFSET + (sizeof(uint32_t) * 2)},
   {EEPROM_SCORE_OFFSET + (sizeof(uint32_t) * 3),
    EEPROM_SCORE_OFFSET + (sizeof(uint32_t) * 4),
    EEPROM_SCORE_OFFSET + (sizeof(uint32_t) * 5)}};

/* TODO: move ROM strings to own file */
static const uint8_t text_prompt_select_mode[]       PROGMEM = "PICK A MODE!";
static const uint8_t text_prompt_select_difficulty[] PROGMEM = "PICK A DIFFICULTY!";
static const uint8_t text_result_highscore[]         PROGMEM = "HIGH SCORE:";
static const uint8_t text_result_positive[]          PROGMEM = "A NEW HIGH SCORE!";
static const uint8_t text_result_neutral[]           PROGMEM = "NOT BAD AT ALL!";
static const uint8_t text_result_negative[]          PROGMEM = "YOU NEED PRACTICE...";
static const uint8_t text_manual[]                   PROGMEM = "SCAN FOR\nGAME MANUAL!\n\nBIRIBIRIBEAT";
static const uint8_t text_version[]                  PROGMEM = GAME_VERSION;
static const uint8_t text_copyright[]                PROGMEM = "C 2019 2020\nSHIYOUGANAI";
static const uint8_t text_status[]                   PROGMEM = "STATUS: ";
static const uint8_t text_clear_scores[]             PROGMEM = "HOLD A FOR 3 SECONDS!";
static const uint8_t text_on[]                       PROGMEM = "ON";
static const uint8_t text_off[]                      PROGMEM = "OFF";
static const uint8_t text_1x[]                       PROGMEM = "1X";
static const uint8_t text_2x[]                       PROGMEM = "2X";
#ifdef DEBUG_HUD
static const uint8_t text_state_menu_main[]   PROGMEM = "MENU_MAIN";
static const uint8_t text_state_menu_select[] PROGMEM = "MENU_SELECT";
static const uint8_t text_state_menu_result[] PROGMEM = "MENU_RESULT";
static const uint8_t text_state_run_playing[] PROGMEM = "RUN_PLAYING";
#endif                                                                   

/* local functions shared between states */
void draw_speech_bubble(const uint8_t *text, uint8_t length)
{
    arduboy.drawLine(30,  9, 30, 13);
    arduboy.drawLine(31, 13, 35,  9);
    font.setCursor(SELECT_SPEECH_X, SELECT_SPEECH_Y);
    arduboy.drawRect(SELECT_SPEECH_X - 3U, SELECT_SPEECH_Y - 1U, length * FONT4x6_CHAR_WIDTH + 6U, FONT4x6_LINE_HEIGHT + 2U, WHITE);
    arduboy.drawLine(31,  9, 34,  9, BLACK);
    font.print(reinterpret_cast<const __FlashStringHelper *>(text));
}

void clear_eeprom(void)
{
    EEPROM.put<uint32_t>(EEPROM_STORAGE_SPACE_START, EEPROM_magic_word);
    for(uint8_t i = 0; i < NUM_MODES; i++) {
        for(uint8_t j = 0; j < NUM_DIFFICULTIES; j++)
        {
            EEPROM.put<uint32_t>(EEPROM_addresses[i][j], 0x00000000U);
        }
    }
}

void load_highscores_from_eeprom(void)
{
    for(uint8_t i = 0; i < NUM_MODES; i++) {
        for(uint8_t j = 0; j < NUM_DIFFICULTIES; j++)
        {
            EEPROM.get<uint32_t>(EEPROM_addresses[i][j], otoge.highscores[i][j]);
        }
    }
}

#ifdef DEBUG_HUD
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

uint16_t getFreeSram() {
  uint8_t newVariable;
  // heap is empty, use bss as start memory address
  if ((uint16_t)__brkval == 0)
    return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
  // use heap end as the start of the memory address
  else
    return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
};

void print_free_sram() {
    font.setCursor(0, 0);
    arduboy.fillRect(0, 0, FONT4x6_CHAR_WIDTH*3, FONT4x6_LINE_HEIGHT, BLACK);
    font.print(getFreeSram());
}
#endif

bool base_state::next_frame()
{
    /* this function idles and is woken up by 1ms timer to check
     * if it's time to render the next frame, returns false if we have more
     * time to kill, so ideally we call it again and idle more, ad nauseum */
    #ifdef DEBUG_HUD
    return arduboy.nextFrameDEV();
    #else
    return arduboy.nextFrame();
    #endif
}

void game_run_init::on_entry()
{
    uint32_t magic_word_check;
    /* init arduboy peripherals/systems */
    arduboy.boot();
    arduboy.display(CLEAR_BUFFER);
    arduboy.safeMode();
    arduboy.systemButtons();
    arduboy.audio.begin();
    arduboy.initRandomSeed();
    arduboy.waitNoButtons();
    arduboy.setFrameDuration(FD_66PT667FPS);

    squawk.begin();

    /* check for EEPROM magic word which shows we've been played before
     * could also use a checksum to have data integrity but eh, maybe later
     * if the magic word isn't there, init our EEPROM space */
    if(EEPROM.get<uint32_t>(EEPROM_STORAGE_SPACE_START, magic_word_check) != EEPROM_magic_word) {
        clear_eeprom();
    } else {
        /* if the magic word is there, read in the EEPROM values to RAM */
        load_highscores_from_eeprom();
    }
}

gamestate_e game_run_init::on_loop()
{
    return MENU_MAIN;
}

void game_run_init::on_exit()
{

}

void game_menu_main::on_entry()
{
    menu.set_data(&menu_title);
}

gamestate_e game_menu_main::on_loop()
{
    static int8_t animation_offset;

    arduboy.pollButtons();

    if(arduboy.justPressed(RIGHT_BUTTON)) {
        menu.move_next();
    } else if(arduboy.justPressed(LEFT_BUTTON)) {
        menu.move_previous();
    } else if(arduboy.justPressed(A_BUTTON)) {
        switch(menu.select()) {
            case 0U:
                return MENU_SELECT_MODE;
            case 1U:
                return MENU_CONFIG;
            case 2U:
                return MENU_MANUAL;
            default:
                return MENU_MAIN;
        }
    }

    sprites.drawOverwrite(0, 0, biribiriTitleNotelessCrop, 0);

    /* quick and dirty ad-hoc title screen animation */
    if(arduboy.everyXFrames(32)) {
        if(animation_offset) {
            animation_offset = 0;
        } else {
            animation_offset = 2;
        }
    }
    sprites.drawSelfMasked(84, 33-animation_offset, titleNotes1, 0);
    sprites.drawSelfMasked(123, 2+animation_offset, titleNotes2, 0);

    menu.draw();

    #ifdef DEBUG_HUD
    print_free_sram();
    font.setCursor(0, FONT4x6_LINE_HEIGHT*7);
    font.print(GAME_VERSION);
    font.print(reinterpret_cast<const __FlashStringHelper *>(text_state_menu_main));
    #endif

    arduboy.display(CLEAR_BUFFER);
    return MENU_MAIN;
}

void game_menu_main::on_exit()
{
    otoge.navigator.init(MENU_NAVI_X, MENU_NAVI_Y, MENU_NEUTRAL, 16U);
}

void game_menu_config::on_entry()
{
    menu.set_data(&menu_config);
}

gamestate_e game_menu_config::on_loop()
{
    arduboy.pollButtons();

    if(arduboy.justPressed(DOWN_BUTTON)) {
        menu.move_next();
    } else if(arduboy.justPressed(UP_BUTTON)) {
        menu.move_previous();
    } else if(arduboy.justPressed(A_BUTTON)) {
        switch(menu.select()) {
            case 0U:
                if(!muted) {
                    squawk.mute();
                    otoge.navigator.change_expression(MENU_NEUTRAL);
                    muted = true;
                } else {
                    squawk.unmute();
                    muted = false;
                }
                break;
            case 1U:
                if(2U == otoge.pixels_per_tick) {
                    otoge.pixels_per_tick = 1U;
                } else {
                    otoge.pixels_per_tick++;
                }
                break;
            case 2U:
                erase_timer++;
                break;
            default:
                break;
        }
    } else if(arduboy.justPressed(B_BUTTON)) {
        return MENU_MAIN;
    }

    if(erase_timer) {
        if(((uint16_t)(FRAMES_PER_SECOND * 3U)) < erase_timer)
        {
            erase_timer = 0U;
            clear_eeprom();
            load_highscores_from_eeprom();
            arduboy.fillScreen(WHITE);
        } else if(arduboy.justReleased(A_BUTTON)) {
            erase_timer = 0U;
        } else {
            erase_timer++;
            otoge.navigator.update(7U, 16U);
        }
    }

    otoge.navigator.update(1U, 16U);
    otoge.navigator.draw();
    menu.draw();

    switch(menu.select()) {
        case 0U:
            if(!muted) {
                draw_speech_bubble(text_status, sizeof(text_status) + sizeof(text_on) - 2U);
                font.print(reinterpret_cast<const __FlashStringHelper *>(text_on));
            } else {
                draw_speech_bubble(text_status, sizeof(text_status) + sizeof(text_off) - 2U);
                font.print(reinterpret_cast<const __FlashStringHelper *>(text_off));
            }
            break;
        case 1U:
            if(1U == otoge.pixels_per_tick) {
                draw_speech_bubble(text_status, sizeof(text_status) + sizeof(text_1x) - 2U);
                font.print(reinterpret_cast<const __FlashStringHelper *>(text_1x));
            } else {
                draw_speech_bubble(text_status, sizeof(text_status) + sizeof(text_2x) - 2U);
                font.print(reinterpret_cast<const __FlashStringHelper *>(text_2x));
            }
            break;
        case 2U:
            draw_speech_bubble(text_clear_scores, sizeof(text_clear_scores) - 1U);
        default:
            break;
    }

    arduboy.display(CLEAR_BUFFER);
    return MENU_CONFIG;
}

void game_menu_config::on_exit()
{

}

void game_menu_manual::on_entry()
{
    /* white BG to increase ability of phones to read QR code */
    arduboy.fillScreen(WHITE);

    sprites.drawOverwrite(0, 0, manualQr, 0U);

    font.setCursor(65, FONT4x6_LINE_HEIGHT/2);
    font.setTextColor(BLACK);
    font.println(reinterpret_cast<const __FlashStringHelper *>(text_manual));
    font.println(reinterpret_cast<const __FlashStringHelper *>(text_version));
    font.print(reinterpret_cast<const __FlashStringHelper *>(text_copyright));

    arduboy.display(CLEAR_BUFFER);
}

gamestate_e game_menu_manual::on_loop()
{
    arduboy.pollButtons();

    if(arduboy.justPressed(B_BUTTON)) {
        return MENU_MAIN;
    }

    return MENU_MANUAL;
}

void game_menu_manual::on_exit()
{
    font.setTextColor(WHITE);
    arduboy.invert(false);
}

void game_menu_select_mode::on_entry()
{
    menu.set_data(&menu_mode);
}

gamestate_e game_menu_select_mode::on_loop()
{
    arduboy.pollButtons();

    if(arduboy.justPressed(DOWN_BUTTON)) {
        menu.move_next();
    } else if(arduboy.justPressed(UP_BUTTON)) {
        menu.move_previous();
    } else if(arduboy.justPressed(A_BUTTON)) {
        switch(menu.select()) {
            case 0U:
                /* maybe make this user editable in future */
                randomSeed(6969U);
                otoge.select_mode((mode_e)NORMAL);
                break;
            case 1U:
                /* maybe make this user editable in future */
                randomSeed((unsigned long)random());
                otoge.select_mode((mode_e)CHAOS);
                break;
            default:
                return MENU_SELECT_MODE;
        }
        return MENU_SELECT_DIFFICULTY;
    } else if(arduboy.justPressed(B_BUTTON)) {
        return MENU_MAIN;
    }

    otoge.navigator.update(1U, 16U);

    otoge.navigator.draw();
    menu.draw();
    draw_speech_bubble(text_prompt_select_mode, sizeof(text_prompt_select_mode) - 1U);

    #ifdef DEBUG_HUD
    print_free_sram();
    font.setCursor(0, FONT4x6_LINE_HEIGHT*7);
    font.print(reinterpret_cast<const __FlashStringHelper *>(text_state_menu_select));
    #endif

    arduboy.display(CLEAR_BUFFER);
    return MENU_SELECT_MODE;
}

void game_menu_select_mode::on_exit()
{

}

void game_menu_select_difficulty::on_entry()
{
    menu.set_data(&menu_diff);
}

gamestate_e game_menu_select_difficulty::on_loop()
{
    arduboy.pollButtons();

    if(arduboy.justPressed(DOWN_BUTTON)) {
        menu.move_next();
    } else if(arduboy.justPressed(UP_BUTTON)) {
        menu.move_previous();
    } else if(arduboy.justPressed(A_BUTTON)) {
        squawk.tempo_reset();
        otoge.reset_synth_ticks();
        otoge.reset_scoreboard();
        otoge.select_song(&playable_music_level);
        switch(menu.select()) {
            case 0U:
                otoge.select_difficulty((difficulty_e)EASY);
                break;
            case 1U:
                otoge.select_difficulty((difficulty_e)MEDIUM);
                break;
            case 2U:
                otoge.select_difficulty((difficulty_e)HARD);
                break;
            default:
                return MENU_SELECT_DIFFICULTY;
        }
        return RUN_PLAYING;
    } else if(arduboy.justPressed(B_BUTTON)) {
        return MENU_SELECT_MODE;
    }

    otoge.navigator.update(1U, 16U);

    otoge.navigator.draw();
    menu.draw();
    font.print(otoge.highscores[otoge.get_mode()][menu.select()]);
    draw_speech_bubble(text_prompt_select_difficulty, sizeof(text_prompt_select_difficulty) - 1U);

    #ifdef DEBUG_HUD
    font.setCursor(0, FONT4x6_LINE_HEIGHT*7);
    font.print(reinterpret_cast<const __FlashStringHelper *>(text_state_menu_select));
    #endif

    arduboy.display(CLEAR_BUFFER);
    return MENU_SELECT_DIFFICULTY;
}

void game_menu_select_difficulty::on_exit()
{

}

void game_run_playing::on_entry()
{

}

gamestate_e game_run_playing::on_loop()
{
    /* local variables for run loop */
    track_state_e track_state_curr;
    arduboy.pollButtons();

    /* run all rhythm game logic */
    track_state_curr = otoge.update_frame();

    #ifdef DEBUG_HUD
    font.setCursor(0, FONT4x6_LINE_HEIGHT*7);
    font.print(reinterpret_cast<const __FlashStringHelper *>(text_state_run_playing));
    #endif

    #if 0
    arduboy.display(CLEAR_BUFFER);
    #endif

    if((PASSED == track_state_curr) ||
       (FAILED == track_state_curr)) {
        return MENU_RESULT;
    } else {
        return RUN_PLAYING;
    }
}

void game_run_playing::on_exit()
{

}

void game_menu_result::on_entry()
{
    scoreboard_t final_score = otoge.get_scoreboard();
    mode_e mode_curr = otoge.get_mode();
    difficulty_e diff_curr = otoge.get_difficulty();
    bool new_highscore = false;

    /* check for high score and write back from the RAM cache to EEPROM if necessary */
    if(otoge.highscores[mode_curr][diff_curr] < final_score.total_score) {
        new_highscore = true;
        otoge.highscores[mode_curr][diff_curr] = final_score.total_score;
        EEPROM.put<uint32_t>(EEPROM_addresses[mode_curr][diff_curr], otoge.highscores[mode_curr][diff_curr]);
    }

    otoge.navigator.init(MENU_NAVI_X, MENU_NAVI_Y, MENU_NEUTRAL, 16U);

    if(new_highscore) {
        otoge.navigator.change_expression((navi_expression_e)MENU_POSITIVE);
    } else if((NORMAL == otoge.get_mode()) && 
              (FAILED == otoge.get_track_state())) {
        otoge.navigator.change_expression((navi_expression_e)MENU_NEGATIVE);
    } else {
        otoge.navigator.change_expression((navi_expression_e)MENU_NEUTRAL);
    }
}

gamestate_e game_menu_result::on_loop()
{
    arduboy.pollButtons();

    if(arduboy.justPressed(A_BUTTON)) {
        return MENU_SELECT_MODE;
    }

    otoge.navigator.update(1U, 16U);

    otoge.navigator.draw();
    otoge.draw_scoreboard_bg(SELECT_INFO_X, SELECT_INFO_Y);
    otoge.draw_scoreboard(SELECT_INFO_X+FONT4x6_CHAR_WIDTH*12, SELECT_INFO_Y);

    switch (otoge.navigator.get_expression())
    {
        case MENU_NEUTRAL:
            draw_speech_bubble(text_result_neutral, sizeof(text_result_neutral) - 1U);
            break;
        case MENU_POSITIVE:
            draw_speech_bubble(text_result_positive, sizeof(text_result_positive) - 1U);
            break;
        case MENU_NEGATIVE:
            draw_speech_bubble(text_result_negative, sizeof(text_result_negative) - 1U);
            break;
        default:
            break;
    }

    arduboy.drawRect(SELECT_INFO_X - 3U, SELECT_INFO_Y - 2U, 70U, (5U * FONT4x6_LINE_HEIGHT) + 4U, WHITE);

    #ifdef DEBUG_HUD
    print_free_sram();
    font.setCursor(0, FONT4x6_LINE_HEIGHT*7);
    font.print(reinterpret_cast<const __FlashStringHelper *>(text_state_menu_result));
    #endif

    arduboy.display(CLEAR_BUFFER);
    return MENU_RESULT;
}

void game_menu_result::on_exit()
{
    otoge.navigator.init(MENU_NAVI_X, MENU_NAVI_Y, MENU_NEUTRAL, 16U);
}
