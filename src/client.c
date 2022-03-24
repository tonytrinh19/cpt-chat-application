#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include "cpt_builder.h"

#define SERVER_PORT     12345
#define BUFFER_LENGTH    400
#define FALSE              0
#define SERVER_NAME     "10.65.0.209"

/* Pass in 1 parameter which is either the */
/* address or host name of the server, or  */
/* set the server name in the #define      */
/* SERVER_NAME.                            */
int main(int argc, char *argv[])
{
    int    sd=-1, rc, bytesReceived;
    char   buffer[BUFFER_LENGTH];
    char   server[BUFSIZ];
    struct sockaddr_in6 serveraddr;
    struct addrinfo hints, *res;

    do
    {
        sd = socket(AF_INET6, SOCK_STREAM, 0);
        if (sd < 0)
        {
            perror("socket() failed");
            break;
        }

        if (argc > 1)
            strcpy(server, argv[1]);
        else
            strcpy(server, SERVER_NAME);

        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin6_family      = AF_INET6;
        serveraddr.sin6_port        = htons(SERVER_PORT);
        rc = inet_pton(AF_INET6, server, &serveraddr.sin6_addr.s6_addr);

        if (rc != 1)
        {
            /* The server string that was passed into the inet_pton()        */
            /* function was not a hexidecimal colon IP address.  It must     */
            /* therefore be the hostname of the server.  Use the             */
            /* getaddrinfo() function to retrieve the IP address of the      */
            /* server.                                                       */
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET6;
            hints.ai_flags = AI_V4MAPPED;
            rc = getaddrinfo(server, NULL, &hints, &res);
            if (rc != 0)
            {
                printf("Host not found! (%s)\n", server);
                perror("getaddrinfo() failed\n");
                break;
            }

            memcpy(&serveraddr.sin6_addr,
                   (&((struct sockaddr_in6 *)(res->ai_addr))->sin6_addr),
                   sizeof(serveraddr.sin6_addr));

            freeaddrinfo(res);
        }

        /********************************************************************/
        /* Use the connect() function to establish a connection to the      */
        /* server.                                                          */
        /********************************************************************/
        rc = connect(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        if (rc < 0)
        {
            perror("connect() failed");
            break;
        }

        /********************************************************************/
        /* Send 250 bytes of a's to the server                              */
        /********************************************************************/
        memset(buffer, 'a', sizeof(buffer));
        rc = send(sd, buffer, sizeof(buffer), 0);
        if (rc < 0)
        {
            perror("send() failed");
            break;
        }

        bytesReceived = 0;
        while (bytesReceived < BUFFER_LENGTH)
        {
            rc = recv(sd, & buffer[bytesReceived],
                      BUFFER_LENGTH - bytesReceived, 0);
            if (rc < 0)
            {
                perror("recv() failed");
                break;
            }
            else if (rc == 0)
            {
                printf("The server closed the connection\n");
                break;
            }
            /* Increment the number of bytes that have been received so far  */
            bytesReceived += rc;
        }

    } while (FALSE);

    /* Close down any open socket descriptors                              */
    if (sd != -1) close(sd);
    return EXIT_SUCCESS;
}