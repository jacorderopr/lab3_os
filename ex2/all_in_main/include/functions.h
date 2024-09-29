#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <curses.h>
#include <sys/time.h>

#define ARRAY_SIZE 1000000

// declare the global var
extern double array_tangent_vals[ARRAY_SIZE];

double CalculateSum(double array_tangent[ARRAY_SIZE]);
void FillArrayWithTangentValues(double array_tangent[ARRAY_SIZE]);


#endif
