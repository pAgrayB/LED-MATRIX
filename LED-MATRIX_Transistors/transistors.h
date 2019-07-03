#ifndef TRANSISTORS_H
#define TRANSISTORS_H

#include <SPI.h>

// Physical orientation of transistors with respect to the shift register
#define T0 0b00000001
#define T1 0b00000010
#define T2 0b00000100
#define T3 0b00001000
#define NONE 0x00

class transistors
{
  private:
    int shiftLatch;
    int dataPin;
    uint8_t currentTransistor;

  public:
    void init ()
    {
      shiftLatch = 8;
      dataPin = 11;
      currentTransistor = NONE;
      pinMode(shiftLatch, OUTPUT);
      pinMode(dataPin, OUTPUT);
      digitalWrite(shiftLatch, LOW);
      digitalWrite(dataPin, LOW);
    }

    void clear ()
    {
      currentTransistor = NONE;
    }

    void set (int transistor)
    {
      if (transistor < 0 || transistor > 3)
      {
        return;
      }

      switch (transistor)
      {
        case 0:
          currentTransistor = T0;
          break;
        case 1:
          currentTransistor = T1;
          break;
        case 2:
          currentTransistor = T2;
          break;
        case 3:
          currentTransistor = T3;
          break;
        default:
          currentTransistor = NONE;
          break;
      }
    }

    void update ()
    {
      SPI.transfer(currentTransistor);
      digitalWrite(shiftLatch, HIGH);
      digitalWrite(shiftLatch, LOW);
    }
};

// Pre-instantiated transistors variable
extern transistors Mosfets;

#endif
