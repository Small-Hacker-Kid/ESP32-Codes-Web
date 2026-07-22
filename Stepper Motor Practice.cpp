//This program makes the rotor spin clockwise while the button is being pressed
#include <Arduino.h>
#include <Stepper.h> //#Red squiggly line because The library for Stepper needs to be included

const int stepsPerRevolution = 2048;
// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
#define Button 13

// Initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void setup(){
  // set the speed at 5 rpm
  myStepper.setSpeed(5);
  //initialize the serial port
  Serial.begin(115200);
  pinMode(Button, INPUT);
}

void loop(){
  // step one revolution in one direction
  if(digitalRead(Button) == LOW){
    delay(20);
    Serial.println("Clockwise");
    while(digitalRead(Button) == LOW){
      myStepper.step(1);
    }
  }

  // revolve other direction
  /*Serial.println("Counterclockwise");
  myStepper.step(-2048);
  delay(1000);
  */
}