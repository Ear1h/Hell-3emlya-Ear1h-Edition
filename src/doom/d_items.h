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
//	Items: key cards, artifacts, weapon, ammunition.
//


#ifndef __D_ITEMS__
#define __D_ITEMS__

#include "doomdef.h"

enum wepflags_e
{
    WPF_NOFLAG = 0x00000000,     // no flag
    WPF_NOTHRUST = 0x00000001,   // doesn't thrust Mobj's
    WPF_SILENT = 0x00000002,     // weapon is silent
};

// Weapon info: sprite frames, ammunition use.
typedef struct
{
    ammotype_t	ammo;
    int		upstate;
    int		downstate;
    int		readystate;
    int		atkstate;
    int		flashstate;
    int     altstate;
    int     altflashstate;
    int     weaponflag;
} weaponinfo_t;

extern  weaponinfo_t    weaponinfo[NUMWEAPONS];

#endif
