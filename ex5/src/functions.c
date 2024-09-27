#include "functions.h"

BallPosition ball_pos_array[10];
int ball_pos_array_index = 0;

int counter_val = 0;
int dx, dy;
int row, col;
int break_loop = 0;

void *UpdateAllBallPos(void *)
{
  dx = dy = 1; // tal vez hay que hacer uno para cada bola
  while (!break_loop)
  {

    clear();

    mvprintw(0, 0, "%d", counter_val); // displays the counter, DOES NOT update it!
    getmaxyx(stdscr, row, col);        /* Obtiene el numbero de filas y columnas */

    for (int i = 0; i < ball_pos_array_index; i++)
    {
      // getmaxyx(stdscr, row, col); /* Obtiene el numbero de filas y columnas */
      UpdateBallPos(i);
    }
    refresh();
    usleep(100000); /* Duerme por 100ms */
  }
}

void UpdateBallPos(int ball_pos_index)
{

  mvprintw(ball_pos_array[ball_pos_index].y, ball_pos_array[ball_pos_index].x, "o");

  ball_pos_array[ball_pos_index].x += dx;
  ball_pos_array[ball_pos_index].y += dy;
  if (ball_pos_array[ball_pos_index].x >= col - 1)
  {
    dx = -1;
  }
  if (ball_pos_array[ball_pos_index].y >= row - 1)
  {
    dy = -1;
  }
  if (ball_pos_array[ball_pos_index].x <= 1)
  {
    dx = 1;
  }
  if (ball_pos_array[ball_pos_index].y <= 1)
  {
    dy = 1;
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
    case KEY_LEFT:
      /* code */
      break;
    case 'f':
      // add a new ball
      if (ball_pos_array_index < 10)
      {

        ball_pos_array[ball_pos_array_index].x = (rand() % 20) + 1;
        ball_pos_array[ball_pos_array_index].y = (rand() % 20) + 1;
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