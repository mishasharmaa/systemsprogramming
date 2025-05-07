#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid ; // Process ID
    int burstTime ; // Burst Time
    int priority ; // Priority
 };

//arrays to gold wait and turnaround times
//made them global so they can be accessed in main as well as calculateTimes
int wt[5] = {};
int tat[5] = {};


void calculateTimes ( struct Process processes [] , int n ) {

    //array of burst times;
    int bt[5] = {};

    //populate it with burst times that were given
    for(int i = 0; i<5; i++){
        bt[i] = processes[i].burstTime;
    }

    
     
    //wait time would be all the previous burst times added up from 0
    //tat would be all the burst times plus the process' own burst time

    //bt[i-1] + wt[i-1] ;
    
    //wait time for the first process will be 0
    wt[0] = 0; 

    //calculate the rest of the wait times by using the previous wait time and burst time starting from wt[1]
    for(int i = 1; i<n; i++){
        wt[i] = bt[i-1]+wt[i-1];
    }

    //calculate turnaround time by using burst time and wait time
    for(int i = 0; i<n; i++){
        tat[i] = bt[i] + wt[i];
    }
}

int compare ( const void *a , const void * b ) {
    struct Process * p1 = ( struct Process *) a ;
    struct Process * p2 = ( struct Process *) b ;
    return p1 -> priority - p2 -> priority ;
}

void qsort ( void * base , size_t num , size_t size , int (* compar ) ( const void * , const void *) ) ;

int main () {
    
struct Process processes [5] = {
    {1 , 10 , 3} , {2 , 1 , 1} , {3 , 2 , 4} , {4 , 1 , 5} , {5 , 5 , 2}
};


struct Process p1;
p1.pid = 1;

printf ( "Before Sorting...\n\n" ) ;
// Print processes before sorting
printf("Process ID\tBurst Time\tPriority\n");


//get the size of the processes array
int n = sizeof processes / sizeof processes[0]; 


for(int i = 0; i<5; i++){
    printf("%d\t\t",processes[i].pid);
    printf("%d\t\t",processes[i].burstTime);
    printf("%d\n",processes[i].priority);
}

qsort ( processes , 5 , sizeof ( struct Process ) , compare ) ;
calculateTimes (processes , 5) ;

printf ( "After Sorting...\n\n" ) ;

printf("Process ID\tBurst Time\tPriority\tWait Time\tTurnaround Time\n");
for(int i = 0; i<5; i++){
    printf("%d\t\t",processes[i].pid);
    printf("%d\t\t",processes[i].burstTime);
    printf("%d\t\t",processes[i].priority);
    printf("%d\t\t",wt[i]);
    printf("%d\n",tat[i]);
}

//initialize average wait time
double avg_wt = 0;

//calculate average wait time
for(int i=0; i<5; i++){
    avg_wt = wt[i] + avg_wt;
}
avg_wt = avg_wt/n;

//Display wait time
printf("Average Wait Time: %.2f\n", avg_wt);
return 0;
}
