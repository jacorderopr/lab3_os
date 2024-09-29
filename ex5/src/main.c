#include "functions.h"

int main()
{
  pthread_t id1, id2, id3;

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  curs_set(0);

  srand((unsigned)time(NULL));

  pthread_create(&id3, NULL, GetCommands, NULL);
  pthread_create(&id1, NULL, UpdateAllBallPos, NULL);
  pthread_create(&id2, NULL, UpdateCounter, NULL);

  pthread_join(id3, NULL);
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  endwin();

  return 0;
}
