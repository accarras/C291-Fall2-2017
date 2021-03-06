/*
Author:	Tony Carrasco
Class: C291 Fall 2017
File name: assignment6.c
Last updated: December 10, 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

int main()
{
  int numbers[7];

  // all possible letters for each number
  char allLetters[8][4] = {
    { 'A', 'B', 'C'},
    { 'D', 'E', 'F'},
    { 'G', 'H', 'I' },
    { 'J', 'K', 'L' },
    { 'M', 'N', 'O' },
    { 'P', 'Q', 'R', 'S'},
    { 'T', 'U', 'V' },
    { 'W', 'X', 'Y', 'Z' }
  };

  char letters[7][4];  

  //get the number from the user. This will correspond with indexes in letters array
  printf("Please enter 7 digit number (do not use number 0 and 1): \n");
  char number[7];
  scanf("%s", &number);

  int index;
  for (int i = 0; i < 7; i++){
    index = (number[i]) - 50; //our dial starts from number 2 
    // had a little trouble converting to int, but totally fixed it
    for(int jj=0;jj<4;jj++){
      letters[i][jj] = allLetters[index][jj];
    }
  }

  char filename[256];
  char word[7];

  FILE *fp;
  printf("enter name of file that you would like to save to: ");
  scanf("%s", filename); // gets file to save to from user
  fp = fopen(filename,"w");

  // loop for each character of the phone number
  // fortunately, there are only for posibilities and
  // 7 number possibilities, so O(n) isn't too bad
  for (int i1 = 0; i1 < 4; i1++)
    {
      for (int i2 = 0; i2 < 4; i2++)
        {
          for (int i3 = 0; i3 < 4; i3++)
            {
              for (int i4 = 0; i4 < 4; i4++)
                {
                  for (int i5 = 0; i5 < 4; i5++)
                    {
                      for (int i6 = 0; i6 < 4; i6++)
                        {
                          for (int i7 = 0; i7 < 4; i7++)
                            {
                              word[0] = letters[0][i1];
                              word[1] = letters[1][i2];
                              word[2] = letters[2][i3];
                              word[3] = letters[3][i4];
                              word[4] = letters[4][i5];
                              word[5] = letters[5][i6];
                              word[6] = letters[6][i7];
				     
			      if (strlen(word)==7){
				fprintf (fp,"%s \n", word);// stores word in file
			     }			      
			      
			      			
				
			      
			    }
			}
		    }
		}
	    }
	}
    }
  fclose(fp);// closes file
  return 0;
}
