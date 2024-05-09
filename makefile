FILE_MAIN=./src/main.c
F_HELPER=./src/helper.c
F_BROKER=./src/broker.c

L_MOSQUITTO=-lmosquitto

F_OUTPUT=-o broker

CC=-std=c11

COMPILE=gcc $(CC) $(F_MAIN) $(F_HELPER) $(F_BROKER) $(L_MOSQUITTO) 

all:release

release:
	$(COMPILE)

debug:
	$(COMPILE) -g	
