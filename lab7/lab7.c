// Misha Sharma: 100826646
// May Robertson: 100751769

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 4 // Number of pages
#define QUEUE_SIZE 3 // Max. size of the queue

int front = -1; // Front of the queue
int rear = -1;  // Rear of the queue
int pageFrames[QUEUE_SIZE]; // Queue to hold pages
int pageFaults = 0; // Counter for page faults

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return (rear + 1) % QUEUE_SIZE == front;
}

void enqueue(int item) {
    if (isFull()) {
        printf("Queue is full! Cannot enqueue\n");
        return;
    }
    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % QUEUE_SIZE;
    pageFrames[rear] = item;
    printf("Page inserted: %d\n", item);
}

int dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! Cannot dequeue\n");
        return -1;
    }
    int removedPage = pageFrames[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % QUEUE_SIZE;
    }
    printf("Page removed: %d\n", removedPage);
    return removedPage;
}

bool isPageHit(int pageNumber) {
    for (int i = front; i != (rear + 1) % QUEUE_SIZE; i = (i + 1) % QUEUE_SIZE) {
        if (pageFrames[i] == pageNumber) {
            return true;
        }
    }
    return false;
}

void managePageFrames(int pageNumber) {
    if (!isPageHit(pageNumber)) {
        if (isFull()) {
            dequeue();
        }
        enqueue(pageNumber);
        pageFaults++;
    }
}

int main() {
    memset(pageFrames, -1, sizeof(pageFrames)); // Initialize pageFrames with -1
    
    int pages[SIZE] = {1, 2, 3, 4}; // Example test case
    
    for (int i = 0; i < SIZE; i++) {
        managePageFrames(pages[i]);
    }
    
    printf("\nTotal number of page faults: %d\n", pageFaults);
    return 0;
}
