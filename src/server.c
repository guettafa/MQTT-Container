#include "server.h"

char* createTeamStr(int onOrOff) 
{
    char* state = "off";
    if (onOrOff) state = "on";
    
    char* teamStr; asprintf(&teamStr,"4:%s", state);
    return teamStr;
}


