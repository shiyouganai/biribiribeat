/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining main gameplay logic class.
 */
#include "rhythm_manager.h"
#include "note.h"
#include "notelist.h"
#include "Arduboy2.h"
#include "squawk_defines.h"
#include "Squawk.h"
#include "bitmaps/sprites_buttons.h"
#include "fonts/Font4x6.h"

/* debug defines, uncomment if needed */
#if 0
#define DEBUG_SERIAL
#define DEBUG_HUD
#define DRAW_MEASURES
#endif

#ifdef DRAW_MEASURES
int16_t line_pos[TRACK_LINES];
#endif

/* size of memory bank for notes */
#define NOTE_BANK_SIZE 24U

/* offsets for track markers in px */
#define SLOT1_Y 49U
#define SLOT2_Y 62U
#define SLOT3_Y 75U
#define SLOT4_Y 88U
#define SLOT5_Y 101U
#define SLOT6_Y 114U

/* HUD location */
#define HUD_X 4U
#define HUD_Y 2U

/* game balance */
#define LIFE_STARTING   35U
#define LIFE_LOSS_MISS  5U
#define LIFE_GAIN_GREAT 2U
#define LIFE_GAIN_GOOD  1U

#define SCORE_GAIN_GREAT 500U
#define SCORE_GAIN_GOOD  200U

/* chart parsing defines */
#define CHART_PARSING 0U
#define CHART_PARSED  1U
#define CHART_STALLED 2U

/* global variables */
extern Arduboy2Base arduboy;
extern Sprites sprites;
extern SquawkSynth squawk;
extern Font4x6 font;

static notelist *notelist_free_head;
static notelist *notelist_used_head;
static notelist notelist_bank[NOTE_BANK_SIZE];
static uint8_t hitmarks[8];
#ifdef DEBUG_HUD
static uint8_t used_notes = 0;
#endif

static const uint8_t text_ready[]       PROGMEM = "GET READY";
static const uint8_t text_begin[]       PROGMEM = "START!";
static const uint8_t text_failed[]      PROGMEM = "CHARGE DEPLETED";
static const uint8_t text_passed[]      PROGMEM = "CHARGE COMPLETE";
static const uint8_t text_score_bg[]    PROGMEM = "TOTAL\nGREAT\nGOOD\nMISS\nMAX COMBO";
static const uint8_t text_score_great[] PROGMEM = "GREAT";
static const uint8_t text_score_good[]  PROGMEM = "GOOD";
static const uint8_t text_score_miss[]  PROGMEM = "MISS";
static const uint8_t text_score_combo[] PROGMEM = " CMB";

uint8_t log10_floored(uint32_t number)
{
    int8_t tens = 0U;
    while(number >= 10U) {
        number = number/10U;
        tens++;
    }
    return tens;
}

void rhythm_manager::draw_hud_bg(uint8_t x, uint8_t y)
{
    arduboy.fillRect(1, 11, life_bar, 1, WHITE);
    arduboy.drawRect(0, 0, 46, 14, WHITE);
    arduboy.drawRect(46, 5, 2, 4, WHITE);
    arduboy.drawLine(36, 1, 36, 12, WHITE);

    /* draw scoring box */
    sprites.drawExternalMask(SLOT1_Y, 0, (hitmarks[5]) ? leftArrowFilled : leftArrow, leftArrowFilled+2, 0, 0);
    sprites.drawExternalMask(SLOT2_Y, 0, (hitmarks[4]) ? downArrowFilled : downArrow, downArrowFilled+2, 0, 0);
    sprites.drawExternalMask(SLOT3_Y, 0, (hitmarks[7]) ? upArrowFilled : upArrow, upArrowFilled+2, 0, 0);
    sprites.drawExternalMask(SLOT4_Y, 0, (hitmarks[6]) ? rightArrowFilled : rightArrow, rightArrowFilled+2, 0, 0);
    sprites.drawExternalMask(SLOT5_Y, 0, (hitmarks[3]) ? aTileFilled : aTile, abTileMask, 0, 0);
    sprites.drawExternalMask(SLOT6_Y, 0, (hitmarks[2]) ? bTileFilled : bTile, abTileMask, 0, 0);
}

void rhythm_manager::draw_hud(uint8_t x, uint8_t y)
{
    int8_t offset = 0;

    #ifdef DEBUG_HUD
    static uint8_t load_min = 0, load_max = 0, load_curr = 0;

    load_curr = arduboy.cpuLoad();
    if(load_curr > load_max) {
        load_max = load_curr;
    }
    if(load_curr < load_min) {
        load_min = load_curr;
    }
    
    font.setCursor(x+FONT4x6_CHAR_WIDTH*15U, y+FONT4x6_LINE_HEIGHT*4U);
    font.println(load_max);
    font.println(load_curr);
    font.print(used_notes);
    #endif

    offset -= log10_floored(scoreboard.total_score) * FONT4x6_CHAR_WIDTH;
    offset += FONT4x6_CHAR_WIDTH * 5U;
    font.setCursor(x+offset, y);
    font.print(scoreboard.total_score);
}

void rhythm_manager::draw_scoreboard_bg(uint8_t x, uint8_t y)
{
    font.setCursor(x, y);
    font.print(reinterpret_cast<const __FlashStringHelper *>(text_score_bg));
}

void rhythm_manager::draw_scoreboard(uint8_t x, uint8_t y)
{
    uint8_t y_curr = y;
    int8_t  offset = 0;

    offset = log10_floored(scoreboard.total_score) * FONT4x6_CHAR_WIDTH;
    font.setCursor(x-offset, y_curr);
    font.print(scoreboard.total_score);

    y_curr += FONT4x6_LINE_HEIGHT;
    offset = log10_floored((uint32_t)scoreboard.greats) * FONT4x6_CHAR_WIDTH;
    font.setCursor(x-offset, y_curr);
    font.print(scoreboard.greats);

    y_curr += FONT4x6_LINE_HEIGHT;
    offset = log10_floored((uint32_t)scoreboard.goods) * FONT4x6_CHAR_WIDTH;
    font.setCursor(x-offset, y_curr);
    font.print(scoreboard.goods);

    y_curr += FONT4x6_LINE_HEIGHT;
    offset = log10_floored((uint32_t)scoreboard.misses) * FONT4x6_CHAR_WIDTH;
    font.setCursor(x-offset, y_curr);
    font.print(scoreboard.misses);

    y_curr += FONT4x6_LINE_HEIGHT;
    offset = log10_floored((uint32_t)scoreboard.max_combo) * FONT4x6_CHAR_WIDTH;
    font.setCursor(x-offset, y_curr);
    font.print(scoreboard.max_combo);
}

void rhythm_manager::reset_scoreboard()
{
    /* reset game status */
    life_bar = LIFE_STARTING;

    scoreboard.goods = 0;
    scoreboard.greats = 0;
    scoreboard.misses = 0;
    scoreboard.combo = 0;
    scoreboard.max_combo = 0;
    scoreboard.total_score = 0;
}

void rhythm_manager::reset_synth_ticks()
{
    ticks_curr  = 0;
    ticks_last  = 0;
    ticks_delta = 0;
    ticks_total = 0;
    loops_total = 0;
    return;
}

void rhythm_manager::select_mode(mode_e mode)
{
    this->game_mode = mode;
}

mode_e rhythm_manager::get_mode()
{
    return this->game_mode;
}

void rhythm_manager::select_song(const playable_song_t *const song)
{
    /* reset track status */
    reset_synth_ticks();

    timing_window  = MISS;

    notelist_used_head = NULL;
    notelist_free_head = NULL;
    chart_index_curr = NULL;
    track_state = SETUP;

    /* init double linked list */
    for(uint8_t i = 0; i < NOTE_BANK_SIZE; i++) {
        notelist_bank[i].remove();
        if(i > 0) {
            notelist_bank[i].set_prev(&notelist_bank[i - 1]);
        }
        if(i < (NOTE_BANK_SIZE - 1)) {
            notelist_bank[i].set_next(&notelist_bank[i + 1]);
        }
        notelist_free_head = &notelist_bank[i];
    }

    for(uint8_t i = 0; i < 8; i++) {
        hitmarks[i] = 0U;
    }

    /* get new song info */
    song_curr = song;
    ticks_per_beat = (pgm_read_byte(&song_curr->mod_speed))*QUARTER_NOTE_TICKS;
    beats_per_min = (squawk.get_tick_rate()*SECONDS_IN_MIN)/ticks_per_beat;
    pixels_per_beat = pixels_per_tick*ticks_per_beat;

    ticks_count_in = (ticks_per_beat*8U);
    chart_ticks_parsed = ticks_count_in;

    /* set up navigator */
    navigator.init(PLAY_NAVI_X, PLAY_NAVI_Y, PLAYING_NEUTRAL, ticks_per_beat);

    #ifdef DRAW_MEASURES
    line_pos[0] = (SMALL_BUTTON_SPRITE_HEIGHT/2)+pixels_per_tick*ticks_per_beat*16;
    line_pos[1] = (SMALL_BUTTON_SPRITE_HEIGHT/2)+pixels_per_tick*ticks_per_beat*4;
    line_pos[2] = (SMALL_BUTTON_SPRITE_HEIGHT/2)+pixels_per_tick*ticks_per_beat*8;
    line_pos[3] = (SMALL_BUTTON_SPRITE_HEIGHT/2)+pixels_per_tick*ticks_per_beat*12;
    #endif
}

void rhythm_manager::update_synth_ticks()
{
    /* critical section */
    cli();
    ticks_curr = squawk.get_tick_counter();
    ticks_count_in_curr = squawk.get_count_in();
    sei();
    ticks_delta = ticks_curr - ticks_last;
    ticks_total += ticks_delta;
    ticks_last = ticks_curr;
    return;
}

void rhythm_manager::select_difficulty(difficulty_e difficulty)
{
    game_difficulty = difficulty;

    /* initial chart parse */
    charts_parsed = 0U;
    pattern_lib_curr = (const step_pattern_library_t *)pgm_read_ptr(&(song_curr->charts[game_difficulty]));
    const step_pattern_t **patterns_tmp = (const step_pattern_t **)pgm_read_ptr(&(pattern_lib_curr->library));
    const step_pattern_t *pattern_tmp   = (const step_pattern_t *)pgm_read_ptr(patterns_tmp);
    chart_index_curr = (const uint8_t *)pgm_read_ptr(&(pattern_tmp->chart));

    if(NORMAL == game_mode) {
        if(CHART_PARSED == parse_chart_smlike(&chart_index_curr, &chart_ticks_parsed)) {
            charts_parsed++;
        }
    } else {
        generate_chart_chaos(&chart_ticks_parsed);
    }

    /* start the synth */
    squawk.set_count_in(ticks_count_in);
    squawk.play((const uint8_t *)pgm_read_ptr(&song_curr->synth_track));
    track_state = IN_PROGRESS;
}

difficulty_e rhythm_manager::get_difficulty() {
    return game_difficulty;
}

void rhythm_manager::load_next_chart()
{
    const step_pattern_t **patterns_tmp = (const step_pattern_t **)pgm_read_ptr(&(pattern_lib_curr->library));
    const uint8_t num_patterns_tmp = (const uint8_t)pgm_read_ptr(&(pattern_lib_curr->num_patterns));

    if(charts_parsed < num_patterns_tmp) {
        patterns_tmp = &patterns_tmp[charts_parsed];
        const step_pattern_t *pattern_tmp   = (const step_pattern_t *)pgm_read_ptr(patterns_tmp);
        chart_index_curr = (const uint8_t *)pgm_read_ptr(&(pattern_tmp->chart));
        charts_parsed++;
    } else {
        squawk.set_count_in((uint8_t)0xFF);
    }
}

track_state_e rhythm_manager::get_track_state()
{
    return this->track_state;
}

scoreboard_t rhythm_manager::get_scoreboard()
{
    return this->scoreboard;
}

/* majority of work happens in here */
track_state_e rhythm_manager::update_frame()
{
    /* local variables */
    notelist *notelist_curr;
    note *note_curr;
    #ifdef DEBUG_HUD
    uint8_t note_count = 0;
    #endif
    uint8_t chart_status = 0;
    int16_t note_curr_ticks_to_hit = 0;

    /* PRE-DRAW UPDATE */

    /* update synth timing */
    update_synth_ticks();

    /* update janky animation timers */
    scored_poptime = max(scored_poptime - ticks_delta, 0);

    if(navi_poptime)
    {
        navi_poptime = max(navi_poptime - ticks_delta, 0);
        if(!navi_poptime) {
            navigator.change_expression(PLAYING_NEUTRAL);
        }
    }

    /* update navigator */
    navigator.update(ticks_delta, ticks_per_beat);

    /* update hit markers */
    for(uint8_t i = 0; i < 8; i++) {
        if(hitmarks[i]) {
            hitmarks[i]--;
        }
    }

    /* update and grade notes */
    notelist_curr = notelist_used_head;
    while(notelist_curr != NULL) {
        note_curr = &(notelist_curr->data);

        /* update */
        note_curr->update(ticks_delta, pixels_per_tick);

        /* grade */
        note_curr_ticks_to_hit = note_curr->get_ticks_to_hit(ticks_curr);
        if(note_curr_ticks_to_hit <= (int16_t)(-6)) {
            timing_window = MISS;
        } else if(note_curr_ticks_to_hit <= (int16_t)(-2)) {
            timing_window = GOOD_LATE;
        } else if(note_curr_ticks_to_hit <= (int16_t)(2)) {
            timing_window = GREAT;
        } else if(note_curr_ticks_to_hit <= (int16_t)(6)) {
            timing_window = GOOD_EARLY;
        } else {
            timing_window = UNGRADED;
        }

        switch(timing_window) {
            case MISS:
                life_bar -= (int8_t)LIFE_LOSS_MISS;
                scoreboard.misses++;
                if(32U <= scoreboard.combo)
                {
                    navi_poptime = ticks_per_beat*4U;
                    navigator.change_expression(PLAYING_NEGATIVE);
                }
                scoreboard.combo = 0;
                scored_poptime = ticks_per_beat*2U;
                scored_last = timing_window;
                note_curr->grade = timing_window;
                break;
            case GREAT:
                if(arduboy.justPressed(note_curr->button)) {
                    uint8_t button = note_curr->button;
                    uint8_t bit = 0;
                    life_bar += (int8_t)LIFE_GAIN_GREAT;
                    scoreboard.greats++;
                    scoreboard.combo++;
                    scoreboard.total_score += SCORE_GAIN_GREAT;
                    scored_poptime = ticks_per_beat*2U;
                    scored_last = timing_window;
                    note_curr->grade = timing_window;
                    while (button >>= 1) {
                        bit++;
                    }
                    hitmarks[bit] = 10;
                }
                break;
            case GOOD_LATE:
            case GOOD_EARLY:
                if(arduboy.justPressed(note_curr->button)) {
                    uint8_t button = note_curr->button;
                    uint8_t bit = 0;
                    life_bar += (int8_t)LIFE_GAIN_GOOD;
                    scoreboard.goods++;
                    scoreboard.combo++;
                    scoreboard.total_score += SCORE_GAIN_GOOD;
                    scored_poptime = ticks_per_beat*2U;
                    scored_last = timing_window;
                    note_curr->grade = timing_window;
                    while (button >>= 1) {
                        bit++;
                    }
                    hitmarks[bit] = 10;
                }
                break;
            default:
                break;
        }

        if(scoreboard.combo && (!(scoreboard.combo % 32)))
        {
            navi_poptime = ticks_per_beat*4U;
            navigator.change_expression(PLAYING_POSITIVE);
        }

        if(scoreboard.max_combo < scoreboard.combo) {
            scoreboard.max_combo++;
        }

        /* iterate */
        notelist_curr = notelist_curr->get_prev();
    }

    /* check for FAILING */
    if(life_bar > (int8_t)35) {
        life_bar = (int8_t)35;
    } else if((life_bar <= (int8_t)0) && (IN_PROGRESS == track_state)) {
        squawk.stop();
        scored_poptime = 0U;
        animation_timer = (uint16_t)(FRAMES_PER_SECOND * 4U);
        navigator.change_expression(PLAYING_NEGATIVE);
        track_state = FAILING;
        life_bar = (int8_t)0;
    }

    /* DRAW */

    /* draw navigator */
    navigator.draw();

    /* draw hud background and track */
    draw_hud_bg(0, 0);

    /* draw combo popups */
    if(scoreboard.combo)
    {
        font.setCursor(80+FONT4x6_CHAR_WIDTH*2, FONT4x6_LINE_HEIGHT*5);
        font.print(scoreboard.combo);
        font.print(reinterpret_cast<const __FlashStringHelper *>(text_score_combo));
    }

    /* draw state dependent things */
    switch(track_state)
    {
        case IN_PROGRESS:
            #ifdef DRAW_MEASURES
            /* for each of the beat lines */
            for(uint8_t i = 0; i < TRACK_LINES; i++) {
                if(ticks_delta) {
                    /* advance the line */
                    line_pos[i] -= ticks_delta*pixels_per_tick;
                    if(line_pos[i] <= (SMALL_BUTTON_SPRITE_HEIGHT/2)) {
                        line_pos[i] += (pixels_per_tick*ticks_per_beat*4);
                    }
                }
                /* always draw the lines */
                arduboy.drawFastHLine(SLOT1_Y+1, line_pos[i], 77, WHITE);
            }
            #endif

            /* draw note score popups */
            if(scored_poptime) {
                font.setCursor(80+FONT4x6_CHAR_WIDTH*2, FONT4x6_LINE_HEIGHT*3);
                switch(scored_last) {
                    case GREAT:
                        font.print(reinterpret_cast<const __FlashStringHelper *>(text_score_great));
                        break;
                    case GOOD_EARLY:
                    case GOOD_LATE:
                        font.print(reinterpret_cast<const __FlashStringHelper *>(text_score_good));
                        break;
                    case MISS:
                        font.print(reinterpret_cast<const __FlashStringHelper *>(text_score_miss));
                        break;
                    default:
                        break;
                }
            }

            /* draw notes */
            notelist_curr = notelist_used_head;
            while(notelist_curr != NULL) {
                note_curr = &(notelist_curr->data);
                
                if(UNGRADED == note_curr->grade) {
                    note_curr->draw();
                }

                notelist_curr = notelist_curr->get_prev();
            }

            /* draw countdown message */
            if(ticks_total < ticks_count_in) {
                if(ticks_total > (uint8_t)(ticks_count_in - ticks_per_beat)) {
                    font.setCursor(FONT4x6_CHAR_WIDTH*15, FONT4x6_LINE_HEIGHT*4);
                    font.print(reinterpret_cast<const __FlashStringHelper *>(text_begin));
                } else {
                    font.setCursor(FONT4x6_CHAR_WIDTH*13, FONT4x6_LINE_HEIGHT*4);
                    font.print(reinterpret_cast<const __FlashStringHelper *>(text_ready));
                }
            }
            break;
        case FAILING:
            /* draw track failure message */
            if(!animation_timer) {
                track_state = FAILED;
            } else {
                animation_timer--;
            }
            if((animation_timer % (uint16_t)(FRAMES_PER_SECOND)) > (uint16_t)(FRAMES_PER_SECOND/2)) {
                font.setCursor(FONT4x6_CHAR_WIDTH*10, FONT4x6_LINE_HEIGHT*4);
                font.print(reinterpret_cast<const __FlashStringHelper *>(text_failed));
            }
            break;
        case PASSING:
            /* draw track pass message */
            if(!animation_timer) {
                track_state = PASSED;
                squawk.stop();
            } else {
                animation_timer--;
            }
            if((animation_timer % (uint16_t)(FRAMES_PER_SECOND)) > (uint16_t)(FRAMES_PER_SECOND/2)) {
                font.setCursor(FONT4x6_CHAR_WIDTH*10, FONT4x6_LINE_HEIGHT*4);
                font.print(reinterpret_cast<const __FlashStringHelper *>(text_passed));
            }
            break;
        default:
            break;
    }

    /* draw score HUD */
    draw_hud(HUD_X, HUD_Y);

    /* write framebuffer to display */
    arduboy.display(CLEAR_BUFFER);

    /* POST DRAW UPDATE */
    /* post-render variable tasks, place here to reduce microstutter */

    /* garbage collection on note pool */
    notelist_curr = notelist_used_head;
    while(notelist_curr != NULL) {
        notelist *temp = notelist_curr;
        note_curr = &(temp->data);

        notelist_curr = temp->get_prev();
        
        if(UNGRADED == note_curr->grade) {
            #ifdef DEBUG_HUD
            note_count++;
            #endif
        } else {
            temp->remove();

            if(notelist_free_head != NULL) {
                notelist_free_head->set_next(temp);
                temp->set_prev(notelist_free_head);
            }
            notelist_free_head = temp;

            if(notelist_used_head == temp) {
                notelist_used_head = notelist_curr;
            }
        }
    }

    #ifdef DEBUG_HUD
    if(note_count != used_notes) {
        used_notes = note_count;
    }
    #endif

    /* parse stepchart into free note pool spaces*/
    if(NORMAL == game_mode) {
        chart_status = parse_chart_smlike(&chart_index_curr, &chart_ticks_parsed);
    } else {
        /* in chaos mode, if this evaluates true, we've finished
         * the bgm loop once and should speed up */
        if(squawk.get_loop_counter() > loops_total) {
            loops_total++;
            squawk.tempo_up();
        }
        chart_status = generate_chart_chaos(&chart_ticks_parsed);
    }
    if(CHART_PARSED == chart_status)
    {
        load_next_chart();
        #ifdef DEBUG_SERIAL
        Serial.println("NOTELIST INCOMING:");
        notelist_curr = notelist_used_head;
        while(notelist_curr != NULL) {
            note_curr = notelist_curr->get_data();
            Serial.println(note_curr->button);
            Serial.println(note_curr->get_ticks_to_hit(0U));
            notelist_curr = notelist_curr->get_prev();
        }
        #endif
    }

    /* check for empty notelist */
    if((IN_PROGRESS == track_state) &&
       (NULL == notelist_used_head)) {
        scored_poptime = 0U;
        animation_timer = (uint16_t)(FRAMES_PER_SECOND * 4U);
        navigator.change_expression(PLAYING_POSITIVE);
        track_state = PASSING;
    }

    return track_state;
}

uint8_t rhythm_manager::parse_chart_smlike(const uint8_t **chart_index, uint16_t *ticks_parsed)
{
    /* local variables */
    uint8_t action_curr;
    uint8_t lines_in_measure;
    uint8_t notes_in_measure;
    const uint8_t *readahead_index;
    notelist * notelist_curr;

    if((chart_index == NULL) || (ticks_parsed == NULL)) {
        /* we have no valid chart, so return */
        return CHART_PARSED;
    }

    #ifdef DEBUG_SERIAL
    Serial.println("chart good");
    #endif

    if (notelist_free_head == NULL) {
        /* we have no space for new notes, so return */
        return CHART_STALLED;
    }

    #ifdef DEBUG_SERIAL
    Serial.println("at least one note free");
    #endif

    while (pgm_read_byte(*chart_index) != PATTERN_EOF) {
        /* determine how many lines in the next measure */
        readahead_index = *chart_index;
        lines_in_measure = 0;
        notes_in_measure = 0;
        /* start reading line by line */
        action_curr = pgm_read_byte((readahead_index)++);
        while (action_curr != PATTERN_EOM) {
            #ifdef DEBUG_SERIAL
            Serial.print("readahead action: ");
            Serial.println(action_curr);
            Serial.print("readahead metadata: ");
            Serial.println(metadata_curr);
            #endif
            lines_in_measure++;
            while (action_curr) {
                notes_in_measure += action_curr & 1U;
                action_curr >>= 1;
            }
            action_curr = pgm_read_byte((readahead_index)++);
        }

        #ifdef DEBUG_SERIAL
        Serial.print("lines in measure: ");
        Serial.println(lines_in_measure);
        Serial.print("notes in measure: ");
        Serial.println(notes_in_measure);
        #endif

        /* see if we have enough open notes for the whole measure */
        notelist_curr = notelist_free_head;
        for (uint8_t cnt = 1U; cnt < notes_in_measure; cnt++) {
            notelist_curr = notelist_curr->get_prev();
            if(NULL == notelist_curr) {
                #ifdef DEBUG_SERIAL
                Serial.print("ran out of notes?");
                #endif
                return CHART_STALLED;
            }
        }

        #ifdef DEBUG_SERIAL
        Serial.println("enough open notes");
        #endif

        /* if we have enough open notes, read in the whole measure */
        /* start reading line by line */
        action_curr = pgm_read_byte((*chart_index)++);
        while(action_curr != PATTERN_EOM) {
            #ifdef DEBUG_SERIAL
            Serial.println(action_curr);
            Serial.println(metadata_curr);
            #endif

            parse_action(action_curr, ticks_parsed);

            /* we finished loading the action, increment timeline by the right amount */
            *ticks_parsed += ((ticks_per_beat*4U)/lines_in_measure);

            /* read the next line */
            action_curr = pgm_read_byte((*chart_index)++);
        }

        /* we finished loading the measure, loop for more measures */
    }

    /* we finished loading the whole chart, return */
    return CHART_PARSED;
}

uint8_t rhythm_manager::generate_chart_chaos(uint16_t *ticks_parsed)
{
    /* local variables */
    uint8_t action_curr;
    uint8_t duration_curr;
    notelist * notelist_curr;

    if(ticks_parsed == NULL) {
        return CHART_PARSED;
    }

    while(notelist_free_head != NULL) {
        action_curr = NO_BUTTON;
        duration_curr = 0x00;

        action_curr = generate_step();
        duration_curr = generate_rest();

        /* see if we have enough open notes for the generated action */
        notelist_curr = notelist_free_head;
        for (uint8_t cnt = 1U; cnt < 2U; cnt++) {
            notelist_curr = notelist_curr->get_prev();
            if(NULL == notelist_curr) {
                #ifdef DEBUG_SERIAL
                Serial.print("ran out of notes?");
                #endif
                return CHART_STALLED;
            }
        }

        #ifdef DEBUG_SERIAL
        Serial.print(action_curr);
        Serial.print("\n");
        Serial.print(duration_curr);
        Serial.print("\n");
        #endif

        parse_action(action_curr, ticks_parsed);

        /* increment timeline by generated rest */
        *ticks_parsed += duration_curr*(ticks_per_beat/4);
    }
    return CHART_STALLED;
}

uint8_t rhythm_manager::parse_action(uint8_t action_curr, uint16_t *ticks_parsed)
{
    uint8_t offset_curr;
    uint8_t button_curr;
    notelist * notelist_curr;
    note * note_curr;

    /* determine which notes are in the action */
    while (action_curr) {
        if (action_curr & A_BUTTON) {
            offset_curr = SLOT5_Y;
            button_curr = A_BUTTON;
            action_curr = action_curr & (~A_BUTTON);
        } else if (action_curr & B_BUTTON) {
            offset_curr = SLOT6_Y;
            button_curr = B_BUTTON;
            action_curr = action_curr & (~B_BUTTON);
        } else if (action_curr & UP_BUTTON) {
            offset_curr = SLOT3_Y;
            button_curr = UP_BUTTON;
            action_curr = action_curr & (~UP_BUTTON);
        } else if (action_curr & DOWN_BUTTON) {
            offset_curr = SLOT2_Y;
            button_curr = DOWN_BUTTON;
            action_curr = action_curr & (~DOWN_BUTTON);
        } else if (action_curr & LEFT_BUTTON) {
            offset_curr = SLOT1_Y;
            button_curr = LEFT_BUTTON;
            action_curr = action_curr & (~LEFT_BUTTON);
        } else if (action_curr & RIGHT_BUTTON) {
            offset_curr = SLOT4_Y;
            button_curr = RIGHT_BUTTON;
            action_curr = action_curr & (~RIGHT_BUTTON);
        } else {
            /* ERROR, should not ever get here */
            return CHART_PARSED;
        }

        /* if we reach here, we're initing a note */
        notelist_curr = notelist_free_head;
        note_curr = &(notelist_curr->data);
        note_curr->init(offset_curr, ((*ticks_parsed)-ticks_curr)*pixels_per_tick, *ticks_parsed, button_curr);
        /* remove from free list */
        notelist_free_head = notelist_curr->get_prev();
        notelist_curr->remove();

        /* double link to used list */
        notelist_curr->set_prev(notelist_used_head);
        if(notelist_used_head != NULL) {
            notelist_used_head->set_next(notelist_curr);
        }
        notelist_used_head = notelist_curr;
    }

    return 0U;
}

uint8_t rhythm_manager::generate_step(void)
{
    uint8_t action = (uint8_t)_BV((uint8_t)(random(6U)+2U));
    if(!random(10U)) {
        /* 10% chance of randomly making a jump */
        action |= (uint8_t)_BV((uint8_t)(random(6U)+2U));
    }
    /* ed's big thumb bad jump filter */
    switch (action)
    {
        case (UP_BUTTON | LEFT_BUTTON):    /* fallthrough */
        case (UP_BUTTON | RIGHT_BUTTON):   /* fallthrough */
        case (DOWN_BUTTON | LEFT_BUTTON):  /* fallthrough */
        case (DOWN_BUTTON | RIGHT_BUTTON): /* fallthrough */
        case (A_BUTTON | B_BUTTON):
            /* regenerate a good single step instead */
            action = (uint8_t)_BV((uint8_t)(random(6U)+2U));
            break;
        default:
            /* we good, jump on */
            break;
    }
    return action;
}

uint8_t rhythm_manager::generate_rest()
{
    uint8_t rest_value;

    switch(game_difficulty)
    {
        case EASY:
            rest_value = 4U;
            break;
        case MEDIUM:
            rest_value = ((uint8_t)random(2U)+1)*2U;
            break;
        case HARD:
            rest_value = 2U;
            break;
        default:
            rest_value = 4U;
    };

    return rest_value;
}