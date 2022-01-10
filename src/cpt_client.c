//
// Created by toni on 2022-03-25.
//
#include <unistd.h>
#include <stdlib.h>
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
            uint16_t first_half_channel_id = *(res->data++);
            first_half_channel_id <<= 8;
            uint16_t second_half_channel_id = *(res->data++);
            channel_id = first_half_channel_id | second_half_channel_id;

            uint16_t first_half_user_id = *(res->data++);
            first_half_user_id <<= 8;
            uint16_t second_half_user_id = *(res->data++);
            user_id = first_half_user_id | second_half_user_id;

            // Skips the msg_len for now
            res->data++;
            res->data++;
            printf("%d: %s\n", user_id, (char *) res->data);
        } else if (res->code == SEND) {
            // DO nothing
            printf("\n");
        } else {
            printf("%s\n", (char *) res->data);
        }
    }
    return NULL;
}

void login(CptRequest *request, int fd)
{
    ssize_t rc = -1;
    uint8_t *buff;
    size_t size_buf;
    uint8_t res_buff[MSG_MAX_LEN];
    CptResponse *response;
    // TODO: before serializing the packet, needs to figure out whether the input is a command
    // or just a regular text

    // TODO: response code must match request cmd
    cpt_request_msg(request, NULL);
    request->version = 3; // Version 3
    cpt_request_cmd(request, LOGIN); // SEND Message
    cpt_request_chan(request, GLOBAL_CHANNEL); // Global channel
    size_buf = get_size_for_serialized_request_buffer(request);
    buff = calloc(size_buf, sizeof(uint8_t));
    cpt_serialize_request(request, buff);

    rc = send(fd, buff, size_buf, 0);
    if (rc < 0)
    {
        perror("send() failed");
    }

    rc = recv(fd, res_buff, sizeof(res_buff), 0);
    if (rc < 0)
    {
        perror("recv() failed");
    }
    response = cpt_parse_response(res_buff, rc);
    if (response->code == LOGIN)
    {
        printf("Logged in successfully\n");
    }
    cpt_response_destroy(response);
    cpt_request_reset(request);
}
