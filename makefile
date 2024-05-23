F_SERVER=./src/server.c
F_CLIENT=./src/client.c
F_MQTT=./src/mqtt.c

L_MOSQUITTO=-lmosquitto
L_THREAD=-lpthread

GNU_SOURCE=-D_GNU_SOURCE

CC=-std=gnu99

COMPILE=gcc $(CC) -I ./include

clean:
	rm -rf build/mqtt build/server build/client

mqtt:
	$(COMPILE) $(F_MQTT) -o build/mqtt $(L_MOSQUITTO)

server:
	$(COMPILE) -g $(F_SERVER) -lpthread -o build/server

client:
	$(COMPILE) $(F_CLIENT) -o build/client
