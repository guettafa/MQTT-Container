#include "broker.h"

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result != 0) {
        fprintf(stderr, "Erreur: connexion broker MQTT.\n");
    }
}

void on_publish(struct mosquitto *mosq, void *userdata, int mid) {
    printf("Message publié.\n");
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    printf("Message Reçu : (%s) %s\n",message->topic, (char *)message->payload);
}

int main() {
    struct mosquitto *mosq = NULL;
    int rc, otherrc;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Erreur: création de l'instance mosquitto.\n");
        return 1;
    }
    
    mosquitto_username_pw_set(mosq,getenv("MOSQUITTO_USERNAME"),getenv("MOSQUITTO_PASSWORD"));

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);
    mosquitto_publish_callback_set(mosq, on_publish);

    rc = mosquitto_connect(mosq, HOST, PORT, 60);
    if (rc != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Connexion impossible au broker: %s\n", mosquitto_strerror(rc));
        return 1;
    }

    // Exemple
    const char* MQTT_MESSAGE = createTeamStr(1);

    // Envoie message 
    otherrc = mosquitto_publish(mosq, NULL, TOPIC, strlen(MQTT_MESSAGE), MQTT_MESSAGE, QOS, false);
    if (rc != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to publish message: %s\n", mosquitto_strerror(rc));
    }

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

char* createTeamStr(bool onOrOff) 
{
    char* state = "off";
    if (onOrOff) state = "on";
    
    char* teamStr; asprintf(&teamStr,"4:%s", state);
    return teamStr;
}
