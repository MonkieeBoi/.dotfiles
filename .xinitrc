#!/bin/sh
setxkbmap -option caps:escape
feh --no-fehbg --bg-fill ~/Pictures/Wallpapers/wallpaper.jpg
picom &
dwmblocks &
# slstatus &
xset r rate 300 50
# qtile start
# exec i3
exec dwm
