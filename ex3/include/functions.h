#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

void *CreateTxtFile(void *);
void *ReadFile(void *);
void *ProcessFile(void *);
void *GetSquareRootData(void *);

float ApproximateSqrt(int R);
void PrintTimes();

extern int input_buffer[10000];
extern float processed_buffer[10000];
extern char *FILENAME;
extern int n_read_values;

extern struct timeval time_array[6];
extern pthread_mutex_t mutex;
extern pthread_cond_t cond_wait_read;

#endif
