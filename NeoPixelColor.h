#ifndef NeoPixelColor_h
#define NeoPixelColor_h

#include <stdint.h>

class NeoPixelColor {
 public:
    NeoPixelColor(uint8_t red, uint8_t green, uint8_t blue);
    int red() { return this->red_value; };
    int green() { return this->green_value; };
    int blue() { return this->blue_value; };

    static NeoPixelColor& RED;
    static NeoPixelColor& GREEN;
    static NeoPixelColor& BLUE;
    static NeoPixelColor& WHITE;
    static NeoPixelColor& BLACK;
    
 private:
    uint8_t red_value;
    uint8_t green_value;
    uint8_t blue_value;
};

#endif //NeoPixelColor_h
