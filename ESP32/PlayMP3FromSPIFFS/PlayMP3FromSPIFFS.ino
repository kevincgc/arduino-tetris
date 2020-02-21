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
volatile bool isInterrupt;
const int interruptPin = 5;


// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
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
  isInterrupt = true;
}

void setup()
{
  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  Serial.printf("Sample MP3 playback begins...\n");
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(5), ISR, CHANGE);

  audioLogger = &Serial;
  out = new AudioOutputI2S(0, 1);
  mp3 = new AudioGeneratorMP3();
}

void loop()
{
  if (isInterrupt) {
    noInterrupts();
    mp3->stop();
    isInterrupt = false;
    interrupts();
  }
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    if (digitalRead(interruptPin)) {
      file = new AudioFileSourceSPIFFS("/darude_s.mp3");
    } else {
      file = new AudioFileSourceSPIFFS("/tetris_s.mp3");
    }
    id3 = new AudioFileSourceID3(file);
    id3->RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
    mp3->begin(id3, out);
  }
}
