#ifndef NEOPIXELSTRIP_H
#define NEOPIXELSTRIP_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "NeoPixelColor.h"
#include "Handler.h"

enum STRIP_STATE {
  BLINK_STATE_START = 0,
  BLINK_STATE_ON,
  BLINK_STATE_WAIT_FOR_ON_EXPIRE,
  BLINK_STATE_OFF,
  BLINK_STATE_WAIT_FOR_OFF_EXPIRE,
  CHASE_STATE_START,
  STATE_TERMINAL,
};
  
class NeoPixelStrip: public Handler {
public:
  NeoPixelStrip(Adafruit_NeoPixel& pixels);
  void off();
  void on(NeoPixelColor& color);
  void blink(NeoPixelColor& color, uint16_t delay, uint8_t repeat);
  void chase(NeoPixelColor& color, uint16_t delay, uint8_t repeat);
  void handle();
  
private:
  void reset();

  Adafruit_NeoPixel& pixels;
  NeoPixelColor& color;

  // Initialized by reset() method:
  uint32_t start_time_millis;
  uint16_t delay_millis;
  uint8_t repeat_times;
  uint8_t last_pixel;
  enum STRIP_STATE state;

};

#endif // NEOPIXELSTRIP_H
