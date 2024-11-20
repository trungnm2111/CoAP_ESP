#include "coap_server.h"

WiFiUDP udp;
Coap coap(udp);

uint8_t flg_receive_json = 0;
//CoAP server endpoint url callback
static void callback_light(CoapPacket &packet, IPAddress ip, int port);

void Coap_Init(void)
{
    // Init led 25
    pinMode(25, OUTPUT);
    digitalWrite(25, HIGH);

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Create topic light");
    coap.server(callback_light, "light");

    coap.start();               // start coap server/client
}

// CoAP server endpoint URL
void callback_light(CoapPacket &packet, IPAddress ip, int port) 
{
    // send response  
    char p[packet.payloadlen + 1];
    if (packet.type == COAP_CON) {
    Serial.println("Send ACK..");

    // Gửi phản hồi ACK đến client để xác nhận
    coap.sendResponse(ip, port, packet.messageid, "ACK");
    }
    switch (packet.code)
    {

    case COAP_POST:
        memcpy(p, packet.payload, packet.payloadlen);
        p[packet.payloadlen] = '\0';
        // Serial.println("[Coap Request post]");
        // Serial.println(p);
        coap.sendResponse(ip, port, packet.messageid, MessageResponse(Message_Post).c_str());
        break;

    case COAP_PUT:
        memcpy(p, packet.payload, packet.payloadlen);
        p[packet.payloadlen] = '\0';
        // Serial.println("[Coap Request put]");
        // Serial.println(p);
        coap.sendResponse(ip, port, packet.messageid, MessageResponse(Message_Put).c_str());
        flg_receive_json = 1;
        break;

    case COAP_GET:
        // Serial.println("[Coap Request get]");
        CoapPacketData storedPacket;
        coap.getPacketData(&storedPacket);
        if (storedPacket.data != NULL) {
            // Serial.print("Stored Packet Payload: ");
            // Serial.write(storedPacket.data, storedPacket.len);
            // Serial.println();
        }else {
            // Serial.println("Invalid packet index");
        }
        coap.sendResponse(ip, port, packet.messageid, (char *)storedPacket.data);
        coap.sendResponse(ip, port, packet.messageid, MessageResponse(Message_Get).c_str());
        /* code */
        break;
    default:
        break;
    }
}

void Coap_Loop(void)
{
    coap.loop();
}