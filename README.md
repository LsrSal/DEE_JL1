# DEE_JL1
Alternative firmware for JL1 laser engraver boards.

JL1 board used in number of laser engravers, from homonymous machine to number others, unsurprisingly named JL2, JL3 etc. Some are re-branded of the same.
It came with firmware and software with non-standard protocol and not supported by most popular software that speaks laser GRBL dialect of G-code.

Hardware is based on ST32F103 MCU and couple A5988 stepper driver ICs (very similar to A4988. Open source code for this platform is available.

Intent of this project is to help with freeing JL1 based laser machines from limitations of custom protocol and extremely limited software selection.

This project is compiled exclusively from publicly available sources.

# Variants
As of this writing, the only variation detected in the wild are flash size of the STM32F103. This variation is well documented in Arduino world and apparently also spilled into JL1 boards.
Two variants have flash size of 64K vs 128K.

# Other firmware alternatives
Thre is "JL3" firmware floating around, provided by Wainlux, which sell "JL3" model. It is generally identical to JL1 with some differences but uses exactly the same JL1 board. As a result JL3 firmware is usable on JL1 frame with some limitations. It is required Windows executable to upload, but upload process is very simple.
Main benefit of using JL3 firmware is simple flashing with only USB cable and factory bootloader. Drawback is impossibility of using hard homing cycle, because home switches located at different corners and offset in JL3 firmware is hard coded and not configurable. Using hard homing cycle on JL1 frame with JL3 firmware will cause running into limit. Most use it without any issues with hard homing disabled and homing by hand before powering up.

There is another effort to get latest and greatest code base for JL1 GRBL firmware: https://github.com/dlarue/STM32F1xx
As of this writing the main limitation of that effort is compiled firmware size. It is still bigger than 64K limitation of some JL1 boards.
If you like to fiddle with the code - I would advice to rather take that project as starting point. It is still in active development and expected to be up to date.

# Programming
At this time the only tested method is by using ST Link, ST Link V2 in particular. These are readily available on Amazon and AliExpress, cost about $10.
JL1 board has unpopulated 4-pin header that is actually ST Link interface.
Please be careful and connect ST Link power only to 3.3V source. 5V may damage the board.
When ST Link interface is connected - no need for additional power sources for the board. It is powered through the link.
There might be other ways to program it, including over serial connection. Read guides for programming "Blue Pill" boards as JL1 using the same MCU.

Exact method of programming JL1 board at this time is beyond the scope of present project.
(It is confirmed that JL1 board can be flashed with serial_over_USB, without STLink, by jumping BOOT0 to VCC before applying power, using chip's built in serial boot loader. BOOT0 is available at R19.)

# FYI
Provided firmware supporting laser cross pointer that is included with JL1 frame (missing from other JL* frames.) Laser pointer driver is tied to M7 and M8 commands to turn ON and M9 to turn off. LaserGRBL framing code (UI button edit) can be easily modified to support that pointer, including custom offsets. Others may chose to use that output for air assist or cooling. Just for you to know: that laser pointer output is supported and available.

# Wireless mod
It is not essential but still convenient to operate this machine wirelessly. One slow weekend I got inspiration to try to make my JL1 wireless. Need a few pieces to make it work: STM firmware talking on second serial port, ESP firmware to make wireless-to-serial bridge, and maybe convenience firmware to make easy acces to ESP through existing USB.

First I need to recompile firmware to move STM serial from USART 1 to 2. Additionally need to drive Enable pin of ESP high. "JL1 V2_2 GRBL COM2.hex" is identical to original JL1 V2 in every way except pull-up ESP enable and different serial interface.
For wireless_to_serial I use ESP-LINK https://github.com/jeelabs/esp-link. Installation of ESP link is beyond scope of this work as there are many guides. If you decided to use ESP-LINK: after completing obvious installation and configuration - go to last tab and disable logging, as these messages will pollute GRBL communication. Nothing else really. Just connect to it over Telnet or Web-socket or whatever. ESP-link is not the only ESP wireless to serial bridge, there are many. Even Arduino has library that can be easily customized and adopted. Make your own choise. For me ESP-LINK just works.
And the last one, convenience: I wrote quick utility Arduino code for transparent serial bridge to access SEP on existing USB/serial interface. Makes flashing ESP very easy. You still may prefer to add one wire to enable ESP flashing mode - see image.png above. It connects existing button to ESP pin to enable flashing.

Originally I tap directly to ESP pins to flash ESP12F module. This is less than convenient and task not for everyone. Trying to access ESP programmatically with transparent serial pipe connecting STM UART 1 and 2 was not very successful: I was able to start flashing ESP but never able to complete it. Something about very specific timing and changing baud rate and probably buffer overflow. Eventually I made a bit_repeater that is protocol agnostic, has minimal latency and works just fine for 115200 baud UART. See attached Arduino sketch. You may recompile it yourself or use precompiled binary.

You still need ST_Link dongle to flash STM (easy way) or flash over serial (hard way. It works, confirmed, but to me not worth $10 to struggle). Flash STM with "bit repeater" first, then flash ESP with whatever wireless to serial you chose, then flash STM again with GRBL COM2  firmware.
To flash ESP - do the mod - add wire to button. To flash ESP - keep 12V off, start flashing, press and hold button, apply 12V power, when see programming started - you may let button go.

Reminder, apparently me and other folks done it: this probably will be done with board out of enclosure and board disconnected form all harnesses. Power switchis on front panel, your board is not dead, but power switch is not ON. Take panel with board or use jumper in the power switch connector. And once again: ST_Link use 3.3V power pin, never 5V.

Enjoy one less wire in the clutter!
