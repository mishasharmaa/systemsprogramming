#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void task2(){
    printf("Task 2: Multiple fork()\n");
    pid_t pid1, pid2;

    pid1 = fork();
    pid2 = fork();

    if (pid1 > 0 && pid2 >0){
        printf("Parent Process (A) %d\n", getpid());

    } else if (pid1==0 && pid2 > 0 ){
        printf("First Child Process (B) %d\n", getpid());

    } else if (pid1 > 0 && pid2==0){
        printf("Second Child Process (C) %d\n", getpid());

    } else if(pid1==0 && pid2==0){
        printf("Grandchild Process (D) %d\n", getpid());

    } else {
        printf("error\n");
    }

}


int main(){
    printf("Starting lab3\n");
    task2();
    return 0;
}
