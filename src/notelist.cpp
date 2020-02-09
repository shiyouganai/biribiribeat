/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief File defining linked-list of notes class.
 */
#include "notelist.h"
#include "note.h"
#include "stddef.h"

notelist::notelist()
{
    prev = NULL;
    next = NULL;
}

void notelist::set_prev(notelist *prev)
{
    this->prev = prev;
}

notelist * notelist::get_prev()
{
    return prev;
}

void notelist::set_next(notelist *next)
{
    this->next = next;
}

notelist * notelist::get_next()
{
    return next;
}

void notelist::remove()
{
    if(prev != NULL) {
        prev->set_next(next);
    }
    if(next != NULL) {
        next->set_prev(prev);
    }
    prev = NULL;
    next = NULL;
}