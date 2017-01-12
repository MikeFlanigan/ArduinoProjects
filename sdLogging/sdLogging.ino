#include <SD.h>

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.

// Chip Select pin is tied to pin 8 on the SparkFun SD Card Shield
const int chipSelect = 8;  
File myFile; 

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");




    // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


void loop()
{
//  // make a string for assembling the data to log:
//  String dataString = "";
//
//  // open the file. note that only one file can be open at a time,
//  // so you have to close this one before opening another.
//  // this opens the file and appends to the end of file
//  // if the file does not exist, this will create a new file.
//  File dataFile = SD.open("datalog.txt", FILE_WRITE);
//
//  // if the file is available, write to it:
//  if (dataFile)   {  
//    int timeStamp = millis();
//    //write to uSD card
//    dataFile.print(timeStamp);
//    dataFile.print(" ms");
//    dataFile.print(", ");
//    //output also on Serial monitor for debugging
//    Serial.print(timeStamp);
//    Serial.print(",");
//
//    dataFile.println(); //create a new row to read data more clearly
//    dataFile.close();   //close file
//    Serial.println();   //print to the serial port too:
//
//  }  
//  // if the file isn't open, pop up an error:
//  else
//  {
//    Serial.println("error opening datalog.txt");
//  } 
}
