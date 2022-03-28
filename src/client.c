#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "cpt_request_builder.h"

#define SERVER_PORT     8000
#define BUFFER_LENGTH    400
#define FALSE              0
#define TRUE               1
#define MSG_MAX_LEN     65536
#define SERVER_NAME     "10.65.14.202"
// 10.0.0.169
// school: 10.65.0.209, 10.65.15.72

static size_t get_size_for_serialized_request_buffer(const CptRequest *request) {
    size_t num = 6;
    num += request->msg_len;
    return num;
}

struct items {
    int sd;
    int count;
};

static void *listeningThread(void *args) {
    struct items *items = (struct items *) args;
    if (items->count == 0) {
        while (TRUE) {
            char buffer[BUFFER_LENGTH];
            int rc;
            rc = recv(items->sd, buffer,
                      sizeof(buffer), 0);
            if (rc < 0) {
                perror("recv() failed");
            } else if (rc == 0) {
                printf("The server closed the connection\n");
            }
            buffer[rc] = '\0';
            printf("RECEIVED: %s\n", buffer);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int sd = -1, rc, bytesReceived;
    char buffer[BUFFER_LENGTH];
    char server[BUFSIZ];
    struct sockaddr_in6 serveraddr;
    struct addrinfo hints, *res;
    pthread_t thread_id;
    CptRequest *request = cpt_request_init();
    int once = 0;

    do {
        sd = socket(AF_INET6, SOCK_STREAM, 0);
        if (sd < 0) {
            perror("socket() failed");
            break;
        }

        struct items items;
        items.count = once;
        items.sd = sd;

        if (argc > 1)
            strcpy(server, argv[1]);
        else
            strcpy(server, SERVER_NAME);

        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin6_family = AF_INET6;
        serveraddr.sin6_port = htons(SERVER_PORT);
        rc = inet_pton(AF_INET6, server, &serveraddr.sin6_addr.s6_addr);

        if (rc != 1) {
            /* The server string that was passed into the inet_pton()        */
            /* function was not a hexidecimal colon IP address.  It must     */
            /* therefore be the hostname of the server.  Use the             */
            /* getaddrinfo() function to retrieve the IP address of the      */
            /* server.                                                       */
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET6;
            hints.ai_flags = AI_V4MAPPED;
            rc = getaddrinfo(server, NULL, &hints, &res);
            if (rc != 0) {
                printf("Host not found! (%s)\n", server);
                perror("getaddrinfo() failed\n");
                break;
            }

            memcpy(&serveraddr.sin6_addr,
                   (&((struct sockaddr_in6 *) (res->ai_addr))->sin6_addr),
                   sizeof(serveraddr.sin6_addr));

            freeaddrinfo(res);
        }

        /********************************************************************/
        /* Use the connect() function to establish a connection to the      */
        /* server.                                                          */
        /********************************************************************/
        rc = connect(sd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
        if (rc < 0) {
            perror("connect() failed");
            break;
        }

        // Create a thread to listen to server's messages
        pthread_create(&thread_id, NULL, listeningThread, (void *) &items);

        // Take input from client and send it to the server
        request->version = 13;
        request->cmd_code = 100;
        request->channel_id = 25739;
        char message[MSG_MAX_LEN];
        ssize_t message_len;
        message_len = read(STDIN_FILENO, message, MSG_MAX_LEN);
        message[message_len] = '\0';
        cpt_request_msg(request, message);


        size_t size_buf = get_size_for_serialized_request_buffer(request);
        uint8_t *buff = calloc(size_buf, sizeof(uint8_t));
        size_t size = cpt_serialize_request(request, buff);

        // * sizeof(uint8_t)
        rc = send(sd, buff, size_buf, 0);
        if (rc < 0) {
            perror("send() failed");
            break;
        }


        bytesReceived = 0;
        // BUFFER_LENGTH
//        while (bytesReceived < (int) size_buf)
//        {
// buffer[bytesReceived]

//            /* Increment the number of bytes that have been received so far  */
//            bytesReceived += rc;
        cpt_request_reset(request);
        close(sd);
        free(buff);
        once++;
    } while (TRUE);

    cpt_request_destroy(request);
    /* Close down any open socket descriptors                              */
    if (sd != -1) close(sd);
    return EXIT_SUCCESS;
}
