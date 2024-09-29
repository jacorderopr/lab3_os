#include "functions.h"



int main(){
    struct timeval start_time, end_time;

    gettimeofday(&start_time, NULL);

    FillArrayWithTangentValues(array_tangent_vals);

    pthread_t pthread_array[5];
    int current_segment[5];


    pthread_mutex_init(&mutex, NULL);

 
    int curr_segment_test_var = 0;
    for(int i = 0; i < 5; i++){
        current_segment[i] = i;
           
        pthread_create(&pthread_array[i], NULL, SegmentSum, (void*) &current_segment[i]); // &current_segment[i]
          
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