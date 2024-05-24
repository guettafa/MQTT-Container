F_MAIN=./src/main.c 
F_SERVER=./src/server.c

L_MOSQUITTO=-lmosquitto
L_THREAD=-lpthread

CC=gcc -std=gnu99

COMPILE=$(CC) -I ./include

all: release

release:
	$(COMPILE) $(F_MAIN) $(F_SERVER) -o build/release  $(L_MOSQUITTO)

debug:
	$(COMPILE) -g $(F_MAIN) $(F_SERVER) -o build/debug  $(L_MOSQUITTO)