#include "mqtt.h"
#include "wifi.h"

// see https://forum.arduino.cc/index.php?topic=396450

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char message[numChars] = {0};
int playerId = 0;

float lastSpeeds[2] = { -1.0, -1.0 };

float playerSpeed = 0.0;

boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  connectWifi();
  setupMQTT();
}

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    parsedDataToMQTTMessage();
    newData = false;
  }
}

//============

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

//============

void parseData() {      // split the data into its parts
  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  strcpy(message, strtokIndx); // copy it to messageFromPC

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  playerId = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  playerSpeed = atof(strtokIndx);     // convert this part to a float
}

//============

void parsedDataToMQTTMessage() {
  // debug (rebuild message)
//  Serial.print("<");
//  Serial.print(message[0]);
//  Serial.print(", ");
//  Serial.print(playerId);
//  Serial.print(", ");
//  Serial.print(playerSpeed);
//  Serial.println(">");
  connectMQTT();
  
  if (message[0] == 'P') {
    if (lastSpeeds[playerId - 1] != playerSpeed) {
      lastSpeeds[playerId - 1] = playerSpeed;
      mqttPlayerSpeed(playerId, playerSpeed);
    }
  } else if (message[0] == 'S') {
    mqttStart();
  } else if (message[0] == 'W') {
    mqttEnd(playerId);
  } else if (message[0] == 'L') {
    int playerLoop = (int)playerSpeed;
    mqttLoop(playerId, playerLoop);
  }
}
