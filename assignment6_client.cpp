#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
  
#define PORT 8080  
#define MAXLINE 1024  
  
struct Packet {  
    int choice;  
    char text[MAXLINE];  
};  
  
int main() {  
    int sockfd;  
    struct sockaddr_in servaddr;  
  
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {  
        perror("Socket creation failed");  
        return -1;  
    }  
  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(PORT);  
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
  
    while (true) {  
        std::cout << "\n MENU\n";  
        std::cout << "1. Change Case\n";  
        std::cout << "2. Reverse String\n";  
        std::cout << "3. Exit\n";  
        std::cout << "Enter your choice (1-3): ";  
  
        Packet pkt;  
        if (!(std::cin >> pkt.choice)) break;  
        std::cin.ignore(); // Flush newline character from buffer  
  
        if (pkt.choice == 3) {  
            memset(pkt.text, 0, sizeof(pkt.text));  
            sendto(sockfd, &pkt, sizeof(pkt), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));  
            std::cout << "[CLIENT] Exiting client application.\n";  
            break;  
        }  
  
        if (pkt.choice != 1 && pkt.choice != 2) {  
            std::cout << "Invalid selection! Please choose 1, 2, or 3.\n";  
            continue;  
        }  
  
        std::cout << "Enter string: ";  
        std::string inputStr;  
        std::getline(std::cin, inputStr);  
  
        strncpy(pkt.text, inputStr.c_str(), sizeof(pkt.text) - 1);  
        pkt.text[sizeof(pkt.text) - 1] = '\0';  
  
        sendto(sockfd, &pkt, sizeof(pkt), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));  
  
        char buffer[MAXLINE];  
        socklen_t len = sizeof(servaddr);  
        int n = recvfrom(sockfd, buffer, MAXLINE - 1, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);  
        buffer[n] = '\0';  
  
        std::cout << "[CLIENT] Server Result: " << buffer << "\n";  
    }  
  
    close(sockfd);  
    return 0;  
}
