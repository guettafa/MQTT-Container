#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mosquitto.h"

// -----   MACROS   -----

// PORT
#define PORT_TCP 2002
#define PORT_MQTT 8883

// IP ADDRESS
#define DEST_IP "mqttbroker.lan"
#define MQTT_BROKER_HOST "mqttbroker.lan"
#define LOCALHOST "127.0.0.1"

// MQTT RELATED
#define QOS 1
#define TOPIC "final"

// OTHER
#define BUFFER_SIZE 1024

//  -----   FUNCTIONS    -----

/// @brief Function used in thread for the receiver that store
///        the received message from the pi to the given struct
/// @param args ReceiverStruct instance
/// @return nothing
extern void *
receiver();


/// @brief Transform the received button state from the pi 
///        to a more comprehensible one 
/// @param onOrOff if the button has been pressed under format ( 0 - not pressed / 1 - pressed)
/// @return the team string that the broker will receive / Ex: 4:on or 4:off
extern char*
createTeamStr(int onOrOff);


/// @brief Transform the "on" or off string receive from the broker
///        to a 1 if on and 0 if off
/// @param onOff The "on" or "off" string
/// @return the team string the PI will receive / Example : 4:1 or 4:0
extern char* 
reConvertTo10(char* onOff);