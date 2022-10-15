export EDITOR="vim"
export TERMINAL="st"
source ~/Documents/nord-tty
[[ -f ~/.bashrc ]] && . ~/.bashrc
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then
    startx
fi
