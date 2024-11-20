#ifndef _COAP_SERVER_H
#define _COAP_SERVER_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <coap-simple.h>
#include <WiFi.h>
#include "message.h"

#define ssid      "nmt"
#define password  "123456789" 

extern uint8_t flg_receive_json;
struct Data_env{
    float temp;
    float humidity;
    float light;
};

extern struct Data_env data_env;
extern WiFiUDP udp;
extern Coap coap;

// UDP and CoAP class
// other initialize is "Coap coap(Udp, 512);"
// 2nd default parameter is COAP_BUF_MAX_SIZE(defaulit:128)
// For UDP fragmentation, it is good to set the maximum under
// 1280byte when using the internet connection.

void Coap_Init(void);
void Coap_Loop(void);

#endif