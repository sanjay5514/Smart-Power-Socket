#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int relayPin = 8;
const int incButton = 9;
const int decButton = 10;
const int startButton = 11;

int timerMinutes = 0;
bool isRunning = false;
unsigned long startTime;
unsigned long countdownMillis;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(incButton, INPUT_PULLUP);
  pinMode(decButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.print("Set Time (min):");
  lcd.setCursor(0, 1);
  lcd.print(timerMinutes);
}

void loop() {
  if (!isRunning) {
    if (digitalRead(incButton) == LOW) {
      timerMinutes++;
      delay(300);
    }
    if (digitalRead(decButton) == LOW && timerMinutes > 0) {
      timerMinutes--;
      delay(300);
    }
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(timerMinutes);

    if (digitalRead(startButton) == LOW && timerMinutes > 0) {
      isRunning = true;
      countdownMillis = timerMinutes * 60000UL;
      startTime = millis();
      digitalWrite(relayPin, HIGH);
      lcd.clear();
    }
  } else {
    unsigned long elapsed = millis() - startTime;
    unsigned long remaining = countdownMillis - elapsed;
    int remainingMinutes = remaining / 60000;
    int remainingSeconds = (remaining % 60000) / 1000;

    lcd.setCursor(0, 0);
    lcd.print("Time Remaining:");
    lcd.setCursor(0, 1);
    lcd.print(remainingMinutes);
    lcd.print("m ");
    lcd.print(remainingSeconds);
    lcd.print("s  ");

    if (elapsed >= countdownMillis) {
      digitalWrite(relayPin, LOW);
      lcd.clear();
      lcd.print("Timer Done!");
      delay(3000);
      isRunning = false;
      lcd.clear();
      lcd.print("Set Time (min):");
    }
  }
}
