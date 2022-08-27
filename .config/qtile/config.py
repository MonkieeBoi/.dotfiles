# Copyright (c) 2010 Aldo Cortesi
# Copyright (c) 2010, 2014 dequis
# Copyright (c) 2012 Randall Ma
# Copyright (c) 2012-2014 Tycho Andersen
# Copyright (c) 2012 Craig Barnes
# Copyright (c) 2013 horsik
# Copyright (c) 2013 Tao Sauvage
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

from libqtile import bar, layout, widget, hook, qtile
from libqtile.config import Click, Drag, Group, Key, Match, Screen
from libqtile.lazy import lazy
# from libqtile.utils import guess_terminal
import os
import subprocess

mod = "mod4"
terminal = "kitty"

keys = [
    # A list of available commands that can be bound to keys can be found
    # at https://docs.qtile.org/en/latest/manual/config/lazy.html
    # Switch between windows
    Key([mod], "h", lazy.layout.left(), desc="Move focus to left"),
    Key([mod], "l", lazy.layout.right(), desc="Move focus to right"),
    Key([mod], "j", lazy.layout.down(), desc="Move focus down"),
    Key([mod], "k", lazy.layout.up(), desc="Move focus up"),
    Key(["mod1"], "Tab", lazy.layout.next(), desc="Move window focus to other window"),
    # Move windows between left/right columns or move up/down in current stack.
    # Moving out of range in Columns layout will create new column.
    Key([mod, "shift"], "h", lazy.layout.shuffle_left(), desc="Move window to the left"),
    Key([mod, "shift"], "l", lazy.layout.shuffle_right(), desc="Move window to the right"),
    Key([mod, "shift"], "j", lazy.layout.shuffle_down(), desc="Move window down"),
    Key([mod, "shift"], "k", lazy.layout.shuffle_up(), desc="Move window up"),
    # Grow windows. If current window is on the edge of screen and direction
    # will be to screen edge - window would shrink.
    Key([mod, "control"], "h", lazy.layout.grow_left(), desc="Grow window to the left"),
    Key([mod, "control"], "l", lazy.layout.grow_right(), desc="Grow window to the right"),
    Key([mod, "control"], "j", lazy.layout.grow_down(), desc="Grow window down"),
    Key([mod, "control"], "k", lazy.layout.grow_up(), desc="Grow window up"),
    Key([mod], "n", lazy.layout.normalize(), desc="Reset all window sizes"),
    # Toggle between split and unsplit sides of stack.
    # Split = all windows displayed
    # Unsplit = 1 window displayed, like Max layout, but still with
    # multiple stack panes
    Key(
        [mod, "shift"],
        "Return",
        lazy.layout.toggle_split(),
        desc="Toggle between split and unsplit sides of stack",
    ),
    # Toggle between different layouts as defined below
    Key([mod], "Tab", lazy.next_layout(), desc="Toggle between layouts"),
    Key([mod], "w", lazy.window.kill(), desc="Kill focused window"),
    Key([mod, "control"], "r", lazy.reload_config(), desc="Reload the config"),
    Key([mod, "control"], "q", lazy.shutdown(), desc="Shutdown Qtile"),
    Key([mod], "q", lazy.spawn("rofi -show drun -theme ~/.config/rofi/adil1090x.rasi")),
    Key([mod], "r", lazy.spawncmd(), desc="Spawn a command using a prompt widget"),
    Key([mod], "s", lazy.hide_show_bar("top"), desc="Toggle panel"),
    # Sound
    Key([], "XF86AudioMute", lazy.spawn("amixer -q set Master toggle")),
    Key([], "XF86AudioLowerVolume", lazy.spawn("amixer -c 0 sset Master 1%- unmute")),
    Key([], "XF86AudioRaiseVolume", lazy.spawn("amixer -c 0 sset Master 1%+ unmute")),
    # Media keys
    Key([], "XF86AudioNext", lazy.spawn("playerctl next")),
    Key([], "XF86AudioPrev", lazy.spawn("playerctl previous")),
    Key([], "XF86AudioPlay", lazy.spawn("playerctl play-pause")),
    Key([], "XF86AudioStop", lazy.spawn("playerctl stop")),
    # Toggle Floating
    Key([mod], "f", lazy.window.toggle_floating(), desc='Toggle floating'),
    Key([mod], "o", lazy.screen.set_wallpaper("/home/monke/Pictures/Wallpapers/ign-011.png", mode="fill"), desc="Toggle wallpaper between degenerate and normal"),
    # Opening stuff
    Key([mod], "t", lazy.spawn(terminal), desc="Launch terminal"),
    Key([mod, "shift"], "t", lazy.spawn("kitty -o background_opacity=1"), desc="Launch kitty without transparency (for vim purposes)"),
    Key([mod], "e", lazy.spawn("nautilus"), desc="Open Filemanager"),
    Key([mod], "b", lazy.spawn("google-chrome --profile-directory='Profile 2'"), desc="Open no fun browser"),
    Key([mod, "mod1"], "b", lazy.spawn("google-chrome --profile-directory='Default'"), desc="Open fun browser"),
    Key([mod, "control"], "n", lazy.spawn("google-chrome --guest"), desc="Open upgraded incognito window"),
    # Key([mod], "", lazy.spawn(""), desc=""),
    # Key([mod], "", lazy.spawn(""), desc=""),
    # Kill screen
    Key([mod], "i", lazy.spawn("xset dpms force off"), desc="Turn off screen"),
    # Screenshot using xclip and imagemagick - switch to xsel later for clipmeny
    Key([mod, "shift"], "s", lazy.spawn("/home/monke/.config/qtile/screenshot.sh"), desc="Screnshot with selection and save to clipboard"),
    # Clipmenu w/ rofi
    # Key([mod], "v", lazy.spawn(""), desc="Open clipboard using rofi and clipmenu"),
]

groups = [Group(i) for i in "12345"]

for i in groups:
    keys.extend(
        [
            # mod1 + letter of group = switch to group
            Key(
                [mod],
                i.name,
                lazy.group[i.name].toscreen(),
                desc="Switch to group {}".format(i.name),
            ),
            # mod1 + shift + letter of group = switch to & move focused window to group
            Key(
                [mod, "shift"],
                i.name,
                lazy.window.togroup(i.name, switch_group=True),
                desc="Switch to & move focused window to group {}".format(i.name),
            ),
            # Or, use below if you prefer not to switch to that group.
            # # mod1 + shift + letter of group = move focused window to group
            # Key([mod, "shift"], i.name, lazy.window.togroup(i.name),
            #     desc="move focused window to group {}".format(i.name)),
        ]
    )

layouts = [
    layout.Columns(
        border_focus = "#5e81ac",
        border_focus_stack=["#d75f5f", "#8f3d3d"], 
        # border_normal = "#5e81ac",
        border_normal = "#3B4252",
        border_normal_stacked = "#3B4252",
        border_width = 1,
        insert_position = 1
    ),
    layout.Max(),
    layout.Floating(
        border_focus = "#5e81ac",
        border_normal = "#3B4252",
    ),
    # Try more layouts by unleashing below layouts.
    # layout.Stack(num_stacks=2),
    # layout.Bsp(),
    # layout.Matrix(),
    # layout.MonadTall(),
    # layout.MonadWide(),
    # layout.RatioTile(),
    # layout.Tile(),
    # layout.TreeTab(),
    # layout.VerticalTile(),
    # layout.Zoomy(),
]

widget_defaults = dict(
   font="JetBrains Mono Nerd Font",
   fontsize=12,
   padding=3,
   background = "#434C5E"
)
extension_defaults = widget_defaults.copy()

screens = [
    Screen(
        wallpaper='~/Pictures/Wallpapers/wallpaper.jpg',
        # wallpaper='~/Pictures/Wallpapers/ign-011.png',
        wallpaper_mode='fill',
        top=bar.Bar(
            [
                widget.GroupBox(
                    active = "#ffffff",
                    inactive = "#eceff4",
                    urgent_text = "ffffff",
                    highlight_method = "block",
                    # highlight_color = ["#4c566a","4c566a"],
                    urgent_alert_method = "block",
                    urgent_border = "bf616a",
                    this_current_screen_border = "#5e81ac",
                    rounded=False
                ),
                widget.TextBox(
                    text = ' ',
                    font = "Ubuntu Mono",
                    background = "#2E3440",
                    foreground = "#434C5E",
                    padding = -2,
                    fontsize = 43
                    ),
                widget.Prompt(
                    background = "#2E3440",
                    ),
                # widget.Chord(
                #     chords_colors={
                #         "launch": ("#ff0000", "#ffffff"),
                #     },
                #     name_transform=lambda name: name.upper(),
                # ),
                # NB Systray is incompatible with Wayland, consider using StatusNotifier instead
                # widget.StatusNotifier(),
                # widget.WindowName(
                #     background = "#2E3440",
                #     ),
                widget.Spacer(bar.STRETCH, background = "#2E3440"),
                widget.TextBox(
                    text = ' ',
                    font = "Ubuntu Mono",
                    foreground = "#2E3440",
                    background = "#434C5E",
                    padding = -2,
                    fontsize = 43
                    ),
                widget.Clock(format="%a %I:%M:%S %p %Y-%m-%d"),
                widget.TextBox(
                    text = ' ',
                    font = "Ubuntu Mono",
                    foreground = "#2E3440",
                    background = "#434C5E",
                    padding = -1,
                    fontsize = 43
                    ),
                widget.Spacer(bar.STRETCH, background = "#2E3440"),
                widget.Clipboard(timeout=5, background = "#2E3440"),
                widget.WidgetBox(
                    widgets = [
                        widget.Systray(background = "#2E3440"),
                        ],
                    text_open = ' ',
                    text_closed = '',
                    close_button_location = "right",
                    font = "Ubuntu Mono", background = "#2E3440", foreground = "#434C5E",
                    padding = -1,
                    fontsize = 43
                    ),
                # widget.Net(
                    # format = '↓{down} ↑{up}',
                    # prefix = "M"
                    # ),
                # widget.Backlight(
                #     backlight_name = "intel_backlight",
                #     ),
                widget.TextBox(
                    text='',
                    fontsize='12',
                    ),
                widget.Memory(
                    measure_mem = "G",
                    format = '{MemUsed:.1f}{mm}/{MemTotal:.1f}{mm}'
                    ),
                widget.TextBox(
                    text=' ',
                    fontsize='12',
                    ),
                widget.Volume(),
                widget.TextBox(
                    text=' ',
                    fontsize='12',
                    ),
                widget.Battery(
                    format="{percent:2.0%}",
                    ),
                widget.CurrentLayoutIcon(
                    custom_icon_paths = [os.path.expanduser("~/.config/qtile/icons")],
                    padding = 0,
                    scale = 0.6
                    ),
                # widget.CurrentLayout(),
            ],
            24,
            background = "#2e3440",
        ),
    ),
]

# Drag floating layouts.
mouse = [
    Drag([mod], "Button1", lazy.window.set_position_floating(), start=lazy.window.get_position()),
    Drag([mod], "Button3", lazy.window.set_size_floating(), start=lazy.window.get_size()),
    Click([mod], "Button2", lazy.window.bring_to_front()),
]

dgroups_key_binder = None
dgroups_app_rules = []  # type: list
follow_mouse_focus = True
bring_front_click = False
cursor_warp = False
floating_layout = layout.Floating(
    float_rules=[
        # Run the utility of `xprop` to see the wm class and name of an X client.
        *layout.Floating.default_float_rules,
        Match(wm_class="confirmreset"),  # gitk
        Match(wm_class="makebranch"),  # gitk
        Match(wm_class="maketag"),  # gitk
        Match(wm_class="ssh-askpass"),  # ssh-askpass
        Match(title="branchdialog"),  # gitk
        Match(title="pinentry"),  # GPG key password entry
    ],
    border_focus = "#5e81ac",
    border_normal = "#3B4252",
)
auto_fullscreen = True
focus_on_window_activation = "smart"
reconfigure_screens = True

# If things like steam games want to auto-minimize themselves when losing
# focus, should we respect this or not?
auto_minimize = True

# When using the Wayland backend, this can be used to configure input devices.
wl_input_rules = None

# XXX: Gasp! We're lying here. In fact, nobody really uses or cares about this
# string besides java UI toolkits; you can see several discussions on the
# mailing lists, GitHub issues, and other WM documentation that suggest setting
# this string if your java app doesn't work correctly. We may as well just lie
# and say that we're a working one by default.
#
# We choose LG3D to maximize irony: it is a 3D non-reparenting WM written in
# java that happens to be on java's whitelist.
wmname = "LG3D"
