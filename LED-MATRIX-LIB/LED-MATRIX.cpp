#include "LED-MATRIX.h"

/*  Initiates objects needed to control LED rows and columns */
void LEDmatrix::init ()
{
    Mosfets.init();
    Tlc.init();
}

/*  Sets each LED to 0 brightness */
void LEDmatrix::clear()
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            display[row][col] = 0;
        }
    }
}

/*
    Stores pattern specified by user to buffer with entries
    ranging from 0-4095
*/
void LEDmatrix::set( uint16_t pattern [4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if ( pattern[row][col] < 4096 && pattern[row][col] >= 0)
            {
                display[row][col] = pattern[row][col];
            } else {
                display[row][col] = 0;
            }
        }
    }
}

/*
    Uploads pattern in buffer to display for pattern_dur milliseconds.
    Pattern is multiplexed with each row on row_on_time milliseconds.
*/
void LEDmatrix::update (unsigned long pattern_dur, unsigned long row_on_time)
{
    unsigned long enterTime = millis();
    for (int row = 0; millis() - enterTime < pattern_dur; row++)
    {
        if (row == 4)
        {
         row = 0;
        }

        /* Fixes issue of next row of LEDs mimiking pattern of row before.
        */
        Tlc.clear();
        Tlc.update();

        delay(1); //time for Tlc to get settled for next row pattern

        Mosfets.set(row);

        for (int col = 0; col < 4; col++)
        {
                Tlc.set(col, display[row][col]);
        }
        Mosfets.update();
        Tlc.update();
        delay(row_on_time);
    }
}



/*
    Specifies outputs to interact with rows of LED-matrix.
    Clears buffer.
    Ensures all GPIO pins needed start out at LOW.
    Begins SPI transaction at 4MHz with MSB first.
*/
void transistors::init ()
    {
      shiftLatch = 8;
      dataPin = 11;
      currentTransistor = NONE;
      pinMode(shiftLatch, OUTPUT);
      pinMode(dataPin, OUTPUT);
      digitalWrite(shiftLatch, LOW);
      digitalWrite(dataPin, LOW);
      SPI.begin();
      SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    }

/*  Clears buffer */
void transistors::clear ()
    {
      currentTransistor = NONE;
    }

/*  Allows specification of row in buffer. */
void transistors::set (int transistor)
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

/*  Sends items from buffer to Arduino Uno via SPI. */
void transistors::update ()
    {
      SPI.transfer(currentTransistor);
      digitalWrite(shiftLatch, HIGH);
      digitalWrite(shiftLatch, LOW);
    }


/*  Pre-instantiated matrix object */
LEDmatrix matrix;
