#include "functions.h"

BallPosition ball_pos;

int counter_val = 0;
int dx, dy;
int row, col;

/**
 * @brief Updates the position of a ball in a terminal window.
 *
 * This function continuously updates the position of a ball represented by
 * the character "o" in a terminal window using the ncurses library. It moves
 * the ball in a specified direction, changing direction when the ball reaches
 * the window boundaries. The function also displays a counter value at the
 * top left corner of the screen. The position is refreshed in each iteration,
 * creating an animation effect.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the ball's position updating process is complete.
 *
 * @note The function runs indefinitely until externally terminated. It uses
 * `usleep()` to control the speed of the ball's movement, sleeping for
 * 100 milliseconds between updates. The function assumes that the ncurses
 * library has been properly initialized before being called.
 */

void *UpdateBallPos(void *)
{
  dx = dy = 1;

  while (1)
  {
    clear();
    getmaxyx(stdscr, row, col);        /* Obtiene el numbero de filas y columnas */
    mvprintw(0, 0, "%d", counter_val); // displays the counter, DOES NOT update it!
    mvprintw(ball_pos.y, ball_pos.x, "o");
    refresh();

    ball_pos.x += dx;
    ball_pos.y += dy;
    if (ball_pos.x >= col - 1)
    {
      dx = -1;
    }
    if (ball_pos.y >= row - 1)
    {
      dy = -1;
    }
    if (ball_pos.x <= 1)
    {
      dx = 1;
    }
    if (ball_pos.y <= 1)
    {
      dy = 1;
    }

    usleep(100000); /* Duerme por 100ms */
  }
}

/**
 * @brief Continuously increments a counter variable.
 *
 * This function runs in an infinite loop, incrementing the global counter
 * variable `counter_val` by one every second. It uses `usleep()` to pause
 * execution for 1 second between increments, effectively controlling the
 * rate at which the counter updates.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the counter updating process is complete.
 */

void *UpdateCounter(void *)
{

  while (1)
  {

    counter_val++;
    usleep(1000000); /* Duerme por 1sg*/
  }
}