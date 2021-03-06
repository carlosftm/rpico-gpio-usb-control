# Control of GPIO with commands trough USB CDC with Raspberry Pi Pico.

This project was created to control a 5V Relay with RaspberryPi Pico board that connected to a PC or RPi via virtual Com-Port (USB CDC). The board is controlled with commands entered by the user on a terminal like Putty, minicom, Tereaterm, etc.

In order to avoid triggering the relay by a mistyped character, the command are to be entered as follow:
1. Type '>' to indicate the beginning of a commands
1. Now type 'r' or 'R' to indicate that you what to control the GPIO-15 that will trigger the optocoupler that activates the relay.
1. Finally enter the state you want to set the GPIO. '1' for GPIO high (3.3v) and '0' to set the GPIO low (0v).

The same functionality is replicated to control the on-board LED and 4 additional GPIO.

This is the list of additional commands:
* *'L'* or *'l'*: To control the on-board LED connected to GPIO-25
* *'0'*,*'1'*,*'2'*,*'3'*: To control GPIO-0 to GPIO-3 respectively

To obtain help, the user needs to type '?'. The same message appears after the board is booted and the on-board LED flashed for some second as booting up indication.

**Caution! The software might be over engineered** as such a simple functionality could be done by just mapping strings to functions. But the idea is to have fun programming and take the chance to make use of software engineering concepts like the finite state machine (FSM) used in this example.

