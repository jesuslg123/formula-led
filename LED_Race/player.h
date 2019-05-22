#include <FastLED.h>

struct Player {
  int id;
  int buttonPin;
  int buttonState;
  int prevPosition;
  int position;
  int loop;
  float speed;
  bool isWinner;
  bool isOffTrack;
  bool blinking;
  CRGB::HTMLColorCode color;
  CRGB::HTMLColorCode highSpeedColor;
};
