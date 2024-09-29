#include "functions.h"

// global vars
// DEFINE the global var (which was declared in the functions.h)
double array_tangent_vals[ARRAY_SIZE];


void FillArrayWithTangentValues(double array_tangent[ARRAY_SIZE]){

    for(int i = 0; i < ARRAY_SIZE; i++){
        array_tangent[i] = tan(i);
    }
}


double CalculateSum(double array_tangent[ARRAY_SIZE]){
    double* total_sum = malloc(sizeof(double));


    for(int i = 0; i < ARRAY_SIZE; i++){
        *total_sum += array_tangent[i];
    }


    return *total_sum;
}
