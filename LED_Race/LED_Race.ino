#include "FastLED.h"
#define NUM_LEDS 300
#define LED_PIN 6

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define PLAYER1_PIN 7
#define PLAYER2_PIN 8

#define ACCELERATION 0.3
#define FRICTION 0.015
#define HIGHSPEED 4

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
  CRGB::HTMLColorCode color;
  CRGB::HTMLColorCode highSpeedColor;
};

struct Player player1;
struct Player player2;



void setup() {
  initLCD();

  
  initPlayer(&player1, PLAYER1_PIN, CRGB::Red, CRGB::Green);
  initPlayer(&player2, PLAYER2_PIN, CRGB::Blue, CRGB::Yellow);

  FastLED.addLeds < NEOPIXEL, LED_PIN > (leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {
  movePlayer(&player1);
  movePlayer(&player2);
  drawPlayer(player1);
  drawPlayer(player2);
  
  updateLCD();
  
  delay(5);
}




void initLCD() {
  lcd.init();
  lcd.backlight();
} 


void updateLCD() {
  printPlayer(player1, 0);
  printPlayer(player2, 1);
}

void printPlayer(struct Player player, int line) {
  lcd.setCursor(0, line);
  lcd.print((char)236 + ":" + (String)player.loop + " " + (char)62 + ":" + (String)player.speed + "m/s");
}

void initPlayer(struct Player *player, int pin, CRGB::HTMLColorCode color, CRGB::HTMLColorCode highSpeedColor) {
  player->buttonPin = pin;
  player->buttonState = LOW;
  player->prevPosition = 0;
  player->position = 0;
  player->loop = 0;
  player->speed = 0.0;
  player->color = color;
  player->highSpeedColor = highSpeedColor;
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

  if (player->position < player->prevPosition) { 
    player->loop += 1;
  }

  Serial.println("Speed: " + (String)player->speed + " Position: " + (String)player->position + " P1: " + (String)player1.loop + " P2: " + (String)player2.loop);
}

void drawPlayer(struct Player player) {
  if (player.prevPosition != player.position) {
    leds[player.position] = player.speed < HIGHSPEED ? player.color : player.highSpeedColor;
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
