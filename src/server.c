#include "server.h"

char* createTeamStr(int onOrOff) 
{
    char* state = "off";
    if (onOrOff) state = "on";
    
    char* teamStr; asprintf(&teamStr,"4:%s", state);
    return teamStr;
}

char* reConvertTo10(char* onOff) {return !strcmp(onOff, "on") ? "4:1\n" : "4:0\n";}

