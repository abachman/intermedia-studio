// huzzah button

#define LEDPIN    0

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  digitalWrite(LEDPIN, LOW);
  delay(1000);
  digitalWrite(LEDPIN, HIGH);
  delay(1000);
}
