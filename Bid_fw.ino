/**
Author: Richard Nole
Description:
Platform: Sparkfun ESP8266 Thing-Dev

Components:
- ADC
- EEPROM(I2C)
- Pressure Sensor(I2C)
- Humidity Sensor(I2C)
*/

#include "Bid_fw.h"

HTU21D  Temp_sensor;
struct_bid   bid_data;

void setup() {
  Serial.begin(115200);
  Wifi_init();
  Temp_sensor.begin();
  
}

void loop() {
  
  Serial.println(F("Leyendo sensores... "));
  bid_data.uv           = UV_sensor_read();                   //Units: mW/cm2
  bid_data.humidity     = Temp_sensor.readHumidity();         
  bid_data.temperature  = Temp_sensor.readTemperature();      //Units: Cº
}

void Wifi_init(void){

  WiFiManager wifiManager;
  IPAddress _ip, _gw, _sn;
  _ip.fromString(STATIC_IP);
  _gw.fromString(STATIC_GW);
  _sn.fromString(STATIC_SN);
  
  wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);
  
  if (!wifiManager.autoConnect(WIFI_SSID, WIFI_PASSWORD)) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected!");
  Serial.println("local ip: ");
  Serial.println(WiFi.localIP());
}

float UV_sensor_read(void) {
  uint16_t adc_reading = 0;
  float uv_voltage, uv_intensity = 0;

  adc_reading  = analogRead_average(UV_SENSOR);
  uv_voltage   = (adc_reading * 3.3) / 1023.0;
  
  uv_intensity = (15.0 - 0.0) * (uv_voltage - 0.99) / (2.9 - 0.99);
  
  if(uv_intensity < 0)
    uv_intensity = 0;
    
  return uv_intensity;
}


