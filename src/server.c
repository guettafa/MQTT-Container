#include "server.h"

char* checkState(char* state) {return !strcmp(state, "on") ? "1" : "0";}

char* createTeamStr(int onOrOff) 
{
    char* state = "off";
    if (onOrOff) state = "on";
    
    char* teamStr; asprintf(&teamStr,"4:%s", state);
    return teamStr;
}

char* reConvertTo10(char* onOff) 
{
    char *separated, *fullResult;
    separated = strtok(onOff, ":");
    
    char* teamNum = separated;
    separated = strtok(NULL, ":");

    char* state = separated;

    asprintf(&fullResult, "%s:%s", teamNum, checkState(state));
    return fullResult;
}

