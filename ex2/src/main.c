#include "functions.h"



int main(){

    FillArrayWithTangentValues(array_tangent_vals);

    printf("\n%f\n", array_tangent_vals[1000000 - 1]);


    pthread_t pthread_array[5];
    int current_segment[5];

    pthread_attr_t attr;

    pthread_attr_init(&attr);
    int curr_segment_test_var = 0;
    for(int i = 0; i < 5; i++){
        current_segment[i] = i;
        pthread_create(&pthread_array[i], &attr, SegmentSum, (void*) &current_segment[i]); // &current_segment[i]
       
    }
    double total_sum = 0;
    for(int i = 0; i < 5; i++){
        void* segment_sum_ptr;
        pthread_join(pthread_array[i], &segment_sum_ptr);

        double* segment_sum = (double*) segment_sum_ptr;
        printf("Sum of segment %d is: %f\n", i, *segment_sum);
        total_sum += *segment_sum;
    }

    printf("The total Sum: %f\n", total_sum);

    printf("\nExiting Main!\n");
    return 0;
}