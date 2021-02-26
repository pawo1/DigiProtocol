# DigiProtocol
DigiProtocol is Library designed for Communication with DigiSpark over USB. 
It’s based on DigiUSB library but adds protocol-frame.

Full documentation available at 
[docs.pandretix.pl/digiprotocol](https://docs.pandretix.pl/digiprotocol/)

You can read more about project at [my website](https://pandretix.pl/en/digiprotocol/)

Currently tools binaries and makefile is available only for Windows. In next 
commit I'll add Linux support. 

## Requirements

To use DigiProtocol you will need both [libusb](https://libusb.info) for PC, and
DigiUSB for DigiSpark (available in ArduinoIDE libraries).

## Installation

Using DigiProtocol is pretty easy. On PC side it's header only library, so you
can add it to your include directory, or add path to it during compilation.

On the AVR side, you have to add library to ArduinoIDE. Choose Digiprotocol.zip 
in Library Manager, or unzip it manually to the Arduino library directory.

