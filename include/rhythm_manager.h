/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring main gameplay logic class.
 */
#ifndef RHYTHM_MANAGER_H
#define RHYTHM_MANAGER_H

#include <stddef.h>
#include <stdint.h>
#include <navi.h>

#define TITLE_LENGTH_MAX 14
#define TRACK_LINES      4
#define NUM_DIFFICULTIES 3
#define NUM_MODES        2

/* actual fps: 66.667, floored to 66 here */
#define FRAMES_PER_SECOND 66U

/* metadata for charts */
#define PATTERN_EOM 0xFE
#define PATTERN_EOF 0xFF
#define NO_BUTTON   0x00

#define PEOM PATTERN_EOM
#define PEOF PATTERN_EOF

/* uncomment for drawing measure lines */
//#define DRAW_MEASURES

/* enumerations */
enum mode_e
{
    NORMAL,
    CHAOS
};

enum timing_e
{
    UNGRADED,
    GREAT,
    GOOD_EARLY,
    GOOD_LATE,
    MISS
};

enum difficulty_e
{
    EASY,
    MEDIUM,
    HARD
};

enum track_state_e
{
    SETUP,
    IN_PROGRESS,
    FAILING,
    FAILED,
    PASSING,
    PASSED
};

/* classes for managing parts of the game */
struct scoreboard_t
{
    uint16_t greats;
    uint16_t goods;
    uint16_t misses;
    uint16_t combo;
    uint16_t max_combo;
    uint32_t total_score;
};

struct step_pattern_t
{
    const uint8_t *const chart;
};

struct step_pattern_library_t
{
    const uint8_t                 num_patterns;
    const step_pattern_t *const * library;
};

struct playable_song_t
{
    const char                          song_name[TITLE_LENGTH_MAX];
    const uint8_t                       mod_speed;
    const uint8_t *const                synth_track;
    const step_pattern_library_t *const charts[NUM_DIFFICULTIES];
};

class rhythm_manager
{
    private:
        /* member variables */
        /* volatile because of a phantom bug where game_difficulty loses its value */
        volatile mode_e              game_mode;
        volatile difficulty_e        game_difficulty;
        scoreboard_t                 scoreboard;
        track_state_e                track_state;
        timing_e                     timing_window;
        timing_e                     scored_last;
        int8_t                       scored_poptime;
        int8_t                       navi_poptime;
        int8_t                       life_bar;
        uint8_t                      charts_parsed;
        uint16_t                     animation_timer;
        #ifdef DRAW_MEASURES
        int16_t                      line_pos[TRACK_LINES];
        #endif
        const uint8_t                *chart_index_curr;
        const playable_song_t        *song_curr;
        const step_pattern_library_t *pattern_lib_curr;

        /* member functions */
        uint8_t parse_action(uint8_t action_curr, uint16_t *ticks_parsed);
        uint8_t parse_chart_smlike(const uint8_t **chart_index, uint16_t *ticks_parsed);
        uint8_t generate_chart_chaos(uint16_t *ticks_parsed);
        uint8_t generate_step();
        uint8_t generate_rest();
        void    load_next_chart();

    public:
        /* member variables */
        navi     navigator;
        uint8_t  pixels_per_tick = 1U;
        uint8_t  ticks_per_beat;
        uint8_t  beats_per_min;
        uint8_t  pixels_per_beat;
        uint8_t  ticks_delta;
        uint8_t  ticks_count_in;
        uint8_t  ticks_count_in_curr;
        uint16_t ticks_last;
        uint16_t ticks_curr; 
        uint16_t ticks_total;
        uint16_t loops_total;
        uint16_t chart_ticks_parsed;
        uint32_t highscores[NUM_MODES][NUM_DIFFICULTIES] = {{0,0,0},{0,0,0}};

        /* member functions */
        void          draw_hud_bg(uint8_t x, uint8_t y);
        void          draw_hud(uint8_t x, uint8_t y);
        void          draw_scoreboard_bg(uint8_t x, uint8_t y);
        void          draw_scoreboard(uint8_t x, uint8_t y);
        scoreboard_t  get_scoreboard();
        void          reset_scoreboard();
        void          select_song(const playable_song_t *const);
        void          select_difficulty(difficulty_e);
        difficulty_e  get_difficulty();
        void          select_mode(mode_e);
        mode_e        get_mode();
        bool          song_playing();
        track_state_e get_track_state();
        track_state_e update_frame();
        void          update_synth_ticks();
        void          reset_synth_ticks();
};

#endif