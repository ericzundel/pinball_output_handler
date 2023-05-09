#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>

#include "Handler.h"
#include "OutputHandler.h"

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

// Execute all of the output handlers
void OutputHandler::handleAll() {
  Serial.println("handleAll()");
  delay(1000);
  for (HandlerNode *node = this->head; node != NULL; node = node->next) {
    Serial.println("Calling next handler");
    delay(1000);
    node->handler.handle();
  }
}
