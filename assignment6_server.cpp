#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
  
#define PORT 8080  
#define MAXLINE 1024  
  
// Data structure to hold menu choice and message payload  
struct Packet {  
    int choice;  
    char text[MAXLINE];  
};  
  
// Function to change case (Uppercase <-> Lowercase)  
std::string changeCase(std::string str) {  
    for (char &c : str) {  
        if (std::isupper(c)) c = std::tolower(c);  
        else if (std::islower(c)) c = std::toupper(c);  
    }  
    return str;  
}  
  
// Function to reverse the string  
std::string reverseString(std::string str) {  
    std::reverse(str.begin(), str.end());  
    return str;  
}  
  
int main() {  
    int sockfd;  
    struct sockaddr_in servaddr, cliaddr;  
  
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {  
        perror("Socket creation failed");  
        return -1;  
    }  
  
    memset(&servaddr, 0, sizeof(servaddr));  
    memset(&cliaddr, 0, sizeof(cliaddr));  
  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = INADDR_ANY;  
    servaddr.sin_port = htons(PORT);  
  
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {  
        perror("Bind failed");  
        return -1;  
    }  
  
    std::cout << "[SERVER] UDP Server running on port " << PORT << "...\n";  
  
    while (true) {  
        Packet pkt;  
        socklen_t len = sizeof(cliaddr);  
  
        int n = recvfrom(sockfd, &pkt, sizeof(pkt), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);  
        if (n <= 0) continue;  
  
        if (pkt.choice == 3) {  
            std::cout << "[SERVER] Client requested exit. Closing connection.\n";  
            std::string exitMsg = "Session ended by server.";  
            sendto(sockfd, exitMsg.c_str(), exitMsg.length(), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);  
            break;  
        }  
  
        std::cout << "[SERVER] Choice Received: " << pkt.choice  
        << " | Input Text: \"" << pkt.text << "\"\n";  
  
        std::string result;  
        if (pkt.choice == 1) {  
            result = changeCase(pkt.text);  
        } else if (pkt.choice == 2) {  
            result = reverseString(pkt.text);  
        } else {  
            result = "Invalid Option";  
        }  
  
        sendto(sockfd, result.c_str(), result.length(), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);  
    }  
  
    close(sockfd);  
    return 0;  
}
