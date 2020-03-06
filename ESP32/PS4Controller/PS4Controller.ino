#include <PS4Controller.h>

const int UP_PIN = 19, DOWN_PIN = 18, LEFT_PIN = 5, RIGHT_PIN = 17, MUSIC_PIN = 16, FAST_PIN = 4, SLOW_PIN = 0;
int speedState;

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

  Serial.println("Ready.");
  speedState = 0;
  digitalWrite(MODE_PIN, LOW);
}

void loop()
{
  // Below has all accessible outputs from the controller
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

    if (PS4.data.status.charging)
      Serial.println("The controller is charging");
    if (PS4.data.status.audio)
      Serial.println("The controller has headphones attached");
    if (PS4.data.status.mic)
      Serial.println("The controller has a mic attached");

    //    Serial.print("Battey Percent : ");
    //    Serial.println(PS4.data.status.battery, DEC);
    //
    //    unsigned long oldTime;
    //    switch (speedState) {
    //      case 0:
    //        if (PS4.data.button.triangle) {
    //          oldTime = millis();
    //          speedState = 1;
    //        }
    //        break;
    //      case 1:
    //        if (!PS4.data.button.triangle) {
    //          speedState = 0;
    //        }
    //        if (millis() > oldTime + 50000) {
    //          speedState = 2;
    //        }
    //        break;
    //      case 2:
    //        digitalWrite(MODE_PIN, (digitalRead(MODE_PIN) == LOW) ? HIGH : LOW);
    //        speedState = 0;
    //        break;
    //    }
  }
}
