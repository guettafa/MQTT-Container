
# Project Title
This repo was made during my IDO programming course and it contains the code to receive a message from a pi and transmit it to an MQTT broker, change its format and re-send it to the pi.

## Context 
The pi is connected to a button + a LED 8x8 matrix and if this button is pressed, the number 1 is sent to a container that will publish to a broker and transform the format with a team number. The message is then retrieved from the broker and sent to the pi so the matrix will flash the led that correspond to the team number.

Ex : if team 4 pressed the button, the 4th led will turn on


## Installation

Debian

```bash
  sudo apt install mosquitto-clients libmosquitto-dev
```
Arch

```bash
  sudo pacman -S mosquitto
```
    
