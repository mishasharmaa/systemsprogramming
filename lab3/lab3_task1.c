#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void task1(){
    printf("Task1: Single Fork()\n");
    pid_t pid;

    pid = fork();

    if(pid < 0){
        perror("Fork Failed");
    } else if (pid == 0){
        printf("Child Process: My Process ID is %d\n", getpid());
    } else {
        printf("Parent Process: My Process ID is %d, My Child's ID is %d\n", getpid(), pid);
    }
    printf("\n");
}


int main(){

    printf("Starting lab3 task 1\n");

    task1();
}
