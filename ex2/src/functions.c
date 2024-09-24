#include "functions.h"

// global vars
// DEFINE the global var (which was declared in the functions.h)
double array_tangent_vals[ARRAY_SIZE];
pthread_mutex_t mutex;

void FillArrayWithTangentValues(double array_tangent[ARRAY_SIZE]){

    for(int i = 0; i < ARRAY_SIZE; i++){
        array_tangent[i] = tan(i);
    }
}

void* SegmentSum(void* param){
    // the param MUST be able to be casted to an int*
    // pthread_mutex_lock(&mutex);
    int* segment_ptr = (int*) param;
    int segment_index = *segment_ptr;
    
    int segment_size = ARRAY_SIZE / 5;
    int start_index = segment_index * segment_size;
    int end_index = (segment_index + 1) * segment_size;

    double* total_sum = (double*)malloc(sizeof(double)); // only need 1 space
    
    for(int i = start_index; i < end_index; i++){
        *total_sum += array_tangent_vals[i];
    }

    // pthread_mutex_unlock(&mutex);
    return (void*) total_sum;
}