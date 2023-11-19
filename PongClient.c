#include <GL/glfw3.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int clientSocket;
#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"


void initializeClient() {
    struct sockaddr_in serverAddr;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Failed to initialize Winsock");
        exit(EXIT_FAILURE);
    }

    // Criar socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    // Converter o endereço IP para formato binário
    if (inet_addr(SERVER_IP) == INADDR_NONE) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Conectar ao servidor
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection Failed");
        fprintf(stderr, "Error code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");
}
