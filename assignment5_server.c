#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define PORT 45678 
 
int main() { 
    int server_socket, client_socket; 
    struct sockaddr_in server_addr; 
    char buffer[1024] = {0}; 
 
    server_socket = socket(AF_INET, SOCK_STREAM, 0); 
 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT); 
 
    bind(server_socket, (struct sockaddr *)&server_addr, 
         sizeof(server_addr)); 
 
    listen(server_socket, 1); 
    printf("Server is listening...\n"); 
    fflush(stdout); 
 
    client_socket = accept(server_socket, NULL, NULL); 
 
    int n = recv(client_socket, buffer, sizeof(buffer) - 1, 0); 
    if (n > 0) { 
        buffer[n] = '\0'; 
        buffer[strcspn(buffer, "\r\n")] = '\0'; 
        printf("Message received: %s\n", buffer); 
 
        char reply[] = "Hello Client! Message received successfully."; 
        send(client_socket, reply, strlen(reply), 0); 
    } 
 
    close(client_socket); 
    close(server_socket); 
    return 0; 
}
