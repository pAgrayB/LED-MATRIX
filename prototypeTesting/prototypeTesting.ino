#include "LED-MATRIX.h"

uint16_t pattern [4][4];

void setup() {
  matrix.init();
  matrix.clear();

  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++)
    {
      pattern[row][col] = 4095;
    }
  }

}

void loop() {
  matrix.set(pattern);
  matrix.update(1000, 3);

}
