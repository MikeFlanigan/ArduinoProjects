#include <Servo.h>

Servo S1, S2;

Servo myArray[] = {S1, S2};



void setup() {
  // put your setup code here, to run once:
  myArray[0].attach(2);
  myArray[1].attach(3);

}

void loop() {
  // put your main code here, to run repeatedly:

}
