
#include <Wire.h>


#define MAX_NODES   10 // 0, 1, 2,...
#define MIN_ID      ((255-MAX_NODES) + 1) // 246....255

byte inputValue = 0;
byte value = 0;
byte nodeID = 0;

#define LED_BUILTIN 13

//////////////////////////////// SETUP
void setup() {
  Serial.begin(19200);   //

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Wire.begin();            // join i2c bus (address optional for master)
}

//////////////////////////////// LOOP
void loop() {
}


//////////////////////////////// FONCTIONS
void serialEvent() {

  while (Serial.available()) {

    inputValue = Serial.read();

    if (inputValue >= 0 && inputValue < MIN_ID) {
      value = inputValue;
    }
    else {
      nodeID = inputValue - MIN_ID + 8;
      Wire.beginTransmission(nodeID); // transmit to device #4
      Wire.write(value + 10);         // sends one byte
      Wire.endTransmission();         // stop transmitting
      startBlink(LED_BUILTIN, 1);
    }
  }
}


void startBlink(int thePin, int cycles) {
  for (int i = 0; i < cycles; i++) {
    digitalWrite(thePin, HIGH);
    delay(50);
    digitalWrite(thePin, LOW);
    delay(50);
  }
}
