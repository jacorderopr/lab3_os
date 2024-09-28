#include "functions.h"

void *CreateTxtFile(void *);
void *ReadFile(void *);
void *ProcessFile(void *);
void *GetSquareRootData(void *);

float ApproximateSqrt(int R);
void PrintTimes();
int input_buffer[10000];
float processed_buffer[10000];
char *FILENAME = "data.txt";
int n_read_values = 0;

struct timeval time_array[6];
pthread_mutex_t mutex;
pthread_cond_t cond_wait_read;

int main()
{
    
    
 
    pthread_t create_or_check_file;

    pthread_create(&create_or_check_file, NULL, CreateTxtFile, NULL);

    pthread_join(create_or_check_file, NULL); // wait for thread to finish before creating other threads!!

    pthread_t read_values;
    pthread_t process_values;

    pthread_mutex_init(&mutex, NULL);

    // pthread_t

    pthread_create(&read_values, NULL, ReadFile, NULL);
    pthread_create(&process_values, NULL, ProcessFile, NULL);

    pthread_join(read_values, NULL);
    pthread_join(process_values, NULL);

    pthread_t square_root_values;
    pthread_create(&square_root_values, NULL, GetSquareRootData, NULL);

    pthread_join(square_root_values, NULL);

    PrintTimes();
    return 0;
}

/*
Write a program that, as soon as it starts, creates an initial thread that checks if the file data.txt exists. If it already exists, the thread returns 1.
If it does not exist, the thread creates the file and writes 10,000 pseudo-random unsigned 8-bit integer values, one below the other, and returns 0.*/
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

/*
The first thread is responsible for reading the data from the file individually and storing
 them in an array named input_buffer using an index named n_read_values
 to indicate how many values have been read from the file.*/

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

void* GetSquareRootData(void*){
    gettimeofday(&(time_array[4]), NULL);

    FILE* file_ptr = fopen("sqrt.txt", "w");

    for(int i = 0; i < 10000; i++){
        fprintf(file_ptr, "%f\n", processed_buffer[i]);
    }

    fclose(file_ptr);
    gettimeofday(&(time_array[5]), NULL);

}

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