
// Rutine for repeat part of the code every X miliseconds
#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

//Set up a timer Variable
uint32_t timer;

double InputRoll;    // Roll angle value
double InitialRoll;  // Roll initial angle

void setup() {
  
  Serial.begin(9600);
  
  timer = micros();       // Initialize timer
  
  
  InitSensors();          // Initialize sensors
  InitMotors();           // Initialize motors
  delay(1000);            // Wait until sensors be ready
  
  InitialValues();        // Get the initial angle values
  
  SetSetpoint(0);         // Set the PID setpoint to 0

}


double RollAngle =0; // Roll angle variable


void loop() {
  
  runEvery(10){         // Exetutes this part of the code every 10 miliseconds -> 100Hz 
       
    RollAngle = 0.98* (RollAngle + getDGyroRoll()) + 0.02 * (getAccelRoll());
    timer = micros();    // Reset the timer

    MotorControl(Compute(RollAngle-InitialRoll));  // Sends the real roll angle -> Roll - InitialRoll
      
  }

  #include <Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


// Accel
?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?
//Set up accelerometer variables
float accBiasX, accBiasY, accBiasZ;
float accAngleX, accAngleY;
double accRoll = 0;

//Set up gyroscope variables
float gyroBiasX, gyroBiasY, gyroBiasZ;
float gyroRateX, gyroRateY, gyroRateZ;
float gyroRoll = 0;
//double gyro_sensitivity = 70;  //From datasheet, depends on Scale, 2000DPS = 70, 500DPS = 17.5, 250DPS = 8.75.

// Gyro Variables
int x;
int y;
int z;
?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?
?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?
?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?
void InitSensors() {

  Wire.begin();      // Initialize I2C
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}



// Calculate bias for the Gyro and accel, the values it gives when it's not moving
// You have to keep the robot vertically and static for a few seconds
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
for (int i = 1; i < 100; i++) {  // Takes 100 values to get more precision
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

  gyroBiasX += Wire.read() << 8 | Wire.read();
  gyroBiasY += Wire.read() << 8 | Wire.read()
  gyroBiasZ += Wire.read() << 8 | Wire.read();


  accBiasX += Wire.read() << 8 | Wire.read();
  accBiasY += Wire.read() << 8 | Wire.read();
  accBiasZ += Wire.read() << 8 | Wire.read();

  delay(1);

}

// Final bias values for every axis
gyroBiasX = gyroBiasX / 100;
gyroBiasY = gyroBiasY / 100;
gyroBiasZ = gyroBiasZ / 100;

accBiasX = accBiasX / 100;
accBiasY = accBiasY / 100;
accBiasZ = accBiasZ / 100;


//Get Starting Pitch and Roll
accRoll = ((atan2(AcZ - accBiasZ, -(AcX - accBiasX)) + PI) * RAD_TO_DEG;

if (accRoll <= 360 & accRoll >= 180) {
  accRoll = accRoll - 360;
}


}


void InitialValues() {

  //  Accelerometer

  double InitialAngle = 0;
  double dGyro = 0;
  for (int i = 1; i < 100; i++) {  // Takes 100 values to get more precision

    accRoll = (atan2(AcZ - accBiasZ, -(AcX - accBiasX)) + PI) * RAD_TO_DEG;

    gyroRateY = (GyY - gyroBiasY) * .07;

    dGyro = gyroRateY * ((double)(micros() - timer) / 1000000);

    InitialAngle = 0.98 * (InitialAngle + dGyro) + 0.02 * (accRoll);
    timer = micros();

    delay(1);

  }

  InitialRoll = InitialAngle;

  Serial.print("Roll Inicial: ");
  Serial.println(InitialRoll);

}


// Roll from accelerometer
double getAccelRoll() {

  accRoll = (atan2(AcZ - accBiasZ, -(AcX - accBiasX)) + PI) * RAD_TO_DEG;

  if (accRoll <= 360 & accRoll >= 180) {
    accRoll = accRoll - 360;
  }

  return accRoll;

}



// Angular velocity of Roll by gyroscope
double getDGyroRoll() {

  getGyroValues();     // Get values from gyro

  // read raw angular velocity measurements from device
  gyroRateY = -(GyY - gyroBiasY) * .07;
  //gyroRateY = -((int)y - gyroBiasY)*.07;
  //gyroRateZ = ((int)z - gyroBiasZ)*.07;

  double dgyroRoll = gyroRateY * ((double)(micros() - timer) / 1000000);

  return dgyroRoll;

}

