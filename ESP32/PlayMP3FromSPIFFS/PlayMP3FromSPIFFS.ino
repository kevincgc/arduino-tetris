#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

// To run, set your ESP8266 build to 160MHz, and include a SPIFFS of 512KB or greater.
// Use the "Tools->ESP8266/ESP32 Sketch Data Upload" menu to write the MP3 to SPIFFS
// Then upload the sketch normally.

// pno_cs from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html

AudioGeneratorMP3 *mp3;
AudioFileSourceSPIFFS *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;
int song;
volatile bool changeSong;
const int interruptPin = 12;

void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  (void)cbData;
  Serial.printf("ID3 callback for: %s = '", type);

  if (isUnicode) {
    string += 2;
  }

  while (*string) {
    char a = *(string++);
    if (isUnicode) {
      string++;
    }
    Serial.printf("%c", a);
  }
  Serial.printf("'\n");
  Serial.flush();
}

void IRAM_ATTR ISR() {
  changeSong = true;
}

void setup()
{
  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  Serial.printf("Sample MP3 playback begins...\n");
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), ISR, RISING);

  audioLogger = &Serial;
  out = new AudioOutputI2S(0, 1);
  mp3 = new AudioGeneratorMP3();
}

void loop()
{
  if (changeSong) {
    //noInterrupts();
    mp3->stop();
    song++;
    if (song == 3) song = 0;
    changeSong = false;
    //interrupts();
  }
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    switch (song) {
      case 0:
        file = new AudioFileSourceSPIFFS("/tetris.mp3");
        break;
      case 1:
        file = new AudioFileSourceSPIFFS("/polkka.mp3");
        break;
      case 2:
        file = new AudioFileSourceSPIFFS("/2hu.mp3");
        break;
    }
    id3 = new AudioFileSourceID3(file);
    id3->RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
    mp3->begin(id3, out);
  }
}
