#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT_TCP 8888
#define PORT_MQTT 8883

#define DEST_IP "127.0.0.1"
#define BUFFER_SIZE 1024

typedef struct ReceiverStruct {

    int socketReceiver;
    struct sockaddr_in addrs_dist;
    char* buffer;
} ReceiverStruct;

void *receiver(void *args) {

    ReceiverStruct* rs = (ReceiverStruct*) args;

    while (1) {
        int len, n;

        len = sizeof(rs->addrs_dist); 
        
        // Stocker le message reçu dans n
        n = recvfrom(rs->socketReceiver, (char *)rs->buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&rs->addrs_dist, &len);
        // rs->buffer[n] = '\0';
        
        // Afficher
        //printf("%s",rs->buffer);
        fflush(stdout); 
    }
    pthread_exit(NULL);
}

int main() {
    int sockSender = 0;
    int sockReceiver = 0;
    
    sockSender = socket(AF_INET, SOCK_DGRAM, 0);
    sockReceiver = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in dest_addr, local_addr;

    char buffer[BUFFER_SIZE];

    pthread_t t_receiver;

    // PREPARE -----

        // RECEIVER

    memset(&local_addr, 0, sizeof(local_addr));
    // Receive the number from pi 
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(PORT_TCP);

        // SENDER

    memset(&dest_addr, 0, sizeof(dest_addr));
    // Send it to container
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
    dest_addr.sin_port = htons(PORT_MQTT);

    // ACT ------

    // Pret a recevoir 
    bind(sockReceiver, (const struct sockaddr *)&local_addr, sizeof(local_addr));

    // Prepare the struct
    ReceiverStruct *rs;
    rs->addrs_dist = local_addr;
    rs->socketReceiver = sockReceiver;

    printf("Debut Thread\n");

    if (pthread_create(&t_receiver,NULL,receiver, (void*) rs) != 0) {
        printf("Cannot create thread for receiver");
        return 1;
    }

    char* message = (char*) rs->buffer;
    printf("%s\n", message);
    sendto(sockSender, message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&dest_addr, sizeof(dest_addr));

    pthread_join(t_receiver,NULL);


    // Fermer le socket
    close(sockReceiver);
    close(sockSender);
    return 0;
}