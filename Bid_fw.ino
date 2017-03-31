/**
Author: Richard Nole
Description:
Platform: Sparkfun ESP8266 Thing-Dev

Components:
- MCP3208(External ADC)
- Pressure Sensor(I2C)
- Humidity Sensor(I2C)
*/

#include "Bid_fw.h"

HTU21D  Temp_sensor;
MCP3208 ADC(SS);
struct_bid   bid_data;

void setup() {
  Serial.begin(115200);
  Wifi_init();
  Temp_sensor.begin();
  ADC.begin();
}

void loop() {
  
  Serial.println(F("Leyendo sensores... "));
  bid_data.uv           = UV_sensor_read();                   //Units: mW/cm2
  bid_data.humidity     = Temp_sensor.readHumidity();         
  bid_data.temperature  = Temp_sensor.readTemperature();      //Units: Cº
  bid_data.co           = MCP3208_read_co();
  bid_data.co2          = MCP3208_read_co2();
  bid_data.no2          = MCP3208_read_no2();
  bid_data.so2          = MCP3208_read_so2();
  bid_data.o3           = MCP3208_read_o3();
  bid_data.noise        = MCP3208_read_noise();
}

/* Wifi_init
 * Inicializa el Wifi con IP estáticas. Los parámetros IP
 * se pueden cambiar en el archivo Definitions.h
 * Entradas: Ninguna 
 * Salidas: Ninguna
 */
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

/* UV_sensor_read
 * Hace 10 lecturas del ADC, las promedia y la mapea 
 * a la curva UV del sensor ML8511
 * Entrada: ninguna
 * Salida: Intensidad UV (unidades: mW/cm2)
 */
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


