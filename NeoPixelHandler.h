#ifndef NEOPIXELSTRIP_H
#define NEOPIXELSTRIP_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "NeoPixelColor.h"
#include "Handler.h"

enum STRIP_STATE {
  STATE_START = 0,
  STATE_ON,
  STATE_OFF,
  STATE_RAINBOW,
  BLINK_STATE_START,
  BLINK_STATE_ON,
  BLINK_STATE_WAIT_FOR_ON_EXPIRE,
  BLINK_STATE_OFF,
  BLINK_STATE_WAIT_FOR_OFF_EXPIRE,
  CHASE_STATE_START,
  CHASE_STATE_NEXT_PIXEL,
  CHASE_STATE_WAIT_ON_NEXT_PIXEL,
  CHASE_STATE_ONE_ITERATION_COMPLETE,
  RAINBOW_CYCLE_STATE_START,
  RAINBOW_CYCLE_STATE_NEXT_COLOR,
  RAINBOW_CYCLE_STATE_WAIT_ON_NEXT_COLOR,
  RAINBOW_CYCLE_STATE_ONE_ITERATION_COMPLETE,
  STATE_TERMINAL,
};
  
class NeoPixelHandler: public Handler {
public:
  NeoPixelHandler(Adafruit_NeoPixel& pixels);
  void off();
  void on(NeoPixelColor& color);
  void rainbow();
  void blink(NeoPixelColor& color, int delay, int repeat);
  void chase_up(NeoPixelColor& color, int delay, int repeat);
  void chase_down(NeoPixelColor& color, int delay, int repeat);
  void rainbow_cycle(int delay, int repeat);
  void handle();
  
private:
  void reset();
  void chase(NeoPixelColor& color, int delay, int repeat, int direction);
  
  Adafruit_NeoPixel& pixels;
  NeoPixelColor color; // Used by actions other than STATE_ON
  NeoPixelColor default_color;// Used by STATE_ON
  enum STRIP_STATE default_state; // default back to STATE_RAINBOW. STATE_ON or STATE_OFF
  int32_t cycle_color_start_millis; // used by rainbow_cycle
  long first_pixel_hue;

  // Initialized by reset() method:
  int32_t start_time_millis;
  int delay_millis;
  int repeat_times;
  uint8_t last_pixel; // used by chase and rainbow_chase
  enum STRIP_STATE state;
  int direction;

};

#endif // NEOPIXELSTRIP_H
