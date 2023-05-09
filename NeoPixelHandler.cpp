#include <stdint.h>
#include <stdlib.h>

#include "NeoPixelColor.h"
#include "NeoPixelHandler.h"

/****************************************************************************
 * NeoPixelHandler class
 ****************************************************************************/

NeoPixelHandler::NeoPixelHandler(Adafruit_NeoPixel& p) : pixels(p), color(NeoPixelColor::RED) {
  debug("NeoPixelHandler::NeoPixelHandler()");
  this->off();
  this->handle();
}

void NeoPixelHandler::handle() {
  //debug("NeoPixelHandler::handle()");
  enum STRIP_STATE next_state = this->state;
  
  switch (this->state) {
  case BLINK_STATE_START:
    debug("In BLINK_STATE_START");
    // Nothing to do, fall through to the next state
    
  case BLINK_STATE_ON:
    debug("In BLINK_STATE_ON");
    this->start_time_millis = millis();
    for (int i = 0; i < this->pixels.numPixels(); i++) {
      this->pixels.setPixelColor(i, pixels.Color(this->color.red(), this->color.green(), this->color.blue()));
    }
    this->pixels.show();
    next_state = BLINK_STATE_WAIT_FOR_ON_EXPIRE;
    debug("End BLINK_STATE_ON");
    break;
    
  case BLINK_STATE_WAIT_FOR_ON_EXPIRE:
    debug("in BLINK_STATE_WAIT_FOR_ON_EXPIRE");
    if (millis() - this->start_time_millis >= this->delay_millis) {
      next_state = BLINK_STATE_OFF;
    } else {
            // do nothing. Say in this state.
    }
    break;
    
  case BLINK_STATE_OFF:
    debug("In BLINK_STATE_OFF");
    this->start_time_millis = millis();
    this->pixels.clear();
    this->pixels.show();
    next_state = BLINK_STATE_WAIT_FOR_OFF_EXPIRE;
    break;
    
  case BLINK_STATE_WAIT_FOR_OFF_EXPIRE:
    debug("in BLINK_STATE_WAIT_FOR_OFF_EXPIRE");
    if (millis() - this->start_time_millis >= this->delay_millis) {
      if (this->repeat_times > 1) {
	this->repeat_times--;
	this->start_time_millis = millis();
	next_state = BLINK_STATE_ON;
      } else {
	next_state = STATE_TERMINAL;
      }
    } else {
      // do nothing. Say in this state.
    }
    break;

  case CHASE_STATE_START:
    // fall through
    
  default:
  case STATE_TERMINAL:
    //debug("In STATE_TERMINAL");
    // fall thorough
    break;    
  }

  this->state = next_state;
}

void NeoPixelHandler::reset() {
  debug("reset()");
    this->start_time_millis = 0;
    this->delay_millis = 0;
    this->repeat_times = 0;
    this->state = STATE_TERMINAL;
    this->last_pixel = 0;
}

void NeoPixelHandler::off() {
  this->reset();
  this->pixels.clear();
  this->pixels.show();
}

void NeoPixelHandler::on(NeoPixelColor& color) {
  this->reset();
  this->state = STATE_TERMINAL;
  for (int i = 0; i < this->pixels.numPixels(); i++) {
    this->pixels.setPixelColor(i, color.red(), color.green(), color.green());
  }
  this->pixels.show();
}

void NeoPixelHandler::blink(NeoPixelColor& color,
			   int delay_millis,
			   int repeat_times) {
  this->reset();
  this->color = color;
  this->start_time_millis = millis();
  this->delay_millis = delay_millis;
  this->repeat_times = repeat_times;

  // Start up the blink state machine
  this->state = BLINK_STATE_START;
}

void NeoPixelHandler::chase(NeoPixelColor& color, int delay, int repeat) {
  this->reset();
  this->color = color;
  this->start_time_millis = millis();
  this->delay_millis = delay_millis;
  this->repeat_times = repeat_times;
  
  // Start up the chase state machine
  this->state = CHASE_STATE_START;
}
