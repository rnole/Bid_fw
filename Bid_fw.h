#ifndef _BID_FW_H
#define _BID_FW_H

#include "Definitions.h"
#include <Wire.h>
#include <SparkFunHTU21D.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>            
#include <ESP8266WebServer.h>     
#include <WiFiManager.h>

typedef struct{
  float temperature;
  float humidity;
  float uv;
}struct_bid;



#endif
