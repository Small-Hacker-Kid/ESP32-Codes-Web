#include <Arduino.h>

byte ledPins[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23};
int ledCounts;

void setup(){
  ledCounts = sizeof(ledPins) / sizeof(ledPins[0]);
  for(int i = 0; i < ledCounts; i ++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for(int i = 0; i < ledCounts; i ++){
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  } // This makes lights go DOWN the list

  for(int i = ledCounts - 1; i > -1; i--){
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  } // This makes lights go UP the list
}