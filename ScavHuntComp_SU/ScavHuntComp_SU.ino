#include <TinyGPS++.h>
#include <SoftwareSerial.h>

double waypt_LAT = 41.882591;
double waypt_LON = -71.378951;

int pause_time = 10000;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 57600;

unsigned long OldMillis = 0;
unsigned long currentMillis = 0;

bool BeginHotCold = false;
bool cmd_LED_ON = false;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud);
  pinMode(13, OUTPUT);
}
void loop() {
  currentMillis = millis();


  // Dispatch incoming characters
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  if (gps.location.isValid()){
  Serial.print("sats");
  Serial.print(gps.satellites.value());
  Serial.print(" speed meters / sec");
  Serial.print(gps.speed.mps());

  double dist_to_wpt_meters =
    TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      waypt_LAT,
      waypt_LON);
  Serial.print("dist to waypt meters ");
  Serial.print(dist_to_wpt_meters, 3);
  Serial.println();
//  dist_to_wpt_meters = 30;
  if (dist_to_wpt_meters < 1000) {
    BeginHotCold = true;
  }
  else {
    BeginHotCold = false;
    digitalWrite(13, LOW);
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
  }
  else{
    Serial.println("waiting for valid position");
  }


}
