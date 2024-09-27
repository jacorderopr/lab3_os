#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <curses.h> /* ncurses.h incluye stdio.h */
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


typedef struct {
  int x;
  int y;
  int dx;
  int dy;
} BallPosition;

#define ENTER_NCURSES 10
#define SPACEBAR_NCURSES 32

void UpdateBallPos(int ball_index);
void ChangeBallDirection(int ball_index);

void* UpdateAllBallPos(void*);
void* UpdateCounter(void*);
void* GetCommands(void*);

extern BallPosition ball_pos_array[10];
extern int ball_pos_array_index;


extern int break_loop;
extern int counter_val;
extern int row, col;



#endif