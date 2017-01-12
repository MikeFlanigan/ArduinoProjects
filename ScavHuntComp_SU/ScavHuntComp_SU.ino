#include <EEPROM.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

double waypt_LAT = 41.882591;
double waypt_LON = -71.378951;

int pause_time = 10000;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 57600;

unsigned long OldMillis = 0;
unsigned long currentMillis = 0;
unsigned long tensec = 10000;

int start_month = 1;
int start_day = 13;

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
  Serial.begin(115200);
  ss.begin(GPSBaud);
  pinMode(13, OUTPUT);

  value = EEPROM.read(address);
  ScavHuntStep = int(value);
  Serial.print("Scavenger hunt step: ");
  Serial.println(ScavHuntStep);
}
void loop() {
  currentMillis = millis();


  // Dispatch incoming characters
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  if (gps.location.isValid()) {
    if (ScavHuntStep == PREGAME) {
      Serial.println(welcome_message);
      if (gps.date.month() == 1 and gps.date.day() == 12) {
        ScavHuntStep = SOLEDAD;
      }
    }
    else if (ScavHuntStep == SOLEDAD) {
      waypt_LAT = 32.839826;
      waypt_LON = -117.244696;
      tolerance = 5; // meters
      arrived = DistanceToWPT(waypt_LAT, waypt_LON, tolerance);
      if (arrived = true) {
        ScavHuntStep = SAILBAY;
        arrived = false;
      }
    }
    else if (ScavHuntStep == SAILBAY) {
      if (gps.time.hour() >= 1 or gps.time.hour() <= 7) {
        waypt_LAT = 32.718905;
        waypt_LON = -117.187166;
        tolerance = 15; // meters
        arrived = DistanceToWPT(waypt_LAT, waypt_LON, tolerance);
        if (arrived = true) {
          ScavHuntStep = BEACHBIKE;
          arrived = false;
        }
      }
      else if (gps.time.hour() < 1) {
        Serial.print(1 - gps.time.hour());
        Serial.print(" ");
        Serial.println(60 - gps.time.minute());
      }
      else if (gps.time.hour() > 7) {
        Serial.print(24 - gps.time.hour() + 1);
        Serial.print(" ");
        Serial.println(60 - gps.time.minute());
      }
    }
    else if (ScavHuntStep == BEACHBIKE) {
      waypt_LAT = 32.798776;
      waypt_LON = -117.258491;
      tolerance = 30; // meters
      arrived = DistanceToWPT(waypt_LAT, waypt_LON, tolerance);
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
      waypt_LAT = 37.442571; // need actual coordinates of final place
      waypt_LON = -122.143201;
      tolerance = 100; // meters
      arrived = DistanceToWPT(waypt_LAT, waypt_LON, tolerance);
    }
  }
  else {
    Serial.print("waiting for gps fix, current number of satellites: ");
    Serial.println(gps.satellites.value());
  }
  EEPROM.write(address, ScavHuntStep); // this currently blasts the EEPROM continuously, can change if seems problematic
}



bool DistanceToWPT(double waypt_LAT, double waypt_LON, int tolerance) {
  bool arrived_loc = false; // named _loc out of scope paranoia

  double dist_to_wpt_meters =
    TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      waypt_LAT,
      waypt_LON);

  //  dist_to_wpt_meters = 30;
  if (dist_to_wpt_meters > 1000) {
    Serial.print(dist_to_wpt_meters, 9);
    Serial.println(" meters");
    BeginHotCold = false;
    digitalWrite(13, LOW);
  }
  else {
    BeginHotCold = true;
  }

  if (BeginHotCold == true) {
    pause_time = dist_to_wpt_meters * 10;
    if (cmd_LED_ON == false) {
      digitalWrite(13, HIGH);
    }
    else if (cmd_LED_ON == true) {
      digitalWrite(13, LOW);
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

