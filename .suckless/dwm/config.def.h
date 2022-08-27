/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 0;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const Bool viewontag         = True;  /* Switch view on tag switch */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#3B3252";
static const char col_gray3[]       = "#d8dee9";
static const char col_gray4[]       = "#eceff4";
static const char col_cyan[]        = "#5381ac";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-theme", "~/.config/rofi/monke-plagarised.rasi", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *termcmdnotrans[]  = { "kitty", "-o", "background_opacity=1", NULL };
static const char *browsercmd[]  = { "google-chrome", "--profile-directory=Default", NULL };
static const char *workbrowsercmd[]  = { "google-chrome", "--profile-directory=Work", NULL };
static const char *guestbrowsercmd[]  = { "google-chrome", "--guest", NULL };
static const char *screenshotcmd[]  = { "screenshot", NULL };
static const char *wallpapercmd[]  = {"wallpapernormal", NULL };
static const char *revertwallpapercmd[]  = {"wallpaperdegen", NULL };
static const char *musicnextcmd[]  = {"playerctl", "next", NULL };
static const char *musicprevcmd[]  = {"playerctl", "previous", NULL };
static const char *musicplaycmd[]  = {"playerctl", "play-pause", NULL };
static const char *musicstopcmd[]  = {"playerctl", "stop", NULL };
/* static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+1%", "kill -44 $(pidof dwmblocks)",    NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-1%", "kill -44 $(pidof dwmblocks)",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle", "kill -44 $(pidof dwmblocks)",  NULL }; */
/* static const char *light_up[] = {"/usr/bin/light", "-A", "5", "kill -44 $(pidof dwmblocks)", NULL};
static const char *light_down[] = {"/usr/bin/light", "-U", "5", "kill -44 $(pidof dwmblocks)", NULL}; */

static const Key keys[] = {
	/* modifier              key        function        argument */
	/* { 0,                     XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
    { 0,                     XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                     XF86XK_AudioMute, spawn, {.v = mutevol } },
    { 0,			         XF86XK_MonBrightnessUp,   spawn,	{.v = light_up} },
	{ 0,			         XF86XK_MonBrightnessDown, spawn,	{.v = light_down} }, */
    { 0,                     XF86XK_AudioMute,         spawn, SHCMD("pactl set-sink-mute 0 toggle; kill -44 $(pidof dwmblocks)") },
    { 0,                     XF86XK_AudioLowerVolume,  spawn, SHCMD("pactl set-sink-mute 0 false ; pactl set-sink-volume 0 -1%; kill -44 $(pidof dwmblocks)") },
    { 0,                     XF86XK_AudioRaiseVolume,  spawn, SHCMD("pactl set-sink-mute 0 false ; pactl set-sink-volume 0 +1%; kill -44 $(pidof dwmblocks)") },
	{ 0,                     XF86XK_AudioNext, spawn,   {.v = musicnextcmd } },
	{ 0,                     XF86XK_AudioPrev, spawn,   {.v = musicprevcmd } },
	{ 0,                     XF86XK_AudioPlay, spawn,   {.v = musicplaycmd } },
	{ 0,                     XF86XK_AudioStop, spawn,   {.v = musicstopcmd } },
	{ MODKEY,                XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,      XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,    XK_Return, spawn,          {.v = termcmdnotrans } },
	{ MODKEY,                XK_q,      spawn,          {.v = roficmd } },
	{ MODKEY,                XK_b,      spawn,          {.v = workbrowsercmd } },
	{ MODKEY|ShiftMask,      XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY|ControlMask,    XK_n,      spawn,          {.v = guestbrowsercmd } },
	{ MODKEY|ShiftMask,      XK_s,      spawn,          {.v = screenshotcmd} },
	{ MODKEY,                XK_o,      spawn,          {.v = wallpapercmd} },
	{ MODKEY|ShiftMask,      XK_o,      spawn,          {.v = revertwallpapercmd} },
	{ MODKEY,                XK_s,      togglebar,      {0} },
	{ MODKEY,                XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                XK_Return, zoom,           {0} },
	{ MODKEY,                XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,      XK_c,      killclient,     {0} },
	{ MODKEY,                XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,      XK_space,  togglefloating, {0} },
	{ MODKEY,                XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,      XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                 XK_1,                      0)
	TAGKEYS(                 XK_2,                      1)
	TAGKEYS(                 XK_3,                      2)
	TAGKEYS(                 XK_4,                      3)
	TAGKEYS(                 XK_5,                      4)
	TAGKEYS(                 XK_6,                      5)
	TAGKEYS(                 XK_7,                      6)
	TAGKEYS(                 XK_8,                      7)
	TAGKEYS(                 XK_9,                      8)
	{ MODKEY|ShiftMask,      XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

