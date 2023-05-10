/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 1;     /* border pixel of windows */
static const unsigned int snap           = 32;    /* snap pixel */
static const int swallowfloating         = 0;     /* 1 means swallow floating windows by default */
static const int showbar                 = 0;     /* 0 means no bar */
static const int topbar                  = 1;     /* 0 means bottom bar */
static const char baricon[]              = "";
static const int splitstatus             = 1;     /* 1 for split status items */
static const char *splitdelim            = "|";   /* Character used for separating status */
static const Bool viewontag              = True;  /* Switch view on tag switch */
static const char *fonts[]               = { "JetBrains Mono Nerd Font:size=9" };
static const char col_gray1[]            = "#2e3440";
static const char col_gray2[]            = "#3B3252";
static const char col_gray3[]            = "#d8dee9";
static const char col_gray4[]            = "#eceff4";
static const char col_cyan[]             = "#5381ac";
static const char *colors[][3]           = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;

const char *spcmd1[] = {"st", "-n", "spterm", NULL };
const char *spcmd2[] = {"st", "-n", "spnotes", "-e", "vimwiki", NULL };
const char *spcmd3[] = {"st", "-n", "spfm", "-e", "vifmrun", NULL };
const char *spcmd4[] = {"st", "-n", "spmusic", "-e", "cmus", NULL };
const char *spcmd5[] = {"st", "-n", "spwhen", "-e", "spwhen", NULL };
const char *spcmd6[] = {"stalonetray", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"spnotes",     spcmd2},
    {"spvifm",      spcmd3},
    {"spmusic",     spcmd4},
    {"spwhen",      spcmd5},
    {"sptray",      spcmd6},
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class       instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "Gimp",         NULL,      NULL,           0,         1,          0,           0,        -1 },
    { "discord",      NULL,      NULL,           1 << 3,    0,          0,           0,        -1 },
    { "st",           NULL,      NULL,           0,         0,          1,           0,        -1 },
    { "kitty",        NULL,      NULL,           0,         0,          1,           0,        -1 },
    { NULL,           NULL,      "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
    { NULL,           "spterm",  NULL,           SPTAG(0),  1,          1,           0,        -1 },
    { NULL,           "spnotes", NULL,           SPTAG(1),  1,          1,           0,        -1 },
    { NULL,           "spfm",    NULL,           SPTAG(2),  1,          1,           0,        -1 },
    { NULL,           "spmusic", NULL,           SPTAG(3),  1,          1,           0,        -1 },
    { NULL,           "spwhen",  NULL,           SPTAG(4),  1,          1,           0,        -1 },
    { "stalonetray",  NULL,      NULL,           SPTAG(5),  1,          0,           1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "﬿",      tile },    /* first entry is default */
    { "",      NULL },    /* no layout function means floating behavior */
    { "",      monocle },
};

/* custom symbols for nr. of clients in monocle layout */
/* when clients >= LENGTH(monocles), uses the last element */
static const char *monocles[] = { "", "", "", "", "", "", "", "", "", "" };

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
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static const Key keys[] = {
    /* modifier                     key        function              argument */
    { MODKEY,                       XK_s,      togglebar,            {0} },
    { MODKEY,                       XK_j,      focusstack,           {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,           {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,           {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,           {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,             {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,             {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_j,      movestack,            {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,            {.i = -1 } },
    { MODKEY,                       XK_Return, zoom,                 {0} },
    { MODKEY,                       XK_Tab,    view,                 {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,           {0} },
    { MODKEY,                       XK_t,      setlayout,            {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,            {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,            {.v = &layouts[2]} },
    { MODKEY|ControlMask,           XK_space,  setlayout,            {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating,       {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscreen,     {0} },
    { MODKEY|ControlMask,           XK_f,      togglefakefullscreen, {0} },
    { MODKEY|ControlMask,           XK_j,      moveresize,           {.v = "0x 25y 0w 0h" } },
    { MODKEY|ControlMask,           XK_k,      moveresize,           {.v = "0x -25y 0w 0h" } },
    { MODKEY|ControlMask,           XK_l,      moveresize,           {.v = "25x 0y 0w 0h" } },
    { MODKEY|ControlMask,           XK_h,      moveresize,           {.v = "-25x 0y 0w 0h" } },
    { MODKEY|ControlMask|ShiftMask, XK_j,      moveresize,           {.v = "0x 0y 0w 25h" } },
    { MODKEY|ControlMask|ShiftMask, XK_k,      moveresize,           {.v = "0x 0y 0w -25h" } },
    { MODKEY|ControlMask|ShiftMask, XK_l,      moveresize,           {.v = "0x 0y 25w 0h" } },
    { MODKEY|ControlMask|ShiftMask, XK_h,      moveresize,           {.v = "0x 0y -25w 0h" } },
    { MODKEY|ControlMask|Mod1Mask,  XK_j,      moveresize,           {.v = "0x 1y 0w 0h" } },
    { MODKEY|ControlMask|Mod1Mask,  XK_k,      moveresize,           {.v = "0x -1y 0w 0h" } },
    { MODKEY|ControlMask|Mod1Mask,  XK_l,      moveresize,           {.v = "1x 0y 0w 0h" } },
    { MODKEY|ControlMask|Mod1Mask,  XK_h,      moveresize,           {.v = "-1x 0y 0w 0h" } },
    { MODKEY|ShiftMask|Mod1Mask,    XK_j,      moveresize,           {.v = "0x 0y 0w 1h" } },
    { MODKEY|ShiftMask|Mod1Mask,    XK_k,      moveresize,           {.v = "0x 0y 0w -1h" } },
    { MODKEY|ShiftMask|Mod1Mask,    XK_l,      moveresize,           {.v = "0x 0y 1w 0h" } },
    { MODKEY|ShiftMask|Mod1Mask,    XK_h,      moveresize,           {.v = "0x 0y -1w 0h" } },
    { MODKEY,                       XK_0,      view,                 {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,                  {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,             {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,             {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,               {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,               {.i = +1 } },
    { MODKEY,                       XK_a,      togglescratch,        {.ui = 0 } },
    { MODKEY,                       XK_w,      togglescratch,        {.ui = 1 } },
    { MODKEY,                       XK_e,      togglescratch,        {.ui = 2 } },
    { MODKEY,                       XK_grave,  togglescratch,        {.ui = 3 } },
    { MODKEY,                       XK_c,      togglescratch,        {.ui = 4 } },
    { MODKEY,                       XK_y,      togglescratch,        {.ui = 5 } },
    { MODKEY,                       XK_q,      scratchpad_show,      {0} },
    { MODKEY|ControlMask,           XK_q,      scratchpad_hide,      {0} },
    { MODKEY|ShiftMask,             XK_r,      scratchpad_remove,    {0} },
    { MODKEY|ShiftMask,             XK_q,      quit,                 {0} },
    TAGKEYS(                        XK_1,                            0)
    TAGKEYS(                        XK_2,                            1)
    TAGKEYS(                        XK_3,                            2)
    TAGKEYS(                        XK_4,                            3)
    TAGKEYS(                        XK_5,                            4)
    TAGKEYS(                        XK_6,                            5)
    TAGKEYS(                        XK_7,                            6)
    TAGKEYS(                        XK_8,                            7)
    TAGKEYS(                        XK_9,                            8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

