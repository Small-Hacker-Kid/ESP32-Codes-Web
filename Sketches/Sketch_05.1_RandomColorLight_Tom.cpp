#include <Arduino.h>

const byte ledPins[] = {4, 2 , 15};
const byte chns[] = {0, 1, 2};
int red, green, blue;
void setup(){
    for(int i = 0; i < 3; i++){
        ledcSetup(chns[i], 1000, 8);
        ledcAttachPin(ledPins[i], chns[i]);
    }
}

void setColor(byte r, byte g, byte b){
    ledcWrite(chns[0], 255 - r);
    ledcWrite(chns[1], 255 - g);
    ledcWrite(chns[2], 255 - b);
}

void loop(){
    red = random(0, 256);
    green = random(0, 256);
    blue = random(0, 256);
    setColor(red, green, blue);
    delay(200);
}