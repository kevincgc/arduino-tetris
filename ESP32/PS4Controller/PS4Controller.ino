#include <PS4Controller.h>
#include "Tone32.h"

const int UP_PIN = 19, DOWN_PIN = 18, LEFT_PIN = 5, RIGHT_PIN = 17, MUSIC_PIN = 16, FAST_PIN = 4, SLOW_PIN = 0, LINE_CLEAR_PIN = 21;
volatile bool playSound = false;

void setup()
{
  Serial.begin(115200);
  PS4.begin("e8:61:7e:c7:bf:36");
  pinMode(UP_PIN, OUTPUT);
  pinMode(DOWN_PIN, OUTPUT);
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
  pinMode(MUSIC_PIN, OUTPUT);
  pinMode(FAST_PIN, OUTPUT);
  pinMode(SLOW_PIN, OUTPUT);
  pinMode(LINE_CLEAR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(LINE_CLEAR_PIN), isr, RISING);

  Serial.println("Ready.");
}

void loop()
{
  if (PS4.isConnected()) {
    if ( PS4.data.button.up || PS4.data.button.cross ) {
      digitalWrite(UP_PIN, HIGH);
    } else {
      digitalWrite(UP_PIN, LOW);
    }
    if ( PS4.data.button.down || PS4.data.button.circle ) {
      digitalWrite(DOWN_PIN, HIGH);
    } else {
      digitalWrite(DOWN_PIN, LOW);
    }
    if ( PS4.data.button.left ) {
      digitalWrite(LEFT_PIN, HIGH);
    } else {
      digitalWrite(LEFT_PIN, LOW);
    }
    if ( PS4.data.button.right ) {
      digitalWrite(RIGHT_PIN, HIGH);
    } else {
      digitalWrite(RIGHT_PIN, LOW);
    }
    if ( PS4.data.button.triangle ) {
      digitalWrite(MUSIC_PIN, HIGH);
    } else {
      digitalWrite(MUSIC_PIN, LOW);
    }
    if ( PS4.data.button.l2 ) {
      digitalWrite(SLOW_PIN, HIGH);
    } else {
      digitalWrite(SLOW_PIN, LOW);
    }
    if ( PS4.data.button.r2 ) {
      digitalWrite(FAST_PIN, HIGH);
    } else {
      digitalWrite(FAST_PIN, LOW);
    }


    if (playSound) {
      tone(2, NOTE_B6, 1000 / 8, 0);
      tone(2, NOTE_C6, 1000 / 8, 0);
      playSound = false;
    }
  }
}

void isr() {
  playSound = true;
}
