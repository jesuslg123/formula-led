#include <Arduino.h>
#include <Tone.h>

#define MAX_MELODY_LENGTH 27
#define SPEAKER1_PIN 8
#define SPEAKER2_PIN 9

Tone tone1;
Tone tone2;

int raceStartMelody[2][MAX_MELODY_LENGTH] = {
  { NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C6 },
  { 700, 700, 700, 1000 }
};

// http://www.mariopiano.com/mario-sheet-music-flagpole-fanfare.html
int flagPoleFanfareMelody[3][MAX_MELODY_LENGTH] = {
  { 
    NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5,
    NOTE_G5, NOTE_E5,
    NOTE_GS3, NOTE_C4, NOTE_DS4, NOTE_GS4, NOTE_C5, NOTE_DS5,
    NOTE_GS5, NOTE_DS5,
    NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS5, NOTE_D5, NOTE_F5,
    NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
    NOTE_C6
  },
  { 
    NOTE_G3, NOTE_E3, NOTE_G3, NOTE_C3, NOTE_E3, NOTE_G3,
    NOTE_E4, NOTE_C4,
    NOTE_GS3, NOTE_DS3, NOTE_GS3, NOTE_C3, NOTE_E3, NOTE_GS3,
    NOTE_DS4, NOTE_C4,
    NOTE_AS4, NOTE_F3, NOTE_AS4, NOTE_D3, NOTE_F3, NOTE_AS4,
    NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4,
    NOTE_C4
  },
  { 
    133, 133, 133, 133, 133, 133,
    400, 400,
    133, 133, 133, 133, 133, 133,
    400, 400,
    133, 133, 133, 133, 133, 133,
    400, 133, 133, 133,
    800
  }
};

void playTwoTrackMelody(int melody[3][MAX_MELODY_LENGTH], int duration) {
  for (int thisNote = 0; thisNote < duration; thisNote++) {
    int track1Note = melody[0][thisNote];
    int track2Note = melody[1][thisNote];
    int noteDuration = melody[2][thisNote];

    tone1.play(track1Note, noteDuration);
    tone2.play(track2Note, noteDuration);
    
    delay(noteDuration);
  }
}

void speakerSetup() {
  tone1.begin(SPEAKER1_PIN);
  tone2.begin(SPEAKER2_PIN);
}

void playerBeep(int playerId, float playerSpeed) {
  switch (playerId) {
    case 1:
      tone1.play(NOTE_C4 * playerSpeed, 15);
      break;
    case 2:
      tone2.play(NOTE_D4 * playerSpeed, 15);
      break;
  }
}

void flagPoleFanfare() {
  //flagpole slide
  float noteStep = 15 * (((float)NOTE_G5 - (float)NOTE_G2)/815.0);

  for (float i=NOTE_G3; i<=NOTE_G6; i+=noteStep) {
    tone1.play(i, 20);
    delay(15);
  }

  delay(800);
  
  playTwoTrackMelody(flagPoleFanfareMelody, MAX_MELODY_LENGTH);
}

int raceStartSound(int step) {
  int note = raceStartMelody[0][step];
  int noteDuration = raceStartMelody[1][step];
  
  tone1.play(note, noteDuration);
  tone2.play(note, noteDuration);

  delay(noteDuration);

  tone1.stop();
  tone2.stop();

  return noteDuration;
}
