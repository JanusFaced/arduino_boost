const int ledBuiltIn = LED_BUILTIN;
const int ledExternal = 9;
const int speaker = 8;

int standart_pause = 3000;
int blinkDuration = 100;
int speakerDuration = 777;

void setup() {

  pinMode(ledBuiltIn, OUTPUT);
  pinMode(ledExternal, OUTPUT);
  pinMode(speaker, OUTPUT);

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

  for (int i = 0; i < 3; i++) {

    digitalWrite(ledExternal, HIGH);
    delay(blinkDuration);

    digitalWrite(ledExternal, LOW);
    delay(blinkDuration);

  }

  tone(speaker, 400);
  delay(speakerDuration);

  tone(speaker, 800);
  delay(speakerDuration);

  tone(speaker, 1600);
  delay(speakerDuration);
  
  noTone(speaker);

}
