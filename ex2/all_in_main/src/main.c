#include "functions.h"



int main(){
    struct timeval start_time, end_time;

    gettimeofday(&start_time, NULL);

    FillArrayWithTangentValues(array_tangent_vals);

    double total_sum = CalculateSum(array_tangent_vals);
  
    printf("The total Sum: %f\n", total_sum);

    gettimeofday(&end_time, NULL);

    int seconds = end_time.tv_sec - start_time.tv_sec;
    int microseconds = end_time.tv_usec - start_time.tv_usec;

    if(microseconds < 0){
        seconds -= 1;
        microseconds += 1000000;
    }

    float elapsed_time = seconds + microseconds / 1e6;

    printf("Elapsed Time Using Threads: %f seconds\n", elapsed_time);
    
    return 0;
}