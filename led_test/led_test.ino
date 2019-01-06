#define fadePin 3

void setup(){
  pinMode(fadePin, OUTPUT);
  analogWrite(fadePin, 0);
}

void loop(){
//analogWrite(fadePin, 150);
  for(int i = 0; i<360; i++){
    //convert 0-360 angle to radian (needed for sin function)
    float rad = DEG_TO_RAD * i; //calculate sin of angle as number between 0 and 255
    int sinOut = constrain((sin(rad) * 128) + 128, 0, 255);
    analogWrite(fadePin, sinOut);
    delay(3);
  }
}


