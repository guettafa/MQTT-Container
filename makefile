F_SERVER=./src/server.c
F_CLIENT=./src/client.c

F_SUBSCRIBER=./src/subscriber.c
F_SUBSCRIBER2=./src/subscriber2.c

F_PUBLISHER=./src/publisher.c

L_MOSQUITTO=-lmosquitto
L_THREAD=-lpthread

GNU_SOURCE=-D_GNU_SOURCE

CC=-std=gnu99

COMPILE=gcc $(CC) -I ./include

clean:
	rm -rf build/subscriber build/publisher build/server build/client a.out

publisher:
	$(COMPILE) $(F_PUBLISHER) $(D_GNU_SOURCE) -o build/publisher $(L_MOSQUITTO)

subscriber:
	$(COMPILE) $(F_SUBSCRIBER) -o build/subscriber $(L_MOSQUITTO)

subscriber2:
	$(COMPILE) $(F_SUBSCRIBER2) -o build/subscriber $(L_MOSQUITTO)

server:
	$(COMPILE) -g $(F_SERVER) -lpthread  

client:
	$(COMPILE) $(F_CLIENT) -o build/client
