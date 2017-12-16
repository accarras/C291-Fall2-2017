/* score.c --- 
 * 
 * Filename: score.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Tue Oct  4 15:22:20 2016
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2016 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
//#include <cstring>
//#include <cstdlib>

int intcmp(const void *aa, const void *bb);


int compute_score(int previous_score, int lines_cleared) {
  enum {NORMAL, TETRIS};
  int new_score;

  static int state = NORMAL;
  switch (lines_cleared) {
  case 0:
    new_score = 0;
    break;
  case 1:
    new_score = 100;
    break;
  case 2:
    new_score = 250;
    break;
  case 3:
    new_score = 500;
    break;
  case 4: 
    new_score = 800;
    state = TETRIS;
    break;
  }
  switch (state) {
  case NORMAL: 
    return (previous_score + new_score); 
    break;
  case TETRIS: 
    if (lines_cleared == 4) {
      return (previous_score + 1200);
    }
    else {
      state = NORMAL;
      return (previous_score + new_score); 
    }
    break;
  default:
    state = NORMAL;
    return (previous_score + new_score);
    break;
  }
}

void display_score(int score, int x, int y) {
  mvprintw(y,x,"*** SCORE ***",score);
  mvprintw(y+1,x,"%8d",score);
}

void undisplay_score(int score, int x, int y) {
  mvprintw(y,x,"             ",score);
  mvprintw(y+1,x,"        ",score);
}


void display_time(int time, int x, int y) {
  mvprintw(y,x,"*** TIME  ***",time);
  mvprintw(y+1,x,"%8d",time);
}


void undisplay_time(int time, int x, int y) {
  mvprintw(y,x,"             ",time);
  mvprintw(y+1,x,"        ",time);
}

void store_score1(int score){
  char filename = "highscore.txt";
  FILE *fp;
  // printf("enter name of file that you would like to save score to: ");
  // scanf("%s", filename); // gets file to save to from user
  fp = fopen(filename,"w");
  fprintf(fp,"%d/n", score);
}

/*void print_score1(int x, int y){
  char filename = "highscore.txt";
  FILE *fp;
  // printf("enter name of file that you would like to read score from: ");
  // scanf("%s", filename); // gets file to save to from user
  fp = fopen(filename,"r");
  //fprintf (fp,"%s \n", score);
  int numberArray[1024];
  int i = 0;
  for (i = 0; i < 1024; i++){
    fscanf(filename, "%d,", &numberArray[i]);
  }

  qsort(numberArray, 1024, sizeof(int), intcmp);
  int k = 0;
  for (k = 0; k<10; k++){
    mvprintw( y+k,x,"Number is: %d\n\n", numberArray[k]);
  }
}

int intcmp(const void *aa, const void *bb)
{
   const int *a = aa, *b = bb;
   return (*a < *b) ? -1 : (*a > *b);
 }
*/


/* score.c ends here */
