/* Silly Can Bowl Demo */

#include <Servo.h>

Servo myservo;

int Pass = 0;
const int First_Loop = 0;
const int Steady_State = 1;

int fire = 60;
int halt = 175;

int motion = 0;

int state = 0;
int Pressed = 1;
int notPressed = 0;

int flash_time = 0;

int period = 250;
int ledPin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(12, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(halt);
  for (int count = 0; count < 10; count ++) {
    digitalWrite(ledPin, HIGH);
    delay(period);
    digitalWrite(ledPin, LOW);
    delay(period);
  }
}


void loop()
{
  myservo.write(halt);
  motion = digitalRead(12); // Check for motion
  Serial.print("Motion state: ");
  Serial.println(motion);

  //////////////////// Firing Logic /////////////////////////////////////
  if  (motion == HIGH)
  {
    state = Pressed;
    myservo.write(fire);
    delay(400);
    myservo.write(halt);
    digitalWrite(ledPin, HIGH);
    for (int count = 0; count < 10; count ++) {
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
    }
  }
}
