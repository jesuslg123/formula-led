#include <ESP8266WiFi.h>

// Wifi configuration
const char* ssid = "XI-GUEST";
const char* password = "goxinggo";
#define MAX_MSG_LEN (128)
const IPAddress serverIPAddress(127, 0, 0, 1);

void connectWifi() {
  delay(10);
  // Connecting to a WiFi network
  Serial.printf("\nConnecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected on IP address ");
  Serial.println(WiFi.localIP());
}
