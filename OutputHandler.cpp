#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>

#include "PinballOutputHandler.h"

// Implements a null teriminated list of handlers
HandlerNode::HandlerNode(Handler& handlerRef, HandlerNode *list) : handler(handlerRef) {
  this->next = list;
}

OutputHandler::OutputHandler() {
  this->head = NULL;
}

// Add a new handler to the OutputHandler
void OutputHandler::add(Handler& handler) {
  // Create a new node that points to the existing list and save as the new head
  this->head = new HandlerNode(handler, this->head);
}

NeoPixelHandler* OutputHandler::add(Adafruit_NeoPixel& pixels) {
  debug("Adding pixels to OutputHandler");
  // Reset the pixels
  pixels.begin();
  NeoPixelHandler *handler = new NeoPixelHandler(pixels);
  this->add(*handler);
  return handler;
}

// Execute all of the output handlers
void OutputHandler::handleAll() {
  //debug("handleAll()");
  for (HandlerNode *node = this->head; node != NULL; node = node->next) {
    //debug("Calling next handler");
    node->handler.handle();
  }
}
