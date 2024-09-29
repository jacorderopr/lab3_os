#include "functions.h"

// global vars
// DEFINE the global var (which was declared in the functions.h)
double array_tangent_vals[ARRAY_SIZE];
pthread_mutex_t mutex;

//  * @brief Fills an array with the tangent values of indices.
//  *
//  * This function populates the provided array with the tangent values of the 
//  * indices from 0 to `ARRAY_SIZE - 1`. The tangent values are calculated using 
//  * the `tan()` function from the math library.
//  *
//  * @param[out] array_tangent An array of size `ARRAY_SIZE` that will be filled 
//  * with tangent values. The tangent of index `i` will be stored in `array_tangent[i]`.
//  */

void FillArrayWithTangentValues(double array_tangent[ARRAY_SIZE]){

    for(int i = 0; i < ARRAY_SIZE; i++){
        array_tangent[i] = tan(i);
    }
}

/**
 * @brief Calculates the sum of a segment of an array in a multithreaded context.
 *
 * This function computes the sum of a specific segment of a global array 
 * (`array_tangent_vals`). The segment is determined by the integer value 
 * pointed to by the parameter, which represents the segment index. The 
 * function divides the array into five segments and calculates the sum 
 * of the corresponding part of the array for the given thread.
 *
 * @param[in] param A pointer to an integer representing the index of the 
 * segment to be summed. It must be castable to `int*`.
 *
 * @return A pointer to a dynamically allocated double containing the sum of 
 * the segment.
 * 
 * @note The function dynamically allocates memory for the sum, but it does not 
 * handle freeing the memory. The calling thread is responsible for deallocating 
 * the returned pointer.
 */

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