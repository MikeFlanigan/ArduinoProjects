#include <Servo.h>
//#include <stdexcept>
Servo SNote0, SNote1, SNote2, SNote3, SNote4, SNote5, SNote6, SNote7, SAir;

Servo ServoArray[] = {SNote0, SNote1, SNote2, SNote3, SNote4, SNote5, SNote6, SNote7, SAir};

int Note0 = 0;
int Note1 = 1;
int Note2 = 2;
int Note3 = 3;
int Note4 = 4;
int Note5 = 5;
int Note6 = 6;
int Note7 = 7;
int Air = 8;

int Note0_ON = 72; // intitially 80
int Note1_ON = 60; // initially 68
int Note2_ON = 68; // inititially 76
int Note3_ON = 101; // initially 91
int Note4_ON = 108; // initially 98
int Note5_ON = 117; // init 107
int Note6_ON = 77; // init 87
int Note7_ON = 79; // init 89
int Air_ON = 75; // initially 114

int OnArray[] = {Note0_ON, Note1_ON, Note2_ON, Note3_ON, Note4_ON, Note5_ON, Note6_ON, Note7_ON, Air_ON};

int Note0_OFF = 160;
int Note1_OFF = 160;
int Note2_OFF = 160;
int Note3_OFF = 25;
int Note4_OFF = 25;
int Note5_OFF = 23;
int Note6_OFF = 163;
int Note7_OFF = 180;
int Air_OFF = 20;

int OffArray[] = {Note0_OFF, Note1_OFF, Note2_OFF, Note3_OFF, Note4_OFF, Note5_OFF, Note6_OFF, Note7_OFF, Air_OFF};

int lowCi = 1;
int Di = 2;
int Dprimei = 21;
int Ei = 3;
int Fi = 4;
int Fsharpi = 41;
int Gi = 5;
int Ai = 6;
int Bi = 7;
int highCi = 8;

bool lowC[] = {true, true, true , true , true, true, true, true, true};
bool D[] = {true, true, true , true , true, true, true, false, true};
bool Dprime[] = {false, false, true , false , false, false, false, false, true};
bool E[] = {true, true, true , true , true, true, false, false, true};
bool F[] = {true, true, true , true , true, false, true, true, true};
bool Fsharp[] = {true, true, true , true , false, true, true, false, true};
bool G[] = {true, true, true , true , false, false, false, false, true};
bool A[] = {true, true, true , false , false, false, false, false, true};
bool B[] = {true, true, false , false , false, false, false, false, true};
bool highC[] = {true, false, true , false , false, false, false, false, true};


int song[] = {Di, Di, Ei, Di, Gi, Fsharpi, Di, Di, Ei, Di, Ai, Gi, Di, Di, Dprimei, Bi, Gi, Fsharpi, Ei, highCi, highCi, Bi, Gi, Ai, Gi};
int song_len = 25; // Fhsapr E shitty hard coded song length for right now...

bool AllON = false;
bool NoteFlag = false;

unsigned long Now = 0;
unsigned long Last = 0;
unsigned long period = 1000;

void setup() {
  Serial.begin(9600);
  ServoArray[Note0].attach(2);
  ServoArray[Note1].attach(3);
  ServoArray[Note2].attach(4);
  ServoArray[Note3].attach(5);
  ServoArray[Note4].attach(6);
  ServoArray[Note5].attach(7);
  ServoArray[Note6].attach(8);
  ServoArray[Note7].attach(9);
  ServoArray[Air].attach(10);

  ServoArray[Note0].write(Note0_OFF);
  ServoArray[Note1].write(Note1_OFF);
  ServoArray[Note2].write(Note2_OFF);
  ServoArray[Note3].write(Note3_OFF);
  ServoArray[Note4].write(Note4_OFF);
  ServoArray[Note5].write(Note5_OFF);
  ServoArray[Note6].write(Note6_OFF);
  ServoArray[Note7].write(Note7_OFF);
  ServoArray[Air].write(Air_OFF);
  delay(1000);
  ServoArray[Air].write(Air_ON);
}

void loop() {
  Now = millis(); // update clock time

  //  Serial.print("notes in song:");
  //  Serial.println(song_len);



  ALLOFF();
  delay(5000);
  for (int s = 0; s < song_len; s++) {
    if (s == 5 || s == 11 || s == 18 || s == 24) {
      PlayNote(song[s], 2, false);
    }
    else if (s == 1 || s == 7 || s == 13 || s == 20) {
      PlayNote(song[s], 1, true);
    }
    else {
      PlayNote(song[s], 1, false);
    }
  }
}



void ALLOFF() {
  ServoArray[8].write(OffArray[8]);
  delay(375);
  for (int i = 0; i < 8; i ++) { // 8 not including air // 9 including air
    ServoArray[i].write(OffArray[i]);
  }
}

void PlayNote(int InNote, int duration, bool doub) {
  if (InNote == lowCi) {
    for (int k = 0; k < 9; k ++) {
      if (lowC[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("lowC");
  }
  else if (InNote == Di) {
    for (int k = 0; k < 9; k ++) {
      if (D[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("D");
  }
  else if (InNote == Ei) {
    for (int k = 0; k < 9; k ++) {
      if (E[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("E");
  }
  else if (InNote == Fi) {
    for (int k = 0; k < 9; k ++) {
      if (F[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("F");
  }
  else if (InNote == Fsharpi) {
    for (int k = 0; k < 9; k ++) {
      if (Fsharp[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("Fsharp");
  }
  else if (InNote == Gi) {
    for (int k = 0; k < 9; k ++) {
      if (G[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("G");
  }
  else if (InNote == Ai) {
    for (int k = 0; k < 9; k ++) {
      if (A[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("A");
  }
  else if (InNote == Bi) {
    for (int k = 0; k < 9; k ++) {
      if (B[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("B");
  }
  else if (InNote == highCi) {
    for (int k = 0; k < 9; k ++) {
      if (highC[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("highC");
  }
  else if (InNote == Dprimei) {
    for (int k = 0; k < 9; k ++) {
      if (Dprime[k]) {
        ServoArray[k].write(OnArray[k]);
      }
      else {
        ServoArray[k].write(OffArray[k]);
      }
    }
    Serial.print("highC");
  }

  if (not doub) {
    delay(750 * duration);
//    ALLOFF();

  }
  else {
    delay(500);
    ServoArray[8].write(OffArray[8]); // air off
    delay(200);
    ServoArray[8].write(OnArray[8]); // air on
    delay(500);
//    ALLOFF();
  }
  delay(200);
}

