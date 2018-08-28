// huzzah button

#define LEDPIN    0
#define BUTTONPIN 4

#define LEDA  1
#define LEDB  3

int buttonState = 0;
int clicks = 0;
int cstep = 0;
bool counted = false;

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT);

  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);

  digitalWrite(LEDA, LOW);
  digitalWrite(LEDB, LOW);
}

void loop() {
  buttonState = digitalRead(BUTTONPIN);

  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(LEDPIN, LOW);
    if (!counted) {
      clicks++;
      cstep = (cstep + 1) % 3;
      Serial.print("COUNT ");
      Serial.println(clicks);
      counted = true;
    }

    switch (cstep) {
      case 0:
        digitalWrite(LEDA, HIGH);
        digitalWrite(LEDB, LOW);
        break;
      case 1:
        digitalWrite(LEDA, LOW);
        digitalWrite(LEDB, HIGH);
        break;
      case 2:
        digitalWrite(LEDA, HIGH);
        digitalWrite(LEDB, HIGH);
    }
  } else {
    // turn LED off:
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(LEDA, LOW);
    digitalWrite(LEDB, LOW);

    counted = false;
  }
}
