void callback(char* topic, byte* payload, unsigned int length);
void setupMQTT();
void connectMQTT();
void mqttStart();
void mqttLoop(Player player);
void mqttEnd(Player player);
