#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

long double all(int arg) {
    long long trailing_sum = 0;
    for (int i = 0; i <= arg; i++) {
        trailing_sum += i;
    }
    printf("All: %lld\n", trailing_sum);
    
    return trailing_sum;
}

long double even(int arg) {
    long long trailing_sum = 0;
    for (int i = 0; i <= arg; i += 2) {
        trailing_sum += i;
    }
    printf("Even: %lld\n", trailing_sum);
    
    return trailing_sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s size\n", argv[0]);
        return 1;
    }

    pthread_t child_pid1, child_pid2;
    int size = atoi(argv[1]);

    long double result_odd = all(size);
    long double result_even = even(size);

    if (result_even && result_odd != 0) {
        printf("Program Result: %Lf\n", (result_odd) / (result_even));
    } else {
        printf("Error: Division by zero\n");
    }

    return 0;
}

