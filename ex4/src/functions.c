#include "functions.h"


BallPosition ball_pos;


int counter_val = 0;
int dx, dy;
int row, col;


void* UpdateBallPos(void*){
  dx = dy = 1;

  while(1){
    clear();
    getmaxyx(stdscr, row, col); /* Obtiene el numbero de filas y columnas */
     mvprintw(0, 0, "%d", counter_val); // displays the counter, DOES NOT update it!
     mvprintw(ball_pos.y, ball_pos.x, "o");
    refresh();

    ball_pos.x += dx;
    ball_pos.y += dy;
    if (ball_pos.x >= col - 1) {
      dx = -1;
    }
    if (ball_pos.y >= row - 1) {
      dy = -1;
    }
    if (ball_pos.x <= 1) {
      dx = 1;
    }
    if (ball_pos.y <= 1) {
      dy = 1;
    }

    usleep(100000); /* Duerme por 100ms */
}
}


void* UpdateCounter(void*){

  while (1) {
    
   counter_val++;
    usleep(1000000); /* Duerme por 1sg*/

  }

}