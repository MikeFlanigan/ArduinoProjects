#include <TimerOne.h>

int seconds = 10;

void setup() {
  Serial.begin(9600);

  Timer1.initialize();         // initialize timer1, should default to a 1 second period
  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt

}

void callback()
{
  --seconds;  // decrement seconds variable
}


void loop() {

  while (seconds != -1)
  {
    Serial.println(seconds);
  }
}
