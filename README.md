# LED-Matrix
This repository serves to document the design of an 8x8 matrix of LEDs controlled by an Arduino Nano.

![LED-MATRIX](https://github.com/pAgrayB/LED-MATRIX/blob/master/Photos/Front.JPG)

# Electrical Design

![power design](https://github.com/pAgrayB/LED-MATRIX/blob/master/Photos/power_schematic.png)

The design included soldering together an LED matrix by hand and creating a control system for the matrix without using an LED matrix driver. This was done for the sake of learning.

As shown in the schematic above, the LEDs are arranged in a matrix. All cathodes are soldered together in rows and all anodes are soldered together in columns. Each row is connected to the source of an N-Channel, logic level MOSFET. This allows each row to be controlled by an output of a shift register. The shift register, in turn, is controlled via SPI by the Arduino NANO. Each column is connected to an output pin of the TLC5940, a constant current LED driver. The TLC5940 is also controlled via SPI by the Arduino NANO.

A problem with this approach is that unwanted LEDs will turn on when turning three or more LEDs is different rows or columns. For example, if the LEDs in positions (0,0), (0,7) and (7,7) turn on, so will LED in position (7,0). This problem is solved by switching between rows very quickly and tricking the eye to view a single image. This is called multiplexing and is implemented in the Software Design of the LED matrix. 

A 12V, 1A, 1W wall adapter is used as a constant voltage source for the source of the MOSFETs.

# Software Design
The arduino SPI library and Alex Leone's Tlc5940 library are used together to allow interaction with the LED-matrix by an Arduino NANO. Specifically, the communication was designed so that an 8x8 2D array in C++ is all that is needed to manipulate the lights. For example:

    uint16_t pattern [8][8];      // must be of type uint16_t to push to buffer
    
    for (int row = 0; row < 7; row++) {
      for (int col = 0; col < 7; col++) {
        pattern[row][col] = 4095; // brightness between 0-4095
      }
    }
    
    matrix.init();                // initializes global matrix object from matrix library
    matrix.set(pattern);          // pushes pattern entries to buffer
    matrix.update(1000, 1);       // uploads patterns from buffer to matrix
     
Turns on all LEDs to max brightness, delays the code for 1000ms and sweeps through each row in 1ms. 

The library also comes with an example script called BasicUse that covers all matrix methods in detail.

*This library hides the complexity of communicating with the shift-register and LED driver individually and of manual multiplexing.*

# Acknowledgements
Special thanks to Wesley Jenkins for suggesting to have the LED-MATRIX controlled by manipulating a 2D array instead of using a function to turn on each LED individually. This allowed for easier design as it resembled the arduino library written for the TLC5940, which I was able used as a guide for designing the LED-MATRIX library. Wesley's github username is "MajinSupai".

Thank you also to Alex Leone, the writer of the TLC5940 library. 

# Future Improvements
* Lower voltage source for LEDs, 10V is left on output pins of TLC5940. Energy is wasted.
* Even easier software to create patterns, "nested for-loops" are unintuitive to create neat patterns
* A physical case to hold both PCBs in place and to expose circuitry for demonstrating operation of matrix
* Energy consumption analysis
* Software testing by new users
