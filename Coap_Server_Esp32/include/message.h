#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <Arduino.h>
#include "ArduinoJson.h"
#include <coap-simple.h>
#include "coap_server.h"

typedef enum{
    Message_Post = 0,
    Message_Put = 1,
    Message_Get = 2,
    Message_Delete = 3,
}MessageType;

String MessageResponse(uint8_t type);
void HandleJsonData(void);

#endif