#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mosquitto.h"

#define PORT 1883
#define TOPIC "final"
#define QOS 1
#define HOST "mqttbroker.lan"

char* createTeamStr(bool onOrOff);
