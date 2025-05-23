#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    float fahrenheit, celsius;

    printf("Server socket created!\n");

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket bound successfully\n");

 
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Listening to socket...\n");

  
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Accepting new connections!\n");
    printf("Connection Established\n");

    read(new_socket, buffer, BUFFER_SIZE);
    fahrenheit = atof(buffer);
    printf("Received from Client ==> %.2f\n", fahrenheit);

   
    celsius = (fahrenheit - 32) * 5 / 9;
    snprintf(buffer, BUFFER_SIZE, "%.2f", celsius);

  
    send(new_socket, buffer, strlen(buffer), 0);

    close(new_socket);
    close(server_fd);

    return 0;
}
