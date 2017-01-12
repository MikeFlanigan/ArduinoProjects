/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo RtHipServo;  // create servo object to control a servo
Servo RtThighServo;
Servo RtShinServo;
// twelve servo objects can be created on most boards

int RtHipAng;    // variable to store the servo position
int RtThighAng;
int RtShinAng;

int RtHipAngDemo[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 180}; // variable to store the servo position
int RtThighAngDemo[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 180};
int RtShinAngDemo[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 180};

int stride; // mm

unsigned long oldMillis = 0;
unsigned long currentMillis = 0;
unsigned long interval = 20;

boolean OneRun = 0; // set to 1 if I want the setup sequence to run
boolean Step = 0; // set to 1 if I want the step sequence to run

boolean OneShotPrint = 1; // for a single print at the finish

char ch;

int ii = 0; // var for incrementing

///////////////////////////////////////////////////////////////////////////////////////////////
//          DECLARATIONS ABOVE
///////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  while (!Serial); // waits until Serial is ready (pretty sweet, means program won't run early

  RtHipServo.attach(3);
  RtThighServo.attach(5);
  RtShinServo.attach(6);

  // read command is really useless... outputs last command not actual feedback
  //  int RtHipAng_init = RtHipServo.read();
  //  int RtThighAng_init = RtThighServo.read();
  //  int RtShinAng_init = RtShinServo.read();

  RtHipServo.write(90);
  RtThighServo.write(90);
  RtShinServo.write(90);
  delay(1500);
}

void loop()
{
  currentMillis = millis(); // running timer

  //if (Serial.available()) {
  ch = Serial.read(); // 0 - Go to setup, 1- Loop through test

  // Single setup sequence
  //if (ch = '0') {
  while (OneRun == HIGH) {
    RtThighServo.write(0); // go to clear
    delay(250);
    RtShinServo.write(0); // go to extended pt of stride
    delay(250);
    RtHipServo.write(0); // go to extent of stride
    delay(250);
    RtThighServo.write(0); // go to lift point
    delay(250);
    OneRun = LOW;
  }
  //}

  // Coordinated motion sequence
  //if (ch = '1') {
  if (currentMillis - oldMillis >= interval && ii < 11 ) {
    RtHipServo.write(RtHipAngDemo[ii]);
    RtThighServo.write(RtThighAngDemo[ii]);
    RtShinServo.write(RtShinAngDemo[ii]);
    ii = ii + 1; // increment loop
    oldMillis = currentMillis; // update old time
    Serial.println("Debug Flag");
  }
  // }

  if (ii >= 11 && OneShotPrint) {
    RtHipServo.write(RtHipAngDemo[ii]);
    RtThighServo.write(RtThighAngDemo[ii]);
    RtShinServo.write(RtShinAngDemo[ii]);

    Serial.println("Finished");
    Serial.print("ii = ");
    Serial.println(ii);
    OneShotPrint = 0; // diables the oneshot print
  }
  //}
  //Serial.println(ch);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//          CUSTOM FUNCTIONS BELOW
///////////////////////////////////////////////////////////////////////////////////////////////

void L_Forward(int s)
{
  // For i :1:stride{

  //  }
}

void L_resForward(int stride) {
  //  Tocenter ang= Atan(strideabspos/lspan)
  //  Toforward ang= atan(strideabsposend/lspan)
  //
  //  Thighup(enough)
  //  Shinout(enough)
  //  Hipforward(current+tocenter+toforward)
  //
  //  Shin(touchdownablge)
  //  Thigh(restangle)
}

void L_Back(int stride) {

}

void L_resBack(int stride) {

}

void R_Forward(int stride) {

}

