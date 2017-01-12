//  Serial.println(CswtichBot_val);
// Open 1018
// left closed 522
// right closed broken
// both closed NA

//  Serial.println(CswtichTop_val);
//  // Open 1018
//  // left closed 436
//  // right closed 523
//  // both closed 317
//
//  Serial.println(Rswitch_val);
//  // Open 1015
//  // left closed 525
//  // right closed 435
//  // both closed 317
//
//  Serial.println(IntSwitch_val);
//  // Open  ==1
//  // closed  ==0

// Servo
// 22 ==132   & 90 == 250  & 180 (max) == 405
// the command values drift and pick up off sets seemingly from endstop crashes


#include <Servo.h> // ah i forget these braket notations


Servo LockServo;

int ServoFeedbackPin = A4;
int ServoFBPos_raw = 0;
int ServoFBPos_Filtered = 0;
float Memory = .15;

int CSwitchesBot = A3;
int CSwitchesTop = A2;
int RSwitches = A1;
int IntSwitchPin = 2;

int ExtLEDleft = 8;
int ExtLEDright = 9;
int IntLEDr = 6;
int IntLEDg = 7;

int CswtichBot_val = 0;
int CswtichTop_val = 0;
int Rswitch_val = 0;
bool Rswitch_left = false;
bool Rswitch_leftOld = false;
bool Rswitch_right = false;
bool Rswitch_rightOld = false;

bool IntSwitch_val = false;
bool IntSwitch_valOld = false;
int pos = 90;
int cmd_pos = 90;

bool Locking = false;
bool Unlocking = false;
bool Locked = false;
bool inProcess = false;
bool failedToUnlock = false;
bool failedToLock = false;

unsigned long OldMillis = 0;
unsigned long currentMillis = 0;

void setup() {
  Serial.begin(9600);

  LockServo.attach(3);
  LockServo.write(pos);

  pinMode(ServoFeedbackPin, INPUT_PULLUP);
  pinMode(CSwitchesBot, INPUT_PULLUP);
  pinMode(CSwitchesTop, INPUT_PULLUP);
  pinMode(RSwitches, INPUT_PULLUP);

  // digital input
  pinMode(IntSwitchPin, INPUT_PULLUP);

  pinMode(ExtLEDleft, OUTPUT);
  pinMode(ExtLEDright, OUTPUT);
  pinMode(IntLEDr, OUTPUT);
  pinMode(IntLEDg, OUTPUT);
}

void loop() {

  // read inputs
  CswtichBot_val = analogRead(CSwitchesBot);
  CswtichTop_val = analogRead(CSwitchesTop);
  Rswitch_val = analogRead(RSwitches);
  IntSwitch_val = digitalRead(IntSwitchPin);
  ServoFBPos_raw = analogRead(ServoFeedbackPin);

  Serial.print("C Switches Bottom: ");
  Serial.print(CswtichBot_val);
  Serial.print(" C Switches Top: ");
  Serial.print(CswtichTop_val);
  Serial.print(" R Switches: ");
  Serial.print(Rswitch_val);
  Serial.print(" Inter Switch: ");
  Serial.println(IntSwitch_val);


  // min 35 max 150
  if (IntSwitch_val) { // a change in switch state
    cmd_pos = 80;
    digitalWrite(IntLEDr, HIGH);
  }
  else if (!IntSwitch_val) {
    cmd_pos = 145;
    digitalWrite(IntLEDr, LOW);
  }

  while (pos < cmd_pos) {
    pos += 1;
    delay(30);
  }
  while (pos > cmd_pos) {
    pos -= 1;
    delay(30);
  }

  LockServo.write(pos);
  // reading inputs and filtering values
  //  currentMillis = millis();

  //  if (Rswitch_val > 900) {
  //    Rswitch_left = false;
  //    Rswitch_right = false;
  //  }
  //  else if (Rswitch_val < 900 and Rswitch_val > 475 ) {
  //    Rswitch_left = true;
  //  }
  //  else// temporary
  //  {
  //    Rswitch_left = false;
  //    Rswitch_right = false;
  //  }

  //  ServoFBPos_Filtered = (1 - Memory) * ServoFBPos_raw + Memory * ServoFBPos_Filtered;


  // Debugging tools
  //  Serial.print("Raw Servo Position: ");
  //  Serial.print(ServoFBPos_raw);
  //  Serial.print("    Filtered Servo Position: ");
  //  Serial.println(ServoFBPos_Filtered);




  //  // logic for requesting a lock/unlock
  //  // inside switch
  //  if (IntSwitch_val != IntSwitch_valOld) { // a change in switch state
  //    IntSwitch_valOld = IntSwitch_val;
  //    if (!Locked and !Locking) {
  //      Locking = true;
  //    }
  //    else if (Locked and !Unlocking) {
  //      Unlocking = true;
  //    }
  //  }
  //  // outside top left rectangle switch
  //  if (Rswitch_left != Rswitch_leftOld) { // a change in switch state
  //    Rswitch_leftOld = Rswitch_left;
  //    if (!Locked and !Locking) {
  //      Locking = true;
  //    }
  //    else if (Locked and !Unlocking) {
  //      Unlocking = true;
  //    }
  //  }
  //
  //
  //
  //  // Servo commands to lock and unlock
  //  if (Locking and !Locked) {
  //    if (ServoFBPos_Filtered > 200) {
  //      LockServo.write(50); // fast move
  //      pos = 50;
  //    }
  //    else if (ServoFBPos_Filtered <= 200 and ServoFBPos_Filtered > 140) {
  //      pos = pos - 1;
  //      LockServo.write(pos);
  //      delay(10);
  //      Serial.print("Command Pos");
  //      Serial.println(pos);
  //    }
  //  }
  //  if (Unlocking and Locked) {
  //    if (ServoFBPos_Filtered < 340) {
  //      LockServo.write(150); // fast move
  //      pos = 150;
  //    }
  //    else if (ServoFBPos_Filtered >= 340 and ServoFBPos_Filtered < 400) {
  //      pos = pos + 1;
  //      LockServo.write(pos);
  //      delay(10);
  //      Serial.print("Command Pos");
  //      Serial.println(pos);
  //    }
  //  }
  //
  //
  //  // State update
  //  if (ServoFBPos_Filtered > 400) {
  //    //unlocked
  //    Locked = false;
  //    Locking = false;
  //    Unlocking = false;
  //  }
  //  else if (ServoFBPos_Filtered < 140) {
  //    //locked
  //    Locked = true;
  //    Locking = false;
  //    Unlocking = false;
  //  }

}
