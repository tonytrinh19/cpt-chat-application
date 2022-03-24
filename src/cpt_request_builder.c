//
// Created by toni on 2022-03-23.
//

#include <stdlib.h>
#include <string.h>
#include "cpt_request_builder.h"
#define VERSION_MAX 15
#define VERSION_MIN 0

CptRequest * cpt_request_init()
{
    CptRequest * request = calloc(1, sizeof(CptRequest));
    request->version      = 0;
    request->cmd_code     = 0;
    request->channel_type = 0;
    request->channel_id   = 0;
    request->msg_len      = 0;
    request->msg          = NULL;
    return request;
}

void cpt_request_destroy(CptRequest * request)
{
    request->version      = 0;
    request->cmd_code     = 0;
    request->channel_type = 0;
    request->channel_id   = 0;
    request->msg_len      = 0;
    if (request->msg)
    {
        free(request->msg);
    }
    request->msg = NULL;
    free(request);
}


void cpt_request_version(CptRequest * cpt, uint8_t version_major, uint8_t version_minor)
{
    uint8_t version = 0;
    if (version_minor < VERSION_MIN || version_major < VERSION_MIN || version_minor > VERSION_MAX || version_major > VERSION_MAX)
    {
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

void cpt_request_cmd(CptRequest * cpt, uint8_t cmd)
{
    cpt->cmd_code = cmd;
}

void cpt_request_len(CptRequest * cpt, uint16_t msg_len)
{
    cpt->msg_len = msg_len;
}

void cpt_request_chan(CptRequest * cpt, uint16_t channel_id)
{
    cpt->channel_id = channel_id;
}

void cpt_request_msg(CptRequest * cpt, char * msg)
{
    cpt->msg     = strdup(msg);
    cpt_request_len(cpt, (uint16_t) strlen(cpt->msg));
}

void cpt_request_reset(CptRequest * packet)
{
    packet->version      = 0;
    packet->cmd_code     = 0;
    packet->channel_type = 0;
    packet->channel_id   = 0;
    packet->msg_len      = 0;
    packet->msg          = NULL;
}
