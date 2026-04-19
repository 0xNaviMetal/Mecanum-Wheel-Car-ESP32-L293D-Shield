#include "soc/gpio_struct.h"
#include <BluetoothSerial.h>
BluetoothSerial BT;

constexpr uint8_t SerialPin = 21;
constexpr uint8_t ClockPin  = 19;
constexpr uint8_t LatchPin  = 23;
constexpr uint8_t OutputEnablePin = 18;

constexpr uint8_t ALL_STOP = 0b00000000;
constexpr uint8_t M1_CW    = 0b00001000;
constexpr uint8_t M1_CCW   = 0b00000100;
constexpr uint8_t M2_CW    = 0b00010000;
constexpr uint8_t M2_CCW   = 0b00000010;
constexpr uint8_t M3_CW    = 0b10000000;
constexpr uint8_t M3_CCW   = 0b00100000;
constexpr uint8_t M4_CW    = 0b00000001;
constexpr uint8_t M4_CCW   = 0b01000000;

#define SET_HIGH(pin) GPIO.out_w1ts = (1 << pin)
#define SET_LOW(pin)  GPIO.out_w1tc = (1 << pin)

void pulseFast(uint8_t pin) {
  SET_HIGH(pin);
  delayMicroseconds(5);
  SET_LOW(pin);
  delayMicroseconds(5);
}

void writeMotor(uint8_t control) {
  for (int i = 0; i < 8; ++i) {
    if (control & 0x80) SET_HIGH(SerialPin);
    else                SET_LOW(SerialPin);
    pulseFast(ClockPin);
    control <<= 1;
  }
  pulseFast(LatchPin);
}

void setup() {
  Serial.begin(115200);
  BT.begin("BT.ESP32");  

  pinMode(SerialPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(LatchPin, OUTPUT);
  pinMode(OutputEnablePin, OUTPUT);

  digitalWrite(OutputEnablePin, LOW);  
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    Serial.print("Received command: ");
    Serial.println(cmd);  
    
    switch (cmd) {
      case 'F': writeMotor(M1_CW | M2_CW | M3_CW | M4_CW); break;
      case 'B': writeMotor(M1_CCW | M2_CCW | M3_CCW | M4_CCW); break;
      case 'L': writeMotor(M1_CW | M4_CCW | M2_CCW | M3_CW); break;
      case 'R': writeMotor(M1_CCW | M4_CW | M2_CW | M3_CCW); break;
      case 'W': writeMotor(M1_CW | M3_CW); break;
      case 'X': writeMotor(M4_CW | M2_CW); break;
      case 'Y': writeMotor(M2_CCW | M4_CCW); break;
      case 'Z': writeMotor(M1_CCW | M3_CCW); break;
      case 'M': writeMotor(M1_CW | M4_CW | M2_CCW | M3_CCW); break;
      case 'K': writeMotor(M1_CCW | M4_CCW | M2_CW | M3_CW); break;
      case 'S': writeMotor(ALL_STOP); break;
    }
  }
}
