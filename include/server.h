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

#define DEST_IP "mqttbroker.lan"
#define BUFFER_SIZE 1024


/// @brief Structure to handle the buffer received by the receiver 
///        ( it is used in the a separated thread too)
typedef 
struct ReceiverStruct 
{
    int socketReceiver;
    struct sockaddr_in addrs_dist;
    char* buffer;

} ReceiverStruct;


/// @brief Function used in thread for the receiver that store
///        the received message from the pi to the given struct
/// @param args ReceiverStruct instance
/// @return nothing
extern void *
receiver(void *args);


/// @brief Transform the received button state from the pi 
///        to a more comprehensible one 
/// @param onOrOff 
/// @return 
char* createTeamStr(int onOrOff);
