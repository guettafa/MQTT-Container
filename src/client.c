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
#define MESSAGE "hello!\n"

struct ReceiverStruct
{
    int socketReceiver;
    struct sockaddr_in addrs_dist;
    char* buffer;
};


void *receiver(void* args) {
    // while (1) {
    //     int len, n;
        

    //     len = sizeof(adr_dist); 
    //     // Stocker le message reçu dans n
    //     n = recvfrom(socket_local, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&adr_dist, &len);
    //     buffer[n] = '\0';

    //     // Afficher
    //     printf("Reçu: %s", buffer);
    //     fflush(stdout); 
    // }
}

int main() {
    int sockSender = 0;
    int sockReceiver = 0;
    
    sockSender = socket(AF_INET, SOCK_DGRAM, 0);
    sockReceiver = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in dest_addr;
    struct sockaddr_in local_addr;

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
    dest_addr.sin_port = htons(PORT_TCP);

    // ACT ------

    // Pret a recevoir 
    bind(sockReceiver, (const struct sockaddr *)&local_addr, sizeof(local_addr));

    // Envoyer le message
    sendto(sockSender, (const char *)MESSAGE, strlen(MESSAGE), MSG_CONFIRM, (const struct sockaddr *)&dest_addr, sizeof(dest_addr));

    // Fermer le socket
    close(sockReceiver);
    close(sockSender);
    return 0;
}