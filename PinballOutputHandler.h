#ifndef PINBALLOUTPUTHANDLER_H
#define PINBALLOUTPUTHANDLER_H

/**
 * PinballOutputHandler.h Common include file for the library.
 */
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "Handler.h"
#include "OutputHandler.h"
#include "NeopixelColor.h"
#include "NeopixelHandler.h"

static void debug(String value) {
  //Serial.println(value);
  //delay(500);
}

static void debug(int value) {
  //Serial.println(value);
  //delay(100);
}

#endif
