
void MorseCode(String message) {
  bool early_stop = false;

  //  // start every message with 5 rapid blue flashes
  smartDelay(1000);
  for (int i = 0; i < 5; i++) {
    digitalWrite(B_led_pin, HIGH);
    digitalWrite(R_led_pin, LOW);
    smartDelay(100);
    digitalWrite(B_led_pin, LOW);
    digitalWrite(R_led_pin, HIGH);
    smartDelay(100);
  }
  digitalWrite(B_led_pin, LOW);
  digitalWrite(R_led_pin, LOW);

  int Munits = 0;

  for (int i = 0; i <= message.length(); i++) {
    // early break out
    unsigned long dist_to_wpt_meters =
      TinyGPSPlus::distanceBetween(
        gps.location.lat(),
        gps.location.lng(),
        g_waypt_LAT,
        g_waypt_LON);
    if (dist_to_wpt_meters < 1000) {
      early_stop = true;
      break;
    }
    // end early breakout

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
      char *m_signal[] = {"dash", "dash", "dot", "dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "r") {
      char *m_signal[] = {"dot", "dash", "dot"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "s") {
      char *m_signal[] = {"dot", "dot", "dot"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "t") {
      char *m_signal[] = {"dash"};
      Munits = 1;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "u") {
      char *m_signal[] = {"dot", "dot", "dash"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "v") {
      char *m_signal[] = {"dot", "dot", "dot", "dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "w") {
      char *m_signal[] = {"dot", "dash", "dash"};
      Munits = 3;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "x") {
      char *m_signal[] = {"dash", "dot", "dot", "dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "y") {
      char *m_signal[] = {"dash", "dot", "dash", "dash"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "z") {
      char *m_signal[] = {"dash", "dash", "dot", "dot"};
      Munits = 4;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == " ") {
      char *m_signal[] = {"space"};
      Munits = 1;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "1") {
      char *m_signal[] = {"dot", "dash", "dash", "dash", "dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "2") {
      char *m_signal[] = {"dot", "dot", "dash", "dash", "dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "3") {
      char *m_signal[] = {"dot", "dot", "dot", "dash", "dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "4") {
      char *m_signal[] = {"dot", "dot", "dot", "dot", "dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "5") {
      char *m_signal[] = {"dot", "dot", "dot", "dot", "dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "6") {
      char *m_signal[] = {"dash", "dot", "dot", "dot", "dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "7") {
      char *m_signal[] = {"dash", "dash", "dot", "dot", "dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "8") {
      char *m_signal[] = {"dash", "dash", "dash", "dot", "dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "9") {
      char *m_signal[] = {"dash", "dash", "dash", "dash", "dot"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    else if (String(message[i]) == "0") {
      char *m_signal[] = {"dash", "dash", "dash", "dash", "dash"};
      Munits = 5;
      blink182(m_signal, Munits);
    }
    Serial.println();
  }
  if (not early_stop) {
    //  // end every message with 5 rapid blue flashes
    smartDelay(1000);
    for (int i = 0; i < 5; i++) {
      digitalWrite(B_led_pin, HIGH);
      digitalWrite(R_led_pin, LOW);
      smartDelay(100);
      digitalWrite(B_led_pin, LOW);
      digitalWrite(R_led_pin, HIGH);
      smartDelay(100);
    }
  }

  digitalWrite(B_led_pin, LOW);
  digitalWrite(R_led_pin, LOW);
  smartDelay(1000);
}


void blink182(char *blinkies[], int Munits) {
  if (UIstate == 1) {
    morse_time_unit = 400; // one morse time unit
  }
  else {
    morse_time_unit = 900; // one morse time unit
  }

  for (int i = 0; i < Munits; i++) {
    if (blinkies[i] == "dash") {
      if (UIstate == 1) {
        digitalWrite(R_led_pin, HIGH);
        digitalWrite(beep_pin, HIGH);
      }
      else {
        digitalWrite(R_led_pin, HIGH);
      }
      Serial.print(" Dash ");
      smartDelay(morse_time_unit * 3);
    }
    else if (blinkies[i] == "dot") {
      if (UIstate == 1) {
        digitalWrite(R_led_pin, HIGH);
        digitalWrite(beep_pin, HIGH);
      }
      else {
        digitalWrite(R_led_pin, HIGH);
      }
      Serial.print(" Dot ");
      smartDelay(morse_time_unit);
    }
    else if (blinkies[i] == "space") {
      digitalWrite(R_led_pin, LOW);
      digitalWrite(beep_pin, LOW);
      Serial.print(" space ");
      smartDelay(morse_time_unit * 4);
    }
    digitalWrite(R_led_pin, LOW);
    digitalWrite(beep_pin, LOW);
    smartDelay(morse_time_unit);
  }
  digitalWrite(R_led_pin, LOW);
  digitalWrite(beep_pin, LOW);
  smartDelay(3 * morse_time_unit); // time between letters is 3 units
}

