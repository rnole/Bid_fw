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
#include <Wire.h>
#include <SparkFunHTU21D.h>
#include "Bid_fw.h"

HTU21D  Temp_sensor;

void setup() {
  Temp_sensor.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

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


