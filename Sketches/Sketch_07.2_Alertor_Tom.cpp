#include <Arduino.h>
#define BUZZER 13
#define BUTTON 4

void setup(){
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON, INPUT);
}

void loop(){
    if(digitalRead(BUTTON) == LOW){
        delay(20);
        if(digitalRead(BUTTON) == LOW){
            digitalWrite(BUZZER, HIGH);
        }
    } else{
        digitalWrite(BUZZER, LOW);
    }
    Serial.println("Hello WORld");
    delay(1000);
}