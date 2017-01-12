// MPU6065 Sensor


void InitSensors()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);



  // Calculate bias for the Gyro and accel, the values it gives when it's not moving
  // You have to keep the robot vertically and static for a few seconds
  ///*
  for (int i = 1; i < 100; i++) {  // Takes 100 values to get more precision

    Get_Sensor_Data(); // Get Sensor Data

    gyroBiasX += GyX;
    gyroBiasY += GyY;
    gyroBiasZ += GyZ;

    accBiasX += AcX;
    accBiasY += AcY;
    accBiasZ += AcZ;

    delay(1); // 1 millisecond delay

  }

  // Final bias values for every axis
  gyroBiasX = gyroBiasX / 100;
  gyroBiasY = gyroBiasY / 100;
  gyroBiasZ = gyroBiasZ / 100;

  accBiasX = accBiasX / 100;
  accBiasY = accBiasY / 100;
  accBiasZ = accBiasZ / 100;

//  initial_Pitch = (atan2(AcZ - accBiasZ, -(AcX - accBiasX)) + PI  ) * RAD_TO_DEG;
  initial_Pitch = (atan2(AcZ , -(AcX)) + PI  ) * RAD_TO_DEG;

}



void Get_Sensor_Data()
{
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
}


// Angular velocity of Roll by gyroscope
double getDGyroPitch() {

  Get_Sensor_Data();

  gyroRateY = -(GyY - gyroBiasY) / 131; // should give deg/s

  double dgyroRoll = gyroRateY * ((double)(micros() - timer) / 1000000);

  return dgyroRoll;

}


// Roll from accelerometer
double getAccelPitch() {

  Get_Sensor_Data();

  accPitch = (atan2(AcZ, -(AcX)) + PI) * RAD_TO_DEG;
  //accPitch = (atan2(AcZ - accBiasZ, -(AcX - accBiasX)) + PI) * RAD_TO_DEG;

  /*
    if (accRoll <= 360 & accRoll >= 180){
      accRoll = accRoll - 360;
    }
   */

  return accPitch;

}
