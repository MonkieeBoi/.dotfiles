# Suckless Monke Rice
Suckless software so easy even a monkey could do it

# Screenshots

![](./assets/screenshot.png)
![](./assets/screenshot1.png)

# Installation (for me not you)
```
rm .bashrc
echo ".dotfiles" >> .gitignore
git clone --bare https://github.com/MonkieeBoi/.dotfiles.git $HOME/.dotfiles
git --git-dir=$HOME/.dotfiles --work-tree=$HOME checkout
source .bashrc
config config --local status.showUntrackedFiles no
pacman -S - < ~/Downloads/pkgs
```

# What I Use
**Operating System** - [Arch Linux](https://archlinux.org/)

**Color Scheme** - [Nord](https://www.nordtheme.com/)

**Window Manager** - [dwm](https://dwm.suckless.org/)

**Terminal** - [st](https://st.suckless.org/)

**Text Editor** - [NeoVim](https://neovim.io/)

**Menus** - [dmenu](https://tools.suckless.org/dmenu/)

**File Manager** - [vifm](https://vifm.info/)

**Browser** - [qutebrowser](https://qutebrowser.org/)

**Image Viewer & Wallpapers** - [feh](https://feh.finalrewind.org/)

**Compositor** - [picom](https://github.com/yshui/picom)

**Screenshots** - [shotgun](https://github.com/neXromancers/shotgun) + [hacksaw](https://github.com/neXromancers/hacksaw)

**Audio Visualiser** - [CAVA](https://github.com/karlstav/cava)

**Keybinds** - [sxhkd](https://github.com/baskerville/sxhkd)

**Notifications** - [dunst](https://dunst-project.org/)

**Font** - [JetBrains Mono Nerd Font](https://www.nerdfonts.com/)

**Pointer Movement** - [keym](https://github.com/cwkx/keym)
