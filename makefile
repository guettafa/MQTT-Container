F_HELPER=./src/helper.c
F_BROKER=./src/broker.c

L_MOSQUITTO=-lmosquitto

F_OUTPUT=-o broker

CC=-std=c11

all:
	gcc $(CC) $(F_BROKER) $(L_MOSQUITTO) 