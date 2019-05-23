#include <Arduino.h>

char charsToSend[32];
char s[4];

void sendMessage(char msg, int playerId, float playerSpeed) {
  Serial.write("<");
  Serial.write(msg);
  Serial.write(", ");
  Serial.print(playerId);
  Serial.print(", ");
  Serial.write(dtostrf(playerSpeed, 3, 2, s));
  Serial.write('>');
  Serial.write('\n');
}

void raceStartSound(int step) {
  sendMessage('S', 0, step);
}

void playerBeep(int playerId, float playerSpeed) {
  sendMessage('P', playerId, playerSpeed);
}

void raceEndSound() {
  sendMessage('W', 0, 0);
}
