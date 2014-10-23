GuardPuppy
==============

Description:
--------------
The GuardPuppy is a simple application for **Olimex SAM7EX256** board. 
The goal is to monitor the microphone input and alarm when my baby wakes up :). Not so complicated, isn't it?

Feel free to reuse... when it will be finished >:-).

- OS: **ChibiOS-master** (new SAM7EX256 HAL support)
- Compiler: Sourcery CodeBench Lite (arm-none-eabi 2012.03.56-1)
- Target: AT91SAM7X256
- Board: Olimex SAM7EX256
- Debugger: Olimex ARM-USB-TINY-H
- IP address: 192.168.1.20 (static)
- Serial config: 38400 8/N/1

---------------------------------------------------------------------------------------------------------------------
Notes:
--------------
1. The flashing is solved via an USB JTAG device (see armflash.cfg or armdebug.cfg for details).

2. In case of openocd privilege problem (works only with root access) add a file to udev rules as follows:

	**/etc/udev/rules.d/82-olimex-arm-usb-tiny-h.rule**
<pre>
    SUBSYSTEM=="usb", ACTION=="add", ATTR{idProduct}=="002a", ATTR{idVendor}=="15ba", MODE="666", GROUP="plugdev"
</pre>
and for root usage add to dialup group
<pre>
sudo usermod -a -G dialout $USER
</pre>
3. Set the correct location in Makefile for CHIBIOS variable!

4. I'm using Eclipse on a Linux/FreeBSD for development and debugging but using a Makefile. Because of this the compilation on other OS is possible but not tested.

5. The ChibiOS version was changed from 2.6.6 stable. Place relative to project like this: <B>CHIBIOS = ../../ARM/ChibiOS</B>

---------------------------------------------------------------------------------------------------------------------
Links:
--------------
* https://www.olimex.com/Products/ARM/Atmel/SAM7-EX256/
* https://www.olimex.com/Products/ARM/JTAG/ARM-USB-TINY-H/
