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

typedef 
struct ReceiverStruct 
{
    int socketReceiver;
    struct sockaddr_in addrs_dist;
    char* buffer;

} ReceiverStruct;

extern void *
receiver(void *args);