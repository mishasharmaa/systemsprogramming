// Include necessary libraries for input/output, process creation and process synchronization
#include<sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int args, char *argv[]) {
// Step 1: Validate input arguments
pid_t pid;
// Ensure that at least two commands are passed via the command line
if(args>=2){
    // Step 2: Create a child process using fork()
    
    pid = fork();
}


if (pid == 0) {
    // Inside the child process
    // Print the child process ID (PID)
    printf("I am a child process with id: %d\n", getpid());
    printf("I'll execute: %s\n", argv[1]);
    printf("Below are the results for: %s\n\n", argv[1]);
    // Execute the first command using execvp()
    //execvp("ls", args);
    ///execvp(char *argv[1], char *params[]);
    //execvp(argv[1], &argv[1]);

    char *args[] = {argv[1], NULL};
    execvp(argv[1], NULL);
}
// Step 3: use else for the parent process
else {
    // Inside the parent process
    // Use wait() to ensure the child process finishes before proceeding
    wait(NULL);
    // Print the parent process ID (PID)
    printf("\nI am a parent process with id:  %d\n", getpid());
    printf("I'll execute: %s\n", argv[2]);
    printf("Below are the results for: %s\n\n", argv[2]);
    // Execute the second command using execvp()
    char *args[] = {argv[2], NULL};
    execvp(argv[2], args);
    //execvp(char *command, char *params[]);
}
}
