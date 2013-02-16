The GuardPuppy is a simple application for Olimex SAM7EX256 board. 
The goal is to monitor the microphone input and alarm when my baby wakes up :). Not so complicated, isn't it?

Feel free to reuse... when it will be finished >:-).

OS: ChibiOS 2.4
Target: AT91SAM7X256
Board: Olimex SAM7EX256
Debugger: Olimex ARM-USB-TINY-H


The IP address: 192.168.1.20 (static)
Serial config: 38400 8/N/1

---------------------------------------------------------------------------------------------------------------------
Notes:

The flashing is solved via an USB JTAG device (see Debugger) and can be done with OpenOCD with the following command:
openocd -f interface/olimex-arm-usb-tiny-h.cfg -f armflash.cfg 

The cross compiler is Sourcery CodeBench Lite (arm-none-eabi 2012.03.56-1).

I'm using Eclipse on a Linux/FreeBSD for development and debugging but using a Makefile. Because of this the compilation on other os us not tested.

Links:
https://www.olimex.com/Products/ARM/Atmel/SAM7-EX256/
https://www.olimex.com/Products/ARM/JTAG/ARM-USB-TINY-H/