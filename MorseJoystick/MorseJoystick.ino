#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int VRX = A0;
const int VRY = A1;

String morseBuffer = "";
String finalText = "";
String lastDisplayedText = "";

unsigned long lastInputTime = 0;
unsigned long lastMorseInput = 0;

const unsigned long idleLimit = 5000;    
const unsigned long letterDelay = 700;   

// --- HOLD-TO-CLEAR VARIABLES ---
bool holdingLeft = false;
unsigned long leftHoldStart = 0;

// --- EDGE DETECTION FOR DOT/DASH/SPACE/BACKSPACE ---
bool upRegistered = false;
bool rightRegistered = false;
bool downRegistered = false;
bool leftSlideRegistered = false;

// Morse dictionary
char morseToChar(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';

  if (code == "-----") return '0';
  if (code == ".----") return '1';
  if (code == "..---") return '2';
  if (code == "...--") return '3';
  if (code == "....-") return '4';
  if (code == ".....") return '5';
  if (code == "-....") return '6';
  if (code == "--...") return '7';
  if (code == "---..") return '8';
  if (code == "----.") return '9';

  if (code == ".-.-.-") return '.';
  if (code == "--..--") return ',';
  if (code == "..--..") return '?';
  if (code == ".----.") return '\'';
  if (code == "-.-.--") return '!';
  if (code == "-..-.") return '/';
  if (code == "-.--.") return '(';
  if (code == "-.--.-") return ')';
  if (code == ".-...") return '&';
  if (code == "---...") return ':';
  if (code == "-.-.-.") return ';';
  if (code == "-...-") return '=';
  if (code == ".-.-.") return '+';
  if (code == "-....-") return '-';
  if (code == "..--.-") return '_';
  if (code == ".-..-.") return '\"';
  if (code == "...-..-") return '$';
  if (code == ".--.-.") return '@';

  return '?';
}

// --- Helper function to print finalText across 4 lines ---
void printToLCD(String text) {
  lcd.clear();
  for (int row = 0; row < 4; row++) {
    int start = row * 20;
    if (start >= text.length()) break; // no more text
    int len = min(20, text.length() - start);
    lcd.setCursor(0, row);
    lcd.print(text.substring(start, start + len));
  }
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Morse to Text");
  delay(1200);
  lcd.clear();
  lastInputTime = millis();
}

void loop() {
  int x = analogRead(VRX);
  int y = analogRead(VRY);

  bool inputDetected = false;

  // ---- DOT (UP) ----
  if (y < 300) {
    if (!upRegistered) {
      morseBuffer += ".";
      inputDetected = true;
      lastMorseInput = millis();
      upRegistered = true;
    }
  } else {
    upRegistered = false;
  }

  // ---- DASH (RIGHT) ----
  if (x > 700) {
    if (!rightRegistered) {
      morseBuffer += "-";
      inputDetected = true;
      lastMorseInput = millis();
      rightRegistered = true;
    }
  } else {
    rightRegistered = false;
  }

  // ---- SPACE (DOWN) ----
  if (y > 1000) {
    if (!downRegistered) {
      finalText += " ";
      inputDetected = true;
      downRegistered = true;
      delay(250); // prevent accidental repeat
    }
  } else {
    downRegistered = false;
  }

  // ---- BACKSPACE / HOLD CLEAR (LEFT) ----
  if (x < 300) {
    if (!leftSlideRegistered) {
      leftSlideRegistered = true;
      leftHoldStart = millis();
    }

    // HOLD-TO-CLEAR
    if (millis() - leftHoldStart >= 1000) {
      finalText = "";
      morseBuffer = "";
      lastDisplayedText = "";
      lcd.clear();
      leftSlideRegistered = false;
      delay(300);
      return;
    }

    // SINGLE BACKSPACE
    if (finalText.length() > 0) {
      finalText.remove(finalText.length() - 1, 1);
      inputDetected = true;
      delay(250);
    }

  } else {
    leftSlideRegistered = false;
  }

  // ---- AUTO-DECODE LETTER ----
  if (morseBuffer.length() > 0 && millis() - lastMorseInput > letterDelay) {
    char decoded = morseToChar(morseBuffer);
    finalText += decoded;
    morseBuffer = "";
    inputDetected = true;
  }

  // ---- 5-second idle reset ----
  if (inputDetected) lastInputTime = millis();

  if (millis() - lastInputTime > idleLimit) {
    if (x < 300 || x > 700 || y < 300 || y > 700) {
      finalText = "";
      morseBuffer = "";
      lastDisplayedText = "";
      lcd.clear();
      lastInputTime = millis();
    }
  }

  // ---- UPDATE LCD ----
  if (finalText != lastDisplayedText) {
    printToLCD(finalText);
    lastDisplayedText = finalText;
  }
}
