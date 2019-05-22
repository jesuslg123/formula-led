#include <Arduino.h>
#include <Tone.h>

#define MAX_MELODY_LENGTH 85
#define SPEAKER1_PIN 8
#define SPEAKER2_PIN 9
#define SPEAKER3_PIN 10

Tone tone1;
Tone tone2;
Tone tone3;

const PROGMEM short raceStartMelody[2][4] = {
  { NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C6 },
  { 700, 700, 700, 1000 }
};

const PROGMEM short flagPoleFanfareMelodyCh1[27] = { 
  NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5,
  NOTE_G5, NOTE_E5,
  NOTE_GS3, NOTE_C4, NOTE_DS4, NOTE_GS4, NOTE_C5, NOTE_DS5,
  NOTE_GS5, NOTE_DS5,
  NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS5, NOTE_D5, NOTE_F5,
  NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
  NOTE_C6
};

const PROGMEM short flagPoleFanfareMelodyCh2[27] = { 
  NOTE_G3, NOTE_E3, NOTE_G3, NOTE_C3, NOTE_E3, NOTE_G3,
  NOTE_E4, NOTE_C4,
  NOTE_GS3, NOTE_DS3, NOTE_GS3, NOTE_C3, NOTE_E3, NOTE_GS3,
  NOTE_DS4, NOTE_C4,
  NOTE_AS4, NOTE_F3, NOTE_AS4, NOTE_D3, NOTE_F3, NOTE_AS4,
  NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_C4
};

const PROGMEM short flagPoleFanfareMelodyDurations[27] = {
  133, 133, 133, 133, 133, 133,
  400, 400,
  133, 133, 133, 133, 133, 133,
  400, 400,
  133, 133, 133, 133, 133, 133,
  400, 133, 133, 133,
  800
};

// http://www.mariopiano.com/mario-sheet-music-flagpole-fanfare.html
const short* flagPoleFanfareMelody[6] = {
  flagPoleFanfareMelodyCh1,
  flagPoleFanfareMelodyDurations,
  flagPoleFanfareMelodyCh2,
  flagPoleFanfareMelodyDurations,
  {},
  {}
};

const PROGMEM short matoyasCaveMelodyCh1[MAX_MELODY_LENGTH] = {
  // page 1
  NOTE_B4, NOTE_D5, NOTE_FS5, NOTE_B4, NOTE_G5, NOTE_FS5, NOTE_E5,
  NOTE_D5, NOTE_E5, NOTE_D5, NOTE_CS5,
  NOTE_D5, NOTE_FS5, NOTE_A5, NOTE_D5, NOTE_B5, NOTE_A5, NOTE_G5,
  NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_G5,
  NOTE_A5, NOTE_CS5, NOTE_E5,
  NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_B4, NOTE_G5, NOTE_A5,
  NOTE_B5, NOTE_D5, NOTE_G5,
  NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_A5, NOTE_B5,
  NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6,
  NOTE_E6, NOTE_D6, NOTE_CS6, NOTE_D6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_FS5,
  // page 2
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_CS5, NOTE_A4,
  NOTE_D5,
  NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_CS5,
  NOTE_D5,
  NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_E5,
  NOTE_FS5,
  NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_G5,
  NOTE_A5,
  NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_AS4
};

const PROGMEM short matoyasCaveMelodyCh1Durations[MAX_MELODY_LENGTH] = {
  // page 1
  200, 200, 200, 200, 400, 200, 200,
  400, 200, 200, 800,
  200, 200, 200, 200, 400, 200, 200,
  400, 200, 200, 400, 200, 200,
  800, 400, 400,
  133, 133, 133, 800, 200, 200,
  800, 400, 400,
  133, 133, 133, 800, 200, 200,
  1000, 200, 200, 200,
  100, 100, 100, 100, 600, 200, 200, 200,
  // page 2
  1000, 200, 200, 200,
  800, 400, 400,
  2800,
  100, 100, 100, 100,
  2800,
  100, 100, 100, 100, 
  2800,
  100, 100, 100, 100,
  2400,
  100, 100, 100, 100, 100, 100, 100, 100
};

const PROGMEM short matoyasCaveMelodyCh2[124] = {
  // page 1 58
  NOTE_A3, NOTE_FS4, NOTE_A3, NOTE_FS4, NOTE_A3, NOTE_G4, NOTE_A3, NOTE_G4,
  NOTE_A3, NOTE_G4, NOTE_A3, NOTE_G4, NOTE_CS4, NOTE_A4, NOTE_CS4, NOTE_A4,
  NOTE_D4, NOTE_A4, NOTE_D4, NOTE_A4, NOTE_D4, NOTE_B4, NOTE_D4, NOTE_B4,
  NOTE_D4, NOTE_B4, NOTE_D4, NOTE_B4, NOTE_CS4, NOTE_A4, NOTE_CS4, NOTE_A4,
  NOTE_A4, NOTE_A4, 0, NOTE_A4, NOTE_A4, 0,
  NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, 0,
  NOTE_B4, NOTE_B4, 0, NOTE_B4, NOTE_B4, 0,
  NOTE_CS5, NOTE_CS5, 0, NOTE_CS5, NOTE_CS5, 0,
  NOTE_A4, NOTE_A4, 0, NOTE_A4, NOTE_A4, 0,
  NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, 0,
  // page 2 (66)
  NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4,
  NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_CS4,
  NOTE_FS4, NOTE_D4, NOTE_G4, NOTE_D4,
  NOTE_A4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_FS4, NOTE_D4, NOTE_G4, NOTE_D4,
  NOTE_A4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_FS4, NOTE_D4, NOTE_G4, NOTE_D4,
  NOTE_A4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_FS4, NOTE_D4, NOTE_G4, NOTE_D4,
  NOTE_A4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E4
};

const PROGMEM short matoyasCaveMelodyCh2Durations[124] = {
  // page 1
  200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200,
  200, 400, 200, 200, 400, 200,
  200, 400, 200, 200, 400, 200,
  200, 400, 200, 200, 400, 200,
  200, 400, 200, 200, 400, 200,
  200, 400, 200, 200, 400, 200,
  200, 400, 200, 200, 400, 200,
  // page 2
  200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 100, 100, 100, 100, 100, 100, 100, 100,
  400, 400, 400, 400,
  400, 200, 200, 400, 400,
  400, 400, 400, 400,
  400, 200, 200, 400, 400,
  400, 400, 400, 400,
  400, 200, 200, 400, 400,
  400, 400, 400, 400,
  400, 200, 200, 400, 400
};

const PROGMEM short matoyasCaveMelodyCh3[7] = {
  // page 1
  NOTE_B2, NOTE_E3,
  NOTE_G3, NOTE_A3, NOTE_G3,
  NOTE_D3, NOTE_G3
  // page 2
  
};

const PROGMEM short matoyasCaveMelodyCh3Durations[7] = {
  // page 1
  800, 800,
  800, 400, 400,
  800, 800
  // page 2
  
};

const short* matoyasCaveMelody[6] = {
  matoyasCaveMelodyCh1,
  matoyasCaveMelodyCh1Durations,
  matoyasCaveMelodyCh2,
  matoyasCaveMelodyCh2Durations,
  matoyasCaveMelodyCh3,
  matoyasCaveMelodyCh3Durations
};

void playMultiTrackMelody(short* melody[6], int noteCountCh1, int noteCountCh2, int noteCountCh3) {
  int thisNoteCh1 = 0;
  int thisNoteCh2 = 0;
  int thisNoteCh3 = 0;
  
  while (thisNoteCh1 < noteCountCh1 || thisNoteCh2 < noteCountCh2 || thisNoteCh3 < noteCountCh3) {
    if (!tone1.isPlaying() && thisNoteCh1 < noteCountCh1) {
      int track1Note = pgm_read_word_near(melody[0] + thisNoteCh1);
      int noteDuration = pgm_read_word_near(melody[1] + thisNoteCh1);
      
      tone1.play(track1Note, noteDuration);
      thisNoteCh1++;
    }

    if (!tone2.isPlaying() && thisNoteCh2 < noteCountCh2) {
      int track2Note = pgm_read_word_near(melody[2] + thisNoteCh2);
      int noteDuration = pgm_read_word_near(melody[3] + thisNoteCh2);
      
      tone2.play(track2Note, noteDuration);
      thisNoteCh2++;
    }

    if (!tone3.isPlaying() && thisNoteCh3 < noteCountCh3) {
      int track3Note = pgm_read_word_near(melody[4] + thisNoteCh3);
      int noteDuration = pgm_read_word_near(melody[5] + thisNoteCh3);
      
      tone3.play(track3Note, noteDuration);
      thisNoteCh3++;
    }
  }
}

void speakerSetup() {
  tone1.begin(SPEAKER1_PIN);
  tone2.begin(SPEAKER2_PIN);
  tone3.begin(SPEAKER3_PIN);
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
  
  playMultiTrackMelody(flagPoleFanfareMelody, 27, 27, 0);
}

void matoyasCave() {
  playMultiTrackMelody(matoyasCaveMelody, MAX_MELODY_LENGTH, 124, 7);
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
