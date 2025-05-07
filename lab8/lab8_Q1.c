#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netdb.h>

// Question 1: File Processing
void fileToString(char fileName[], char buffer[], int bufferSize) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    char line[bufferSize];
    int lineCount = 0;
    while (fgets(line, bufferSize, file) != NULL) {
        lineCount++;
        if (lineCount == 2) {
            strcpy(buffer, line);
            printf("%s\n", buffer);
            break;
        }
    }
    fclose(file);
}

int countString(const char *buffer) {
    int count = 0;
    const char *temp = buffer;
    while ((temp = strstr(temp, "Canada")) != NULL) {
        count++;
        temp += strlen("Canada");
    }
    return count;
}

int main() {
    char fileName[] = "File_National_Anthem_of_Canada.txt";
    char buffer[1024];
    printf("\nReading the Second line from the file...\n");
    printf("*******************************************\n");
    fileToString(fileName, buffer, 1024);
    printf("\nNumber of times Canada appeared in the Second line: %d\n\n", countString(buffer));
    return 0;
}
