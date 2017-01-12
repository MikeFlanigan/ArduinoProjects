
#include<Wire.h>
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
uint32_t timer;
float gyroRateY;

double accRoll = 0;

// PID variables
int outMax = 255;
int outMin = -255;
float lastInput = 0;
double ITerm =0;
double kp = 100;         // Proportional value
double ki = 2;           // Integral value
double kd = 0;           // Derivative value

double Setpoint = 0;     // Initial setpoint is 0

double RollAngle = 0; // Roll angle variable
int power = 135;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
   Serial.begin(9600);

pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);


  // Right Motor
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  analogWrite(5, power);
  analogWrite(9, power);
}


void loop() {
  timer = micros();       // Initialize timer
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

//accRoll = 0;
accRoll = (atan2(AcZ, -(AcX )) - PI / 2) * RAD_TO_DEG;

  gyroRateY = -(GyY) / 131;  // should give deg/s

  double dt = ((double)(micros() - timer) );
  double dgyroRoll = gyroRateY * dt / 1000000;
  double filter = .98;
  RollAngle = filter * (RollAngle + dgyroRoll) + (1 - filter) * (accRoll);

  if (RollAngle > 0)
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    //analogWrite(5, power);

    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    //analogWrite(9, power);
  }
  else
  {
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    //analogWrite(5, power);

    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    //analogWrite(9, power);
  }






  
  Serial.print(" | AccRoll = "); Serial.print(accRoll);
    Serial.print("RollAngle = "); Serial.println(RollAngle);
    /*
    Serial.print(" | gyroRateY =  "); Serial.print(gyroRateY); Serial.print("deg/s");
    Serial.print(" | GyroRoll =  "); Serial.print(dgyroRoll); Serial.print("deg");
    Serial.print(" | AccRoll = "); Serial.print(accRoll);
    Serial.print(" | AcX = "); Serial.print(AcX);
    Serial.print(" | AcY = "); Serial.print(AcY);
    Serial.print(" | AcZ = "); Serial.print(AcZ);
    Serial.print(" | Tmp = "); Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
    Serial.print(" | GyX = "); Serial.print(GyX);
    Serial.print(" | GyY = "); Serial.print(GyY);
    Serial.print(" | GyZ = "); Serial.println(GyZ);
    //delay(333);

  */
}
