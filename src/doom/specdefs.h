//
// Copyright(C) 2025 Vladislav Putintsev (Ear1h)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#ifndef SPECDEFS_H
#define SPECDEFS_H

#include "m_json.h"
/* MACROS */
typedef struct
{
    short action;
    short tag;
    int delay;
} macro_special_t;

typedef struct
{
    int macroid;
    int count;
    macro_special_t *specials;
} macros_t;

/* MESSAGES */
typedef struct
{
    int messageid;
    const char *messages;
} spec_message_t;

/* BASE */

typedef struct
{
    macros_t *spec_macro;
    spec_message_t *spec_message;
}specdefs_t;

specdefs_t *ParseSpecdefs(void);

extern specdefs_t *specdefs;
#endif