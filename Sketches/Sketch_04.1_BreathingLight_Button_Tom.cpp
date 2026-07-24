#include <Arduino.h>

#define PIN_BUTTON 13
#define PIN_LED 2
#define CHN     0
#define FRQ     1000
#define PWM_BIT 8

int brightness = 0;
void reverse(){
  if(brightness == -1){
    for(brightness; brightness < 255; brightness ++) {
          ledcWrite(CHN, brightness);
          delay(10);
        }
    }
  else{
    for(brightness; brightness > -1; brightness --){
    ledcWrite(CHN, brightness);
    delay(10);
    }
  }
}

void setup() {
  ledcSetup(CHN, FRQ, PWM_BIT);
  ledcAttachPin(PIN_LED, CHN);
  pinMode(PIN_BUTTON, INPUT);
}

void loop(){
  if (digitalRead(PIN_BUTTON) == LOW){
      delay(20);
      if(digitalRead(PIN_BUTTON) == LOW){
        reverse();
      }
    while(digitalRead(PIN_BUTTON) == LOW);
    delay(20);
    while(digitalRead(PIN_BUTTON) == LOW);

  }
}  