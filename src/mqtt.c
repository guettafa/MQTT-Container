#include "mqtt.h"

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result == 0) {
        mosquitto_subscribe(mosq, NULL, TOPIC, QOS);
    } else {
        fprintf(stderr, "Erreur: connexion broker MQTT.\n");
    }
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    printf("Message: (%s) %s\n",message->topic, (char *)message->payload);

    int test;
    test = mosquitto_publish(mosq, NULL, TOPIC, message->payloadlen, message->payload, QOS, false);
    if (test != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to publish message: %s\n", mosquitto_strerror(test));
    }
}

int main() {
    struct mosquitto *mosq = NULL;
    int rc;

    char* ca = "/root/projetfinal/blinking-matrix/certificate/final-ca.crt";
    char* cert = "/root/projetfinal/blinking-matrix/certificate/arslane.crt";
    char* key = "/root/projetfinal/blinking-matrix/certificate/arslane.key";

    mosquitto_lib_init();

    mosquitto_username_pw_set(mosq,"minux","0407");
    mosquitto_tls_set(mosq,ca,NULL,cert,key,NULL);

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Erreur: création de l'instance mosquitto.\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    rc = mosquitto_connect(mosq, MQTT_BROKER_HOST, PORT_MQTT, 60);
    if (rc != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Connexion impossible au broker: %s\n", mosquitto_strerror(rc));
        return 1;
    }

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

