FILE_MAIN=./src/main.c
F_HELPER=./src/helper.c
F_BROKER=./src/broker.c

L_MOSQUITTO=-lmosquitto

F_OUTP

CC=-std=c11

all:release

release:
	gcc $(CC) $(F_MAIN) $(F_HELPER) $(F_BROKER) $(L_MOSQUITTO) 

debug:
	gcc $(CC) $(F_MAIN) $(F_HELPER) $(F_BROKER) $(L_MOSQUITTO) -g

