#include <Arduino.h>
#include <Tone.h>

#define SPEAKER1_PIN 8
#define SPEAKER2_PIN 9
#define SPEAKER3_PIN 10

Tone tone1;
Tone tone2;
Tone tone3;

char charsToSend[32];
char s[4];

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

void setupSpeaker() {
  tone1.begin(SPEAKER1_PIN);
  tone2.begin(SPEAKER2_PIN);
//  tone3.begin(SPEAKER3_PIN);
}

void raceStartSound(int step) {
  int note = pgm_read_word_near(raceStartMelody[0] + step);
  int noteDuration = pgm_read_word_near(raceStartMelody[1] + step);
  
  tone1.play(note, noteDuration);
  tone2.play(note, noteDuration);
}

void playerBeep(int playerId, float playerSpeed) { 
  if (tone1.isPlaying() || tone2.isPlaying()) {
    return;
  }
   
  switch (playerId) {
    case 1:
      if ((int)(NOTE_C4 * playerSpeed) >= NOTE_C1) {
        tone1.play(NOTE_C4 * playerSpeed, 15);
      }
      break;
    case 2:
      if ((int)(NOTE_D4 * playerSpeed) >= NOTE_D1) {
        tone2.play(NOTE_D4 * playerSpeed, 15);
      }
      break;
  }
//  sendMessage('P', playerId, playerSpeed);
}

void raceEndSound() {
  //flagpole slide
  float noteStep = 15 * (((float)NOTE_G5 - (float)NOTE_G2)/815.0);

  for (float i=NOTE_G3; i<=NOTE_G6; i+=noteStep) {
    tone1.play(i, 20);
    delay(15);
  }

  delay(800);
  
  playMultiTrackMelody(flagPoleFanfareMelody, 27, 27, 0);
}
