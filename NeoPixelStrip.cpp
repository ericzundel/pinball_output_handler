#include <stdint.h>
#include <stdlib.h>

#include "NeoPixelColor.h"
#include "NeoPixelStrip.h"

/****************************************************************************
 * NeoPixelStrip class
 ****************************************************************************/

NeoPixelStrip::NeoPixelStrip(Adafruit_NeoPixel& p) : pixels(p), color(NeoPixelColor::RED) {
  Serial.println("NeoPixelStrip::NeoPixelStrip()");
  this->off();
  this->handle();
}

void NeoPixelStrip::handle() {
  Serial.println("NeoPixelStrip::handle()");
  delay(1000);
  switch (this->state) {
  case BLINK_STATE_START:
    Serial.println("In BLINK_STATE_START");
    delay(1000);
    // Nothing to do, fall through to the next state
    
  case BLINK_STATE_ON:
    Serial.println("In BLINK_STATE_ON");
    delay(1000);
    for (int i = 0; i < this->pixels.numPixels(); i++) {
      this->pixels.setPixelColor(i, this->color.red(), this->color.green(), this->color.green());
    }
    this->pixels.show();
    this->state = BLINK_STATE_WAIT_FOR_ON_EXPIRE;
    Serial.print("End BLINK_STATE_ON");
    delay(1000);
    break;
    
  case BLINK_STATE_WAIT_FOR_ON_EXPIRE:
    if (this->start_time_millis - millis() >= this->delay_millis) {
      this->state = BLINK_STATE_OFF;
    } // else stay in this state
    break;
    
  case BLINK_STATE_OFF:
    Serial.println("In BLINK_STATE_OFF");
    this->pixels.clear();
    this->pixels.show();
    this->state = BLINK_STATE_WAIT_FOR_OFF_EXPIRE;
    break;
    
  case BLINK_STATE_WAIT_FOR_OFF_EXPIRE:
    if (this->start_time_millis - millis() >= this->delay_millis) {
      if (this->repeat_times > 0) {
	this->repeat_times--;
	this->start_time_millis = millis();
	this->state = BLINK_STATE_ON;
      } else {
	this->state = STATE_TERMINAL;
      }
    }
    break;

  case CHASE_STATE_START:
    // fall through
    
  default:
  case STATE_TERMINAL:
    Serial.println("In STATE_TERMINAL");
    // fall thorough
    break;    
  }
}

void NeoPixelStrip::reset() {
  Serial.println("reset()");
    this->start_time_millis = 0;
    this->delay_millis = 0;
    this->repeat_times = 0;
    this->state = STATE_TERMINAL;
    this->last_pixel = 0;
}

void NeoPixelStrip::off() {
  this->reset();
  this->pixels.clear();
  this->pixels.show();
}

void NeoPixelStrip::on(NeoPixelColor& color) {
  this->reset();
  this->state = STATE_TERMINAL;
  for (int i = 0; i < this->pixels.numPixels(); i++) {
    this->pixels.setPixelColor(i, color.red(), color.green(), color.green());
  }
  this->pixels.show();
}

void NeoPixelStrip:: blink(NeoPixelColor& color,
			   uint16_t delay_millis,
			   uint8_t repeat_times) {
  this->reset();
  this->color = color;
  this->start_time_millis = millis();
  this->delay_millis = delay_millis;
  this->repeat_times = repeat_times;

  // Start up the blink state machine
  this->state = BLINK_STATE_START;
}

void NeoPixelStrip::chase(NeoPixelColor& color, uint16_t delay, uint8_t repeat) {
  this->reset();
  this->color = color;
  this->start_time_millis = millis();
  this->delay_millis = delay_millis;
  this->repeat_times = repeat_times;
  
  // Start up the chase state machine
  this->state = CHASE_STATE_START;
}
