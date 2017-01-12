#include<Wire.h>

// Function declarations
void InitSensors();
void Get_Sensor_Data();
void InitMotors();
void MotorControl(double out);
double Compute(double input);
double getDGyroPitch();
double getAccelPitch();


// Global Variables
//////////// Gyro and Accel Variables
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
float accBiasX, accBiasY, accBiasZ;
float gyroBiasX, gyroBiasY, gyroBiasZ, gyroRateY;
double accPitch = 0;
double initial_Pitch;
///////////////////
////////// Motors Variables
byte vel = 0; // byte creatse an unsigned from 0 to 255
const int Lft_PWM = 5;
const int Rt_PWM = 9;
double out;
///////////////////
/////////// PID Variables
//double kp = 100;         // Proportional gain
double kp = 300;         // Proportional gain
double ki = 0;           // Integral gain
//double ki = .5;           // Integral gain
double kd = 0;           // Derivative gain
double Setpoint = 0;     // Angle setpoint
double output = 0;
//////////////////////


// Main
double Pitch_Angle = 0;
double Corrected_Pitch = 0;
//double cycle_time[110];
//int i = 1;
uint32_t timer;

#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))



void setup() {

  // Debugging LEDs
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  InitSensors();          // Initialize sensors
  InitMotors();           // Initialize motors
  delay(1000);            // Wait until sensors are ready

  timer = micros();       // Initialize timer

  ///////// DEBUGGING
  Serial.begin(9600);

  Pitch_Angle = getAccelPitch() - initial_Pitch; // initial pitch angle

}

void loop() {

  runEvery(10) {        // Exetutes this part of the code every 10 miliseconds -> 100Hz

    //  cycle_time[i] = millis() - _lasttime;

    Pitch_Angle = 0.98 * (Pitch_Angle + getDGyroPitch()) + 0.02 * (getAccelPitch() - initial_Pitch);

    timer = micros();    // Reset the timer

    MotorControl(Compute(Pitch_Angle));
    //   i++;

//    Serial.print("Pitch Angle = "); Serial.println(Pitch_Angle);
//    Serial.print("Accel Angle = "); Serial.println(getAccelPitch() - initial_Pitch);
//    Serial.print("Gyro Angle = "); Serial.println(getDGyroPitch());
    Serial.print("PID out = "); Serial.println(output);
//    Serial.print("vel = "); Serial.print(vel); Serial.print(" | Pitch Angle = "); Serial.println(Pitch_Angle);
  }
  // if (millis() > 1000 && _lasttime < 2000) Serial.println(cycle_time)
}



