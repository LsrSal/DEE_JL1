# DEE_JL1
Alternative firmware for JL1 laser engraver boards.

JL1 board used in number of laser engravers, from homonymous machine to number others, unsurprisingly named JL2, JL3 etc. Some are re-branded of the same.
It came with firmware and software with non-standard protocol and not supported by most popular software that speaks laser GRBL dialect of G-code.

Hardware is based on ST32F103 MCU and couple A5988 stepper driver ICs (very similar to A4988. Open source code for this platform is available.

Intent of this project is to help with freeing JL1 based laser machines from limitations of custom protocol and extremely limited software selection.

This project is compiled exclusively from publicly available sources.

# Programming
At this time the only tested method is by using ST Link, ST Link V2 in particular. These are readily available on Amazon and AliExpress, cost about $10.
JL1 board has unpopulated 4-pin header that is actually ST Link interface.
Please be careful and connect ST Link power only to 3.3V source. 5V may damage the board.
When ST Link interface is connected - no need for additional power sources for the board. It is powered through the link.
There might be other ways to program it, including over serial connection. Read guides for programming "Blue Pill" boards as JL1 using the same MCU.

Exact method of programming JL1 board at this time is beyond the scope of present project.
