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
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            display[row][col] = 0;
        }
    }
}

/*
    Stores pattern specified by user to buffer with entries
    ranging from 0-4095
*/
void LEDmatrix::set( uint16_t pattern [8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
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
        if (row == 8)
        {
         row = 0;
        }

        /* Fixes issue of next row of LEDs mimiking pattern of row before.
        */
        Tlc.clear();
        Tlc.update();

        delay(1); //time for Tlc to get settled for next row pattern

        Mosfets.set(row);

        for (int col = 0; col < 8; col++)
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
void Transistors::init ()
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
void Transistors::clear ()
    {
      currentTransistor = NONE;
    }

/*  Allows specification of row in buffer. */
void Transistors::set (int transistor)
    {
      if (transistor < 0 || transistor > 8)
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
        case 4:
            currentTransistor = T4;
            break;
        case 5:
            currentTransistor = T5;
            break;
        case 6:
            currentTransistor = T6;
            break;
        case 7:
            currentTransistor = T7;
            break;
        default:
          currentTransistor = NONE;
          break;
      }
    }

/*  Sends items from buffer to Arduino Uno via SPI. */
void Transistors::update ()
    {
      SPI.transfer(currentTransistor);
      digitalWrite(shiftLatch, HIGH);
      digitalWrite(shiftLatch, LOW);
    }


/*  Pre-instantiated matrix object */
LEDmatrix matrix;
