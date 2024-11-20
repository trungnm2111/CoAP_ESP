#include "coap_client.h"
#include "message.h"
#include <Ticker.h>

Ticker ticker_sendData;

void setup() 
{
  CoapInit();
  ticker_sendData.attach(10.0, PutMessage);
}

void loop()
{
  CoapRun();
}




/*
------------------------------------------------------------------  Addition -----------------------------------------------------------------------------------
  CoAP Client
if you change LED, req/res test with coap-client(libcoap), run following.
coap-client -m get coap://(arduino ip addr)/light
coap-client -e "1" -m put coap://(arduino ip addr)/light
coap-client -e "0" -m put coap://(arduino ip addr)/light

example test 
  int msgid =coap.put(ip,port,"light","0",strlen("0"));
  int msig = coap.get(IPAddress(134,102,218,18), 5683, "5"); 
  int msgid =coap.put(ip,port,"light","0",strlen("0"));


  ------------------------------------------------------------
  void callback_light(CoapPacket &packet, IPAddress ip, int port);

  UDP and CoAP class
  other initialize is "Coap coap(Udp, 512);"
  2nd default parameter is COAP_BUF_MAX_SIZE(defaulit:128)
  For UDP fragmentation, it is good to set the maximum under
  1280byte when using the internet connection.

  // CoAP server endpoint URL
void callback_light(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("[Light] ON/OFF");
  // send response
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = '\0';
  
  String message(p);

  if (message.equals("0"))
    LEDSTATE = false;
  else if(message.equals("1"))
    LEDSTATE = true;
  if (LEDSTATE) {
    digitalWrite(25, HIGH) ; 
    coap.sendResponse(ip, port, packet.messageid, "trung");
  } else { 
    digitalWrite(25, LOW) ; 
    coap.sendResponse(ip, port, packet.messageid, "dev");
  }
}
  coap.server(callback_light, "light");           //call in setup()
   // add server url endpoints.
  // can add multiple endpoint urls.
  // exp) coap.server(callback_switch, "switch");
  //      coap.server(callback_env, "env/temp");
  Serial.println("Setup Callback Light");
*/


