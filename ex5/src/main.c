#include "functions.h"

int main() {
  pthread_t id1, id2, id3;

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  curs_set(0);

srand((unsigned)time(NULL));

for(int i = 0; i < 6; i++){

ball_pos_array[ball_pos_array_index].x = (rand() % 121);
ball_pos_array[ball_pos_array_index].y = (rand() % 121);

ball_pos_array_index++;

}


// pthread_create(&id3, NULL, GetCommands, NULL);
pthread_create(&id1, NULL, UpdateAllBallPos, NULL);
pthread_create(&id2, NULL, UpdateCounter, NULL);


pthread_join(id1, NULL);
pthread_join(id2, NULL);
// pthread_join(id3, NULL);


  getch();
  endwin();

  return 0;
}

