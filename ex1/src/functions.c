#include "functions.h"

// global vars
float user_input = -1.0;
int is_thread_active = 1;
int should_secondary_thread_check = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_wait_read;
pthread_cond_t cond_wait_print;

void* AskForFloat(void* param){

    do{
        pthread_mutex_lock(&mutex);
        printf("Enter a number between 0 and 1 to calculate arcsine: ");
        
        // ask for user_input
        
        scanf("%f", &user_input);

        pthread_cond_signal(&cond_wait_print); // other thread can now wake up
        // duerme, tienes que dormir hasta que termines de imprimir
        pthread_cond_wait(&cond_wait_read, &mutex);

        pthread_mutex_unlock(&mutex);
        should_secondary_thread_check = 1;

        //usleep(100000); // sleep to allow CalculateArcSine thread to show result.
    }while(user_input <= 100);
    printf("AskForFloat Thread Exited!\n");
    
}

void* CalculateArcSine(void* param){
    while(1){
   
    
    pthread_mutex_lock(&mutex);
    
    if(user_input > 100){
        pthread_cond_signal(&cond_wait_read);
        pthread_mutex_unlock(&mutex);
        break;
    }
     if(user_input >=0.0 && user_input <= 1.0){
         printf("Arcsin of %f is: %f\n", user_input, asinf(user_input));
    }else{
        printf("\n***You must input a number between 0 and 1 to calculate its ArcSine!***\n\n");
    }
    
    pthread_cond_signal(&cond_wait_read); // other thread can now wake up
        // tienes que dormir para no imprimir mas de una vez
    pthread_cond_wait(&cond_wait_print, &mutex); 


    pthread_mutex_unlock(&mutex);
    }
    printf("CalculateArcSine Thread Exited!\n");
}

