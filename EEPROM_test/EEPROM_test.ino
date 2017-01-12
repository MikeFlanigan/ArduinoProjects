#include <EEPROM.h>

int address = 0;
byte value;

void setup() {
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
//  value = EEPROM.read(address);
//  Serial.println(value, DEC);
  int val = 0;
  EEPROM.write(address, val);
}
