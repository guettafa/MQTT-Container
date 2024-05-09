#pragma once

#include "helper.h"

void on_connect(struct mosquitto *mosq, void *userdata, int result);
void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message); 

