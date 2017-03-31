#ifndef _BID_FW_H
#define _BID_FW_H

#include "Definitions.h"
#include <Wire.h>
#include <SparkFunHTU21D.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>            
#include <ESP8266WebServer.h>     
#include <WiFiManager.h>
#include <MCP3208.h>
#include <SPI.h>


typedef struct{
  float temperature;
  float humidity;
  float uv;
  float co;
  float co2;
  float no2;
  float so2;
  float o3;
  float noise;
}struct_bid;



#endif
