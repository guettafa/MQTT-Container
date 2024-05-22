F_SERVER=./src/server.c
F_CLIENT=./src/client.c

F_SUBSCRIBER=./src/subscriber.c
F_PUBLISHER=./src/publisher.c

L_MOSQUITTO=-lmosquitto
L_THREAD=-lpthread

GNU_SOURCE=-D_GNU_SOURCE

CC=-std=gnu99

COMPILE_MOSQUITTO=gcc $(CC) $(L_MOSQUITTO) -I ./include 
COMPILE=gcc $(CC) -I ./include

clean:
	rm -rf build/subscriber build/publisher build/server build/client

publisher:
	$(COMPILE_MOSQUITTO) $(F_PUBLISHER) $(D_GNU_SOURCE) -o build/publisher

subscriber:
	$(COMPILE_MOSQUITTO) $(F_SUBSCRIBER) -o build/subscriber

server:
	$(COMPILE) $(F_SERVER) -o build/server 

client:
	$(COMPILE) -g $(F_CLIENT) -lpthread
