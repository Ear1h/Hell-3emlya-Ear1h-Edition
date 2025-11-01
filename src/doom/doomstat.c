//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
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
//
// DESCRIPTION:
//	Put all global tate variables here.
//

#include <stdio.h>

#include "doomstat.h"
#include "doomtype.h"
#include "m_misc.h"

// Game Mode - identify IWAD as shareware, retail etc.
GameMode_t gamemode = indetermined;
GameMission_t	gamemission = doom;
GameVersion_t   gameversion = exe_final2;
GameVariant_t   gamevariant = vanilla;

// Set if homebrew PWAD stuff has been added.
boolean	modifiedgame;

char *MapName(int e, int m)
{
    static char name[9];

    if (gamemode == commercial)
        M_snprintf(name, sizeof(name), "MAP%02d", m);
    else
        M_snprintf(name, sizeof(name), "E%dM%d", e, m);

    return name;
}




