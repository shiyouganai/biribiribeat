/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File declaring linked-list of notes class.
 */
#ifndef NOTELIST_H
#define NOTELIST_H

#include "note.h"

/* a very pared-down linked list node class that needs manual management */
class notelist {
    private:
        notelist *prev;
        notelist *next;
    public:
        note data;
        notelist();
        void set_next(notelist *next);
        void set_prev(notelist *prev);
        notelist * get_next();
        notelist * get_prev();
        void remove();
};

#endif