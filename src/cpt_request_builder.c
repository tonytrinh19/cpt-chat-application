//
// Created by toni on 2022-03-23.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cpt_request_builder.h"

#define VERSION_MAX 15
#define VERSION_MIN 0
#define UINT16TOUINT8 255

CptRequest *cpt_request_init() {
    CptRequest *request = calloc(1, sizeof(CptRequest));
    request->version = 0;
    request->cmd_code = 0;
    request->channel_id = 0;
    request->msg_len = 0;
    request->msg = NULL;
    return request;
}

void cpt_request_destroy(CptRequest *request) {
    request->version = 0;
    request->cmd_code = 0;
    request->channel_id = 0;
    request->msg_len = 0;
    if (request->msg) {
        free(request->msg);
    }
    request->msg = NULL;
    free(request);
}


void cpt_request_version(CptRequest *cpt, uint8_t version_major, uint8_t version_minor) {
    uint8_t version = 0;
    if (version_minor < VERSION_MIN || version_major < VERSION_MIN || version_minor > VERSION_MAX ||
        version_major > VERSION_MAX) {
        version_minor = 0;
        version_major = 0;
    }

    // Shifts left by 4
    version = version_major;
    version <<= 4;
    // append major and minor
    version |= version_minor;
    cpt->version = version;
}

void cpt_request_cmd(CptRequest *cpt, const uint8_t cmd) {
    cpt->cmd_code = cmd;
}

void cpt_request_len(CptRequest *cpt, const uint16_t msg_len) {
    cpt->msg_len = msg_len;
}

void cpt_request_chan(CptRequest *cpt, const uint16_t channel_id) {
    cpt->channel_id = channel_id;
}

void cpt_request_msg(CptRequest *cpt, const char *msg) {
    cpt->msg = strdup(msg);
    cpt_request_len(cpt, (uint16_t) strlen(cpt->msg));
}

void cpt_request_reset(CptRequest *packet) {
    packet->version = 0;
    packet->cmd_code = 0;
    packet->channel_id = 0;
    packet->msg_len = 0;
    packet->msg = NULL;
}

size_t cpt_serialize_request(const CptRequest *req, uint8_t *buffer) {
    // Count starts with 6 because there are at least 6 uint8_t values in the buffer
    // version + 1, cmd_code + 1, chan_id and chan_type + 2, msg_len + 2
    size_t count = 6;
    uint8_t *msg = (uint8_t *) req->msg;
    // Saves the beginning of the buffer.
    uint8_t *temp = buffer;

    *(buffer++) = req->version;
    *(buffer++) = req->cmd_code;

    uint16_t first_half_channel_id = req->channel_id;
    uint16_t second_half_channel_id = first_half_channel_id & UINT16TOUINT8;
    // Shifts the number 8 bits to the right to get the leftmost 8 bits
    first_half_channel_id >>= 8;

    *(buffer++) = (uint8_t) first_half_channel_id;
    *(buffer++) = (uint8_t) second_half_channel_id;

    uint16_t first_half_msg_len = req->msg_len;
    uint16_t second_half_msg_len = first_half_msg_len & UINT16TOUINT8;
    // Shifts the number 8 bits to the right to get the leftmost 8 bits
    first_half_msg_len >>= 8;

    *(buffer++) = (uint8_t) first_half_msg_len;
    *(buffer++) = (uint8_t) second_half_msg_len;

    for (int i = 0; i < req->msg_len; ++i) {
        *(buffer++) = *msg++;
        count++;
    }

    return count;
}

CptRequest *cpt_parse_request(uint8_t *req_buf, int size) {
    CptRequest *req = calloc((unsigned long) size, sizeof(uint8_t));
    // parse the packet back to the request.
    req->version = *(req_buf++);
    req->cmd_code = *(req_buf++);

    uint16_t first_half_channel_id = *(req_buf++);
    first_half_channel_id <<= 8;
    uint16_t second_half_channel_id = *(req_buf++);
    uint16_t stuff = first_half_channel_id | second_half_channel_id;
    req->channel_id = stuff;

    uint16_t first_half_msg_len = *(req_buf++);
    first_half_channel_id <<= 8;
    uint16_t second_half_msg_len = *(req_buf++);
    uint16_t stuff2 = first_half_msg_len | second_half_msg_len;
    req->msg_len = stuff2;

    req->msg = calloc(req->msg_len, sizeof(char));


    for (int i = 0; i < req->msg_len; ++i) {
        req->msg[i] = (char) *(req_buf++);
    }

    return req;
}
