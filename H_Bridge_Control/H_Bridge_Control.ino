// H Bridge Testing

void setup() {
  // put your setup code here, to run once:
  // Left Motor
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);


// Right Motor
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(3, HIGH);
digitalWrite(4, LOW);
analogWrite(5, 145);


digitalWrite(7, HIGH);
digitalWrite(8, LOW);
analogWrite(9, 175);
//analogWrite(11,power); // led 

//power = power + delta;

  // reverse the direction of the fading at the ends of the fade:
 // if (power == 0 || power == 255) {
 //   delta = -delta ;
//    if (ON1 == 1)
//    {
//      ON1 = 0;
//      ON2 = 1;
//    }
//    else
//    {
//      ON1 = 1;
//      ON2 = 0;
//    }
 // }

 // Serial.println(power);
}
