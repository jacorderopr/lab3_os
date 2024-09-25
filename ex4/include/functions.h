#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <curses.h> /* ncurses.h incluye stdio.h */
#include <pthread.h>
#include <string.h>
#include <unistd.h>


typedef struct {
  int x;
  int y;
} BallPosition;

#define ENTER_NCURSES 10

void* UpdateBallPos(void*);
void* UpdateCounter(void*);


extern BallPosition ball_pos;

extern int counter_val;
extern int dx, dy;
extern int row, col;



#endif