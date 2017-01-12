#include <Wire.h>
#include <SD.h>

const int chipSelect = 8;
File myFile;
int LoadParam = 0;

String LogString =  "";

int transmitDelay = 20;

unsigned long currentMillis = 0;
unsigned long OldMillis = 0;
unsigned long OldMillisPress = 0;
unsigned long OldMillisLCDOn = 0;
unsigned long OldMillisSDsave = 0;
unsigned long OldMillisTiming = 0;

int Seconds = 0;
int OldSeconds = 0;
int Minutes = 0;
int OldMinutes = 0;
unsigned long Hours = 0;
unsigned long OldHours = 0;
int percentHour = 0;

bool Timing = false;
bool LCDPwr = true;
bool LCDOn = true;


int startBtnPin = 5;
int BullshitBtnPin = 6;
int startBtn = 1;
int BullshitBtn = 1;

String DisplayString = "initial";

bool oneshot = false;
bool oneshotClear = false;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(startBtnPin, INPUT_PULLUP);
  pinMode(BullshitBtnPin, INPUT_PULLUP);
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // open the file for reading:
  myFile = SD.open("TimeLog.txt");
  if (myFile) {
    Serial.println("TimeLog.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      LoadParam = LoadParam + 1;
      int val =  myFile.parseInt();
      switch (LoadParam) {
        case 1:
          Seconds = val;
          Serial.print("Saved Seconds: ");
          Serial.println(val);
          break;
        case 2:
          Minutes = val;
          Serial.print("Saved Minutes: ");
          Serial.println(val);
          break;
        case 3:
          Hours = val;
          Serial.print("Saved Hours: ");
          Serial.println(val);
          break;
      }


      //      LogString = LogString + myFile.read();
      //      Serial.write(myFile.read());
    }
    myFile.close(); // close the file:
    //    Serial.println("READREAD");
    //    Serial.println(LogString);
//    Seconds = 15;
//    Minutes = 58;
//    Hours = 43;
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening TimeLog.txt");
  }
}

void loop() {
  //  Serial.print("StartBtn: ");
  //  Serial.print(startBtn);
  //  Serial.print("BullshitBtn: ");
  //  Serial.print(BullshitBtn);
  //  Serial.print("LCDON Command: ");
  //  Serial.print(LCDOn);
  //  Serial.print("  DisplayPower: ");
  //  Serial.print(LCDPwr);
  //  Serial.print("  Timing: ");
  //  Serial.println(Timing);
  //  Serial.println(millis());
  startBtn = digitalRead(startBtnPin);
  BullshitBtn = digitalRead(BullshitBtnPin);


  currentMillis = millis();
  if (currentMillis <= 200) { // this is for rollover clearing.
    OldMillis = 0;
    OldMillisPress = 0;
    OldMillisLCDOn = 0;
    OldMillisSDsave = 0;
  }

  if (LCDOn and not LCDPwr) {
    LCDPwr = true;
    Wire.beginTransmission(0x28);
    Wire.write(0xFE);              // sends one byte
    delay(transmitDelay);
    Wire.write(0x41);
    delay(transmitDelay);
    Wire.endTransmission();    // stop transmitting
  }
  else if (not LCDOn and LCDPwr) {
    LCDPwr = false;
    clearDisp();
  }

  if (LCDOn and LCDPwr and ((currentMillis - OldMillisLCDOn) > 10000)) {
    OldMillisLCDOn = currentMillis;
    LCDOn = false;
  }

  if (not startBtn) {
    OldMillisLCDOn = currentMillis;
    if (not Timing) {
      Timing = true;
    }
    LCDOn = true;
    //    if (currentMillis - OldMillisPress > 500) {
    //      OldMillisPress = currentMillis;
    //      LCDOn = true;
    //    }
  }
  else {
    OldMillisPress = currentMillis;
  }
  if (not BullshitBtn and Timing) {
    Timing = false;
    clearDisp();
  }

  if (LCDPwr == true and Timing == true) {
    if (Minutes == 0 and Hours == 0 and Seconds != OldSeconds) {
      OldSeconds = Seconds;
      DisplayString = String(" Seconds: ") + Seconds + String(" ");
      printToDisp(DisplayString);
      Serial.print("Printing seconds: ");
      Serial.println(DisplayString);
    }
    else if (Minutes > 0 and Hours == 0 and Seconds != OldSeconds) {
      OldSeconds = Seconds;
      DisplayString = String(" mins: ") + Minutes + String(" secs: ") + Seconds;
      printToDisp(DisplayString);
      Serial.print("Printing secs and minutes: ");
      Serial.println(DisplayString);
    }
    else if (Hours > 0 and Seconds != OldSeconds) {
      OldSeconds = Seconds;
      percentHour = int(Minutes / 6);
      DisplayString = String(" Hours: ") + Hours + String(".") + percentHour + String(" ");
      printToDisp(DisplayString);
      Serial.print("Printing hours: ");
      Serial.println(DisplayString);
    }
    else
    {
      //      printToDisp(" This is unexpected ");
    }
  }

  if (Timing == true) {
    if (currentMillis - OldMillis > 1000) {
      OldMillis = currentMillis;
      Seconds = Seconds + 1;
    }
    if (Seconds >= 60) {
      Minutes = Minutes + 1;
      Seconds = 0;
    }
    if (Minutes >= 60) {
      Hours = Hours + 1;
      Minutes = 0;
    }
    if (Seconds >= 10 and Seconds % 10 == 0 and oneshotClear == false) {
      oneshotClear = true;
      clearDisp();
    }

    if (currentMillis - OldMillisSDsave > 5000) {
      OldMillisSDsave = currentMillis;
      myFile = SD.open("TimeLog.txt", FILE_WRITE);

      if (myFile) { // if the file opened okay, write to it:
        myFile.seek(0);
        myFile.print("Seconds: ");
        myFile.println(Seconds);
        myFile.print("Minutes: ");
        myFile.println(Minutes);
        myFile.print("Hours: ");
        myFile.println(Hours);
        myFile.close();
        //        Serial.println("done.");
      }
      else { // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
    }
  }
}

void clearDisp() {
  Wire.beginTransmission(0x28);
  Wire.write(0xFE);              // sends one byte
  delay(transmitDelay);
  Wire.write(0x51);              // sends one byte
  delay(transmitDelay);
  Wire.endTransmission();    // stop transmitting
  //  Serial.println("CLEARDISP");
}

void printToDisp(String x) {
  for (int count = 1; count <= x.length(); count++) {
    Wire.beginTransmission(0x28);
    Wire.write(x.charAt(count));              // sends one byte
    delay(transmitDelay);
    Wire.endTransmission();    // stop transmitting
    //    Serial.println("PRINTDISP");
  }
  Wire.beginTransmission(0x28);
  Wire.write(0xFE);              // sends one byte
  delay(transmitDelay);
  Wire.write(0x46);              // sends one byte
  delay(transmitDelay);
  Wire.endTransmission();    // stop transmitting
}

