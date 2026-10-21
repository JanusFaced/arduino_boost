const int ledBuiltIn = LED_BUILTIN;
const int speakerPin = 9;
const int potFreqPin = A0;

int standart_pause = 1000;
int blinkDuration = 100;
int speakerDuration = 777;

void setup() {

  pinMode(ledBuiltIn, OUTPUT);
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

void main_program() {

  int freqPot = analogRead(potFreqPin);
  int icrValue = map(freqPot, 0, 1023, 255, 65535);
  ICR1 = icrValue;

  int dutyPot = 500;
  int duty = map(dutyPot, 0, 1023, 0, icrValue - 1);
  OCR1A = duty;

}
