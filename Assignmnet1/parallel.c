#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

void* all(void* arg) {
    int size = (intptr_t)arg;
    long long trailing_sum = 0;
    printf("The thread ID of the child process is: %lu\n", pthread_self());
    for (int i = 0; i <= size; i++) {
        trailing_sum += i;
    }
    printf("All: %lld\n", trailing_sum);
    
    long double* result = malloc(sizeof(long double));
    *result = trailing_sum;
    return result;
}

void* even(void* arg) {
    int size = (intptr_t)arg;
    long long trailing_sum = 0;
    printf("The thread ID of the child process is: %lu\n", pthread_self());
    for (int i = 0; i <= size; i += 2) {
        trailing_sum += i;
    }
    printf("Even: %lld\n", trailing_sum);

    long double* result = malloc(sizeof(long double));
    *result = trailing_sum;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s size\n", argv[0]);
        return 1;
    }

    printf("The thread ID of the parent process is: %lu\n", pthread_self());

    pthread_t child_pid1, child_pid2;
    int size = atoi(argv[1]);

    pthread_create(&child_pid1, NULL, all, (void*)(intptr_t)size);
    pthread_create(&child_pid2, NULL, even, (void*)(intptr_t)size);

    long double* result_odd;
    long double* result_even;

    pthread_join(child_pid1, (void**)&result_odd);
    pthread_join(child_pid2, (void**)&result_even);

    if (*result_odd && *result_even != 0) {
        printf("Program Result: %Lf\n", (*result_odd) / (*result_even));
    } else {
        printf("Error: Division by zero\n");
    }

    free(result_odd);
    free(result_even);

    return 0;
}

