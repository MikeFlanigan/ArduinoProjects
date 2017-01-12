
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
    // variable to store the servo position 
int fire = 10;
int halt = 0;
 
void setup() 
{ 
   pinMode(13, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
    delay(3000);                           // in steps of 1 degree 
    myservo.write(fire);              // tell servo to go to position in variable 'pos' 
    delay(3000);                       // waits 15ms for the servo to reach the position 
    myservo.write(halt);              // tell servo to go to position in variable 'pos' 
                     // waits 15ms for the servo to reach the position 
  
} 

