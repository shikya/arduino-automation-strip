int ldr = A7;
int led = 6;
int value =0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(ldr);
  
  Serial.println(value);
  //Serial.print(" ");
 
  delay(100);
}
