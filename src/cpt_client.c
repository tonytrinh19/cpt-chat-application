//
// Created by toni on 2022-03-25.
//
#include "cpt_client.h"
#include "cpt_response.h"
#include "common.h"

size_t get_size_for_serialized_request_buffer(const CptRequest *request)
{
    size_t num = 6;
    num += request->msg_len;
    return num;
}

void login(CptRequest *request, int sd)
{
    int rc;
    size_t size_buf     = get_size_for_serialized_request_buffer(request);
    uint8_t *buff       = calloc(size_buf, sizeof(uint8_t));
    request->cmd_code   = LOGIN;
    request->version    = 3;
    request->channel_id = GLOBAL_CHANNEL;
    cpt_serialize_request(request, buff);
    rc = send(sd, buff, size_buf, 0);
    if (rc < 0)
    {
        perror("send() failed");
    }
    cpt_request_reset(request);
    free(buff);
}


