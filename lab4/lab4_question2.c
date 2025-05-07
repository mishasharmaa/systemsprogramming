//Include necessary libraries for input/output, dynamic memory allocation and threading
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

// Step 1: Create a Function to be executed as the child thread
void* childThreadFun(void* arg) {

    // Print the child thread ID
    printf("I am child thread with ID: %ld\n", pthread_self());
    // Get the size of the array from the parent thread's argument
    int size = *((int*)arg);

    // Dynamically allocate memory for an integer array using malloc
    int *numbers = malloc(size * sizeof(int));
    
    

    //make sure memory has been properly allocated
     if (numbers == NULL) {
       perror("Error: Memory allocation failed");
       pthread_exit(NULL);
    }

    // Populate the array with numbers from 0 to n-1
    for (int i = 0; i < size; i++) {
       numbers[i] = i;
       printf("Inserted %d into the array using child thread...\n", numbers[i]);
    }

    // Return the populated array to the parent thread
    pthread_exit(numbers);

}

// Step 2: Create a Main function executed by the parent thread
int main(int args, char *argv[]){
    // Print the parent thread ID
    //pid_t pid;
    printf("I am main thread with ID: %ld\n", pthread_self());
    // Create a variable to hold the thread ID for the child thread
    int childID;
    // Create the child thread and pass the size of the array as an argument using create_thread()
    int size = atoi(argv[1]);
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, childThreadFun, (void*)&size);
    
    // Declare a pointer to hold the result returned by the child thread
    void* val;

    // Wait for the child thread to complete and get the result using join_thread()
    pthread_join(thread_id, &val);

    // Print the elements of the array in the parent thread
    printf("\nDisplaying elements of the array in parent thread...\n");
    
    int* numbers = (int*) val;
    for (int i = 0; i < size; i++) {
       numbers[i] = i;
       printf("Element at index %d: %d\n", i, numbers[i]);
    }
    // Free the dynamically allocated memory using free()
    free(val);
    // Exit the program (return 0)
    return 0;
}
