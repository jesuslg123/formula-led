#include "FastLED.h"
#define NUM_LEDS 300
#define LED_PIN 6

#define PLAYER1_PIN 7

#define ACCELERATION 0.3
#define FRICTION 0.015

//#define COLOR_PETROL 0x007575
//#define COLOR_LINKEDIN 0x0077B5

CRGB leds[NUM_LEDS];

struct Player {
  int buttonPin;
  int buttonState;
  int prevPosition;
  int position;
  int loop;
  float speed;
};

struct Player player1;
struct Player player2;

void setup() {
//  pinMode(PLAYER1_PIN, INPUT_PULLUP);
  initPlayer(&player1, PLAYER1_PIN);

  FastLED.addLeds < NEOPIXEL, LED_PIN > (leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {
  movePlayer(&player1);
  drawPlayer(player1);

  delay(5);
}

void initPlayer(struct Player *player, int pin) {
  player->buttonPin = pin;
  player->buttonState = LOW;
  player->prevPosition = 0;
  player->position = 0;
  player->loop = 0;
  player->speed = 0.0;
}

bool buttonReleased(struct Player *player) {
  int previousState = player->buttonState;
  player->buttonState = digitalRead(player->buttonPin);

//  Serial.println(player.buttonPin);

  if (previousState == HIGH && player->buttonState == LOW) {
    return true;
  }

  return false;
}

void movePlayer(struct Player *player) {
  if (buttonReleased(player)) {
    player->speed += ACCELERATION; // acceleration
  }

  player->speed -= player->speed * FRICTION;

  if (player->speed < 0) {
    player->speed = 0;
  }

  player->prevPosition = player->position;
  player->position = (int)(player->position + player->speed) % NUM_LEDS;

//  Serial.println("Speed: " + (String)player->speed + " Position: " + (String)player->position);
}

void drawPlayer(struct Player player) {
  if (player.prevPosition != player.position) {
    leds[player.position] = CRGB::Blue;
    leds[player.prevPosition] = CRGB::Black;
    FastLED.show(); 
  }
}

void clearTrack() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
