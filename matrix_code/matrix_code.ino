/*
 * Looks as though squares are enlarging and shrinking from middle of matrix.
 * 
 */


#include "LED-MATRIX.h"

enum {image0, image1, image2, image3};

uint16_t pattern [8][8];
int i = image0;
int dir = 1;

void setup() 
{
  matrix.init();
  matrix.clear();

}

void loop() {

  for (int row = 0; row <= 7; row++)
  {
    for (int col = 0; col <= 7; col++)
    {
      pattern[row][col] = 0;
    }
  }

  matrix.clear();

  switch(i)
  {
    case image0:
    
      for (int col = 3; col <= (7-3); col++)
      {
        for (int row = 3; row <= (7-3); row++)
        {
          pattern[row][col] = 4095;
        }
      }
      break;
      
    case image1:
      for (int col = 2; col <= (7-2); col++)
      {
        for (int row = 2; row <= (7-2); row++)
        {
          pattern[row][col] = 4095;
        }
      }

      for (int col = 3; col <= (7-3); col++)
      {
        for (int row = 3; row <= (7-3); row++)
        {
          pattern[row][col] = 0;
        }
      }
      break;
      
    case image2:
    
      for (int col = 1; col <=(7-1); col++)
      {
        for (int row = 1; row <= (7-1); row++)
        {
          pattern[row][col] = 4095;
        }
      }

      for (int col = 2; col <= (7-2); col++)
      {
        for (int row = 2; row <= (7-2); row++)
        {
          pattern[row][col] = 0;
        }
      }

      for (int col = 3; col <= (7-3); col++)
      {
        for (int row = 3; row <= (7-3); row++)
        {
          pattern[row][col] = 0;
        }
      }
      
      break;
      
    case image3:
    
      for (int col = 0; col <= (7-0); col++)
      {
        for (int row = 0; row <= (7-0); row++)
        {
          pattern[row][col] = 4095;
        }
      }

      for (int col = 1; col <=(7-1); col++)
      {
        for (int row = 1; row <= (7-1); row++)
        {
          pattern[row][col] = 0;
        }
      }

      for (int col = 2; col <= (7-2); col++)
      {
        for (int row = 2; row <= (7-2); row++)
        {
          pattern[row][col] = 0;
        }
      }

      for (int col = 3; col <= (7-3); col++)
      {
        for (int row = 3; row <= (7-3); row++)
        {
          pattern[row][col] = 0;
        }
      }
      break;
      
    default:
    for (int row = 0; row <= 7; row++)
    {
      for (int col = 0; col <= 7; col++)
      {
        pattern[row][col] = 0;
      }
    }
      break;
      
  }
  
  matrix.set(pattern);
  matrix.update(80, 1);
  
  i+=dir;
  
  if (i == image3 || i == image0)
  {
    dir*=-1;
  }

}
