#include "functions.h"

BallPosition ball_pos_array[10];
int ball_pos_array_index = 0;

int counter_val = 0;

int row, col;
int break_loop = 0;

/**
 * @brief Updates the positions of all balls in the terminal window.
 *
 * This function continuously updates the positions of multiple balls stored
 * in an array, using the `UpdateBallPos()` function for each ball. It
 * clears the screen and displays the current counter value at the top left
 * corner. The function runs in a loop until a termination condition (`break_loop`)
 * is met. The screen is refreshed after updating the positions, creating
 * an animated effect.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the process of updating all ball positions is complete.
 *
 * @note The function runs indefinitely until `break_loop` is set to true. It
 * assumes that the ncurses library has been properly initialized, and that
 * the `ball_pos_array_index` variable accurately reflects the number of balls
 * to be updated.
 */

void *UpdateAllBallPos(void *)
{

  while (!break_loop)
  {

    clear();

    mvprintw(0, 0, "%d", counter_val); // displays the counter, DOES NOT update it!

    for (int i = 0; i < ball_pos_array_index; i++)
    {
      getmaxyx(stdscr, row, col); /* Obtiene el numbero de filas y columnas */
      // getmaxyx(stdscr, row, col); /* Obtiene el numbero de filas y columnas */
      UpdateBallPos(i);
    }
    refresh();
    usleep(100000); /* Duerme por 100ms */
  }
}
/**
 * @brief Continuously increments a counter variable until a termination condition is met.
 *
 * This function runs in an infinite loop, incrementing the global counter
 * variable `counter_val` by one every second. It checks for a termination
 * condition (`break_loop`) and pauses execution for 1 second between
 * increments using `usleep()`.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the counter updating process is complete.
 *
 * @note The function runs indefinitely until `break_loop` is set to true.
 * It assumes that `counter_val` is properly defined and accessible in the
 * context where this function is used.
 */

void *UpdateCounter(void *)
{

  while (!break_loop)
  {

    counter_val++;
    usleep(1000000); /* Duerme por 1sg*/
  }
}

/**
 * @brief Handles user input for controlling ball movements and adding new balls.
 *
 * This function continuously listens for key strokes while the `break_loop`
 * condition is not met. It processes different key inputs to control the
 * behavior of the balls in the terminal window:
 * - Pressing 'c' changes the direction of all existing balls.
 * - Pressing the spacebar adds a new ball if the current count is less than
 *   10, initializing its position and movement direction randomly.
 * - Pressing the Enter key sets the `break_loop` variable to terminate the
 *   loop.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the command handling process is complete.
 *
 * @note The function relies on ncurses for capturing key strokes and assumes
 * that the necessary variables, including `ball_pos_array` and
 * `ball_pos_array_index`, are properly defined and accessible in the context
 * where this function is used. The loop will run indefinitely until
 * terminated by user input.
 */

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
      for (int i = 0; i < ball_pos_array_index; i++)
      {
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

/**
 * @brief Updates the position of a ball in the terminal window.
 *
 * This function updates the coordinates of a ball specified by its index
 * in the `ball_pos_array`. It moves the ball based on its current
 * direction (`dx` and `dy`) and handles the boundary collisions by
 * reversing the direction when the ball hits the edge of the terminal
 * window.
 *
 * @param[in] ball_index The index of the ball in the `ball_pos_array`
 *                      that is to be updated.
 *
 * @return None
 *
 * @note The function uses ncurses to print the ball's new position in
 * the terminal window. It assumes that the global variables `col` and
 * `row` (representing the dimensions of the terminal) and
 * `ball_pos_array` are properly defined and accessible in the context
 * where this function is used.
 */
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

/**
 * @brief Changes the direction of a specified ball randomly.
 *
 * This function sets the direction (`dx` and `dy`) of the ball at the
 * given index in the `ball_pos_array` to either positive or negative
 * values, determined randomly. This allows the ball to change its
 * movement direction during runtime.
 *
 * @param[in] ball_index The index of the ball in the `ball_pos_array`
 *                      whose direction is to be changed.
 *
 * @return None
 *
 * @note The function modifies the `dx` and `dy` properties of the
 * specified ball without any checks on boundaries or the number of balls.
 * It assumes that the `ball_pos_array` is properly defined and accessible
 * in the context where this function is used.
 */
void ChangeBallDirection(int ball_index)
{
  // set dx and dy to 1 or -1 randomly
  int set_dx_positive = rand() % 2;
  if (set_dx_positive)
  {
    ball_pos_array[ball_index].dx = 1;
  }
  else
  {
    ball_pos_array[ball_index].dx = -1;
  }

  int set_dy_positive = rand() % 2;
  if (set_dy_positive)
  {
    ball_pos_array[ball_index].dy = 1;
  }
  else
  {
    ball_pos_array[ball_index].dy = -1;
  }
}