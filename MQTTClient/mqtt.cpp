#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string>
#include <sstream>

#define MAX_MSG_LEN (128)
#define MQTT_PORT 1883

const char* mqtt_server = "192.168.1.58";

char *topic_player = "player";
char *topic_track = "track";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

//void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
//
//  // Switch on the LED if an 1 was received as first character
//  if ((char)payload[0] == '1') {
//    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//    // but actually the LED is on; this is because
//    // it is active low on the ESP-01)
//  } else {
//    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//  }
//
//}


void setupMQTT() {
  client.setServer(mqtt_server, MQTT_PORT);
//  client.setCallback(callback);
} 

void connectMQTT() {
  if (client.connected()) { 
    return;
  }
  while (!client.connected()) {
    
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");

      client.publish(topic_track, "Debug");
      //client.subscribe("topic_track");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
 
      delay(5000);
    }
  
  }
  client.loop();
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}


void publish(char *topic, char *message) {
  Serial.println("Topic: " + (String)topic + " Message: " + (String)message);
  client.publish(topic, message);
}


void mqttLoop(int playerId, int loop) {
  publish(topic_player, string2char("{\"command\": \"loop\", \"player\": \"" + (String)playerId + "\", \"loop\": \"" + (String)loop + "\"}")); 
}


void mqttEnd(int playerId) {
  publish(topic_track, string2char("{\"command\": \"end\", \"winner\": \"" + (String)playerId + "\"}")); 
}

void mqttStart() {
  publish(topic_track, "{\"command\": \"start\"}");
}

void mqttPlayerSpeed(int playerId, float playerSpeed) {
  publish(topic_player, string2char("{\"command\": \"speed\", \"player\": \"" + (String)playerId + "\", \"speed\": \"" + (String)playerSpeed + "\"}")); 
}
