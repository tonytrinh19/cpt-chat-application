//
// Created by toni on 2022-03-25.
//
#include "cpt_client.h"

size_t get_size_for_serialized_request_buffer(const CptRequest *request) {
    size_t num = 6;
    num += request->msg_len;
    return num;
}

void *listeningThread(void *args) {
    int *sd = (int *) args;
    while (TRUE) {
        char buffer[MSG_MAX_LEN];
        int rc;
        rc = recv(*sd, buffer,
                  sizeof(buffer), 0);
        if (rc < 0) {
            perror("recv() failed");
            break;
        } else if (rc == 0) {
            printf("The server closed the connection\n");
            break;
        }
        buffer[rc] = '\0';
        printf("%s\n", buffer);
    }

    return NULL;
}
