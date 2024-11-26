#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <math.h>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

void func(SOCKET confd);

int main() {
    WSADATA wsaData;
    SOCKET sockfd, confd;
    struct sockaddr_in servaddr, cliaddr;
    int len = sizeof(cliaddr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. Error Code : %d\n", WSAGetLastError());
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return -1;
    } else {
        printf("Socket created successfully\n");
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(sockfd);
        WSACleanup();
        return -1;
    } else {
        printf("Bind successful\n");
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(sockfd);
        WSACleanup();
        return -1;
    } else {
        printf("Server listening on port 43451\n");
    }

    // Accept incoming connection
    confd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (confd == INVALID_SOCKET) {
        printf("Accept failed\n");
        closesocket(sockfd);
        WSACleanup();
        return -1;
    } else {
        printf("Server accepted connection\n");
        func(confd);  // Handle the client request
    }

    // Cleanup
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET confd) {
    int numbers[2];
    float result;

    // Receive base and exponent
    recv(confd, (char*)&numbers, sizeof(numbers), 0);
    printf("Received base: %d, exponent: %d\n", numbers[0], numbers[1]);

    // Calculate power
    result = pow(numbers[0], numbers[1]);
    send(confd, (char*)&result, sizeof(result), 0);
    printf("Result sent: %.2f\n", result);
}
