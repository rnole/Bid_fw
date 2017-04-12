#include "Definitions.h"

float MCP3208_read_co(void){

  return ADC.analogRead(CO_CHANNEL)/MCP3208_RES;
}

float MCP3208_read_co2(void){

  return ADC.analogRead(CO2_CHANNEL)/MCP3208_RES;
}

float MCP3208_read_no2(void){

  return ADC.analogRead(NO2_CHANNEL)/MCP3208_RES;
}

float MCP3208_read_so2(void){

  return ADC.analogRead(SO2_CHANNEL)/MCP3208_RES;
}

float MCP3208_read_o3(void){

  return ADC.analogRead(O3_CHANNEL)/MCP3208_RES;
}

float MCP3208_read_noise(void){

  return ADC.analogRead(NOISE_CHANNEL)/MCP3208_RES;
}
