#ifndef HANDLER_H
#define HANDLER_H

#include <stdint.h>

/* Handler - defines a class that
 */
class Handler {

 public:
  virtual void handle(); // Implement this method to perform a non-blocking action
};

static void debug(String value) {
  //Serial.println(value);
  //delay(500);
}
#endif
