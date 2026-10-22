#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledBuiltIn = LED_BUILTIN;
const int shimPin = 9;
const int speakerPin = 8;
const int potFreqPin = A0;

int oldFreqPot = 0;
int maxStep = 77;

int standart_pause = 1000;
int blinkDuration = 100;
int speakerDuration = 100;

void setup() {

  lcd.init();
  lcd.backlight();

  pinMode(ledBuiltIn, OUTPUT);
  pinMode(shimPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

}

void loop() {

  blink_work();
  main_program();
  delay(standart_pause);

}

void blink_work() {

  digitalWrite(ledBuiltIn, HIGH);
  delay(blinkDuration);

  digitalWrite(ledBuiltIn, LOW);
  delay(blinkDuration);

}

void speakerAlert() {
  tone(speakerPin, 800, speakerDuration);
  delay(speakerDuration);

  tone(speakerPin, 900, speakerDuration);
  delay(speakerDuration);

  tone(speakerPin, 1000, speakerDuration);
  delay(speakerDuration);

  noTone(speakerPin);
  digitalWrite(speakerPin, LOW);
  delay(speakerDuration);
}

void main_program() {

  int freqPot = analogRead(potFreqPin);

  if ( abs(freqPot - oldFreqPot) > maxStep ) {
    speakerAlert();
    oldFreqPot = freqPot;
  }

  int icrValue = map(freqPot, 0, 1023, 255, 65535); //int icrValue = 20000;
  ICR1 = icrValue;

  int dutyPot = 500;
  int duty = map(dutyPot, 0, 1023, 0, icrValue - 1);
  OCR1A = duty;

  unsigned long freq = 16000000UL / (icrValue + 1);

  lcd.setCursor(0, 0);
  lcd.print("freq: ");
  lcd.print(freq);
  lcd.print(" Hz   ");

  lcd.setCursor(0, 1);
  lcd.print("icrValue: ");
  lcd.print(icrValue);
  lcd.print("    ");

}
