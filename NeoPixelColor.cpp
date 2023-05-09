#include "PinballOutputHandler.h"

NeoPixelColor& NeoPixelColor::RED = *(new NeoPixelColor(255, 0, 0));
NeoPixelColor& NeoPixelColor::GREEN = *(new NeoPixelColor(0, 255, 0));
NeoPixelColor& NeoPixelColor::BLUE = *(new NeoPixelColor(0, 0, 255));
NeoPixelColor& NeoPixelColor::WHITE = *(new NeoPixelColor(255, 255, 255));
NeoPixelColor& NeoPixelColor::BLACK = *(new NeoPixelColor(0, 0, 0));
NeoPixelColor& NeoPixelColor::MAGENTA = *(new NeoPixelColor(255, 0, 255));
NeoPixelColor& NeoPixelColor::PINK = *(new NeoPixelColor(225, 0, 100));
NeoPixelColor& NeoPixelColor::YELLOW = *(new NeoPixelColor(255, 255, 0));

NeoPixelColor::NeoPixelColor(uint8_t red, uint8_t green, uint8_t blue) {
  this->red_value = red;
  this->green_value = green;
  this->blue_value = blue;
}
