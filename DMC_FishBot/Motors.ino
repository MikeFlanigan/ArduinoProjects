// Motor Pins
int pwm_LFT = 5;
int LFT_1 = 3;
int LFT_2 = 4;

int pwm_RT = 9;
int RT_1 = 7;
int RT_2 = 8;

// Prueba set point
double distancia = 0;

void InitMotors() {

  // Set pins as outputs
  pinMode(pwm_LFT, OUTPUT);
  pinMode(pwm_RT, OUTPUT);
  pinMode(LFT_1, OUTPUT);
  pinMode(LFT_2, OUTPUT);
  pinMode(RT_1, OUTPUT);
  pinMode(RT_2, OUTPUT);

  // Set direction to none direction
  digitalWrite(LFT_1, HIGH);
  digitalWrite(LFT_2, HIGH);
  digitalWrite(RT_1, HIGH);
  digitalWrite(RT_2, HIGH);

}


void MotorControl(double out) {

  // Sets direction
  if (out > 0)
  { // forward
    digitalWrite(LFT_1, HIGH);
    digitalWrite(LFT_2, LOW);
    digitalWrite(RT_1, LOW);
    digitalWrite(RT_2, HIGH);
  }
  else
  { // backward
    digitalWrite(LFT_1, LOW);
    digitalWrite(LFT_2, HIGH);
    digitalWrite(RT_1, HIGH);
    digitalWrite(RT_2, LOW);
  }

  byte vel = abs(out);    // Absolute value of velocity

  // Checks velocity fits the max ouptut range
  if (vel < 0)
    vel = 0;
  if (vel > 255)
    vel = 255;

  // Writes the PWM
  analogWrite(pwm_LFT, vel);
  analogWrite(pwm_RT, vel);

}
