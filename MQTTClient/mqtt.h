void callback(char* topic, byte* payload, unsigned int length);
void setupMQTT();
void connectMQTT();
void mqttStart();
void mqttPlayerSpeed(int playerId, float playerSpeed);
void mqttLoop(int playerId, int loop);
void mqttEnd(int playerId);
