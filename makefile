F_SERVER=./src/server.c
F_SUBSCRIBER=./src/subscriber.c
F_PUBLISHER=./src/publisher.c

L_MOSQUITTO=-lmosquitto

CC=-std=c11

publisher:
	rm -rf publisher
	gcc $(CC) $(F_PUBLISHER) -o publisher $(L_MOSQUITTO) -I ./include 

subscriber:
	rm -rf subscriber
	gcc $(CC) $(F_SUBSCRIBER) -o mqtt $(L_MOSQUITTO) -I ./include 

server:
	rm -rf server
	gcc $(CC) $(F_SERVER) -o server $(L_MOSQUITTO) -I ./include 
