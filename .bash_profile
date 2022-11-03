export EDITOR="nvim"
export TERMINAL="st"
export BROWSER="firefox"
source ~/Documents/nord-tty
[[ -f ~/.bashrc ]] && . ~/.bashrc
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then
    startx
fi
