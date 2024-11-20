#include <Arduino.h>
#include "influxdb.h"
#include "coap_server.h"

void setup()
{
  Coap_Init();
  InfluxDB_setup();
  // start coap server
}

void loop() 
{
  Coap_Loop();
  HandleJsonData();
  Run_InfluxDB();
}


/*
-------------------------------- Client Call To Server -----------------------------------
if you change LED, req/res test with coap-client(libcoap), run following.
coap-client -m get coap://(arduino ip addr)/light
coap-client -e "1" -m put coap://(arduino ip addr)/light
coap-client -e "0" -m put coap://(arduino ip addr)/light


--------------------------------- CoAP Server add endpoint ---------------------------------

   add server url endpoints.
  can add multiple endpoint urls.
  exp) coap.server(callback_switch, "switch");
       coap.server(callback_env, "env/temp");
       coap.server(callback_env, "env/humidity");
}
*/

