
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

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
