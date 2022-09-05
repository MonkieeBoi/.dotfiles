#!/bin/sh
setxkbmap -option caps:escape
setxkbmap -option keypad:pointerkeys
xset r rate 300 50
# feh --no-fehbg --bg-fill ~/Pictures/Wallpapers/wallpaper.jpg
~/.fehbg
picom -b
dwmblocks &
diodon &
dunst &
exec dwm
# qtile start
