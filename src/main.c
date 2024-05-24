#include "server.h"

// ---- GLOBAL VARS ----

struct mosquitto *g_mosq;
int socket_dist;

void *receiver() {

    char buffer[BUFFER_SIZE];

    while(1) {
        int datalen = read(socket_dist, buffer, BUFFER_SIZE);

        if (datalen != 0) {
            char* result = createTeamStr(atoi(buffer));
            mosquitto_publish(g_mosq, NULL, TOPIC, strlen(result), result, QOS, false);    
        }
    }
    pthread_exit(NULL);
}

void on_connect(struct mosquitto *g_mosq, void *userdata, int result) {
    if (result == 0) {
        mosquitto_subscribe(g_mosq, NULL, TOPIC, QOS);
    } else {
        fprintf(stderr, "Erreur: connexion broker MQTT.\n");
    }
}

void on_message(struct mosquitto *g_mosq, void *userdata, const struct mosquitto_message *message) {
    send(socket_dist, (char*) message->payload, strlen((char*) message->payload), 0);
    printf("Message: (%s) %s\n",message->topic, (char *)message->payload);
}

int main(void) {

    //  -----   TCP PART -----

    int socket_local;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket and init address
    socket_local = socket(AF_INET, SOCK_STREAM, 0);
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT_TCP);

    // Bind socket to interface
    bind(socket_local, (struct sockaddr *)&address, sizeof(address));
    
    // Wait for a coming  connection
    listen(socket_local, 3);
    socket_dist = accept(socket_local, (struct sockaddr *)&address, (socklen_t*)&addrlen);
   

    // ----- MQTT PART  -----

    int rc;

    pthread_t  t_receiver;

    char* ca = "/root/projetfinal/blinking-matrix/certificate/final-ca.crt";
    char* cert = "/root/projetfinal/blinking-matrix/certificate/arslane.crt";
    char* key = "/root/projetfinal/blinking-matrix/certificate/arslane.key";

    mosquitto_lib_init();
    g_mosq = mosquitto_new(NULL, true, NULL);

    // mosquitto_username_pw_set(g_mosq,"minux","0407");
    // mosquitto_tls_set(g_mosq,ca,NULL,cert,key,NULL);

    if (!g_mosq) {
        fprintf(stderr, "Erreur: création de l'instance mosquitto.\n");
        return 1;
    }

    mosquitto_connect_callback_set(g_mosq, on_connect);
    mosquitto_message_callback_set(g_mosq, on_message);

    rc = mosquitto_connect(g_mosq, LOCALHOST, PORT_MQTT, 60);
    if (rc != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Connexion impossible au broker: %s\n", mosquitto_strerror(rc));
        return 1;
    }

    if (pthread_create(&t_receiver,NULL,receiver, NULL) != 0) {
        printf("Cannot create thread for receiver");
        return 1;
    }

    mosquitto_loop_forever(g_mosq, -1, 1);

    return 0;
}


