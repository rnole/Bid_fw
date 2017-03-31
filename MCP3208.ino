#include "Definitions.h"

float MCP3208_read_co(void){

  return analogRead(CO_CHANNEL)/1023;
}

float MCP3208_read_co2(void){

  return analogRead(CO2_CHANNEL)/1023;
}

float MCP3208_read_no2(void){

  return analogRead(NO2_CHANNEL)/1023;
}

float MCP3208_read_so2(void){

  return analogRead(SO2_CHANNEL)/1023;
}

float MCP3208_read_o3(void){

  return analogRead(O3_CHANNEL)/1023;
}

float MCP3208_read_noise(void){

  return analogRead(NOISE_CHANNEL)/1023;
}
