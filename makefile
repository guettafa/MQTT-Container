F_SERVER=./src/server.c
F_CLIENT=./src/testClient.c

F_BROKER=./src/mqtt.c

L_MOSQUITTO=-lmosquitto

CC=-std=c11

broker:
	rm -rf mqtt
	gcc $(CC) $(F_BROKER) -o mqtt $(L_MOSQUITTO) -I ./include 

server:
	rm -rf server
	gcc $(CC) $(F_SERVER) -o server $(L_MOSQUITTO) -I ./include 

client:
	gcc $(CC) $(F_CLIENT) -o client $(L_MOSQUITTO) -I ./include 
