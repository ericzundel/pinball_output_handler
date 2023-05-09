/*
 * output_handler_example - Example file for using the PinballOutputHandler library.
 * Author: Eric Z. Ayers <ericzundel@gmail.com>
 * 
 * The library weaps the AdafruitNeopixel library in order to perform effects
 * in the background without calling delay() to block your program.
 * This works by keeping state in the handler objects and then activating a
 * state machine for each handler when handleAll() is called in the main loop.
 * 
 * See https://github.com/ericzundel/pinball_output_handler
 */
#include <PinballOutputHandler.h>

// This object holds all of your background handlers.  To execute the handlers, call outputHandler.handleAll()
// in loop().
OutputHandler outputHandler;

// Initialize all the neopixel strips and save them in an array so you can
// change values like brightness later.
#define NUM_STRIPS 6

Adafruit_NeoPixel pixels[NUM_STRIPS] = {
  // Initialize the strips with the number of LEDS, pin number, and init parameters.
  // Replace the pin numbers with the pins you are using for your neopixel strips
  Adafruit_NeoPixel(10, 17, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(10, 19, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(10, 21, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(10, 22, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(10, 26, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(10, 28, NEO_GRB + NEO_KHZ800)
};

// An array to hold output handlers that correspond to the strips
NeoPixelHandler *handlers[NUM_STRIPS]; // to hold handlers that can control 6 strips

// Define custom colors here
NeoPixelColor cyan(0, 255, 255);

void setup() {
  Serial.begin(9600);
  Serial.println("Send in the Serial Monitor a number to simulate a button");

  // Initialize the output handler with the neopixel strip objects. Save the handler objects for later.
  for (int i = 0; i < NUM_STRIPS; i++) {
    handlers[i] = outputHandler.add(pixels[i]); // Note, this library calls begin() on the Adafruit_NeoPixel library.
    pixels[i].setBrightness(25); // Set brightness to 10% to save power.
  }
} // end setup()

void loop() {
  //debug("loop");

  // I don't have buttons on my test board, I'm simulating by sending numbers over the Serial Monitor.
  if (Serial.available()) {
    char incomingByte = Serial.read();

    Serial.print("Got input: ");
    Serial.println(incomingByte);
    if (incomingByte == '0') {
      Serial.println("Blinking Strip 0 with custom color CYAN");
      // Call the handler to start the blink. The actuall blinking is handled when you call handleAll();
      // blink (color, delay in milliseconds, number of times to repeat)
      handlers[0]->blink(cyan, 100, 40);
    } else if (incomingByte == '1') {
      Serial.println("Blinking Strip 1 RED");
      handlers[1]->blink(NeoPixelColor::RED, 250, 5);
    } else if (incomingByte == '2') {
      Serial.println("Blinking Strip 2 PINK");
      handlers[2]->blink(NeoPixelColor::PINK, 200, 20);
    } else if (incomingByte == '3') {
      Serial.println("Blinking Strip 3 GREEN");
      handlers[3]->blink(NeoPixelColor::GREEN, 100, 30);
    } else if (incomingByte == '4') {
      Serial.println("Setting strip 0 to MAGENTA");
      handlers[0]->on(NeoPixelColor::MAGENTA);
    } else if (incomingByte == '5') {
      Serial.println("Turning off strip 0");
      handlers[0]->off();
    } else if (incomingByte == '6') {
      Serial.println("Chasing strip 0 up in YELLOW");
      // chase_up(color, delay in milliseconds, number of times to repeat)
      handlers[0]->chase_up(NeoPixelColor::YELLOW, 50, 6);
    } else if (incomingByte == '7') {
      Serial.println("Chasing strip 0 down in BLUE");
      // chase_down(color, delay in milliseconds, number of times to repeat)
      handlers[0]->chase_down(NeoPixelColor::BLUE, 100, 5);
    } else if (incomingByte == '8') {
      Serial.println("Rainbow cycle strip 0");
      // rainbow_cycle(delay in milliseconds, number of times to repeat
      handlers[0]->rainbow_cycle(1000, 4);
    } else if (incomingByte == '9') {
      Serial.println("Rainbow strip 0");
      // make the strip light up in rainbow colors
      handlers[0]->rainbow();
    } else if (incomingByte == '\n') {
      // ignore newlines
    } else {
      Serial.print("Didn't understand input: ");
      Serial.println(incomingByte);
    }
  }

  // Call the output Handler every time you go through the main loop.
  outputHandler.handleAll();
} // end loop()
