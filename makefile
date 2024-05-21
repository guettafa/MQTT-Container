F_SERVER=./src/server.c
F_CLIENT=./src/client.c

F_SUBSCRIBER=./src/subscriber.c
F_PUBLISHER=./src/publisher.c

L_MOSQUITTO=-lmosquitto
L_THREAD=-lpthread

GNU_SOURCE=-D_GNU_SOURCE

CC=-std=gnu99

clean:
	rm -rf build/subscriber
	rm -rf build/publisher
	rm -rf build/server
	rm -rf build/client


publisher:
	gcc $(CC) $(F_PUBLISHER) -o build/publisher $(L_MOSQUITTO) $(D_GNU_SOURCE) -I ./include 

subscriber:
	gcc $(CC) $(F_SUBSCRIBER) -o build/subscriber $(L_MOSQUITTO) -I ./include 

server:
	gcc $(CC) $(F_SERVER) -o build/server -I ./include 

client:
	gcc $(CC) $(F_CLIENT) -o build/client -I ./include 
