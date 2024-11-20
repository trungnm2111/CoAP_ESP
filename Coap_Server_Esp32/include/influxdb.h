#ifndef _INFLUXDB_H
#define _INFLUXDB_H

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "coap_server.h"

#define DEVICE "ESP32"

// // Set up your InfluxDB details here
#define INFLUXDB_URL "http://10.20.102.115:8086"
#define INFLUXDB_TOKEN "sUoUvoaW6Onq6JSu1bHaT5C_NGFUFrwOQOMy9gk3bpxTAHrA-sA5b51VNxOULT-IPIlpkJEBUL025mHEmMPukQ=="
#define INFLUXDB_ORG "cee6ce748659fb46"
#define INFLUXDB_BUCKET "Esp_Data"

  
// Time zone info
#define TZ_INFO "UTC7"

// // InfluxDB v2 server url, e.g. https://eu-central-1-1.aws.cloud2.influxdata.com (Use: InfluxDB UI -> Load Data -> Client Libraries)
// #define INFLUXDB_URL "http://localhost:8086"
// // InfluxDB v2 server or cloud API token (Use: InfluxDB UI -> Data -> API Tokens -> <select token>)
// #define INFLUXDB_TOKEN "qfsRbbMg7Ge30Gm16qzXdDUqJ_QpX2_nMb0HHTuybeOlYsz811lpBgmHofy_gy2uG-DSyxxY37LrqdYxcFB0jw=="
// // InfluxDB v2 organization id (Use: InfluxDB UI -> User -> About -> Common Ids )
// #define INFLUXDB_ORG "4d3fb74f72599776"
// // InfluxDB v2 bucket name (Use: InfluxDB UI ->  Data -> Buckets)
// #define INFLUXDB_BUCKET "env"

// Time zone info
#define TZ_INFO "UTC7"

extern uint8_t flag_stt_influxdb;

void InfluxDB_setup();
void Run_InfluxDB();

#endif