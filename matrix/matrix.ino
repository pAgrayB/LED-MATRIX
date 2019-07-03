#include <SPI.h>

#define transistor0_ON 0b00000001 //row 0
#define transistor1_ON 0b00000010 //row 1
#define transistor2_ON 0b00000100 //row 2
#define transistor3_ON 0b00001000 //row 3

int shiftLatch = 8;
int driverLatch = 9;
int dataPin = 11;
// ClockPin is pin 13 by default on Uno in Arduino SPI Library

void setup() {
  pinMode(shiftLatch, OUTPUT);
  pinMode(driverLatch, OUTPUT);
  pinMode(dataPin, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
}

void loop() {

}
