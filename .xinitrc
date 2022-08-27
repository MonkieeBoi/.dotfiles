#!/bin/sh
setxkbmap -option caps:escape
# feh --no-fehbg --bg-fill ~/Pictures/Wallpapers/ign-011.png
picom &
xset r rate 300 50
qtile start
# exec i3
# exec dwm
