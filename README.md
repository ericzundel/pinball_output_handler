# PinballOutputHandler
A library that handles non-blocking control of the elements of a pinball machine.
Intended for use in the Drew Charter School Engineering Pinball machine project.

See `output_handler_example.ino` for example code.

## Purpose

This library is mean to allow the pinball machine to service multiple inputs and outputs without blocking.  The most pressing problem was how to create visual effects with the NeoPixel strips without blocking the rest of the code from processing inputs from the targets, bumpers, and flippers.  

The class `NeoPixelHandler` has logic that wraps some of the functionality of the `Adafruit_NeoPixel` library and makes effects like blinking or animating the strip with a rainbow into a single function call.  

It is important that you not use `delay()` or other calls that block the code if you want your animation effects to be smooth.

## Implementation
The library creates multiple instances of a state machine that are periodically serviced throug a call to `OutputHandler::handleAll()`.  After initializing the list of output handlers, all you need to do is invoke the method on the handler you want (like blink() or rainbow()) and make sure that handleAll() is called inside the main Arduino loop.

## Background

Students in the 3rd year engineering curriculum at Charles R. Drew Charter
School in Atlanta, Georgia built pinball machines in a year long project.
The project had students use many of the skills they had learned in previous years including:

- Prototyping
 - CAD
 - Laser Cutting wood and plastic
 - 3D Printing
 - CNC machining
 - C++ programming
 - Large format printing

Our environment includes programming in the Arduino platform, OnShape CAD, ShopBot CNC and Shapeoko CNCs, Glowforge laser cutters, an HP Latex 115 wide format printer, and a fleet of Ender 3 Pro 3D Printers.

The teacher supplied a common cabinet design machined out of wood.  They designed custom flippers, bumpers, ball guides, targets, backgrounds and obstacles for their machines. They used off the shelf parts like Ardino UNOs and Nanos, LCD panels, neopixel strips, solenoids, switches, solid state relays and buttons.
multiple neopixel strips.  The rest they fabricated themselves with the machines in the lab.

