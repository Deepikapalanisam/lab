#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <math.h>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

void func(SOCKET sockfd);

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. Error Code : %d\n", WSAGetLastError());
        return -1;
    }

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return -1;
    } else {
        printf("Socket created successfully\n");
    }

    // Set up server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("Connection failed\n");
        closesocket(sockfd);
        WSACleanup();
        return -1;
    } else {
        printf("Connected to server\n");
        func(sockfd);  // Send data and receive result
    }

    // Cleanup
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET sockfd) {
    int numbers[2];
    float result;

    // Prompt user for numbers
    printf("Enter base and exponent: ");
    scanf("%d %d", &numbers[0], &numbers[1]);

    // Send numbers to server
    send(sockfd, (char*)&numbers, sizeof(numbers), 0);

    // Receive result from server
    recv(sockfd, (char*)&result, sizeof(result), 0);
    printf("Result: %.2f\n", result);
}
