 
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <OutputHandler.h>
#include <NeoPixelColor.h>
#include <NeoPixelHandler.h>
 
OutputHandler outputHandler;
NeoPixelHandler *handlers[6]; // to hold handlers that can control 6 strips

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("Initializing in 5 seconds");
  delay(5000);
  Serial.println("Initializing");
  Serial.println("Send a number to simulate a button");
  
  // Add six handlers that have 10 LEDs each on different output pins of the Arduino
  handlers[0] = outputHandler.add(*(new Adafruit_NeoPixel(10, 17, NEO_GRB + NEO_KHZ800)));
  handlers[1] = outputHandler.add(*(new Adafruit_NeoPixel(10, 19, NEO_GRB + NEO_KHZ800)));
  handlers[2] = outputHandler.add(*(new Adafruit_NeoPixel(10, 21, NEO_GRB + NEO_KHZ800)));
  handlers[3] = outputHandler.add(*(new Adafruit_NeoPixel(10, 22, NEO_GRB + NEO_KHZ800)));
  handlers[4] = outputHandler.add(*(new Adafruit_NeoPixel(10, 26, NEO_GRB + NEO_KHZ800)));
  handlers[5] = outputHandler.add(*(new Adafruit_NeoPixel(10, 28, NEO_GRB + NEO_KHZ800)));
}

void loop() {
 //debug("loop");

 // I don't have buttons on my test board, I'm simulating by pressing keys on the keyboard
 if (Serial.available()) {
    // read the incoming byte
    char incomingByte = Serial.read();
    switch (incomingByte) {
      case '0':
         // Blink strip 0
         Serial.println("Blinking Strip 0");
         handlers[0]->blink(NeoPixelColor::GREEN, 100, 10);
         break;
         
     case '1':
         // Blink strip 1
         Serial.println("Blinking Strip 1");
         handlers[1]->blink(NeoPixelColor::RED, 250, 5);
         break;
         
     case '2':
         // Blink strip 2
         Serial.println("Blinking Strip 2");
         handlers[2]->blink(NeoPixelColor::PINK, 200, 20);
         break;    

     case '3':
         // Blink strip 3
         Serial.println("Blinking Strip 3");
         handlers[3]->blink(NeoPixelColor::WHITE, 100, 30);
         break;

     case '4':
         // Blink strip 4
         Serial.println("Blinking Strip 4");
         handlers[4]->blink(NeoPixelColor::MAGENTA, 1000, 10);
         break;    

     case '5':
         // Blink strip 5
         Serial.println("Blinking Strip 5");
         handlers[5]->blink(NeoPixelColor::YELLOW, 1000, 10);
         break;     
     default:
         Serial.print("Didn't understand input: ");
         Serial.println(incomingByte);
    }
 }
 outputHandler.handleAll();
}
