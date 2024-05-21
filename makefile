F_SERVER=./src/server.c
F_SUBSCRIBER=./src/subscriber.c
F_PUBLISHER=./src/publisher.c

L_MOSQUITTO=-lmosquitto
GNU_SOURCE=-D_GNU_SOURCE

CC=-std=gnu99

publisher:
	rm -rf publisher
	gcc $(CC) $(F_PUBLISHER) -B -o publisher $(L_MOSQUITTO) $(D_GNU_SOURCE) -I ./include 

subscriber:
	rm -rf subscriber
	gcc $(CC) $(F_SUBSCRIBER) -o subscriber $(L_MOSQUITTO) -I ./include 

server:
	rm -rf server
	gcc $(CC) $(F_SERVER) -o server $(L_MOSQUITTO) -I ./include 
