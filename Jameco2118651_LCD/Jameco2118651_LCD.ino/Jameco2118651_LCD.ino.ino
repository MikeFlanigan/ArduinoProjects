// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

byte x = 0;
boolean oneshot = false;
int state = 0;
int transmitDelay = 1;

void loop() {

  switch (state) {
    case 0: // stuff
      {
        Wire.beginTransmission(0x28);
        Wire.write(0xFE);              // sends one byte
        delay(transmitDelay);
        Wire.write(0x47);
        delay(transmitDelay);
        Wire.endTransmission();    // stop transmitting
        state = 6;
      }
    case 1:
      {
        Wire.beginTransmission(0x28);
        Wire.write("123456");              // sends one byte
        delay(transmitDelay);
        //      Wire.write(0x47);
        //      delay(transmitDelay);
        Wire.endTransmission();    // stop transmitting
        state = 2;
      }
    case 6:
      {
        Wire.beginTransmission(0x28);
        Wire.write(0xFE);              // sends one byte
        delay(transmitDelay);
        Wire.write(0x53);
        delay(transmitDelay);
        Wire.write(0x2);
        delay(transmitDelay);
        Wire.endTransmission();    // stop transmitting
        state = 2;
      }
  }
}
