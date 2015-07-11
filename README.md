# DroneEyes
A very simple little circuit controlled by an Atmel ATtiny13 microcontroller that gives your little 3.7V-powered drone crazy eyes! It's an easy mod.

To keep battery usage small and efficient and to keep the part count low and cheap I've implemented Charlieplexing to control more LEDs than the little 8-pin microcontroller has available. Technically, the ATtiny13 could ontrol upwards of dozens of LEDs with only 6 pins, but DroneEyes works and looks great with six "eyes."

## Compiling and Flashing Chip

I use Atmel's AVR ISP Mark II programmer. It's shit-simple and works great. I'll update this README with a URL to the article on StuffAndyMakes.com where I talk about how I programmed the ATtiny13's for this project.

I everything on Apple equipment. Can't stand Windoze, sorry. If you're on Windoze, AtmelStudio 6 makes programming your chips simple, too. I'd recommend downloading that to do it. No sense in using the command line when you have a well-optimized IDE around the AVR chips. Atmel has all you need to know about it here: http://www.atmel.com/tools/atmelstudio.aspx

If you're going the command line route, this project depends on avrdude and avr-gcc and the like. These are included in the Arduino IDE, but making that work on the command line isn't a cake walk. The better way to get out from under the thumb of the Arduino environment is to install the AVR toolchain yourself. You can get the entire thing with the CrossPack installer here: https://www.obdev.at/products/crosspack/index.html

In this repo I've included the build and flash scripts for bash. Make sure they're executable. Do what you will with the C file, run the build script, make sure the AVR ISP MkII programmer is hooked up to your chip and then run the flash script.

## Give Back

If you do something new and cool with the firmware, please share back with me.
