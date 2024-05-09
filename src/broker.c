#include "broker.h"

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result == 1)
        fprintf(stderr, "Connection impossible to broker"); return EXIT_FAILURE; 
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {

} 
