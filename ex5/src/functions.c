#include "functions.h"

BallPosition ball_pos_array[10];
int ball_pos_array_index = 0;

int counter_val = 0;

int row, col;
int break_loop = 0;

void *UpdateAllBallPos(void *)
{
  
  while (!break_loop)
  {

    clear();

    mvprintw(0, 0, "%d", counter_val); // displays the counter, DOES NOT update it!

    for (int i = 0; i < ball_pos_array_index; i++)
    {
    getmaxyx(stdscr, row, col);        /* Obtiene el numbero de filas y columnas */
      // getmaxyx(stdscr, row, col); /* Obtiene el numbero de filas y columnas */
      UpdateBallPos(i);
    }
    refresh();
    usleep(100000); /* Duerme por 100ms */
  }
}

void *UpdateCounter(void *)
{

  while (!break_loop)
  {

    counter_val++;
    usleep(1000000); /* Duerme por 1sg*/
  }
}

void *GetCommands(void *)
{
  int key_stroke;

  while (!break_loop)
  {
    key_stroke = getch();
    refresh();
    switch (key_stroke)
    {
    case 'c':
      // change direction of balls
      for(int i = 0; i < ball_pos_array_index; i++){
        ChangeBallDirection(i);
      }
      break;
    case SPACEBAR_NCURSES:
      // add a new ball
      if (ball_pos_array_index < 10)
      {

        ball_pos_array[ball_pos_array_index].x = (rand() % 20) + 1;
        ball_pos_array[ball_pos_array_index].y = (rand() % 20) + 1;
        ball_pos_array[ball_pos_array_index].dx = 1;
        ball_pos_array[ball_pos_array_index].dy = -1;

        ball_pos_array_index++;
      }

      break;
    case ENTER_NCURSES:
      // case KEY_ENTER:
      break_loop = 1;
      break;
    }
  }
}

void UpdateBallPos(int ball_index)
{

  mvprintw(ball_pos_array[ball_index].y, ball_pos_array[ball_index].x, "o");

  ball_pos_array[ball_index].x += ball_pos_array[ball_index].dx;
  ball_pos_array[ball_index].y += ball_pos_array[ball_index].dy;

  if (ball_pos_array[ball_index].x >= col - 1)
  {
    ball_pos_array[ball_index].dx = -1;
  }
  if (ball_pos_array[ball_index].y >= row - 1)
  {

    ball_pos_array[ball_index].dy = -1;

  }
  if (ball_pos_array[ball_index].x <= 1)
  {

    ball_pos_array[ball_index].dx = 1;

  }
  if (ball_pos_array[ball_index].y <= 1)
  {

    ball_pos_array[ball_index].dy = 1;

  }
}

void ChangeBallDirection(int ball_index){
  // set dx and dy to 1 or -1 randomly
  int set_dx_positive = rand() % 2;
  if(set_dx_positive){
    ball_pos_array[ball_index].dx = 1;
  }
  else{
    ball_pos_array[ball_index].dx = -1;
  }


  int set_dy_positive = rand() % 2;
  if(set_dy_positive){
    ball_pos_array[ball_index].dy = 1;
  }
  else{
   ball_pos_array[ball_index].dy = -1; 
  }
}