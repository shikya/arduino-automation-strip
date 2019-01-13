#include "LowPower.h"

#define LED 3
#define PIR 2
#define LDR A7
#define LDRTreshhold 200
#define dimmedValue 125

#define off 0
#define lit 1
#define dim 2

int ledState = off;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT); // set strip output
  pinMode(PIR, INPUT); // set pir as input
  pinMode(LED_BUILTIN, OUTPUT); // set builtin led
  digitalWrite(LED_BUILTIN, LOW); // turn off built in led
  Serial.println("");
  Serial.println("isr");
  setStrip(0);

  ledFlash();
}

void loop() {
  attachInterrupt(digitalPinToInterrupt(PIR), isr, CHANGE);
  sleep();
  detachInterrupt(digitalPinToInterrupt(PIR));
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
//  if(ledState==off)
    // setStrip(255);
    Serial.println("RISING");
    ledFlash();
  digitalWrite(LED_BUILTIN, HIGH);
}

void setStrip(char i) {
  Serial.println("Setting strip "+ i);
  analogWrite(LED, i);
  if(i>250)
    ledState = lit;
  if(i<250 && i>0)
    ledState = dim;
  if(i==0)
    ledState = off;
}

bool alreadylit() {
  return analogRead(LDR) < LDRTreshhold ? true : false ;
}

