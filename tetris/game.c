/* game.c
 * 
 * Filename: game.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Tue Sep  6 11:08:59 2016
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
#include <unistd.h> 
#include <ncurses.h>
#include <time.h>
#include "game.h"
#include "well.h"
#include "tetris.h"
#include "tetromino.h"
#include "key.h"

void init_game(void) {
  int x,y;
}

int game(void) {
  static int state = INIT;
  tetromino_t *next = NULL;
  tetromino_t *current = NULL;
  well_t *w;
  int x,y;
  int c;
  int arrow;
  struct timespec tim = {0,1000000};  // Each execution of while(1) is approximately 1mS
  struct timespec tim_ret;
  int move_counter = 0;
  int move_timeout = BASE_FALL_RATE;            

  while(1) {
    switch(state) {
    case INIT:               // Initialize the game, only run one time 
      initscr();
      nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
      noecho();              // Do not echo input characters 
      getmaxyx(stdscr,y,x);  // Get the screen dimensions 
      w = init_well(((x/2)-(WELL_WIDTH/2)),1,WELL_WIDTH,WELL_HEIGHT);
      draw_well(w);
      srand(time(NULL));     // Seed the random number generator with the time. Used in create tet. 
      state = ADD_PIECE;
      break;
    case ADD_PIECE:          // Add a new piece to the game
      if (next) {
	current = next;
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      else {
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      display_tetromino(current);
      state = MOVE_PIECE;
      break;
    case MOVE_PIECE:         // Move the current piece 
      if ((arrow = read_escape(&c)) != NOCHAR) {
	switch (arrow) {
	case UP:
          undisplay_tetromino(current);
          rotate_cw(current);
          display_tetromino(current);
	  mvprintw(10,10,"UP            ");
	  break;
	case DOWN:
	  undisplay_tetromino(current);
          rotate_ccw(current);
          display_tetromino(current);
          mvprintw(10,10,"DOWN          ");
	  break;
	case LEFT:
          undisplay_tetromino(current);
	  move_tet(current, current->upper_left_x-1, current->upper_left_y);
          display_tetromino(current);
          mvprintw(10,10,"LEFT          ");
	  break;
	case RIGHT:
          undisplay_tetromino(current);
          move_tet(current, current->upper_left_x+1, current->upper_left_y);
          display_tetromino(current);
          mvprintw(10, 10,"RIGHT        ");
	case REGCHAR:
          if (c == 0x2b){
	    undraw_well(w);
	    changeWellSize(w->upper_left_x, w->upper_left_y, w->width+(w->width/10), w->height, w);
	    draw_well(w);
	    mvprintw(10, 10, "WELL WIDTH+ ");}
          else if (c == 0x5f){
	    undraw_well(w);
            changeWellSize(w->upper_left_x, w->upper_left_y, w->width-(w->width/10), w->height, w);
            draw_well(w);
            mvprintw(10, 10, "WELL WIDTH- "); } 
	  else if (c == 0x20){
            move_timeout = DROP_RATE;
            }
          else {
            move_timeout = BASE_FALL_RATE;
            mvprintw(10,10,"REGCHAR 0x%02x",c);
	    if (c == 'q'){
	      state = EXIT;
 	    }
          }
	}
      } 
      if (move_counter++ >= move_timeout) {
	undisplay_tetromino(current);
	move_tet(current, current->upper_left_x, current->upper_left_y+1);
	display_tetromino(current);	
       move_counter = 0;
      }
      break;
    case EXIT:
      endwin();
      return(0);
      break;
    }
    refresh();
    nanosleep(&tim,&tim_ret);
  }
}

/* game.c ends here */
