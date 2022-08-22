export PATH="/home/monke/.local/bin:$PATH"
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then
    startx
fi
