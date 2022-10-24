#!/bin/sh
# [[ -f ~/.Xresources ]] && xrdb -merge -I$HOME ~/.Xresources
setxkbmap -option caps:swapescape
setxkbmap -option keypad:pointerkeys
xset r rate 300 50
# feh --no-fehbg --bg-fill ~/Pictures/Wallpapers/wallpaper.jpg
sxhkd &
~/.fehbg
picom -b
dwmblocks &
diodon &
dunst &
warpd
exec dwm
# while type dwm >/dev/null ; do dwm && continue || break ; done
# qtile start
