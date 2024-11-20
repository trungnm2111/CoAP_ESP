#include "message.h"

JsonDocument doc;
Coap coap(udp);
IPAddress serverIp(192, 168, 137, 188);
const int serverPort = 5683;
WiFiUDP udp;



static String CreateMessage(float temperature, float humidity, float light);
static void PingMessage();

SttMessage flags_message;

String CreateMessage(float temperature, float humidity, float light) 
{
    String message = "{\"cmd\": \"Request\", \"action\": \"Put\", \"data_env\" :[]}";
    doc.clear();
    humidity += 10;
    deserializeJson(doc, message);
    doc["data_env"][0] = serialized(String(temperature, 2));
    doc["data_env"][1] = serialized(String(humidity, 2));  
    doc["data_env"][2] = serialized(String(light,2));
    serializeJson(doc, message); 
    return message;
}

static void PingMessage()
{
    CoapPacket pingPacket;
    pingPacket.type = COAP_CON;
    pingPacket.code = 0;  // EMPTY MESSAGE (Mã 0.00)

    uint16_t msgId  = coap.ping(serverIp, serverPort);
    
    if (msgId != 0) {
        Serial.println("PING to server");
    } 
}

void PutMessage() 
{
    String message = CreateMessage(DHT11_ReadTemperature(), DHT11_ReadHumidity(), BH1750FVI_ReadLux());
    const char *payload = (const char *)message.c_str();
    size_t payloadlen = message.length();
    uint16_t put_data = coap.put(COAP_IP_ADDRESS, COAP_DEFAULT_PORT, "light",(char *)payload ,payloadlen);
    Serial.println(message);
    // flags_message.put_message = 1;
}

void GetMessage()
{
    if(flags_message.get_message == 0)
    {
        uint16_t get_data = coap.get(COAP_IP_ADDRESS, COAP_DEFAULT_PORT, "light");
        flags_message.get_message = 1;
    }else
    {
        return;
    }
}



void CoapInit(void)
{
    // Init led 25
    pinMode(25, OUTPUT);
    digitalWrite(25, LOW);
    
    Serial.begin(115200);
    DHT11_Init();
    BH1750FVI_Init();
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); 

    coap.response(callback_response);                                     // client response callback.
    
    coap.start(); 
    PingMessage();
    Serial.println("Connect Server");
    digitalWrite(25, HIGH); 

}

void CoapRun(void)
{
    coap.loop();
}
/* 
    // //   
    // uint16_t delete_data = coap.Delete(COAP_IP_ADDRESS, COAP_DEFAULT_PORT, "light");
*/