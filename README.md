# DroneEyes
A very simple little circuit controlled by an Atmel ATtiny13 microcontroller that gives your little 3.7V-powered drone crazy eyes! It's an easy mod.

To keep battery usage small and efficient and to keep the part count low and cheap I've implemented Charlieplexing to control more LEDs than the little 8-pin microcontroller has available. Technically, the ATtiny13 could ontrol upwards of dozens of LEDs with only 6 pins, but DroneEyes works and looks great with six "eyes."
