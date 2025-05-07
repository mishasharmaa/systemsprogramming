/**
 * Systems Programming Assignment 2
 * 2025-03-24
 * Group 19
 * Andrew Hunter, Misha Sharma, Zach Frank
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>

// The maximum length one directory or file name can be in the path.
#define MAX_NAME_LENGTH 64

// The log file. A global variable is used so it doesn't need to be passed around
// to every function.
FILE* logFile = NULL;

// Print a formated string to the console and to the log file.
void logString(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    // If the log file isn't open don't write to it.
    if (logFile == NULL) {
        return;
    }
    // The va_list has to be reinitialized so it can be used again.
    va_start(args, format);
    vfprintf(logFile, format, args);
    va_end(args);
}

// If an OS error occurs print it out and exit the program.
void exitOnError() {
    // The error for a file already existing is ignored as we create duplicate
    // directories a lot and this error is not a problem.
    if (errno != 0 && errno != EEXIST) {
        logString("Error: %s\n", strerror(errno));
        exit(1);
    }
    errno = 0;
}

// Read the given file into array until ','.
// Prints an error and exits if the string is empty, greater than MAX_NAME_LENGTH
// or a newline or EOF is encountered after some other characters.
//
// Returns true if it is successful or false if a newline or EOF is encountered
// as the first character.
bool readInto(FILE* file, char* array) {
    for (int i = 0; i < MAX_NAME_LENGTH - 1; ++i) {
        char c = fgetc(file);
        if (c == EOF || c == '\n') {
            if (i == 0) {
                // If the first character is an EOF or newline it might not
                // be an error (at the end of the file) so return instead.
                return false;
            }
            logString("Error: Incomplete file name\n");
            exit(1);
        }

        if (c == ',') {
            if (i == 0) {
                logString("Error: string is empty\n");
                exit(1);
            }

            // Insert the NULL terminator to indicate the end of the string.
            array[i] = '\0';
            return true;
        }

        array[i] = c;
    }

    logString("Error: string is too long\n");
    exit(1);
}

// Append 'nextPart'/ to the end of 'directory' and create a directory by that
// name. 'offset' is the length of 'directory'.
void makeDirectory(char* directory, int* offset, char* nextPart) {
    *offset += sprintf(directory + *offset, "%s/", nextPart);
    logString("creating directory %s\n", directory);
    mkdir(directory, 0770);
    exitOnError();
}

// Append 'profile'.txt to the end of directory and create the profile file at
// that path. Set the file to readonly.
// 'offset' is the length of 'directory', 'strTime' is a string representation of
// the current time.
void makeProfileFile(char* directory, int offset, char* profile, char* username, char* strTime) {
    sprintf(directory + offset, "%s.txt", profile);

    logString("creating profile file %s\n", directory);
    FILE* profileFile = fopen(directory, "w");
    exitOnError();

    fprintf(profileFile, "%s profile created on %s\n", username, strTime);
    fclose(profileFile);

    logString("setting profile file permissions %s\n", directory);
    chmod(directory, 0440);
    exitOnError();
}

int main(int argc, char** argv) {
    // Open log file
    logFile = fopen("log.txt", "w");
    exitOnError();

    // Open text file with the directory structure.
    FILE* inputFile = fopen("input.txt", "r");
    exitOnError();

    // Get the current time and print it formated into a string.
    time_t currentTime = time(NULL);
    struct tm* local = localtime(&currentTime);
    char strTime[64];
    strftime(strTime, 64, "%c", local);
    
    while (!feof(inputFile)) {
        char usertype[MAX_NAME_LENGTH];
        char username[MAX_NAME_LENGTH];
        char home[MAX_NAME_LENGTH];
        char profile[MAX_NAME_LENGTH];

        // Read the usertype
        // and check if the line starts with EOF or newline.
        if (!readInto(inputFile, usertype)) {
            continue;
        }

        // Read the rest of the directory names and a newline character.
        // If any part is incomplete or missing then an error will be printed
        // and the program exited.
        if (!(readInto(inputFile, username)
            && readInto(inputFile, home)
            && readInto(inputFile, profile)
            && fgetc(inputFile) == '\n')
        ) {
            logString("Error: Incorrect input file format\n");
            exit(1);
        }

        // The directory and file name is built up in 'directory'.
        char directory[MAX_NAME_LENGTH * 4 + 4];
        int offset = 0;
        // Create all the directories for this user.
        makeDirectory(directory, &offset, usertype);
        makeDirectory(directory, &offset, username);
        makeDirectory(directory, &offset, home);

        // Make the profile file for this user.
        makeProfileFile(directory, offset, profile, username, strTime);
    }

    fclose(inputFile);
    fclose(logFile);
    return 0;
}

