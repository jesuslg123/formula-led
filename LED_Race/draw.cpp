#include <FastLED.h>

#include "constants.h"
#include "player.h"

CRGBArray<NUM_LEDS> leds;

// private

int modulo(int x, int n) {
  return (x % n + n) % n;
}

void setTrackColor(CRGB::HTMLColorCode color) {
  leds = color;
  FastLED.show();
}

void setupTrack() {
  FastLED.addLeds < NEOPIXEL, LED_PIN > (leds, NUM_LEDS);
  setTrackColor(CRGB::Black);
}

void drawWinner(struct Player *winner) {
  setTrackColor(winner->color);
}

void clearTrack() {
  setTrackColor(CRGB::Black);
}

void drawCountdown(int countdownStage) {
  switch (countdownStage) {
    case 3:
      setTrackColor(CRGB::Blue);
      break;
    case 2:
      setTrackColor(CRGB::Red);
      break;
    case 1:
      setTrackColor(CRGB::Green);
      break;
    default:
      clearTrack();
  }
}

void drawOnTrack(int position, int length, CRGB::HTMLColorCode color) {
  for (int j = 0; j < length; j++) {
    int index = modulo(position - j, NUM_LEDS);
    leds[index] = color;
  }
}

CRGB::HTMLColorCode playerColor(struct Player *player) {
   if (player->speed > HIGHSPEED) {
    return player->highSpeedColor;
  } else {
    return player->color;
  }
}

boolean ledsAreBlack(int index, int length) {
  boolean res = true;

  for (int i = 0; i < length; i++) {
    int idx = modulo(index - i, NUM_LEDS);
    res |= (leds[idx].r == 0 && leds[idx].g == 0 && leds[idx].b == 0);
  }
  
  return res;
}

void drawPlayer(struct Player *player) {
  if (player->isOffTrack) {    
    // draw an explosion
    CRGB::HTMLColorCode offTrackColor = player->blinking ? player->color : CRGB::Black;

    drawOnTrack(player->position + 1, 1, offTrackColor);
    drawOnTrack(player->position - player->loop - 1, 1, offTrackColor);

    if (player->speed >= 1 && !player->blinking) {
      player->isOffTrack = false;
      // clear the back of the explosion
      drawOnTrack(player->prevPosition - player->loop - 1, 1, CRGB::Black);
    }

    FastLED.show();
  }
    
  if (player->position != player->prevPosition || (player->position == 0 && player->loop == 0) || ledsAreBlack(player->position, player->loop)) {
    // draw the player
    drawOnTrack(player->prevPosition, player->loop + 1, CRGB::Black);
    drawOnTrack(player->position, player->loop + 1, playerColor(player));

    FastLED.show();
  }
}
