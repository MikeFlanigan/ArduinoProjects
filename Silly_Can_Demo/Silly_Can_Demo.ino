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

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


void loop()
{
  myservo.write(halt);
  motion = digitalRead(12);

 // switch (Pass)
 // {
 //   case First_Loop:
   //   Pass = Steady_State;
     // delay(15000);
      //break;
 //   case Steady_State:
      if  (motion == HIGH && state == notPressed)
      {
        state = Pressed;
        myservo.write(fire);
        delay(400);
        myservo.write(halt);
        digitalWrite(13, HIGH);
      }
      else if (state == Pressed)
      {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
        digitalWrite(13, HIGH);
        delay(16000);    // 1000 for debugging, 16000 for real
        digitalWrite(13, LOW);
        state = notPressed;       // 20 second delay
      }
      else
      {
        digitalWrite(13, LOW);
      }
    //  break;
 // }

}
