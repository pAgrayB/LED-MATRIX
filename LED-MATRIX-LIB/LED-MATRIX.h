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
#define T4 0b00010000
#define T5 0b00100000
#define T6 0b01000000
#define T7 0b10000000
#define NONE 0x00

/*
    Helper class allowing ease of interacting with rows of LED-matrix.
    API is same as the Tlc5940 class in Tlc5940.h
*/
class Transistors
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

/*  Main API to interact with LED matrix. */
class LEDmatrix
{
  private:
      Transistors Mosfets;
      uint16_t display [8][8];

  public:
    void init ();
    void clear ();
    void set ( uint16_t [8][8]);
    void update ( unsigned long, unsigned long);
};



/*  Pre-instantiated matrix object */
extern LEDmatrix matrix;

#endif
