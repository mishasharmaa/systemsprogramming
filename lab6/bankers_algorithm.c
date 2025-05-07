// Misha Sharma: 100826646
// May Robertson: 100751769


#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 4 // Number of resource types

// Function to find the safe sequence
void findSafeSequence(int alloc[P][R], int max[P][R], int available[R]) {
    int need[P][R]; // Need Matrix
    int finish[P] = {0}; // Tracks finished processes
    int safeSeq[P]; // Stores the safe sequence
    int work[R]; // Available resources
    int count = 0; // Counter for safe sequence

    // Calculate Need Matrix: Need[i][j] = Max[i][j] - Allocation[i][j]
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Copy available resources to work array
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    // Finding the safe sequence
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < R; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is in an UNSAFE state!\n");
            return;
        }
    }

    // Printing the Safe Sequence
    printf("System is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
}

int main() {
    int alloc[P][R] = {
        {0, 1, 0, 2},
        {2, 0, 0, 1},
        {3, 0, 2, 1},
        {2, 1, 1, 0},
        {0, 0, 2, 2}
    };

    int max[P][R] = {
        {6, 4, 3, 4},
        {3, 2, 2, 2},
        {9, 1, 2, 4},
        {2, 2, 2, 1},
        {4, 3, 3, 4}
    };

    int available[R] = {3, 3, 2, 2};

    // Call function to find the safe sequence
    findSafeSequence(alloc, max, available);

    return 0;
}
