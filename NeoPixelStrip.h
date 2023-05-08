#ifndef NEOPIXELSTRIP_H
#define NEOPIXELSTRIP_H

#include <Adafruit_Neopixel.h>
#include "NeoPixelColor.h"


private class NeoPixelAction {
  private uint32_t start_millis;
  private uint16_t time_millis;
  private uint8_t repeat;
}

class NeoPixelActionNone extends NeoPixelAction {
  public NeoPixelActionNone();
}

class NeoPixelActionBlink extends NeoPixelAction {
  public NeoPixelActionBlink(NeoPixelColor color);
}

class NeoPixelActionChase extends NeoPixelAction {
  public NeoPixelActionChase();
}

class NeopixelStrip {
public:
  NeoPixelStrip();
  void off();
  void on(NeoPixelColor& color);
  void blink(NeoPixelColor& color, uint32_t delay, uint8_t repeat);
  void chase(NeoPixelColor& color, uint32_t delay, uint8_t repeat);
  
  // Private members

  private uint8_t pin;
  private uint8_t num_pixels;
  
  //
  private NeoPixelAction action;
}

#endif // NEOPIXEL_OBJECT_H
