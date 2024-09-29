#include "functions.h"

// global vars
// DEFINE the global var (which was declared in the functions.h)
int input_buffer[10000];
float processed_buffer[10000];
char *FILENAME = "data.txt";
int n_read_values = 0;

struct timeval time_array[6];
pthread_mutex_t mutex;
pthread_cond_t cond_wait_read;


/**
 * @brief Creates a text file with random numbers if it does not already exist.
 *
 * This function checks if a file with the name specified by `FILENAME` exists. 
 * If the file does not exist, it creates the file and writes 10,000 random numbers 
 * between 1 and 100,000 to it. If the file exists, the function does not modify it. 
 * It returns an integer pointer indicating whether the file was created (`1`) or 
 * already existed (`0`).
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return A dynamically allocated integer pointer where:
 *         - `1` indicates the file was created,
 *         - `0` indicates the file already existed.
 */

void *CreateTxtFile(void *)
{
 

    FILE *file_exists_ptr = fopen(FILENAME, "r");
    int *output = malloc(sizeof(int));

    printf("Checking if %s exists...\n", FILENAME);

    if (file_exists_ptr == NULL)
    {
        printf("%s does NOT exist! Creating it.\n", FILENAME);
        // the file does not exist so we can create it here.
        FILE *file_ptr = fopen(FILENAME, "w");
        srand(time(NULL));

        for (int i = 0; i < 10000; i++)
        {
            int curr_random_num = (rand() % 100000) + 1; // random number between 1-100,000
            fprintf(file_ptr, "%d\n", curr_random_num);
        }
        fclose(file_ptr);
        *output = 1;
    }
    else
    {
        printf("%s EXISTED!\n", FILENAME);
        fclose(file_exists_ptr); // the file existed so we close it.
        *output = 0;
    }
    return (void *)output;
}


/**
 * @brief Reads numbers from a file and stores them in a shared buffer.
 *
 * This function reads integers from a file specified by `FILENAME` and stores 
 * them in the shared `input_buffer`. It locks the shared buffer using a mutex 
 * before each write to ensure thread safety. After reading each number, 
 * it signals another thread to process the data using `pthread_cond_signal()`. 
 * The function also records the start and end times of the operation using 
 * `gettimeofday()` and prints the total number of elements read.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the file reading process completes.
 *
 * @note The function uses a mutex and condition variables to synchronize 
 * access to the shared buffer with other threads.
 */

void *ReadFile(void *)
{
    gettimeofday(&(time_array[0]), NULL);
    FILE *file_ptr = fopen(FILENAME, "r");
    int number;
    while (fscanf(file_ptr, "%d", &number) != EOF)
    {
        pthread_mutex_lock(&mutex);
        input_buffer[n_read_values++] = number;
        pthread_mutex_unlock(&mutex);
        // mandar mensaje para despertar si es que
        pthread_cond_signal(&cond_wait_read);
    }

    printf("total amount of elements read: %d\n", n_read_values);
    fclose(file_ptr);
    gettimeofday(&(time_array[1]), NULL);

}

/**
 * @brief Processes numbers read from a file by approximating their square roots.
 *
 * This function processes 10,000 numbers stored in the shared `input_buffer`, 
 * computing an approximate square root for each value using the `ApproximateSqrt()` 
 * function and storing the result in the `processed_buffer`. The function locks the 
 * mutex to ensure thread-safe access to the buffer and uses a condition variable 
 * (`pthread_cond_wait()`) to wait if the buffer does not have enough values read 
 * from the file. It records the start and end times of the operation using 
 * `gettimeofday()`.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the processing of all 10,000 values is complete.
 *
 * @note The function uses mutex locks and condition variables to synchronize 
 * access to the shared buffer with other threads.
 */

void *ProcessFile(void *)
{
    gettimeofday(&(time_array[2]), NULL);
    for (int n_processed_values = 0; n_processed_values < 10000; n_processed_values++)
    {
        pthread_mutex_lock(&mutex);
        while (n_processed_values >= n_read_values)
        {
            // reached a point that is being written to, so we sleep
            // printf("Cond Wait! i: %d\n", n_processed_values);
            pthread_cond_wait(&cond_wait_read, &mutex);
        }
    
        float R = input_buffer[n_processed_values];

        processed_buffer[n_processed_values] = ApproximateSqrt(R);
        // printf("Processed Buff: %f\n", processed_buffer[n_processed_values]);
        pthread_mutex_unlock(&mutex);

    }
    gettimeofday(&(time_array[3]), NULL);

}

/**
 * @brief Approximates the square root of a given integer using the Babylonian method.
 *
 * This function calculates an approximate square root of the integer `R` 
 * using the Babylonian (or Heron's) method. It performs a fixed number of 
 * iterations to refine the estimate, starting from an initial guess of `R / 2.0`. 
 * The result is dynamically allocated, and the function returns the approximate 
 * square root as a float.
 *
 * @param[in] R An integer value for which the square root is to be approximated.
 *
 * @return The approximate square root of the input integer `R` as a float.
 * 
 * @note The function dynamically allocates memory for the result, but it does 
 * not free it, which may lead to a memory leak. The calling function is 
 * responsible for managing the memory.
 */

float ApproximateSqrt(int R){
    float* result = malloc(sizeof(float));
    float prev_value = R / 2.0;
    int ITERATIONS = 10;

    for(int i = 0; i < ITERATIONS; i++){
        *result = (0.5) * (prev_value + (R / prev_value));
        prev_value = *result;
    }
    
    // printf("Sqrt of %d is approx: %f\n", R, *result);
    return *result;
}

/**
 * @brief Writes the processed square root data to a text file.
 *
 * This function writes the approximate square roots stored in the 
 * `processed_buffer` to a text file named "sqrt.txt". It iterates through 
 * the first 10,000 processed values and writes each value to the file. 
 * The function also records the start and end times of the operation using 
 * `gettimeofday()`.
 *
 * @param[in] param A pointer to any parameter (unused in this function).
 *
 * @return `NULL` when the writing process to the file is complete.
 *
 * @note The function does not check for errors in file opening or writing. 
 * It assumes the `processed_buffer` contains valid data for writing.
 */

void* GetSquareRootData(void*){
    gettimeofday(&(time_array[4]), NULL);

    FILE* file_ptr = fopen("sqrt.txt", "w");

    for(int i = 0; i < 10000; i++){
        fprintf(file_ptr, "%f\n", processed_buffer[i]);
    }

    fclose(file_ptr);
    gettimeofday(&(time_array[5]), NULL);

}

/**
 * @brief Prints the elapsed time for various threads in the processing sequence.
 *
 * This function calculates and displays the elapsed time for each pair of 
 * time measurements stored in the `time_array`. It iterates through the 
 * array, calculating the difference between start and end times for every 
 * two entries. The result is adjusted for negative microseconds to ensure 
 * accurate time calculations. The elapsed time for each thread is printed 
 * in seconds.
 *
 * @return `NULL` when the printing process is complete.
 *
 * @note The function assumes that the `time_array` contains valid `timeval` 
 * structures for the measured times. The output format is specific to the 
 * thread sequence and may need adjustment if the array size changes.
 */

void PrintTimes(){

    for(int i = 0; i < 5; i+= 2){
        int start_sec = time_array[i].tv_sec;
        int start_microsec = time_array[i].tv_usec;

        int end_sec = time_array[i + 1].tv_sec;
        int end_microsec = time_array[i + 1].tv_usec;

        int seconds = end_sec - start_sec;
        int microseconds = end_microsec - start_microsec;

        if(microseconds < 0){
            // adjust the time
            seconds -= 1;
            // add 1 seconds to the NEGATIVE value of microseconds to fix it.
            microseconds += 1000000; // 1 million microsec = 1 sec

        }
        float elapsed_time = seconds + microseconds / 1e6;
        printf("Thread #%d Elapsed Time: %f\n", i / 2 + 1, elapsed_time);

    }
}