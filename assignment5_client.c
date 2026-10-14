#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define PORT 45678 
 
int main() { 
    int sock; 
    struct sockaddr_in server_addr; 
    char message[1024]; 
    char buffer[1024] = {0}; 
 
    sock = socket(AF_INET, SOCK_STREAM, 0); 
 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(PORT); 
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); 
 
    connect(sock, (struct sockaddr *)&server_addr, 
            sizeof(server_addr)); 
 
    printf("Enter message for server: "); 
    fgets(message, sizeof(message), stdin); 
 
    send(sock, message, strlen(message), 0); 
    printf("Message sent to server.\n"); 
 
    int n = recv(sock, buffer, sizeof(buffer) - 1, 0); 
    if (n > 0) { 
        buffer[n] = '\0'; 
        printf("Reply from server: %s\n", buffer); 
    } 
 
    close(sock); 
    return 0; 
}
