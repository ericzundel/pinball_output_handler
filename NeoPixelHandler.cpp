#include <stdint.h>
#include <stdlib.h>

#include "NeoPixelColor.h"
#include "NeoPixelHandler.h"

/****************************************************************************
 * NeoPixelHandler class
 ****************************************************************************/

NeoPixelHandler::NeoPixelHandler(Adafruit_NeoPixel& p) : pixels(p), color(NeoPixelColor::RED),
							 default_color(NeoPixelColor::RED){
  debug("NeoPixelHandler::NeoPixelHandler()");
  this->off();
  this->handle();
}

void NeoPixelHandler::handle() {
  //debug("NeoPixelHandler::handle()");
  enum STRIP_STATE next_state = this->state;
  const int rainbow_cycle_delay_millis = 2;
  
  switch (this->state) {
  case STATE_START:
    // Currently UNUSED
    next_state = STATE_TERMINAL;
    break;
    
  case STATE_ON:
    pixels.clear();
    for (int i = 0; i < this->pixels.numPixels(); i++) {
      this->pixels.setPixelColor(i, pixels.Color(this->default_color.red(), this->default_color.green(), this->default_color.blue()));
    }
    this->pixels.show();
    next_state = STATE_TERMINAL;
    break;
    
  case STATE_OFF:
    this->pixels.clear();
    this->pixels.show();
    next_state = STATE_TERMINAL;
    break;
    
  case STATE_RAINBOW:
    this->pixels.clear();
    this->pixels.rainbow(0);
    this->pixels.show();
    next_state = STATE_TERMINAL;
    break;    
    
  case BLINK_STATE_START:
    debug("In BLINK_STATE_START");
    // Nothing to do, fall through to the next state
    
  case BLINK_STATE_ON:
    //debug("In BLINK_STATE_ON");
    this->start_time_millis = millis();
    for (int i = 0; i < this->pixels.numPixels(); i++) {
      this->pixels.setPixelColor(i, pixels.Color(this->color.red(), this->color.green(), this->color.blue()));
    }
    this->pixels.show();
    next_state = BLINK_STATE_WAIT_FOR_ON_EXPIRE;
    debug("End BLINK_STATE_ON");
    break;
    
  case BLINK_STATE_WAIT_FOR_ON_EXPIRE:
    //debug("in BLINK_STATE_WAIT_FOR_ON_EXPIRE");
    if (millis() - this->start_time_millis >= this->delay_millis) {
      // Timer has expired      
      next_state = BLINK_STATE_OFF;
    } else {
            // do nothing. Say in this state.
    }
    break;
    
  case BLINK_STATE_OFF:
    //debug("In BLINK_STATE_OFF");
    this->start_time_millis = millis();
    this->pixels.clear();
    this->pixels.show();
    next_state = BLINK_STATE_WAIT_FOR_OFF_EXPIRE;
    break;
    
  case BLINK_STATE_WAIT_FOR_OFF_EXPIRE:
    //debug("in BLINK_STATE_WAIT_FOR_OFF_EXPIRE");
    if (millis() - this->start_time_millis >= this->delay_millis) {
      // Timer has expired
      if (this->repeat_times > 1) {
	// Reset so we can repeat the blink
	this->repeat_times--;
	this->start_time_millis = millis();
	next_state = BLINK_STATE_ON;
      } else {
	// We've repeated the max number of times
	next_state = this->default_state;
      }
    } else {
      // do nothing. Say in this state.
    }
    break;

  case CHASE_STATE_START:
    //debug("in CHASE_STATE_START");
    if (this->direction > 0) {
      this->last_pixel = -1;
    } else {
      this->last_pixel = this->pixels.numPixels();
    }
    next_state = CHASE_STATE_NEXT_PIXEL;
    break;
    
  case CHASE_STATE_NEXT_PIXEL:
    //debug ("in CHASE_STATE_NEXT_PIXEL");
    this->last_pixel += this->direction;
    debug ("last pixel is");
    debug(this->last_pixel);
    this->pixels.setPixelColor(this->last_pixel, pixels.Color(this->color.red(), this->color.green(), this->color.blue()));
    this->pixels.show();
    next_state = CHASE_STATE_WAIT_ON_NEXT_PIXEL;
    break;
    
  case CHASE_STATE_WAIT_ON_NEXT_PIXEL:
    //debug ("in CHASE_STATE_WAIT_ON_NEXT_PIXEL");    
    if ((millis() - this->start_time_millis) >= this->delay_millis) {
      // Timer has expired, reset it
      debug("timer expired");
      this->start_time_millis = millis();
      
      if (this->direction > 0 && (this->last_pixel >= (this->pixels.numPixels()-1))) {
	// All pixels are now lit
	next_state = CHASE_STATE_ONE_ITERATION_COMPLETE;
      } else if (this->direction < 0 && (this->last_pixel <= 0)) {
	// All pixels are now lit	
	next_state = CHASE_STATE_ONE_ITERATION_COMPLETE;
      } else {
	// Proceed to light up the next pixel
	next_state = CHASE_STATE_NEXT_PIXEL;
      }
    } else {
      // do nothing. Say in this state.
    }
    break;

  case CHASE_STATE_ONE_ITERATION_COMPLETE:
    //debug("in CHASE_STATE_ONE_ITERATION_COMPLETE");
    if (this->repeat_times > 1) {
      // Reset so we can repeat the chase	
	this->repeat_times--;
	this->start_time_millis = millis();
	pixels.clear();
	next_state = CHASE_STATE_START;
      } else {
	// We've chased the max number of times
	next_state = this->default_state;
      }    
    break;
    
  case RAINBOW_CYCLE_STATE_START:
    debug("in RAINBOW_CYCLE_STATE_START");
    this->first_pixel_hue = 0; // represents the start color on the color wheel
    this->start_time_millis = millis();
    next_state = RAINBOW_CYCLE_STATE_NEXT_COLOR;
    break;
    
  case RAINBOW_CYCLE_STATE_NEXT_COLOR:
    //debug("in RAINBOW_CYCLE_STATE_NEXT_COLOR");    
    {
      long color_increment = (65536L * rainbow_cycle_delay_millis) /this->delay_millis;;
      this->pixels.rainbow(this->first_pixel_hue);
      this->pixels.show();
      this->first_pixel_hue = (this->first_pixel_hue + color_increment) % 65536L ;
      this->cycle_color_start_millis = millis();
      next_state = RAINBOW_CYCLE_STATE_WAIT_ON_NEXT_COLOR;
    }
    break;
    
  case RAINBOW_CYCLE_STATE_WAIT_ON_NEXT_COLOR:
    //debug("in RAINBOW_CYCLE_STATE_WAIT_ON_NEXT_COLOR");    
    if (millis() - this->cycle_color_start_millis >= rainbow_cycle_delay_millis) {
      // Timer has expired
      if (millis() - this->start_time_millis >= this->delay_millis) {
	next_state = RAINBOW_CYCLE_STATE_ONE_ITERATION_COMPLETE;
      } else {
	next_state = RAINBOW_CYCLE_STATE_NEXT_COLOR;
      }
    } else {
      // do nothing. Say in this state.
    }
    break;

  case RAINBOW_CYCLE_STATE_ONE_ITERATION_COMPLETE:
    //debug("in RAINBOW_CYCLE_STATE_ONE_ITERATION_COMPLETE");
    if (this->repeat_times > 1) {
      // Reset so we can repeat the cycle
	this->repeat_times--;
	next_state = RAINBOW_CYCLE_STATE_START;
      } else {
	// We've chased the max number of times
	next_state = this->default_state;
      }    
    break;
    
  default: 
  case STATE_TERMINAL:
    //debug("In STATE_TERMINAL");
    // fall thorough
    break;    
  }

  this->state = next_state;
}

void NeoPixelHandler::reset() {
  this->start_time_millis = millis();
  this->delay_millis = 0;
  this->repeat_times = 0;
  this->state = STATE_TERMINAL;
  this->last_pixel = 0;
}

void NeoPixelHandler::off() {
  this->reset();
  this->default_state = STATE_OFF;
  this->state = STATE_OFF;
}

void NeoPixelHandler::on(NeoPixelColor& color) {
  this->reset();
  this->default_color = color;
  this->default_state = STATE_ON;
  this->state = STATE_ON;
}

void NeoPixelHandler::rainbow() {
  this->reset();
  this->default_state = STATE_RAINBOW;
  this->state = STATE_RAINBOW;
}

void NeoPixelHandler::blink(NeoPixelColor& color,
			   int delay_millis,
			   int repeat_times) {
  this->reset();
  this->color = color;
  this->delay_millis = delay_millis;
  this->repeat_times = repeat_times;

  // Start up the blink state machine
  this->state = BLINK_STATE_START;
}

void NeoPixelHandler::chase_up(NeoPixelColor& color, int delay_millis, int repeat) {
  this->chase(color, delay_millis, repeat, 1);
}

void NeoPixelHandler::chase_down(NeoPixelColor& color, int delay_millis, int repeat) {
  this->chase(color, delay_millis, repeat, -1);
}

/*
 * direction_increment - pass -1 to chase down, pass 1 to chase up.
 */
void NeoPixelHandler::chase(NeoPixelColor& color, int delay_millis, int repeat, int direction_increment) {
  this->reset();
  this->color = color;
  this->delay_millis = delay_millis;
  this->repeat_times = repeat;
  this->direction = direction_increment;

  // Start up the chase state machine
  this->state = CHASE_STATE_START;
}

void NeoPixelHandler::rainbow_cycle(int delay, int repeat) {
  this->reset();
  this->delay_millis = delay;
  this->repeat_times = repeat;

  // Start up the rainbow cycle state machine
  this->state = RAINBOW_CYCLE_STATE_START;
}
