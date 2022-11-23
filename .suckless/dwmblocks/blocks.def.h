//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    // {"",   "cmusinfo",                                                                                      1,    3},
    {" ",  "date '+%a %r|'",                                                                                 1,    0},
    {"",    "cat /tmp/recordingicon",                                                                         0,    4},
    {"  ",  "free -h | awk '/^Mem/ { print $3 }' | sed s/i//g",                                            30,    0},
    {"  ",  "top -bn 1 | awk '/^%Cpu/ {print int($2 + $4 + $6)\"%\"}'",                                    30,    0},
    {" ",    "amixer -M sget Master | awk -F '[][]' '/%/ { print $4 $2 }' | sed 's/on/ /;s/off.*/ﱝ/;1q'",   0,    1},
    {" ",    "battery",                                                                                     90,    0},
    {"  ",  "echo \"$(xbacklight -get | cut -f1 -d '.')%\"",                                                0,    2},
    {"  ",  "date '+%d.%m.%y'",                                                                             1,    0},
    {" ",    "wificonnection",                                                                              60,    0},

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;

