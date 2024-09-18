#include "functions.h"


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