#!/bin/sh
setxkbmap -option caps:escape
setxkbmap -option keypad:pointerkeys
feh --no-fehbg --bg-fill ~/Pictures/Wallpapers/wallpaper.jpg
picom &
dwmblocks &
diodon &
# slstatus &
xset r rate 300 50
# qtile start
# exec i3
exec dwm
