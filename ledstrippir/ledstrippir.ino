int LED = 3;
int PIR = 2;
int LDR = A7;

void setup() {
  // set strip output
  pinMode(LED, OUTPUT);

  // set pir as input
  pinMode(PIR, INPUT);

  // set builtin led
  pinMode(LED_BUILTIN, OUTPUT);
  // turn off built in led
  digitalWrite(LED_BUILTIN, LOW);

  // fade strip to max from 0
  for(int i=0; i<256; i++) {
    analogWrite(LED, i);
      delay(15);
  }

  // fade strip to 0 from max
  for(int i=255; i>0; i--) {
    analogWrite(LED, i);
      delay(15);
  }

  // turn builtin led on
  digitalWrite(LED_BUILTIN, HIGH);
  // turn strip off
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
    // turn builtin led on when pir has detected
    digitalWrite(LED_BUILTIN, HIGH);
    // fade strip to max
    for(int i=0; i<256; i++) {
      analogWrite(LED, i);
      delay(15);
    }

    alllit:
    // wait for sometime
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);

    for(int i=255; i>10; i--) {
      // dim strip to half
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
    delay(5000);

    for(int i=10; i>=0; i--) {
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
