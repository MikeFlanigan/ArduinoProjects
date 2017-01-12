#include <Servo.h>

Servo myservo;
int fire = 140;
int halt = 150;

int state = 0;
int Pressed = 1;
int notPressed = 0;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(halt);
  delay(3000);
  if (state == notPressed)
  {
    myservo.write(fire);
    delay(1000);
    myservo.write(halt);
    state = Pressed;
  }
  else
  {
    // Do nothing
  }
}
