export EDITOR="vim"
source ~/Documents/nord-tty
[[ -f ~/.bashrc ]] && . ~/.bashrc
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then
    startx
fi
