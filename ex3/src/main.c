#include "functions.h"

int main()
{
    pthread_t create_or_check_file;

    pthread_create(&create_or_check_file, NULL, CreateTxtFile, NULL);

    pthread_join(create_or_check_file, NULL); // wait for thread to finish before creating other threads!!

    pthread_t read_values;
    pthread_t process_values;

    pthread_mutex_init(&mutex, NULL);

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
