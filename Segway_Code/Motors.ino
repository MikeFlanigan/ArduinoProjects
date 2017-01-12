
int ON_LED;
int OFF_LED;

void InitMotors()
{
  // Left Motor
  pinMode(3, OUTPUT); // Direction
  pinMode(4, OUTPUT); // Direction
  pinMode(Lft_PWM, OUTPUT); // PWM


  // Right Motor
  pinMode(7, OUTPUT); // Direction
  pinMode(8, OUTPUT); // Direction
  pinMode(Rt_PWM, OUTPUT); //PWM
}



void MotorControl(double out) {

  // Sets direction
  if (out < 0)
  { // forward
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);

    ON_LED = 11;
    OFF_LED = 12;
  }
  else
  { // reverse
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);

    ON_LED = 12;
    OFF_LED = 11;
  }

  vel = abs(out);    // Absolute value of velocity

  // Checks velocity fits the max ouptut range
  if (vel < 0)
  {
    vel = 0;
  }
  if (vel > 255)
  {
    vel = 255;
  }

  // Writes the PWM
  analogWrite(Lft_PWM, vel);
  analogWrite(Rt_PWM, vel);

// Writes the debug led PWM
  analogWrite(ON_LED, vel);
  analogWrite(OFF_LED, 0);

}
