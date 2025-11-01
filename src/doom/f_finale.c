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
//	Game completion, final screen animation.
//


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Functions.
#include "deh_main.h"
#include "i_system.h"
#include "i_swap.h"
#include "z_zone.h"
#include "v_video.h"
#include "w_wad.h"
#include "s_sound.h"
#include "g_umapinfo.h"
#include "g_game.h"
#include "m_misc.h" // [FG] M_StringDuplicate()

// Data.
#include "d_main.h"
#include "dstrings.h"
#include "sounds.h"

#include "doomstat.h"
#include "r_state.h"

#include "wi_stuff.h"

typedef enum
{
    F_STAGE_TEXT,
    F_STAGE_ARTSCREEN,
    F_STAGE_CAST,
} finalestage_t;

// ?
//#include "doomstat.h"
//#include "r_local.h"
//#include "f_finale.h"

// Stage of animation:
finalestage_t finalestage;

unsigned int finalecount;

#define	TEXTSPEED	3
#define	TEXTWAIT	250
#define NEWTEXTSPEED    0.01f // new value                         // phares
#define NEWTEXTWAIT     1000  // new value                         // phares

typedef struct
{
    GameMission_t mission;
    int episode, level;
    const char *background;
    const char *text;
} textscreen_t;

static textscreen_t textscreens[] =
{
    { doom,      1, 8,  "FLOOR4_8",  E1TEXT},
    { doom,      2, 8,  "SFLR6_1",   E2TEXT},
    { doom,      3, 8,  "MFLR8_4",   E3TEXT},
    { doom,      4, 8,  "MFLR8_3",   E4TEXT},

    { doom2,     1, 6,  "SLIME16",   C1TEXT},
    { doom2,     1, 11, "RROCK14",   C2TEXT},
    { doom2,     1, 20, "RROCK07",   C3TEXT},
    { doom2,     1, 30, "RROCK17",   C4TEXT},
    { doom2,     1, 15, "RROCK13",   C5TEXT},
    { doom2,     1, 31, "RROCK19",   C6TEXT},

    { pack_tnt,  1, 6,  "SLIME16",   T1TEXT},
    { pack_tnt,  1, 11, "RROCK14",   T2TEXT},
    { pack_tnt,  1, 20, "RROCK07",   T3TEXT},
    { pack_tnt,  1, 30, "RROCK17",   T4TEXT},
    { pack_tnt,  1, 15, "RROCK13",   T5TEXT},
    { pack_tnt,  1, 31, "RROCK19",   T6TEXT},

    { pack_plut, 1, 6,  "SLIME16",   P1TEXT},
    { pack_plut, 1, 11, "RROCK14",   P2TEXT},
    { pack_plut, 1, 20, "RROCK07",   P3TEXT},
    { pack_plut, 1, 30, "RROCK17",   P4TEXT},
    { pack_plut, 1, 15, "RROCK13",   P5TEXT},
    { pack_plut, 1, 31, "RROCK19",   P6TEXT},
};

const char *finaletext;
const char *finaleflat;

static void F_StartCast(void);
static void F_CastTicker(void);
static boolean F_CastResponder(event_t *ev);
static void F_CastDrawer(void);
static void F_TextWrite(void);
static void F_BunnyScroll(void);
static void F_BunnyScroll(void);
static float Get_TextSpeed(void);

static boolean mapinfo_finale;
static int midstage; // whether we're in "mid-stage"

static boolean MapInfo_StartFinale(void)
{
    mapinfo_finale = false;

    if (!gamemapinfo)
    {
        return false;
    }

    if (secretexit)
    {
        if (gamemapinfo->flags & MapInfo_InterTextSecretClear)
        {
            finaletext = NULL;
        }
        else if (gamemapinfo->intertextsecret)
        {
            finaletext = gamemapinfo->intertextsecret;
        }
    }
    else
    {
        if (gamemapinfo->flags & MapInfo_InterTextClear)
        {
            finaletext = NULL;
        }
        else if (gamemapinfo->intertext)
        {
            finaletext = gamemapinfo->intertext;
        }
    }

    if (gamemapinfo->interbackdrop[0])
    {
        finaleflat = gamemapinfo->interbackdrop;
    }

    if (!finaleflat)
    {
        finaleflat = "FLOOR4_8"; // use a single fallback for all maps.
    }

    int lumpnum = W_CheckNumForName(gamemapinfo->intermusic);
    if (lumpnum >= 0)
    {
        S_ChangeMusic(lumpnum, true);
    }

    mapinfo_finale = true;

    return lumpnum >= 0;
}

static boolean MapInfo_Ticker()
{
    if (!mapinfo_finale)
    {
        return false;
    }

    boolean next_level = false;

    WI_checkForAccelerate();

    if (!next_level)
    {
        // advance animation
        finalecount++;

        if (finalestage == F_STAGE_CAST)
        {
            F_CastTicker();
            return true;
        }

         if (finalestage == F_STAGE_TEXT)
        {
            int textcount = 0;
            if (finaletext)
            {
                float speed =
                    gameversion < exe_doom_2_0 ? TEXTSPEED : Get_TextSpeed();
                textcount = strlen(finaletext) * speed +
                            (midstage ? NEWTEXTWAIT : TEXTWAIT);
            }

            if (!textcount || finalecount > textcount ||
                (midstage && acceleratestage))
            {
                next_level = true;
            }
        }
    }

    if (next_level)
    {
        if (!secretexit && gamemapinfo->flags & MapInfo_EndGame)
        {
            if (gamemapinfo->flags & MapInfo_EndGameCast)
            {
                F_StartCast();
            }
            else
            {
                finalecount = 0;
                finalestage = F_STAGE_ARTSCREEN;
                wipegamestate = -1; // force a wipe
                if (gamemapinfo->flags & MapInfo_EndGameBunny)
                {
                    S_StartMusic(mus_bunny);
                }
                else if (gamemapinfo->flags & MapInfo_EndGameStandard)
                {
                    mapinfo_finale = false;
                }
            }
        }
        else
        {
            gameaction = ga_worlddone; // next level, e.g. MAP07
        }
    }

    return true;
}

static boolean MapInfo_Drawer(void)
{
    if (!mapinfo_finale)
    {
        return false;
    }

    switch (finalestage)
    {
        case F_STAGE_TEXT:
            if (finaletext)
            {
                F_TextWrite();
            }
            break;
        case F_STAGE_ARTSCREEN:
            if (gamemapinfo->flags & MapInfo_EndGameBunny)
            {
                F_BunnyScroll();
            }
            else if (gamemapinfo->endpic[0])
            {
                V_DrawPatch(0, 0,
                    W_CacheLumpName((const char *) gamemapinfo->endpic[0],
                                    PU_STATIC));
            }
            break;
        case F_STAGE_CAST:
            F_CastDrawer();
            break;
    }

    return true;
}
    //
// F_StartFinale
//
void F_StartFinale (void)
{
    musicenum_t music_id = mus_None;

    gameaction = ga_nothing;
    gamestate = GS_FINALE;
    viewactive = false;
    automapactive = false;

    acceleratestage = midstage = 0;
    finaletext = NULL;
    finaleflat = NULL;
    
    switch (gamemode)
    {
        // DOOM 1 - E1, E3 or E4, but each nine missions
        case shareware:
        case registered:
        case retail: {
            music_id = mus_victor;

            switch (gameepisode)
            {
                case 1:
                    finaleflat = "FLOOR4_8";
                        ; // Ty 03/30/98 - new externalized bg flats
                    finaletext = E1TEXT; // Ty 03/23/98 - Was e1text variable.
                    break;
                case 2:
                    finaleflat = "FLOOR4_8";
                    finaletext = E2TEXT; // Ty 03/23/98 - Same stuff for each
                    break;
                case 3:
                    finaleflat = "FLOOR4_8";
                    finaletext = E3TEXT;
                    break;
                case 4:
                    finaleflat = "FLOOR4_8";
                    finaletext = E4TEXT;
                    break;
                default:
                    // Ouch.
                    break;
            }
            break;
        }

        // DOOM II and missions packs with E1, M34
        case commercial: {
            music_id = mus_read_m;

            // Ty 08/27/98 - added the gamemission logic

            switch (gamemap) /* This is regular Doom II */
            {
                case 6:
                    finaleflat = "FLOOR4_8";
                    finaletext =
                        gamemission == pack_tnt    ? C4TEXT
                        : gamemission == pack_plut ? C4TEXT
                                                            : C1TEXT;
                    break;
                case 11:
                    finaleflat = "FLOOR4_8";
                    finaletext =
                        gamemission == pack_tnt    ? C4TEXT
                        : gamemission == pack_plut ? C4TEXT
                                                            : C2TEXT;
                    break;
                case 20:
                    finaleflat = "FLOOR4_8";
                    finaletext =
                        gamemission == pack_tnt    ? C4TEXT
                        : gamemission == pack_plut ? C4TEXT
                                                            : C3TEXT;
                    break;
                case 30:
                    finaleflat = "FLOOR4_8";
                    finaletext =
                        gamemission == pack_tnt    ? C4TEXT
                        : gamemission == pack_plut ? C4TEXT
                                                            : C4TEXT;
                    break;
                case 15:
                    finaleflat = "FLOOR4_8";
                    finaletext =
                        gamemission == pack_tnt    ? C4TEXT
                        : gamemission == pack_plut ? C4TEXT
                                                            : C5TEXT;
                    break;
                case 31:
                    finaleflat = "FLOOR4_8";
                    finaletext =
                        gamemission == pack_tnt    ? C4TEXT
                        : gamemission == pack_plut ? C4TEXT
                                                            : C6TEXT;
                    break;
                default:
                    // Ouch.
                    break;
            }
            // Ty 08/27/98 - end gamemission logic

            break;
        }

        // Indeterminate.
        default: // Ty 03/30/98 - not externalized
            music_id = mus_read_m;
            finaleflat = "F_SKY1"; // Not used anywhere else.
            finaletext = C1TEXT; // FIXME - other text, music?
            break;
    }

    if (!MapInfo_StartFinale())
    {
        S_ChangeMusic(music_id, true);
    }

    finalestage = F_STAGE_TEXT;
    finalecount = 0;
}



boolean F_Responder (event_t *event)
{
    if (finalestage == F_STAGE_CAST)
	return F_CastResponder (event);
	
    return false;
}

// Get_TextSpeed() returns the value of the text display speed  // phares
// Rewritten to allow user-directed acceleration -- killough 3/28/98

static float Get_TextSpeed(void)
{
    return midstage ? NEWTEXTSPEED
                    : (midstage = acceleratestage)
               ? acceleratestage = 0,
                 NEWTEXTSPEED : TEXTSPEED;
}
//
// F_Ticker
//
void F_Ticker(void)
{
    if (MapInfo_Ticker())
    {
        return;
    }

    int i;

    if (gameversion == exe_doom_2_0)
    {
        WI_checkForAccelerate(); // killough 3/28/98: check for acceleration
    }
    else if (gamemode == commercial && finalecount > 50) // check for skipping
    {
        for (i = 0; i < MAXPLAYERS; i++)
            if (players[i].cmd.buttons)
                goto next_level; // go on to the next level
    }

    // advance animation
    finalecount++;

    if (finalestage == F_STAGE_CAST)
    {
        F_CastTicker();
        return;
    }

    if (finalestage == F_STAGE_TEXT)
    {
        float speed = gameversion < exe_doom_2_0 ? TEXTSPEED : Get_TextSpeed();
        if (finalecount >
                strlen(finaletext) * speed +               // phares
                    (midstage ? NEWTEXTWAIT : TEXTWAIT) || // killough 2/28/98:
            (midstage && acceleratestage)) // changed to allow acceleration
        {
            if (gamemode != commercial)
            {
                finalecount = 0;
                finalestage = F_STAGE_ARTSCREEN;
                wipegamestate = -1; // force a wipe
                if (gameepisode == 3)
                    S_StartMusic(mus_bunny);
            }
        }
        else // you must press a button to continue in Doom 2
        {
            if (gameversion == exe_doom_2_0 || midstage)
            {
            next_level:
                if (gamemap == 30)
                    F_StartCast(); // cast of Doom 2 characters
                else
                    gameaction = ga_worlddone; // next level, e.g. MAP07
            }
        }    
    }
}


//
// F_TextWrite
//

#include "hu_stuff.h"


static void F_TextWrite (void)
{
    byte*	src;
    pixel_t*	dest;
    
    int		x,y,w;
    signed int	count;
    const char *ch;
    int		c;
    int		cx;
    int		cy;
    
    // erase the entire screen to a tiled background
    src = W_CacheLumpName ( finaleflat , PU_CACHE);
    dest = I_VideoBuffer;
	
    for (y=0 ; y<SCREENHEIGHT ; y++)
    {
	for (x=0 ; x<SCREENWIDTH/64 ; x++)
	{
	    memcpy (dest, src+((y&63)<<6), 64);
	    dest += 64;
	}
	if (SCREENWIDTH&63)
	{
	    memcpy (dest, src+((y&63)<<6), SCREENWIDTH&63);
	    dest += (SCREENWIDTH&63);
	}
    }

    V_MarkRect (0, 0, SCREENWIDTH, SCREENHEIGHT);
    
    // draw some of the text onto the screen
    cx = 10;
    cy = 10;
    ch = finaletext;
	
    count = ((signed int) finalecount - 10) / TEXTSPEED;
    if (count < 0)
	count = 0;
    for ( ; count ; count-- )
    {
	c = *ch++;
	if (!c)
	    break;
	if (c == '\n')
	{
	    cx = 10;
	    cy += 11;
	    continue;
	}
		
	c = toupper(c) - HU_FONTSTART;
	if (c < 0 || c >= HU_FONTSIZE)
	{
	    cx += 4;
	    continue;
	}
		
	w = SHORT (hu_font[c]->width);
	if (cx+w > SCREENWIDTH)
	    break;
	V_DrawPatch(cx, cy, hu_font[c]);
	cx+=w;
    }
	
}

//
// Final DOOM 2 animation
// Casting by id Software.
//   in order of appearance
//
typedef struct
{
    const char	*name;
    mobjtype_t	type;
} castinfo_t;

castinfo_t	castorder[] = {
    {CC_ZOMBIE, MT_POSSESSED},
    {CC_SHOTGUN, MT_SHOTGUY},
    {CC_HEAVY, MT_CHAINGUY},
    {CC_IMP, MT_TROOP},
    {CC_DEMON, MT_SERGEANT},
    {CC_LOST, MT_SKULL},
    {CC_CACO, MT_HEAD},
    {CC_HELL, MT_KNIGHT},
    {CC_BARON, MT_BRUISER},
    {CC_ARACH, MT_BABY},
    {CC_PAIN, MT_PAIN},
    {CC_REVEN, MT_UNDEAD},
    {CC_MANCU, MT_FATSO},
    {CC_ARCH, MT_VILE},
    {CC_SPIDER, MT_SPIDER},
    {CC_CYBER, MT_CYBORG},
    {CC_HERO, MT_PLAYER},

    {NULL,0}
};

int		castnum;
int		casttics;
state_t*	caststate;
boolean		castdeath;
int		castframes;
int		castonmelee;
boolean		castattacking;


//
// F_StartCast
//
void F_StartCast (void)
{
    wipegamestate = -1;		// force a screen wipe
    castnum = 0;
    caststate = &states[mobjinfo[castorder[castnum].type].seestate];
    casttics = caststate->tics;
    castdeath = false;
    finalestage = F_STAGE_CAST;
    castframes = 0;
    castonmelee = 0;
    castattacking = false;
    S_ChangeMusic(mus_evil, true);
}


//
// F_CastTicker
//
static void F_CastTicker(void)
{
    int		st;
    int		sfx;
	
    if (--casttics > 0)
	return;			// not time to change state yet
		
    if (caststate->tics == -1 || caststate->nextstate == S_NULL)
    {
	// switch from deathstate to next monster
	castnum++;
	castdeath = false;
	if (castorder[castnum].name == NULL)
	    castnum = 0;
	if (mobjinfo[castorder[castnum].type].seesound)
	    S_StartSound (NULL, mobjinfo[castorder[castnum].type].seesound);
	caststate = &states[mobjinfo[castorder[castnum].type].seestate];
	castframes = 0;
    }
    else
    {
	// just advance to next state in animation
	if (caststate == &states[S_PLAY_ATK1])
	    goto stopattack;	// Oh, gross hack!
	st = caststate->nextstate;
	caststate = &states[st];
	castframes++;
	
	// sound hacks....
	switch (st)
	{
	  case S_PLAY_ATK1:	sfx = sfx_dshtgn; break;
	  case S_POSS_ATK2:	sfx = sfx_pistol; break;
	  case S_SPOS_ATK2:	sfx = sfx_shotgn; break;
	  case S_VILE_ATK2:	sfx = sfx_vilatk; break;
	  case S_SKEL_FIST2:	sfx = sfx_skeswg; break;
	  case S_SKEL_FIST4:	sfx = sfx_skepch; break;
	  case S_SKEL_MISS2:	sfx = sfx_skeatk; break;
	  case S_FATT_ATK8:
	  case S_FATT_ATK5:
	  case S_FATT_ATK2:	sfx = sfx_firsht; break;
	  case S_CPOS_ATK2:
	  case S_CPOS_ATK3:
	  case S_CPOS_ATK4:	sfx = sfx_shotgn; break;
	  case S_TROO_ATK3:	sfx = sfx_claw; break;
	  case S_SARG_ATK2:	sfx = sfx_sgtatk; break;
	  case S_BOSS_ATK2:
	  case S_BOS2_ATK2:
	  case S_HEAD_ATK2:	sfx = sfx_firsht; break;
	  case S_SKULL_ATK2:	sfx = sfx_sklatk; break;
	  case S_SPID_ATK2:
	  case S_SPID_ATK3:	sfx = sfx_shotgn; break;
	  case S_BSPI_ATK2:	sfx = sfx_plasma; break;
	  case S_CYBER_ATK2:
	  case S_CYBER_ATK4:
	  case S_CYBER_ATK6:	sfx = sfx_rlaunc; break;
	  case S_PAIN_ATK3:	sfx = sfx_sklatk; break;
	  default: sfx = 0; break;
	}
		
	if (sfx)
	    S_StartSound (NULL, sfx);
    }
	
    if (castframes == 12)
    {
	// go into attack frame
	castattacking = true;
	if (castonmelee)
	    caststate=&states[mobjinfo[castorder[castnum].type].meleestate];
	else
	    caststate=&states[mobjinfo[castorder[castnum].type].missilestate];
	castonmelee ^= 1;
	if (caststate == &states[S_NULL])
	{
	    if (castonmelee)
		caststate=
		    &states[mobjinfo[castorder[castnum].type].meleestate];
	    else
		caststate=
		    &states[mobjinfo[castorder[castnum].type].missilestate];
	}
    }
	
    if (castattacking)
    {
	if (castframes == 24
	    ||	caststate == &states[mobjinfo[castorder[castnum].type].seestate] )
	{
	  stopattack:
	    castattacking = false;
	    castframes = 0;
	    caststate = &states[mobjinfo[castorder[castnum].type].seestate];
	}
    }
	
    casttics = caststate->tics;
    if (casttics == -1)
	casttics = 15;
}


//
// F_CastResponder
//

static boolean F_CastResponder(event_t *ev)
{
    if (ev->type != ev_keydown)
	return false;
		
    if (castdeath)
	return true;			// already in dying frames
		
    // go into death frame
    castdeath = true;
    caststate = &states[mobjinfo[castorder[castnum].type].deathstate];
    casttics = caststate->tics;
    castframes = 0;
    castattacking = false;
    if (mobjinfo[castorder[castnum].type].deathsound)
	S_StartSound (NULL, mobjinfo[castorder[castnum].type].deathsound);
	
    return true;
}


static void F_CastPrint(const char *text)
{
    const char *ch;
    int		c;
    int		cx;
    int		w;
    int		width;
    
    // find width
    ch = text;
    width = 0;
	
    while (ch)
    {
	c = *ch++;
	if (!c)
	    break;
	c = toupper(c) - HU_FONTSTART;
	if (c < 0 || c >= HU_FONTSIZE)
	{
	    width += 4;
	    continue;
	}
		
	w = SHORT (hu_font[c]->width);
	width += w;
    }
    
    // draw it
    cx = SCREENWIDTH/2-width/2;
    ch = text;
    while (ch)
    {
	c = *ch++;
	if (!c)
	    break;
	c = toupper(c) - HU_FONTSTART;
	if (c < 0 || c >= HU_FONTSIZE)
	{
	    cx += 4;
	    continue;
	}
		
	w = SHORT (hu_font[c]->width);
	V_DrawPatch(cx, 180, hu_font[c]);
	cx+=w;
    }
	
}


//
// F_CastDrawer
//

static void F_CastDrawer(void)
{
    spritedef_t*	sprdef;
    spriteframe_t*	sprframe;
    int			lump;
    boolean		flip;
    patch_t*		patch;
    
    // erase the entire screen to a background
    V_DrawPatch (0, 0, W_CacheLumpName (DEH_String("BOSSBACK"), PU_CACHE));

    F_CastPrint (DEH_String(castorder[castnum].name));
    
    // draw the current frame in the middle of the screen
    sprdef = &sprites[caststate->sprite];
    sprframe = &sprdef->spriteframes[ caststate->frame & FF_FRAMEMASK];
    lump = sprframe->lump[0];
    flip = (boolean)sprframe->flip[0];
			
    patch = W_CacheLumpNum (lump+firstspritelump, PU_CACHE);
    if (flip)
	V_DrawPatchFlipped(SCREENWIDTH/2, 170, patch);
    else
	V_DrawPatch(SCREENWIDTH/2, 170, patch);
}


//
// F_DrawPatchCol
//
void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )
{
    column_t*	column;
    byte*	source;
    pixel_t*	dest;
    pixel_t*	desttop;
    int		count;
	
    column = (column_t *)((byte *)patch + LONG(patch->columnofs[col]));
    desttop = I_VideoBuffer + x;

    // step through the posts in a column
    while (column->topdelta != 0xff )
    {
	source = (byte *)column + 3;
	dest = desttop + column->topdelta*SCREENWIDTH;
	count = column->length;
		
	while (count--)
	{
	    *dest = *source++;
	    dest += SCREENWIDTH;
	}
	column = (column_t *)(  (byte *)column + column->length + 4 );
    }
}


//
// F_BunnyScroll
//
void F_BunnyScroll (void)
{
    signed int  scrolled;
    int		x;
    patch_t*	p1;
    patch_t*	p2;
    char	name[10];
    int		stage;
    static int	laststage;
		
    p1 = W_CacheLumpName (DEH_String("PFUB2"), PU_LEVEL);
    p2 = W_CacheLumpName (DEH_String("PFUB1"), PU_LEVEL);

    V_MarkRect (0, 0, SCREENWIDTH, SCREENHEIGHT);
	
    scrolled = (SCREENWIDTH - ((signed int) finalecount-230)/2);
    if (scrolled > SCREENWIDTH)
	scrolled = SCREENWIDTH;
    if (scrolled < 0)
	scrolled = 0;
		
    for ( x=0 ; x<SCREENWIDTH ; x++)
    {
	if (x+scrolled < SCREENWIDTH)
	    F_DrawPatchCol (x, p1, x+scrolled);
	else
	    F_DrawPatchCol (x, p2, x+scrolled - SCREENWIDTH);		
    }
	
    if (finalecount < 1130)
	return;
    if (finalecount < 1180)
    {
        V_DrawPatch((SCREENWIDTH - 13 * 8) / 2,
                    (SCREENHEIGHT - 8 * 8) / 2, 
                    W_CacheLumpName(DEH_String("END0"), PU_CACHE));
	laststage = 0;
	return;
    }
	
    stage = (finalecount-1180) / 5;
    if (stage > 6)
	stage = 6;
    if (stage > laststage)
    {
	S_StartSound (NULL, sfx_pistol);
	laststage = stage;
    }
	
    DEH_snprintf(name, 10, "END%i", stage);
    V_DrawPatch((SCREENWIDTH - 13 * 8) / 2, 
                (SCREENHEIGHT - 8 * 8) / 2, 
                W_CacheLumpName (name,PU_CACHE));
}

static void F_ArtScreenDrawer(void)
{
    const char *lumpname;
    
    if (gameepisode == 3)
    {
        F_BunnyScroll();
    }
    else
    {
        switch (gameepisode)
        {
            case 1:
                if (gameversion >= exe_ultimate)
                {
                    lumpname = "CREDIT";
                }
                else
                {
                    lumpname = "HELP2";
                }
                break;
            case 2:
                lumpname = "VICTORY2";
                break;
            case 4:
                lumpname = "ENDPIC";
                break;
            default:
                return;
        }

        lumpname = DEH_String(lumpname);

        V_DrawPatch (0, 0, W_CacheLumpName(lumpname, PU_CACHE));
    }
}

//
// F_Drawer
//
void F_Drawer (void)
{
    if (MapInfo_Drawer())
    {
        return;
    }
    switch (finalestage)
    {
        case F_STAGE_CAST:
            F_CastDrawer();
            break;
        case F_STAGE_TEXT:
            F_TextWrite();
            break;
        case F_STAGE_ARTSCREEN:
            F_ArtScreenDrawer();
            break;
    }
}


