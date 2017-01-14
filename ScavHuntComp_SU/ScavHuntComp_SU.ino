#include <EEPROM.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int start_month = 1;
int start_day = 15;

double waypt_LAT = 41.882591;
double waypt_LON = -71.378951;

double SOLEDAD_waypt_LAT = 32.839826;
double SOLEDAD_waypt_LON = -117.244696;
int SOLEDAD_tolerance = 15; // meters

double SAILBAY_waypt_LAT = 32.718905;
double SAILBAY_waypt_LON = -117.187166;
int SAILBAY_tolerance = 50; // meters

double BEACHBIKE_waypt_LAT = 32.798776;
double BEACHBIKE_waypt_LON = -117.258491;
int BEACHBIKE_tolerance = 100; // meters

double SANFRAN_waypt_LAT = 37.442571; // need actual coordinates of final place
double SANFRAN_waypt_LON = -122.143201;
int SANFRAN_tolerance = 15; // meters

int pause_time = 10000;

int R_led_pin = 8;
int B_led_pin = 10;
int G_led_pin = 9;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 57600;

unsigned long OldMillis = 0;
unsigned long currentMillis = 0;
unsigned long tensec = 10000;

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

String welcome_message = "hello d exclamation point your journey will begin on 1/13/2017"; // don't forget to update this in the step engine!

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Cele(); // testing cele feature

  Serial.begin(115200);
  ss.begin(GPSBaud);
  pinMode(R_led_pin, OUTPUT);

  value = EEPROM.read(address);
  ScavHuntStep = int(value);
  ScavHuntStep = 1; // temporary!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  Serial.print("Scavenger hunt step: ");
  Serial.println(ScavHuntStep);
}
void loop() {
  currentMillis = millis();

  // Dispatch incoming characters
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  delay(2000); // two sec delay to allow for gps fix
  if (gps.location.isValid()) {
    //    if (ScavHuntStep == PREGAME) {
    //      Serial.println(welcome_message);
    //      if (gps.date.month() == start_month and gps.date.day() == start_day) {
    //        ScavHuntStep = SOLEDAD;
    //      }
    //      else {
    //        MorseCode(String(start_month) + " m " + start_day + " d 2017 y");
    //      }
    //  }
    if (ScavHuntStep == SOLEDAD) {
      arrived = DistanceToWPT(SOLEDAD_waypt_LAT, SOLEDAD_waypt_LON, SOLEDAD_tolerance);
      if (arrived = true) {
        ScavHuntStep = SAILBAY;
        arrived = false;
      }
    }
    else if (ScavHuntStep == SAILBAY) {
      //      if (gps.time.hour() >= 1 or gps.time.hour() <= 7) {
      arrived = DistanceToWPT(SAILBAY_waypt_LAT, SAILBAY_waypt_LON, SAILBAY_tolerance);
      if (arrived = true) {
        ScavHuntStep = BEACHBIKE;
        arrived = false;
      }
    }
    //      else if (gps.time.hour() < 1) {
    //        Serial.print(1 - gps.time.hour());
    //        Serial.print(" ");
    //        Serial.println(60 - gps.time.minute());
    //      }
    //      else if (gps.time.hour() > 7) {
    //        Serial.print(24 - gps.time.hour() + 1);
    //        Serial.print(" ");
    //        Serial.println(60 - gps.time.minute());
    //      }
    //  }
    else if (ScavHuntStep == BEACHBIKE) {
      arrived = DistanceToWPT(BEACHBIKE_waypt_LAT, BEACHBIKE_waypt_LON, BEACHBIKE_tolerance);
      if (arrived = true) {
        pause_time = abs(int((target_speed - gps.speed.mps()) * 1000 + 100)); // abs() just in case they go super fast
        if (currentMillis - OldMillis > pause_time and cmd_LED_ON == false) {
          cmd_LED_ON = true;
          OldMillis = currentMillis;
        }
        else if ((currentMillis - OldMillis) > pause_time and cmd_LED_ON == true) {
          cmd_LED_ON = false;
          OldMillis = currentMillis;
        }
        if (gps.speed.mps() >= target_speed) {
          ScavHuntStep = SANFRAN;
        }
        arrived = false;
      }
    }
    else if (ScavHuntStep == SANFRAN) {
      arrived = DistanceToWPT(SANFRAN_waypt_LAT, SANFRAN_waypt_LON, SANFRAN_tolerance);
    }
  }
//  else {
    MorseCode("gps fix needed");
//    //    Serial.print("gps fix needed");
//    //    Serial.println(gps.satellites.value());
//  }
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
    pause_time = dist_to_wpt_meters * 10;
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

void Cele() {
  for (int i = 0; i < 15; i++) {
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
}

