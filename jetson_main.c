/*
 * main.c
 *
 * Jetson AGX Orin TCP Server
 * Waits for MT7988A client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    char buffer[BUFFER_SIZE];

    /* Create Socket */

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Socket");
        return -1;
    }

    /* Allow Port Reuse */

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /* Configure Server */

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
    {
        perror("Bind");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 1) < 0)
    {
        perror("Listen");
        close(server_fd);
        return -1;
    }

    printf("\n=====================================\n");
    printf(" Jetson TCP Server Started\n");
    printf(" Listening on Port %d\n", PORT);
    printf(" Waiting for MT7988A...\n");
    printf("=====================================\n\n");

    while (1)
    {
        client_fd = accept(server_fd,
                           (struct sockaddr *)&client_addr,
                           &client_len);

        if (client_fd < 0)
        {
            perror("Accept");
            continue;
        }

        printf("MT7988A Connected\n");

        while (1)
        {
            memset(buffer, 0, BUFFER_SIZE);

            int bytes = recv(client_fd,
                             buffer,
                             BUFFER_SIZE,
                             0);

            if (bytes <= 0)
            {
                printf("Client Disconnected\n\n");
                close(client_fd);
                break;
            }

            printf("RX : %s\n", buffer);

            /* Automatic Reply */

            if (strcmp(buffer, "MT7988A_BOOT") == 0)
            {
                send(client_fd,
                     "JETSON_ACK",
                     strlen("JETSON_ACK"),
                     0);

                printf("TX : JETSON_ACK\n");
            }
            else if (strcmp(buffer, "PING") == 0)
            {
                send(client_fd,
                     "PONG",
                     strlen("PONG"),
                     0);

                printf("TX : PONG\n");
            }
            else
            {
                send(client_fd,
                     "MESSAGE_RECEIVED",
                     strlen("MESSAGE_RECEIVED"),
                     0);

                printf("TX : MESSAGE_RECEIVED\n");
            }
        }
    }

    close(server_fd);

    return 0;
}
