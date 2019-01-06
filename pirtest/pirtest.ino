int LED = 3;
int PIR = 2;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, digitalRead(PIR));
}
