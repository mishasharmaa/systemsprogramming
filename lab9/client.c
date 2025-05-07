#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};
    
    if (argc != 2) {
        printf("Usage: %s <temperature in Fahrenheit>\n", argv[0]);
        return 1;
    }

    float fahrenheit = atof(argv[1]);

    printf("Client socket initialized!\n");

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    
    // Convert IPv4 address
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        return 1;
    }
    printf("Connection established\n");


    snprintf(buffer, BUFFER_SIZE, "%.2f", fahrenheit);
    send(sock, buffer, strlen(buffer), 0);
    printf("Temperature %.2f sent to server for conversion into Celsius...\n", fahrenheit);

   
    read(sock, buffer, BUFFER_SIZE);
    printf("Received from Server after conversion ==> %.2f\n", buffer);

   
    close(sock);

    return 0;
}
