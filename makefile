F_SERVER=./src/server.c
F_BROKER=./src/broker.c

L_MOSQUITTO=-lmosquitto

F_OUTPUT=-o broker

CC=-std=c11

broker:
	rm -rf broker
	gcc $(CC) $(F_BROKER) -o broker $(L_MOSQUITTO) -I ./include 

server:
	rm -rf server
	gcc $(CC) $(F_SERVER) -o server $(L_MOSQUITTO) -I ./include 
