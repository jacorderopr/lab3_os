#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

float user_input = 0.0;
int is_thread_active = 1;
int should_secondary_thread_check = 0;
void* AskForFloat(void* param){

    do{
        printf("Enter a number between 0 and 1 to calculate arcsine: ");
        // ask for user_input
        scanf("%f", &user_input);
        should_secondary_thread_check = 1;

        if(user_input < 0 || user_input > 1){
            printf("\n***You must input a number between 0 and 1 to calculate its ArcSine!***\n\n");
        }

        usleep(100000); // sleep to allow CalculateArcSine thread to show result.
    }while(user_input <= 100);
    printf("AskForFloat Thread Exited!\n");
    is_thread_active = 0;
}

void* CalculateArcSine(void* param){
    while(is_thread_active){

    
    if(user_input >= 0.0 && user_input <= 1.0 && should_secondary_thread_check){
        // double current_arcsine = asinf(user_input);

        printf("Arcsin of %f is: %f\n", user_input, asinf(user_input));
        should_secondary_thread_check = 0;
    }
    }
    printf("CalculateArcSine Thread Exited!\n");
}

int main(){

    pthread_t p_ask_for_float;
    pthread_t p_calc_arcsine;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&p_ask_for_float, &attr, AskForFloat, NULL);
    pthread_create(&p_calc_arcsine, &attr, CalculateArcSine, NULL);

    pthread_join(p_ask_for_float, NULL);
    pthread_join(p_calc_arcsine, NULL);

    printf("\nExiting Main!\n");
    return 0;
}