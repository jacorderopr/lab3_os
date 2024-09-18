#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


void* AskForFloat(void* param);
void* CalculateArcSine(void* param);

#endif
