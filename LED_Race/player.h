struct Player {
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
