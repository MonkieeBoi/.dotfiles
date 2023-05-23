//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
    /*Icon*/    /*Command*/     /*Update Interval*/ /*Update Signal*/
    {"^c#2e3440^^b#4c566a^^c#d8dee9^  󰅐 ", "date '+%a %r ^c#2e3440^ |'",                                                                  1,    0},
    {"",                                    "cat /tmp/recordingicon",                                                                       0,    4},
    {"^c#4c566a^^b#4c566a^^c#d8dee9^  ",  "free -h | awk '/^Mem/ { print $3 }' | sed s/i//g",                                            30,    0},
    {"^c#3b4252^^b#3b4252^^c#d8dee9^ 󰍛 ",  "top -bn 1 | awk '/^%Cpu/ {print int($2 + $4 + $6)\"%\"}'",                                    30,    0},
    {"^c#4c566a^^b#4c566a^^c#d8dee9^ ",    "amixer -M sget Master | awk -F '[][]' '/%/ { print $4 $2 }' | sed 's/on/ /;s/off.*/󰝟/;1q'",   0,    1},
    {"^c#3b4252^^b#3b4252^^c#d8dee9^ ",    "battery",                                                                                     90,    0},
    {"^c#4c566a^^b#4c566a^^c#d8dee9^  ",  "date '+%d.%m.%y'",                                                                             1,    0},
    {"^c#3b4252^^b#3b4252^^c#d8dee9^ ",    "wificonnection",                                                                              60,    0},

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;

