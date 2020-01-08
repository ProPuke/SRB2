// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2019 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  r_data.h
/// \brief Refresh module, data I/O, caching, retrieval of graphics by name

#ifndef __R_DATA__
#define __R_DATA__

#include "r_defs.h"
#include "r_state.h"
#include "p_setup.h" // levelflats

#ifdef __GNUG__
#pragma interface
#endif

// Store lists of lumps for F_START/F_END etc.
typedef struct
{
	UINT16 wadfile;
	UINT16 firstlump;
	size_t numlumps;
} lumplist_t;

// Possible alpha types for a patch.
enum patchalphastyle {AST_COPY, AST_TRANSLUCENT, AST_ADD, AST_SUBTRACT, AST_REVERSESUBTRACT, AST_MODULATE, AST_OVERLAY};

UINT32 ASTBlendPixel(RGBA_t background, RGBA_t foreground, int style, UINT8 alpha);
UINT8 ASTBlendPixel_8bpp(UINT8 background, UINT8 foreground, int style, UINT8 alpha);

extern INT16 color8to16[256]; // remap color index to highcolor
extern INT16 *hicolormaps; // remap high colors to high colors..

extern CV_PossibleValue_t Color_cons_t[];

// I/O, setting up the stuff.
void R_InitData(void);
void R_PrecacheLevel(void);

extern size_t flatmemory, spritememory, texturememory;

// Extra Colormap lumps (C_START/C_END) are not used anywhere
// Uncomment to enable
//#define EXTRACOLORMAPLUMPS

// Uncomment to make extra_colormaps order Newest -> Oldest
//#define COLORMAPREVERSELIST

void R_ReInitColormaps(UINT16 num);
void R_ClearColormaps(void);
extracolormap_t *R_CreateDefaultColormap(boolean lighttable);
extracolormap_t *R_GetDefaultColormap(void);
extracolormap_t *R_CopyColormap(extracolormap_t *extra_colormap, boolean lighttable);
void R_AddColormapToList(extracolormap_t *extra_colormap);

#ifdef EXTRACOLORMAPLUMPS
boolean R_CheckDefaultColormapByValues(boolean checkrgba, boolean checkfadergba, boolean checkparams,
	INT32 rgba, INT32 fadergba, UINT8 fadestart, UINT8 fadeend, UINT8 fog, lumpnum_t lump);
extracolormap_t *R_GetColormapFromListByValues(INT32 rgba, INT32 fadergba, UINT8 fadestart, UINT8 fadeend, UINT8 fog, lumpnum_t lump);
#else
boolean R_CheckDefaultColormapByValues(boolean checkrgba, boolean checkfadergba, boolean checkparams,
	INT32 rgba, INT32 fadergba, UINT8 fadestart, UINT8 fadeend, UINT8 fog);
extracolormap_t *R_GetColormapFromListByValues(INT32 rgba, INT32 fadergba, UINT8 fadestart, UINT8 fadeend, UINT8 fog);
#endif
boolean R_CheckDefaultColormap(extracolormap_t *extra_colormap, boolean checkrgba, boolean checkfadergba, boolean checkparams);
boolean R_CheckEqualColormaps(extracolormap_t *exc_a, extracolormap_t *exc_b, boolean checkrgba, boolean checkfadergba, boolean checkparams);
extracolormap_t *R_GetColormapFromList(extracolormap_t *extra_colormap);

lighttable_t *R_CreateLightTable(extracolormap_t *extra_colormap);
lighttable_u32_t *R_CreateTrueColorLightTable(extracolormap_t *extra_colormap);
extracolormap_t *R_CreateColormap(char *p1, char *p2, char *p3);
extracolormap_t *R_AddColormaps(extracolormap_t *exc_augend, extracolormap_t *exc_addend,
	boolean subR, boolean subG, boolean subB, boolean subA,
	boolean subFadeR, boolean subFadeG, boolean subFadeB, boolean subFadeA,
	boolean subFadeStart, boolean subFadeEnd, boolean ignoreFog,
	boolean useAltAlpha, INT16 altAlpha, INT16 altFadeAlpha,
	boolean lighttable);
#ifdef EXTRACOLORMAPLUMPS
extracolormap_t *R_ColormapForName(char *name);
const char *R_NameForColormap(extracolormap_t *extra_colormap);
#endif

#define R_GetRgbaR(rgba) (rgba & 0xFF)
#define R_GetRgbaG(rgba) ((rgba >> 8) & 0xFF)
#define R_GetRgbaB(rgba) ((rgba >> 16) & 0xFF)
#define R_GetRgbaA(rgba) ((rgba >> 24) & 0xFF)
#define R_GetRgbaRGB(rgba) (rgba & 0xFFFFFF)
#define R_PutRgbaR(r) (r)
#define R_PutRgbaG(g) (g << 8)
#define R_PutRgbaB(b) (b << 16)
#define R_PutRgbaA(a) (a << 24)
#define R_PutRgbaRGB(r, g, b) (R_PutRgbaR(r) + R_PutRgbaG(g) + R_PutRgbaB(b))
#define R_PutRgbaRGBA(r, g, b, a) (R_PutRgbaRGB(r, g, b) + R_PutRgbaA(a))

UINT8 NearestColor(UINT8 r, UINT8 g, UINT8 b);

#endif
