
// reference the example file to begin working on this

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("16x8 LED Matrix Test");

  matrix.begin(0x70);  // pass in the address

}

test

void loop() {
  // put your main code here, to run repeatedly:

}
