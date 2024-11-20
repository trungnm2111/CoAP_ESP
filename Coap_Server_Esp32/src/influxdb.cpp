#include "influxdb.h"

// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Create your Data Point here
Point sensor("climate");


void InfluxDB_setup() 
{
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");                  // Sync time
  // Check server connection
  while(!client.validateConnection()) {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
    delay(500);
  }
  Serial.print("Connected to InfluxDB: ");
  Serial.println(client.getServerUrl());
  
  // Add tags
  sensor.addTag("device", DEVICE);
}

void Run_InfluxDB() 
{
// Write point to InfluxDB
  sensor.clearFields();
  sensor.addField("temperature", data_env.temp);
  sensor.addField("humidity", data_env.humidity);
  sensor.addField("light", data_env.light);

  // Serial.print("Writing: ");
  // Serial.println(sensor.toLineProtocol());
      
  if (!client.writePoint(sensor))           // Write point
  {  
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}
