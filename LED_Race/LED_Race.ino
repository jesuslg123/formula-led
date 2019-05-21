#include <FastLED.h>

#include "constants.h"
#include "player.h"
#include "draw.h"
#include "melody.h"

struct Player player1;
struct Player player2;

int raceCountdown = 3;
bool raceFinished = false;

void setup() {
  initPlayer(&player1, PLAYER1_PIN, CRGB::Red, CRGB::Green);
  initPlayer(&player2, PLAYER2_PIN, CRGB::Blue, CRGB::Yellow);

  setupTrack();

  Serial.begin(9600);
}

void loop() {
  if (raceCountdown >= 0) {
    drawCountdown(raceCountdown);
    int noteDuration = raceStartSound(3 - raceCountdown);
    delay(noteDuration + 700);
    
    raceCountdown--;
    return;
  }
  
  if (raceFinished) {
    delay(1000);
    return;
  }

  movePlayer(&player1);
  movePlayer(&player2);
  drawPlayer(&player1);
  drawPlayer(&player2);

  playerBeep(1, player1.speed);
  playerBeep(2, player2.speed);

  if (isRaceFinished()) {
    struct Player winner = findWinner(player1, player2);
    drawWinner(&winner);
    raceFinished = true;
    flagPoleFanfare();
  }

  delay(15);
}

void initPlayer(struct Player *player, int pin, CRGB::HTMLColorCode color, CRGB::HTMLColorCode highSpeedColor) {
  player->buttonPin = pin;
  player->buttonState = LOW;
  player->prevPosition = 0;
  player->position = 0;
  player->loop = 0;
  player->speed = 0.0;
  player->isWinner = false;
  player->isOffTrack = false;
  player->blinking = false;
  player->color = color;
  player->highSpeedColor = highSpeedColor;
}

bool buttonReleased(struct Player *player) {
  int previousState = player->buttonState;
  player->buttonState = digitalRead(player->buttonPin);

  if (previousState == HIGH && player->buttonState == LOW) {
    return true;
  }

  return false;
}

void movePlayer(struct Player *player) {
  if (buttonReleased(player)) {
    player->speed += ACCELERATION; // acceleration

    if (player->isOffTrack) {
      player->blinking = !(player->blinking);
    }
  }

  player->speed -= player->speed * FRICTION;

  if (player->speed < 0) {
    player->speed = 0;
  } else if (player->speed >= MAX_SPEED) {
    player->speed = 0;
    player->isOffTrack = true;
  }

  player->prevPosition = player->position;
  player->position = (int)(player->position + player->speed) % NUM_LEDS;

  if (player->position < player->prevPosition) {
    player->loop += 1;
  }

  if (player->loop == MAX_LOOPS) {
    player->isWinner = true;
  }
  //  Serial.println("Speed: " + (String)player->speed + " Position: " + (String)player->position + " P1: " + (String)player1.loop + " P2: " + (String)player2.loop);
}

bool isRaceFinished() {
  return player1.isWinner || player2.isWinner;
}

struct Player findWinner(struct Player player1, struct Player player2) {
  if (player1.isWinner) {
    return player1;
  } else if (player2.isWinner) {
    return player2;
  }
}
