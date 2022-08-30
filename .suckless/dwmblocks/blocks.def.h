//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"",   "date '+%a %r %d/%m/%Y'",		                                         1,    0},
	{" ", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	            10,   14},
	{" ", "amixer -M sget Master | awk -F\"[][]\" '/%/ { print $2 }' | head -n1",   0,   10},
	{" ", "echo -n \"$(cat /sys/class/power_supply/BAT1/capacity)%\"",	           120,    3},
    {" ", "echo -n \"$(($(brightnessctl get)*100/$(brightnessctl max)))% |\"",      0,   10},

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
