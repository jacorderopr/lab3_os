#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <curses.h>

#define ARRAY_SIZE 1000000

// declare the global var
extern double array_tangent_vals[ARRAY_SIZE];
extern pthread_mutex_t mutex;

void FillArrayWithTangentValues(double array_tangent[ARRAY_SIZE]);
void* SegmentSum(void* param);

#endif
