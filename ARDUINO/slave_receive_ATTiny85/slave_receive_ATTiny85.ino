#include <TinyWireS.h>

// Pin 0 - I2C data/SDA (DIGISPARK)
// Pin 2 - I2C clock/SCL (DIGISPARK)

const int LED_PIN = 1;
const int TRANSISTOR_PIN = 4;

#define I2C_SLAVE_ADDRESS   13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRANSISTOR_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(TRANSISTOR_PIN, LOW);

  TinyWireS.begin(I2C_SLAVE_ADDRESS);               // join i2c bus with address #4

  startBlink(LED_PIN, 4);
}

void loop() {
  if (TinyWireS.available()) {
    byte val = TinyWireS.receive();
    if (val > 0) {
      startBlink(LED_PIN, 1);
    }
    analogWrite(TRANSISTOR_PIN, val);
    // TODO add delay millis();
    //analogWrite(TRANSISTOR_PIN, 0);
  }
}

void startBlink(int thePin, int cycles) {
  for (int i = 0; i < cycles; i++) {
    digitalWrite(thePin, HIGH);
    tws_delay(60);
    digitalWrite(thePin, LOW);
    tws_delay(60);
  }
}
