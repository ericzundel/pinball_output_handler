#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <Adafruit_NeoPixel.h>
#include "Handler.h"
#include "NeoPixelHandler.h"


// Holder for a singly linked list of handlers.
class HandlerNode {
public:
  HandlerNode(Handler& handlerRef, HandlerNode *list);
  Handler& handler;
  HandlerNode *next;
};

class OutputHandler {
 public:
  OutputHandler();
  void add(Handler& handlerRef);
  NeoPixelHandler* add(Adafruit_NeoPixel& pixels);
  void handleAll();
  
 private:
  // NULL terminated list of all handlers, newest is at head of list
  HandlerNode *head;  
};

#endif
