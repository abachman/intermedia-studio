// huzzah button

#define LEDPIN    0

int count = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  count += 1;

  if (count % 100 == 0) {
    Serial.print("count is at ");
    Serial.println(count);

    digitalWrite(LEDPIN, LOW);
    delay(1000);
  } else {
    digitalWrite(LEDPIN, HIGH);
    delay(10);
  }
}
