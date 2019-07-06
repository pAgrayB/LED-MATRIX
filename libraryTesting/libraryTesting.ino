/*
    Basic Pin setup (TLC5940 and SN74HC595N are only connected to ARDUINO)
    ------------                                  ---u----                                 --u--
    ARDUINO   13|-> SCLK (pin 25 & pin 11)    OUT1 |1     28| OUT channel 0              QB |1   16| -> VCC (+5V)
              12|                             OUT2 |2     27|-> GND (VPRG)               QC |2   15| QA
              11|-> SIN (pin 26 & pin 14)     OUT3 |3     26|-> SIN (pin 11)             QD |3   14| -> SER (pin 11)
              10|-> BLANK (pin 23)            OUT4 |4     25|-> SCLK (pin 13)            QE |4   13| -> GND (!OE)
               9|-> XLAT (pin 24)               .  |5     24|-> XLAT (pin 9)             QF |5   12| -> RCLK (LATCH) (pin 8)
               8|---> RCLK (shift-register)     .  |6     23|-> BLANK (pin 10)           QG |6   11| -> SRCLK (CLOCK) (pin 13)
               7|                               .  |7     22|-> GND                      QH |7   10| -> VCC (+5V) (!SRCLK)
               6|                               .  |8     21|-> VCC (+5V)            GND <- |1   16| -> QH'
               5|                               .  |9     20|-> 2K Resistor -> GND          -------- SN74HC595N
               4|                               .  |10    19|-> +5V (DCPRG)
               3|-> GSCLK (pin 18)              .  |11    18|-> GSCLK (pin 3)
               2|                               .  |12    17|-> SOUT
               1|                               .  |13    16|-> XERR
               0|                             OUT14|14    15| OUT channel 15
    ------------                                    -------- TLC5940

    -  Put the longer leg (anode) of the LEDs in the +5V and the shorter leg
         (cathode) in OUT(0-15).
    -  +5V from Arduino -> TLC pin 21 and 19     (VCC and DCPRG)
    -  GND from Arduino -> TLC pin 22 and 27     (GND and VPRG)
    -  digital 3        -> TLC pin 18            (GSCLK)
    -  digital 9        -> TLC pin 24            (XLAT)
    -  digital 10       -> TLC pin 23            (BLANK)
    -  digital 11       -> TLC pin 26            (SIN)
    -  digital 13       -> TLC pin 25            (SCLK)
    -  The 2K resistor between TLC pin 20 and GND will let ~20mA through each
       LED.  To be precise, it's I = 39.06 / R (in ohms).  This doesn't depend
       on the LED driving voltage.
    - (Optional): put a pull-up resistor (~10k) between +5V and BLANK so that
                  all the LEDs will turn off when the Arduino is reset.

    If you are daisy-chaining more than one TLC, connect the SOUT of the first
    TLC to the SIN of the next.  All the other pins should just be connected
    together:
        BLANK on Arduino -> BLANK of TLC1 -> BLANK of TLC2 -> ...
        XLAT on Arduino  -> XLAT of TLC1  -> XLAT of TLC2  -> ...
    The one exception is that each TLC needs it's own resistor between pin 20
    and GND.

    This library uses the PWM output ability of digital pins 3, 9, 10, and 11.
    Do not use analogWrite(...) on these pins.

    This sketch does the Knight Rider strobe across a line of LEDs.

    Alex Leone <acleone ~AT~ gmail.com>, 2009-02-03 */

#include "LED-MATRIX.h"

uint16_t pattern [4][4];

void setup()
{

  
  /* Call matrix.init() to setup the LED-matrix.
  */
  matrix.init();
  /* Matrix.clear() clears the buffer */
  matrix.clear();
}


/*
 * This loop turns on all LEDs
 */
void loop()
{
  
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++)
    {
      pattern[col][row] = 4095;
      
      /* matrix.set( uint16_t 2Darray [4][4] ) stores the 
      desired pattern in a buffer. */
      matrix.set(pattern);
      
      /* matrix.update( pattern_duration_ms, row_on_time_ms) uploads the pattern
      in the buffer to the Arduino.*/
      matrix.update(100, 3);

      pattern[col][row] = 0;
      
    }
  }
      

  
}
