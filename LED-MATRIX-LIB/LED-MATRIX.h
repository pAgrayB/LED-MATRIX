#ifndef LED-MATRIX
#define LED-MATRIX

#include "Tlc5940.h"
#include <SPI.h>

// Physical orientation of transistors with respect to the shift register
// while shifting out MSB first.
#define T0 0b00000001
#define T1 0b00000010
#define T2 0b00000100
#define T3 0b00001000
#define NONE 0x00

/*
    Main API to interact with LED matrix.
*/

class LEDmatrix
{
  private:
      uint16_t display [4][4];

  public:
    void init ();
    void clear ();
    void set ( uint16_t [4][4]);
    void update ( uint16_t, unsigned long);
};

/*
    Helper class allowing ease of interacting with rows of LED-matrix.
    API is same as the Tlc5940 class in Tlc5940.h
*/
class transistors
{
  private:
    int shiftLatch;
    int dataPin;
    uint8_t currentTransistor;

  public:
    void init ();
    void clear ();
    void set (int);
    void update ();
};

// Pre-instantiated transistors variable
extern transistors Mosfets;
extern LEDmatrix matrix;

#endif
