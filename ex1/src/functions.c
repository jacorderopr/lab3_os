#include "functions.h"

// global vars
float user_input = -1.0;
int is_thread_active = 1;
int should_secondary_thread_check = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_wait_read;
pthread_cond_t cond_wait_print;

/**
 * @brief Asks the user for a floating-point number between 0 and 1 to calculate its arcsine.
 *
 * This function repeatedly prompts the user for a floating-point number between 0 and 1.
 * It locks the `mutex` to ensure thread-safe access to shared resources and signals another
 * thread after receiving the input using `pthread_cond_signal()`. The function then waits for
 * the other thread to finish processing the input before prompting again, using
 * `pthread_cond_wait()`. It continues this process until the user inputs a number greater than 100.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the input exceeds 100, at which point the thread will exit.
 *
 * @note The function uses mutex locks and condition variables to coordinate with another thread.
 */

void *AskForFloat(void *param)
{

    do
    {
        pthread_mutex_lock(&mutex);
        printf("Enter a number between 0 and 1 to calculate arcsine: ");

        // ask for user_input

        scanf("%f", &user_input);

        pthread_cond_signal(&cond_wait_print); // other thread can now wake up
        // duerme, tienes que dormir hasta que termines de imprimir
        pthread_cond_wait(&cond_wait_read, &mutex);

        pthread_mutex_unlock(&mutex);
        should_secondary_thread_check = 1;

        // usleep(100000); // sleep to allow CalculateArcSine thread to show result.
    } while (user_input <= 100);
    printf("AskForFloat Thread Exited!\n");
}

/**
 * @brief Calculates the arcsine of a user-provided input between 0 and 1.
 *
 * This function continuously checks the shared `user_input` value and, if the input is
 * between 0 and 1, calculates and prints its arcsine using the `asinf()` function.
 * The function uses a mutex to ensure that only one thread accesses and modifies
 * the `user_input` at a time. The function also coordinates with another thread
 * through condition variables (`pthread_cond_signal` and `pthread_cond_wait`)
 * to control the timing of the input and output operations.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the `user_input` exceeds 100, at which point the thread will exit.
 *
 * @note The function uses condition variables and mutex locks for thread synchronization.
 */

void *CalculateArcSine(void *param)
{
    while (1)
    {

        pthread_mutex_lock(&mutex);

        if (user_input > 100)
        {
            pthread_cond_signal(&cond_wait_read);
            pthread_mutex_unlock(&mutex);
            break;
        }
        if (user_input >= 0.0 && user_input <= 1.0)
        {
            printf("Arcsin of %f is: %f\n", user_input, asinf(user_input));
        }
        else
        {
            printf("\n***You must input a number between 0 and 1 to calculate its ArcSine!***\n\n");
        }

        pthread_cond_signal(&cond_wait_read); // other thread can now wake up
                                              // tienes que dormir para no imprimir mas de una vez
        pthread_cond_wait(&cond_wait_print, &mutex);

        pthread_mutex_unlock(&mutex);
    }
    printf("CalculateArcSine Thread Exited!\n");
}
