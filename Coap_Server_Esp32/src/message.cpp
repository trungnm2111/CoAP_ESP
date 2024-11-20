#include "message.h"

JsonDocument doc;
CoapPacketData packet_data;
struct Data_env data_env;
String MessageResponse(uint8_t type)
{
    String message = "{ \"cmd\" : \"Response\", \"action\" : \"\"} ";
    doc.clear();
    deserializeJson(doc, message);         
    switch(type)
    {
        case Message_Post:
            doc["action"] = "Post";
            break;
        case Message_Put:
            doc["action"] = "Put";
            break;
        case Message_Get:
            doc["action"] = "Get";
            break;
        case Message_Delete:
            doc["action"] = "Delete";
            break;
        default:
            break;
    }
    serializeJson(doc, message);            
    return message;
}

void HandleJsonData(void)
{
    if(flg_receive_json == 1)
    {
        doc.clear();
        coap.getPacketData(&packet_data);
        DeserializationError error =  deserializeJson(doc,(char *)packet_data.data);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }
        if (doc.containsKey("cmd"))         // kiem tra neu co key cmd trong json data nhan duoc tu client
        {
            String cmd = doc["cmd"].as<String>();        // lay gia tri cua key cmd duoi dang string 
            if( strcmp(cmd.c_str(), "Request") == 0)
            {
                String action = doc["action"].as<String>();
                if(strcmp(action.c_str(), "Post") == 0)
                {
                    Serial.println("Post Resquest");
                    data_env.temp = doc["temp"].as<float>();
                    data_env.humidity = doc["humidity"].as<float>();
                    data_env.light    = doc["light"].as<float>();
                }
                else if(strcmp(action.c_str(), "Put") == 0)
                {
                    Serial.println("Put Request");
                    data_env.temp = doc["data_env"][0].as<float>();
                    data_env.humidity = doc["data_env"][1].as<float>();
                    data_env.light    = doc["data_env"][2].as<float>();
                }
            }
        }
        flg_receive_json = 0;
    }
}
