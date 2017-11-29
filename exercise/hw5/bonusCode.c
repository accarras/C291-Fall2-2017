/****************************************************************
Tony Carrasco
11/28/17
C291
Assignment 5
bonus
bonusCode.c
****************************************************************/

#include <stdio.h>

void displayBits(unsigned int value);
unsigned int reverseBits(unsigned int value);

int main()
{
  unsigned int x; // variable to hold user input
  
  printf("%s", "Enter an unsigned integer: ");
  scanf("%u", &x);
  
  
  printf("\nThe Bits of %u= ", x);
  displayBits(x);
  
  x = reverseBits(x); // reverses bits of int
  
  printf("\nThe Bits of %u= ", x);
  displayBits(x);
  
}



//display bits of unsigned int value
void displayBits(unsigned int value){
  // this will convert unsigned int
  // to binary to display
  
  //define displayMask and left shift 31 bits
  unsigned int displayMask = 1 << 31; 
  
  //loop through bits
  for (unsigned int c = 1; c <= 32; ++c) {
    putchar(value & displayMask ? '1' : '0');
    value <<= 1; //shift value left by 1
  }
  putchar('\n');
} // end of displayBits prototype


// bits of unsigned int value in reverse order
unsigned int reverseBits(unsigned int value)
{
  unsigned mask= 1;
  unsigned temp= 0;
  int i;
  for(i = 0; i <= 31; i++)
  {
    temp <<= 1; //shift temp left by 1
    temp |= (value & mask); // inclusive OR operator
    value >>= 1; //shift value right by 1
  }
  return temp;
}
