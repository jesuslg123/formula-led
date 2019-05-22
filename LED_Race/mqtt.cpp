#include <ESP8266WiFi.h>

#include <PubSubClient.h>
#define MAX_MSG_LEN (128)
#define MQTT_PORT 1883

//const IPAddress serverIPAddress(127, 0, 0, 1);
const char* mqtt_server = "192.168.1.58";

const char *topic = "player_one";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setupMQTT() {
  client.setServer(mqtt_server, MQTT_PORT);
  //client.setCallback(callback);
} 

void connectMQTT() {
  if (client.connected()) { 
    return;
  }
  while (!client.connected()) {
    
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");

      client.publish("mqtt_message", "hello arduino");
      client.subscribe("mqtt_message");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
 
      delay(5000);
    }
  
  }
  client.loop();
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
