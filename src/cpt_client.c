//
// Created by toni on 2022-03-25.
//
#include "cpt_client.h"
#include "cpt_response.h"
#include "common.h"

size_t get_size_for_serialized_request_buffer(const CptRequest *request) {
    size_t num = 6;
    num += request->msg_len;
    return num;
}


