#include <EEPROM.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

double waypt_LAT = 41.882591;
double waypt_LON = -71.378951;

///////////////// WAYPOINT 1 //////////////////////////
//double SOLEDAD_waypt_LAT = 32.839826;
//double SOLEDAD_waypt_LON = -117.244696;

double SOLEDAD_waypt_LAT = 41.955784; // fake boston
double SOLEDAD_waypt_LON = -71.027170; // fake boston
int SOLEDAD_tolerance = 15; // meters
///////////////////////////////////////////////////////
///////////////// WAYPOINT 2 //////////////////////////
//double SAILBAY_waypt_LAT = 32.718905;
//double SAILBAY_waypt_LON = -117.187166;

double SAILBAY_waypt_LAT = 41.704719; // fake boston
double SAILBAY_waypt_LON = -71.268396; // fake boston
int SAILBAY_tolerance = 25; // meters
///////////////////////////////////////////////////////
///////////////// WAYPOINT 3 //////////////////////////
//double BEACHBIKE_waypt_LAT = 32.798776;
//double BEACHBIKE_waypt_LON = -117.258491;

double BEACHBIKE_waypt_LAT = 41.625234; // fake boston
double BEACHBIKE_waypt_LON = -71.207034; // fake boston
int BEACHBIKE_tolerance = 15; // meters
///////////////////////////////////////////////////////
///////////////// FINAL WAYPOINT //////////////////////////
//double SANFRAN_waypt_LAT = 37.442571; // need actual coordinates of final place
//double SANFRAN_waypt_LON = -122.143201;

double SANFRAN_waypt_LAT = 41.631468; // fake boston
double SANFRAN_waypt_LON = -71.208389; // fake boston
int SANFRAN_tolerance = 15; // meters
///////////////////////////////////////////////////////

int pause_time = 10000;

int R_led_pin = 8;
int B_led_pin = 10;
int G_led_pin = 9;

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
  if (not start_up_oneshot) {
    if (startup_millis <= currentMillis) {
      start_up_oneshot = true;
    }
  }
  else if (start_up_oneshot) {

    if (gps.location.isValid()) {
      if (ScavHuntStep == SOLEDAD) {
        Serial.println("SOLEDAD");
        arrived = DistanceToWPT(SOLEDAD_waypt_LAT, SOLEDAD_waypt_LON, SOLEDAD_tolerance);
        if (arrived == true) {
          Cele(100);
          ScavHuntStep = SAILBAY;
          arrived = false;
        }
      }
      else if (ScavHuntStep == SAILBAY) {
        Serial.println("SAILBAY");
        arrived = DistanceToWPT(SAILBAY_waypt_LAT, SAILBAY_waypt_LON, SAILBAY_tolerance);
        if (arrived == true) {
          Cele(100);
          ScavHuntStep = BEACHBIKE;
          arrived = false;
        }
      }

      else if (ScavHuntStep == BEACHBIKE) {
        Serial.println("BEACHBIKE");
        arrived = DistanceToWPT(BEACHBIKE_waypt_LAT, BEACHBIKE_waypt_LON, BEACHBIKE_tolerance);
        if (arrived == true) {
          Cele(100);
          ScavHuntStep = SANFRAN;
          arrived = false;
        }
      }

      else if (ScavHuntStep == SANFRAN) {
        Serial.println("SANFRAN");
        arrived = DistanceToWPT(SANFRAN_waypt_LAT, SANFRAN_waypt_LON, SANFRAN_tolerance);
        if (arrived == true) {
          Cele(100);
          Cele(100);
          Cele(100);
        }
      }
    }
    else {
      MorseCode("gps fix needed");
      //    //    Serial.print("gps fix needed");
    }
  }
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
    if (pause_time < 10){
      pause_time = 10;
    }
    if (cmd_LED_ON == false) {
      digitalWrite(G_led_pin, HIGH);
    }
    else if (cmd_LED_ON == true) {
      digitalWrite(G_led_pin, LOW);
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
    delay(100);
    digitalWrite(B_led_pin, LOW);
    digitalWrite(G_led_pin, HIGH);
    digitalWrite(R_led_pin, HIGH);
    delay(100);
    digitalWrite(B_led_pin, HIGH);
    digitalWrite(G_led_pin, LOW);
    digitalWrite(R_led_pin, HIGH);
    delay(100);
  }
  digitalWrite(B_led_pin, LOW);
  digitalWrite(G_led_pin, LOW);
  digitalWrite(R_led_pin, LOW);
}

