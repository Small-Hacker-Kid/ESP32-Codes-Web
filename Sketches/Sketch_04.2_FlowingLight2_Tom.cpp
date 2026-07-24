#include <Arduino.h>

const byte ledPins[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23};
const byte chns[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
const int dutys[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    1023, 512, 256, 128, 64, 32, 16, 8, 4, 2,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    };
int ledCounts;
int delayTimes = 500;
void setup(){
  ledCounts = sizeof(ledPins);
  for(int i = 0; i < ledCounts; i ++){
    ledcSetup(chns[i], 1000, 10);
    ledcAttachPin(ledPins[i], chns[i]);
  }
}

void loop(){
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < ledCounts; j++){
      ledcWrite(chns[j], dutys[i + j]);
    }
    delay(delayTimes);
  }
  for(int i = 0; i < 20; i++){
    for(int j = ledCounts - 1; j > -1; j--){
      ledcWrite(chns[j], dutys[i + (ledCounts - 1 - j)]);
    }
    delay(delayTimes);
  }
}