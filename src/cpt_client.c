//
// Created by toni on 2022-03-25.
//
#include "cpt_client.h"
#include "cpt_response.h"

size_t get_size_for_serialized_request_buffer(const CptRequest *request) {
    size_t num = 6;
    num += request->msg_len;
    return num;
}

void *listeningThread(void *args) {
    int *sd = (int *) args;
    uint16_t channel_id;
    uint16_t user_id;
    while (TRUE) {
        size_t rc;
        uint8_t buffer[MSG_MAX_LEN];
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

        CptResponse *res = cpt_parse_response(buffer, rc);
        if (res == NULL) {
            printf("Something went wrong with the server\n");
            break;
        }

        if (res->code == MESSAGE) {
            uint16_t first_half_channel_id = res->data->channel_id;
            first_half_channel_id <<= 8;
            uint16_t second_half_channel_id = res->data->channel_id;
            channel_id = first_half_channel_id | second_half_channel_id;

            uint16_t first_half_user_id = res->data->user_fd;
            first_half_user_id <<= 8;
            uint16_t second_half_user_id = res->data->user_fd;
            user_id = first_half_user_id | second_half_user_id;

            // Skips the msg_len for now
            res->data->msg++;
            res->data->msg++;
            printf("%d: %d\n", user_id, res->data->user_fd);
        } else if (res->code == SUCCESS) {
            // DO nothing
            printf("\n");
        } else {
            printf("%s\n", (char *) res->data);
        }
    }
    return NULL;
}
