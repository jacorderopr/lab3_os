#include "functions.h"

int main()
{
  pthread_t id1, id2;

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  curs_set(0);

  ball_pos.x = 10;
  ball_pos.y = 20;

  pthread_create(&id1, NULL, UpdateBallPos, NULL);
  pthread_create(&id2, NULL, UpdateCounter, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  getch();
  endwin();

  return 0;
}
