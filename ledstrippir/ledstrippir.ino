int LED = 6;
int PIR = 2;

void setup() {
  pinMode(LED, OUTPUT);
//  pinMode(PIR, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);

  for(int i=0; i<256; i++) {
    analogWrite(LED, i);
      delay(15);
  }

  for(int i=255; i>0; i--) {
    analogWrite(LED, i);
      delay(15);
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second

  start:
  
  if(digitalRead(PIR) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    for(int i=0; i<256; i++) {
      analogWrite(LED, i);
      delay(15);
    }

    alllit:
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);

    for(int i=255; i>100; i--) {
      digitalWrite(LED_BUILTIN, HIGH);
      analogWrite(LED, i);
      if(digitalRead(PIR) == HIGH) {
        while(i<256) {
          analogWrite(LED, i);
          delay(15);
          i++;          
        }
        goto alllit;
      }
      delay(30);
    }

    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

    for(int i=100; i>=0; i--) {
      analogWrite(LED, i);
      if(digitalRead(PIR) == HIGH) {
        while(i<256) {
          analogWrite(LED, i);
          delay(15);
          i++;          
        }
        goto alllit;
      }
      delay(15);      
    }
  }
  analogWrite(LED, LOW);
}
