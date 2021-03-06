/* game.c --- 
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
#include "highscore.h"
#include "game.h"
#include "well.h"
#include "tetris.h"
#include "tetromino.h"
#include "key.h"

void init_game(void) {
  int x,y;
}

highscore_t *game(highscore_t *highscores) {
  static int state = INIT;
  tetromino_t *next = NULL;
  tetromino_t *current = NULL;
  tetromino_t *obstacle = NULL;
  well_t *w;
  int x,y;
  int c;
  int arrow;
  struct timespec tim = {0,1000000};
  struct timespec tim_ret;
  int move_counter = 0;
  int move_timeout = 500;
  int status;
  int counter = 0;
  int maximumWellWidth = WELL_WIDTH * 2;
  int currentWellWidth = WELL_WIDTH;
  int lines_cleared = 0;
  int score = 0;
  char str[80];  
  time_t start = time(0);  
  int seconds_since_start = 0;
  char *filename = "highscore.txt";//[256];
  //  highscore_t *list;
  char *initials = "tcc";

  while(1) {
    switch(state) {
    case INIT:               // Initialize the game, only run one time 
      initscr();
      nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
      noecho();              // Do not echo input characters 
      getmaxyx(stdscr,y,x);  // Get the screen dimensions 
      w = init_well(((x/2)-(WELL_WIDTH/2)),3,WELL_WIDTH,WELL_HEIGHT);
      draw_well(w);
      srand(time(NULL));     // Seed the random number generator with the time. Used in create tet. 
      display_score(score, w->upper_left_x-15,w->upper_left_y);  
      mvprintw(6, 7, "  *** NEXT ");
      //seconds_since_start = difftime( time(0), start);
      //display_time(seconds_since_start, w->upper_left_x-25, w->upper_left_y);
      state = ADD_PIECE;
      break;

    case ADD_PIECE:          // Add a new piece to the game
      lines_cleared += prune_well(w);
      undisplay_score(score, w->upper_left_x-15,w->upper_left_y);
      score = compute_score(score, lines_cleared);
      display_score(score, w->upper_left_x-15,w->upper_left_y);

      undisplay_time(seconds_since_start, w->upper_left_x-25, w->upper_left_y);
      seconds_since_start = difftime(time(0), start);
      display_time(seconds_since_start, w->upper_left_x-25, w->upper_left_y);

   
      if (seconds_since_start >= 300){
	state = GAME_OVER;
	break;
	}
      
      obstacle = create_tetromino((w->upper_left_x+(w->width/2)), w->upper_left_y);
      display_obstacle(obstacle);

      if (next) {
	current = next;
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
        if (check_collision(next) == COLLIDE){
          state = GAME_OVER;
          break;
        }
      }
      else {
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      display_tetromino(current);
      //      undisplay_next_tetromino(next);
      display_next_tetromino(next);
      
      state = MOVE_PIECE;
      break;
    
    case MOVE_PIECE:     // Move the current piece 
      undisplay_time(seconds_since_start, w->upper_left_x-25, w->upper_left_y);
      seconds_since_start = difftime( time(0), start);
      display_time(seconds_since_start, w->upper_left_x-25, w->upper_left_y);


      if (seconds_since_start >= 300){
	state = GAME_OVER;
	break;
      }

      undisplay_next_tetromino(next);
      display_next_tetromino(next);
      
	if ((arrow = read_escape(&c)) != NOCHAR) {
	switch (arrow) {
	case UP:
	  undisplay_tetromino(current);
	  rotate_ccw(current);
	  display_tetromino(current);
	  break;

	case DOWN:
	  undisplay_tetromino(current);
	  rotate_cw(current);
	  display_tetromino(current);
	  break;

	case LEFT:
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x-1,current->upper_left_y);
	  display_tetromino(current);
	  break;

	case RIGHT:
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x+1,current->upper_left_y);
	  display_tetromino(current);
	  break;

	case PLUS:
          currentWellWidth = w->width + (w->width * 0.1);
          if(!(currentWellWidth > maximumWellWidth)) {
            undisplay_score(score, w->upper_left_x-15,w->upper_left_y);
            undraw_well(w);
	    w->width = currentWellWidth;
	    w = changeWellSize(((x/2)-(w->width/2)),1,w->width,WELL_HEIGHT,w);	
            display_score(score, w->upper_left_x-15,w->upper_left_y);   
	    draw_well(w);
	  }
          break;

        case MINUS:
          if(w->width > 10) {  
            undisplay_score(score, w->upper_left_x-15,w->upper_left_y);
	    undraw_well(w);
	    w->width -= (w->width * 0.1);
	    w = changeWellSize(((x/2)-(w->width/2)),1,w->width,WELL_HEIGHT,w);	
            display_score(score, w->upper_left_x-15,w->upper_left_y); 
	    draw_well(w);
          } 
	  break;
	
	case PAUSE:
	  move_timeout = 10000;
          
	  //move_counter = 0;

	  getch();
	  move_timeout = BASE_FALL_RATE;
	  state = ADD_PIECE;
	  break;


	case REGCHAR: 
	  mvprintw(10,10,"REGCHAR 0x%02x",c);
          if (c == ' ') {
	    move_timeout = DROP_RATE;
 	  }
	  if (c == 'q') {
	    state = GAME_OVER;
 	  }
	}
      } 

      if (move_counter++ >= move_timeout) {
	counter++;
	undisplay_tetromino(current);
	status = move_tet(current,current->upper_left_x,current->upper_left_y+1);
	display_tetromino(current);
	if (status == MOVE_FAILED) {
	  lines_cleared+=prune_well(w);
	  undisplay_score(score, w->upper_left_x-15,w->upper_left_y);
	  score = compute_score(score, lines_cleared);
	  display_score(score, w->upper_left_x-15,w->upper_left_y);
          state = ADD_PIECE;
	  move_timeout = rand()%BASE_FALL_RATE;
	}
	move_counter = 0;
      }
      break;
    
    case GAME_OVER:
      nodelay(stdscr,FALSE);
      clear();
      getmaxyx(stdscr,y,x);
      mvprintw(1,x/2-5, " GAME_OVER ");
      mvprintw(2,x/2-5, "#############");
      mvprintw(16,x/2-5,"Hit q to exit");
      display_score(score, x/2-5,4);

      //      printf("Enter Initials in AAA format: ");
      //scanf("%s", &initials);
      
      //      filename = "highscore.txt";
      // printf("Enter name of high score file: ");
      //scanf("%s", &ifilename);
      //load_scores(filename);
      //    free_score_list (list);
      //insert_score(this, initials, score);
      //  store_scores(filename, list);
      //load_scores(filename);
      //print_score_list (list,  x, y, 10);
      
      getch(); // Wait for a key to be pressed. 
      state = EXIT;
      break;
    case EXIT:
      return(highscores);  // Return the highscore structure back to main to be stored on disk. 
      break;
    }
    refresh();
    // printf("time: %d", &tim);
    nanosleep(&tim,&tim_ret);
  }
}

/* game.c ends here */
