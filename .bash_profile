export PATH="$HOME/.local/bin:$PATH"
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then
    startx
fi
