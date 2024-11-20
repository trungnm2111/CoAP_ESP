#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <Arduino.h>
#include "ArduinoJson.h"
#include <WiFiUdp.h>
#include <WiFi.h>

#include "coap_client.h"
#include "bh1750fvi.h"
#include "dht11.h"

#define DHTPIN 5
#define DHTTYPE DHT21 // DHT 11
#define COAP_IP_ADDRESS   IPAddress(192,168,137,29)

#define ssid            "nmt"
#define password        "123456789"

extern DHT dht;
extern WiFiUDP udp;

struct SttMessage{
    uint8_t put_message = 0;
    uint8_t get_message = 0;
    uint8_t delete_message = 0;
};

extern SttMessage flags_message;

void PutMessage();
void DhtInit();
void CoapInit();
void CoapRun();

#endif