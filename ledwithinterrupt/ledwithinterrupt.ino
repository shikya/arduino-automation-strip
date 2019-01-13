#include "LowPower.h"

#define LED 3
#define PIR 2
#define LDR A7
#define LDRTreshhold 450

#define MAX 255
#define DIM 10
#define OFF 0

void setup() {
  //Serial.begin(9600);
  pinMode(LED, OUTPUT); // set strip output
  pinMode(PIR, INPUT); // set pir as input
  //pinMode(LED_BUILTIN, OUTPUT); // set builtin led
  //digitalWrite(LED_BUILTIN, LOW); // turn off built in led
  //Serial.println("");
  //Serial.println("isr");
  setStrip(OFF);

  ledFlash();
}

void loop() {
  int i=OFF;
  Serial.println("Started");
  setStrip(OFF);
  attachInterrupt(digitalPinToInterrupt(PIR), isr, CHANGE);
  Serial.println("sleeping");
  sleep:
  sleep();
  Serial.print("Lumen ");
  Serial.println(analogRead(LDR));
  if(isLit())
    goto sleep;
  Serial.println("\n\nwaking up");
  detachInterrupt(digitalPinToInterrupt(PIR));
  
  startover:
  Serial.println("power on");
  for(; i<MAX; i++) {
    setStrip(i);
    delay(5);
  }
  
  alllit:
  Serial.println("30 sec wait");
  delay(30000);
  Serial.println("Diming");
  for(; i>DIM; i--) {
    setStrip(i);
    if(digitalRead(PIR) == HIGH) {
      goto startover;
    }
    delay(15);
  }

  Serial.println("Diming Complete");
  unsigned long start = millis();
  unsigned long target = start + 20000;
  Serial.print("Start is : ");
  Serial.println(start);
  Serial.print("Target is : ");
  Serial.println(target);
  while(target > millis()) {
    if(digitalRead(PIR) == HIGH) {
      goto startover;
    }    
  }
  Serial.println(millis());
  
  Serial.println("Power Off");
  for(; i>OFF; i--) {
    setStrip(i);
    if(digitalRead(PIR) == HIGH) {
      goto startover;
    }    
    delay(15);
  }
}

void sleep(){
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void ledFlash() {
  setStrip(255);
  delay(20);
  setStrip(0);
  delay(100);
  setStrip(255);
  delay(20);
  setStrip(0);
}

void isr() {
}

void setStrip(int i) {
  analogWrite(LED, i);
}

bool isLit() {
  return(analogRead(LDR) > LDRTreshhold);
}

