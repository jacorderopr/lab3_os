#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <curses.h>

void *AskForFloat(void *param);
void *CalculateArcSine(void *param);
extern pthread_mutex_t mutex;
extern pthread_cond_t cond_wait_read;
extern pthread_cond_t cond_wait_print;

#endif
