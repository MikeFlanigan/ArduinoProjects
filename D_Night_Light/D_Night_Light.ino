
int Blue1 = 3;    
int Blue2 = 5;
int Grn1 = 6;    
int Grn2 = 9;
int Purp1 = 10;    
int Purp2 = 11;

int PhotoPin = A0;

int BlueFade = 255;
int GrnFade = 128;
int PurpFade = 0;

int LightValue = 0;

bool lightON = false;

unsigned long OldMillis = 0;
unsigned long OldMillis2 = 0;
const long period = 1000;
const long period2 = 300000;


void setup() {
  //Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
    //Serial.println(LightValue);

  if (currentMillis - OldMillis2 >= period2) {
    OldMillis2 = currentMillis;
     LightValue = analogRead(PhotoPin);
     if (LightValue <= 500) {
           if (lightON == false){
        lightON = true;
            }
            if (lightON == true){
        lightON = false;
            }
     }
     if (LightValue >= 500) {
           if (lightON == false){
      lightON = false;
           }
     }

     
  }


  if (currentMillis - OldMillis >= period) {
    OldMillis = currentMillis;

if (BlueFade >= 255){
  BlueFade = BlueFade - 5;
}
  else if (BlueFade <= 0) {
    BlueFade = BlueFade + 5;
  }

if (GrnFade >= 255){
  GrnFade = GrnFade - 5;
}
  else if (GrnFade <= 0) {
    GrnFade = GrnFade + 5;
  }

  if (PurpFade >= 255){
  PurpFade = PurpFade - 5;
}
  else if (PurpFade <= 0) {
    PurpFade = PurpFade + 5;
  }

analogWrite(Blue1, BlueFade);
analogWrite(Blue2, BlueFade);
analogWrite(Grn1, GrnFade);
analogWrite(Grn2, GrnFade);
analogWrite(Purp1, PurpFade);
analogWrite(Purp2, PurpFade);

  }
}

