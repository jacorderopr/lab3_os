#include "functions.h"

// global vars
// DEFINE the global var (which was declared in the functions.h)
double array_tangent_vals[ARRAY_SIZE];

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
 * @brief Calculates the sum of elements in an array of doubles.
 *
 * This function computes the sum of all elements in the provided array.
 * It allocates memory for storing the sum, iterates over the array, and 
 * returns the total sum.
 *
 * @param[in] array_tangent An array of doubles with a size of `ARRAY_SIZE` 
 * containing the values to sum.
 *
 * @return The total sum of the elements in the array.
 * 
 * @note The function dynamically allocates memory for the sum but does not 
 * free it, which may result in a memory leak.
 */

double CalculateSum(double array_tangent[ARRAY_SIZE]){
    double* total_sum = malloc(sizeof(double));


    for(int i = 0; i < ARRAY_SIZE; i++){
        *total_sum += array_tangent[i];
    }


    return *total_sum;
}
