
unsigned long OldMillis = 0;
unsigned long currentMillis = 0;

int Munits = 0;

int morse_time_unit = 300;

int led_pin = 13;

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  String mess = "distance to wpt 23491 m";
  MorseCode(mess);
}


void MorseCode(String message) {
  for (int i = 0; i <= message.length(); i++) {
    Serial.print(message[i]);

    if (String(message[i]) == "a") {
      char *m_signal[] = {"dot", "dash"};
      Munits = 2;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "b") {
      char *m_signal[] = {"dash", "dot", "dot", "dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "c") {
      char *m_signal[] = {"dash", "dot", "dash", "dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "d") {
      char *m_signal[] = {"dash", "dot", "dot"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "e") {
      char *m_signal[] = {"dot"};
      Munits = 1;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "f") {
      char *m_signal[] = {"dot", "dot", "dash", "dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "g") {
      char *m_signal[] = {"dash", "dash", "dot"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "h") {
      char *m_signal[] = {"dot", "dot", "dot", "dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "i") {
      char *m_signal[] = {"dot", "dot"};
      Munits = 2;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "j") {
      char *m_signal[] = {"dot", "dash", "dash", "dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "k") {
      char *m_signal[] = {"dash", "dot", "dash"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "l") {
      char *m_signal[] = {"dot", "dash", "dot", "dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "m") {
      char *m_signal[] = {"dash", "dash"};
      Munits = 2;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "n") {
      char *m_signal[] = {"dash", "dot"};
      Munits = 2;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "o") {
      char *m_signal[] = {"dash", "dash", "dash"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "p") {
      char *m_signal[] = {"dot", "dash", "dash", "dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "q") {
      char *m_signal[] = {"dash", "dash", "dot","dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "r") {
      char *m_signal[] = {"dot","dash", "dot"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "s") {
      char *m_signal[] = {"dot","dot", "dot"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "t") {
      char *m_signal[] = {"dash"};
      Munits = 1;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "u") {
      char *m_signal[] = {"dot","dot","dash"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "v") {
      char *m_signal[] = {"dot","dot","dot","dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "w") {
      char *m_signal[] = {"dot","dash","dash"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "x") {
      char *m_signal[] = {"dash","dot","dot","dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "y") {
      char *m_signal[] = {"dash","dot","dash","dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "z") {
      char *m_signal[] = {"dash","dash","dot","dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == " ") {
      char *m_signal[] = {"space"};
      Munits = 1;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "1") {
      char *m_signal[] = {"dot","dash","dash","dash","dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "2") {
      char *m_signal[] = {"dot","dot","dash","dash","dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "3") {
      char *m_signal[] = {"dot","dot","dot","dash","dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "4") {
      char *m_signal[] = {"dot","dot","dot","dot","dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "5") {
      char *m_signal[] = {"dot","dot","dot","dot","dot"};
      Munits =5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "6") {
      char *m_signal[] = {"dash","dot","dot","dot","dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "7") {
      char *m_signal[] = {"dash","dash","dot","dot","dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "8") {
      char *m_signal[] = {"dash","dash","dash","dot","dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "9") {
      char *m_signal[] = {"dash","dash","dash","dash","dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
        else if (String(message[i]) == "0") {
      char *m_signal[] = {"dash","dash","dash","dash","dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    Serial.println();
  }
}


void blink182(char *blinkies[], int Munits) {
  for (int i = 0; i < Munits; i++) {
    if (blinkies[i] == "dash") {
      digitalWrite(led_pin, HIGH);
      Serial.print(" Dash ");
      delay(morse_time_unit * 3);
    }
    else if (blinkies[i] == "dot") {
      digitalWrite(led_pin, HIGH);
      Serial.print(" Dot ");
      delay(morse_time_unit);
    }
    else if (blinkies[i] == "space") {
      digitalWrite(led_pin, LOW);
      Serial.print(" space ");
      delay(morse_time_unit * 4);
    }
    digitalWrite(led_pin, LOW);
    delay(morse_time_unit);
  }
  digitalWrite(led_pin, LOW);
  delay(3 * morse_time_unit); // time between letters is 3 units
}

