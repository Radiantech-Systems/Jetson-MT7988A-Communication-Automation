/*
 * tcp_client.c
 *
 * MT7988A TCP Client
 * Connects to Jetson TCP Server
 * Sends boot message
 * Receives ACK
 * Sends heartbeat (PING)
 * Automatically reconnects if connection is lost
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP      "192.168.1.100"    // Change to your Jetson IP
#define SERVER_PORT    5000
#define BUFFER_SIZE    1024
#define HEARTBEAT_SEC  5

int main(void)
{
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    printf("=====================================\n");
    printf(" MT7988A TCP Client\n");
    printf("=====================================\n");

    while (1)
    {
        /* Create Socket */

        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0)
        {
            perror("socket");
            sleep(2);
            continue;
        }

        memset(&server_addr, 0, sizeof(server_addr));

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);

        if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
        {
            printf("Invalid Jetson IP Address\n");
            close(sock);
            return -1;
        }

        printf("\nConnecting to Jetson (%s)...\n", SERVER_IP);

        if (connect(sock,
                    (struct sockaddr *)&server_addr,
                    sizeof(server_addr)) < 0)
        {
            printf("Connection failed. Retrying in 2 seconds...\n");
            close(sock);
            sleep(2);
            continue;
        }

        printf("Connected to Jetson\n");

        /* Notify Boot */

        strcpy(buffer, "MT7988A_BOOT");

        send(sock,
             buffer,
             strlen(buffer),
             0);

        printf("TX : %s\n", buffer);

        while (1)
        {
            memset(buffer, 0, BUFFER_SIZE);

            int bytes = recv(sock,
                             buffer,
                             sizeof(buffer) - 1,
                             0);

            if (bytes <= 0)
            {
                printf("\nConnection Lost!\n");
                close(sock);
                break;
            }

            buffer[bytes] = '\0';

            printf("RX : %s\n", buffer);

            /* Send Heartbeat */

            sleep(HEARTBEAT_SEC);

            strcpy(buffer, "PING");

            if (send(sock,
                     buffer,
                     strlen(buffer),
                     0) < 0)
            {
                printf("Failed to send heartbeat\n");
                close(sock);
                break;
            }

            printf("TX : %s\n", buffer);
        }

        printf("Reconnecting...\n");
        sleep(2);
    }

    return 0;
}
