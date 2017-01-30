/*
   Much of the gps functionality in this program comes from the "FullExample.ino" sketch provided by Mikal Hart
   as an example application of the TinyGPS++ library.
*/


#include <EEPROM.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//#include <PinChangeInt.h>   // wanted to use the interrupt to switch audio visual but PinChangeInt and SoftSerial conflict

///////////////// WAYPOINT 1 //////////////////////////
double SOLEDAD_waypt_LAT = 32.839826;
double SOLEDAD_waypt_LON = -117.244610;

//double SOLEDAD_waypt_LAT = 42.397831; // test wpt
//double SOLEDAD_waypt_LON = -71.124027; // test wpt
int SOLEDAD_tolerance = 15; // meters
///////////////////////////////////////////////////////
///////////////// WAYPOINT 2 //////////////////////////
double SAILBAY_waypt_LAT = 32.718905;
double SAILBAY_waypt_LON = -117.187166;

//double SAILBAY_waypt_LAT = 42.355081; // test wpt
//double SAILBAY_waypt_LON = -71.159988; // test wpt
int SAILBAY_tolerance = 25; // meters
///////////////////////////////////////////////////////
///////////////// WAYPOINT 3 //////////////////////////
double BEACHBIKE_waypt_LAT = 32.798776;
double BEACHBIKE_waypt_LON = -117.258491;

//double BEACHBIKE_waypt_LAT = 41.639142; // test wpt
//double BEACHBIKE_waypt_LON = -71.201257; // test wpt
int BEACHBIKE_tolerance = 15; // meters
///////////////////////////////////////////////////////
///////////////// FINAL WAYPOINT //////////////////////////
double SANFRAN_waypt_LAT = 37.359446;
double SANFRAN_waypt_LON = -121.978287;

//double SANFRAN_waypt_LAT = 41.631457; // test wpt
//double SANFRAN_waypt_LON = -71.208192; // test wpt
int SANFRAN_tolerance = 15; // meters
///////////////////////////////////////////////////////

double g_waypt_LAT = SOLEDAD_waypt_LAT;
double g_waypt_LON = SOLEDAD_waypt_LON;

int pause_time = 10000;

int morse_time_unit = 900;

int R_led_pin = 8;
int B_led_pin = 10;
int G_led_pin = 9;

int beep_pin = 6;

int UIinterruptPin = A3;
volatile int UIstate = 0; // 0 means just visual, 1 means visual and audio
int OldUIstate = 0;

int old_state_val = 1;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 57600;

unsigned long OldMillis = 0;
unsigned long currentMillis = 0;
unsigned long tensec = 10000;
unsigned long startup_millis = 10000;

bool BeginHotCold = false;
bool cmd_LED_ON = false;

int PREGAME = 0;
int SOLEDAD = 1;
int SAILBAY = 2;
int BEACHBIKE = 3;
int SANFRAN = 4;

bool arrived = false;
int tolerance = 1; // meters

float target_speed = 6.5; // meters per second ... roughly equal to 14.5 mph

int ScavHuntStep = PREGAME;

int address = 0;
byte value;

bool start_up_oneshot = false;
bool gps_fix_found = false;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Cele(10); // testing cele feature

  Serial.begin(115200);
  ss.begin(GPSBaud);
  pinMode(R_led_pin, OUTPUT);
  pinMode(G_led_pin, OUTPUT);
  pinMode(B_led_pin, OUTPUT);

  pinMode(beep_pin, OUTPUT);

  pinMode(UIinterruptPin, INPUT_PULLUP);
  digitalWrite(UIinterruptPin, HIGH);

  value = EEPROM.read(address);
  ScavHuntStep = int(value);
//  ScavHuntStep = 1; // temporary!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! use to reset step engine
  Serial.print("Scavenger hunt step: ");
  Serial.println(ScavHuntStep);
}
void loop() {
  currentMillis = millis();

  // Dispatch incoming characters
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // including the below smart delay messes up the timing in the rest of the program
  //  smartDelay(1000); // feed gps but limit everything else to 1 hz
  if (not start_up_oneshot) {
    gps.encode(ss.read());
    Serial.println("Startup waiting for recent gps fix...");
    if (startup_millis <= currentMillis) {
      start_up_oneshot = true;
    }

    int state_val = digitalRead(UIinterruptPin);
    if (state_val == 1 and old_state_val == 0) { // rising edge of button press
      for (int i = 0; i < 4; i++) {
        digitalWrite(beep_pin, HIGH);
        smartDelay(100);
        digitalWrite(beep_pin, LOW);
        smartDelay(100);
      }
      UIstate = 1;
    }
    old_state_val = state_val;


  }
  else if (start_up_oneshot) {

    if (gps.location.isValid()) {
      gps_fix_found = true;
      if (ScavHuntStep == SOLEDAD) {
        Serial.println("SOLEDAD");
        g_waypt_LAT = SOLEDAD_waypt_LAT;
        g_waypt_LON = SOLEDAD_waypt_LON;
        arrived = DistanceToWPT(SOLEDAD_waypt_LAT, SOLEDAD_waypt_LON, SOLEDAD_tolerance);
        if (arrived == true) {
          ScavHuntStep = SAILBAY;
          g_waypt_LAT = SAILBAY_waypt_LAT;
          g_waypt_LON = SAILBAY_waypt_LON;
          arrived = false;
          Cele(40);
          Serial.println("ARRIVED");
        }
      }
      else if (ScavHuntStep == SAILBAY) {
        Serial.println("SAILBAY");
        g_waypt_LAT = SAILBAY_waypt_LAT;
        g_waypt_LON = SAILBAY_waypt_LON;
        arrived = DistanceToWPT(SAILBAY_waypt_LAT, SAILBAY_waypt_LON, SAILBAY_tolerance);
        if (arrived == true) {
          ScavHuntStep = BEACHBIKE;
          g_waypt_LAT = BEACHBIKE_waypt_LAT;
          g_waypt_LON = BEACHBIKE_waypt_LON;
          arrived = false;
          Cele(40);
          Serial.println("ARRIVED");
        }
      }

      else if (ScavHuntStep == BEACHBIKE) {
        Serial.println("BEACHBIKE");
        g_waypt_LAT = BEACHBIKE_waypt_LAT;
        g_waypt_LON = BEACHBIKE_waypt_LON;
        arrived = DistanceToWPT(BEACHBIKE_waypt_LAT, BEACHBIKE_waypt_LON, BEACHBIKE_tolerance);
        if (arrived == true) {
          ScavHuntStep = SANFRAN;
          g_waypt_LAT = SANFRAN_waypt_LAT;
          g_waypt_LON = SANFRAN_waypt_LON;
          arrived = false;
          Cele(40);
          Serial.println("ARRIVED");
        }
      }

      else if (ScavHuntStep == SANFRAN) {
        Serial.println("SANFRAN");
        g_waypt_LAT = SANFRAN_waypt_LAT;
        g_waypt_LON = SANFRAN_waypt_LON;
        arrived = DistanceToWPT(SANFRAN_waypt_LAT, SANFRAN_waypt_LON, SANFRAN_tolerance);
        if (arrived == true) {
          arrived = false;
          Cele(100);
          Cele(100);
          Cele(100);
          Serial.println("ARRIVED");
          Serial.println("ARRIVED");
          Serial.println("ARRIVED");
        }
      }
    }
    else {
      gps_fix_found = false;
      MorseCode("gps fix needed");
      Serial.print("gps fix needed");
    }
  }

  //  int pot_val = analogRead(A1); // potentiometer to change morse speed
  //  Serial.print("sensor val:");
  //  Serial.println(pot_val);

  EEPROM.write(address, ScavHuntStep); // this currently blasts the EEPROM continuously, can change if seems problematic
}



bool DistanceToWPT(double waypt_LAT, double waypt_LON, int tolerance) {
  bool arrived_loc = false; // named _loc out of scope paranoia

  unsigned long dist_to_wpt_meters =
    TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      waypt_LAT,
      waypt_LON);

  if (dist_to_wpt_meters > 1000) {
    MorseCode(String(dist_to_wpt_meters));
    Serial.println(String(dist_to_wpt_meters));
    BeginHotCold = false;
    digitalWrite(G_led_pin, LOW);
  }
  else {
    BeginHotCold = true;
  }

  if (BeginHotCold == true) {
    pause_time = (dist_to_wpt_meters - tolerance) * 10;
    Serial.println(dist_to_wpt_meters - tolerance);
    if (pause_time < 10) {
      pause_time = 10;
    }
    if (cmd_LED_ON == true) {
      if (UIstate == 1) {
        digitalWrite(B_led_pin, HIGH);
        digitalWrite(beep_pin, HIGH);
      }
      else {
        digitalWrite(B_led_pin, HIGH);
      }
      Serial.println("ON");
    }
    else if (cmd_LED_ON == false) {
      digitalWrite(B_led_pin, LOW);
      digitalWrite(beep_pin, LOW);
      Serial.println("OFF");
    }

    if (currentMillis - OldMillis > pause_time and cmd_LED_ON == false) {
      cmd_LED_ON = true;
      OldMillis = currentMillis;
    }
    else if ((currentMillis - OldMillis) > pause_time and cmd_LED_ON == true) {
      cmd_LED_ON = false;
      OldMillis = currentMillis;
    }
  }
  if (dist_to_wpt_meters <= tolerance) {
    arrived_loc = true;
  }
  return arrived_loc;
}

void Cele(int mult) {
  for (int i = 0; i < mult; i++) {
    digitalWrite(B_led_pin, HIGH);
    digitalWrite(G_led_pin, HIGH);
    digitalWrite(R_led_pin, LOW);
    digitalWrite(beep_pin, LOW);
    smartDelay(100);
    digitalWrite(B_led_pin, LOW);
    digitalWrite(G_led_pin, HIGH);
    digitalWrite(R_led_pin, HIGH);
    digitalWrite(beep_pin, HIGH);
    smartDelay(100);
    digitalWrite(B_led_pin, HIGH);
    digitalWrite(G_led_pin, LOW);
    digitalWrite(R_led_pin, HIGH);
    digitalWrite(beep_pin, LOW);
    smartDelay(100);
  }
  digitalWrite(B_led_pin, LOW);
  digitalWrite(G_led_pin, LOW);
  digitalWrite(R_led_pin, LOW);
}


// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}


//void UIswitch() {
//  UIstate ++;
//  if (UIstate == 3) {
//    UIstate = 0;
//  }
//}
