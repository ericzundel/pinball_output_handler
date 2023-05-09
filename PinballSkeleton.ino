 

#include <Adafruit_NeoPixel.h>

#include "OutputHandler.h"
#include "NeoPixelColor.h"
#include "NeoPixelStrip.h"

Adafruit_NeoPixel adafruit_strip(22, 10);
NeoPixelStrip mystrip(adafruit_strip);
OutputHandler outputHandler;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("Initializing in 5 seconds");
  delay(5000);
  Serial.println("Initializing");

  adafruit_strip.begin();
 
  outputHandler.add(mystrip);
  mystrip.blink(NeoPixelColor::BLUE, 500, 5);
}

void loop() {
 // put your main code here, to run repeatedly:
 delay(100);
 Serial.println("loop");
 outputHandler.handleAll();
 //if (digitalRead(bumperPin) == HIGH) {
 // mystrip.blink(....);
 //}
}
