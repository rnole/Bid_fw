
/*  Mqtt_send_data
 *  Genera el objeto JSON con los valores de los sensores
 *  y los envía al servidor
 *  Entrada: Puntero a estructura bid_data
*/
void Mqtt_send_data(struct_bid *bdata){

    char *body  = Mqtt_generate_data_body(bdata);
    int plength = strlen(body);
    client.publish_long("topic/test", body, plength);
}


/*  Mqtt_reconnect
 *  Espera hasta que el cliente mqtt se haya
 *  conectado; una vez hecho eso, se subscribe
 *  al topic "topic/test"
*/
void Mqtt_reconnect() {
  
  while (!client.connected()) {
    
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      
      Serial.println("connected");
      client.publish("outTopic", "hello world");
      client.subscribe("topic/test");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

/*  Mqtt_callback
 *  Esta funcion es llamada cada vez que se recibe un topic
 *  con un payload
*/
void Mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

/*  Mqtt_generate_data_body
 *  Genera el objecto JSON que se va a enviar al servidor
 *  con los valores de los sensores
 *  Entrada: Puntero a la estructura bid_data
 *  Salida: Puntero al string que contiene el JSON
*/
char* Mqtt_generate_data_body(struct_bid *bdata){

  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& message = jsonBuffer.createObject();
  message["owner"] = "jobenas/esptest";
  message["entryType"] = "data";
  message["co"]     = bdata->co;
  message["co2"]    = bdata->co2;
  message["no2"]    = bdata->no2;
  message["so2"]    = bdata->so2;
  message["o3"]     = bdata->o3;
  message["noise"]  = bdata->noise;

  char bodyString[200];
  message.printTo(bodyString, sizeof(bodyString));

  return bodyString;
}

