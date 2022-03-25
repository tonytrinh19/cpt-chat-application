#include "cpt_response.h"

CptResponse * cpt_response_init(uint16_t res_code) {
    CptResponse *cpt_res = malloc(sizeof(CptResponse));

    if (cpt_res == NULL) {
        printf("malloc error: cpt_response_init()\n");
    }

    cpt_res->code = (uint8_t) res_code;

    return cpt_res;
}


void cpt_response_destroy(CptResponse * response) {
    cpt_response_reset(response);
    free(response);
    response = NULL;
}


void cpt_response_reset(CptResponse * response) {
    response->code = 0;
    free(response->data);
    response->data = NULL;
}


CptMsgResponse * cpt_msg_response_init(uint8_t * msg, uint16_t chan_id, uint16_t user_id) {
    CptMsgResponse *cpt_msg_res = malloc(sizeof(CptMsgResponse));
    if (cpt_msg_res == NULL) {
        printf("malloc error: cpt_msg_response_init()\n");
        return NULL;
    }

    cpt_msg_res->channel_id = chan_id;
    cpt_msg_res->user_id    = user_id;
    cpt_msg_res->msg        = (uint8_t *)strdup((char*)msg); // ?
    cpt_msg_res->msg_len    = (uint16_t) strlen((char*)cpt_msg_res->msg);

    return cpt_msg_res;
}


void cpt_msg_response_destroy(CptMsgResponse * msg_res) {
    free(msg_res->msg);
    msg_res->msg         = NULL;
    msg_res->msg_len     = 0;
    msg_res->user_id     = 0;
    msg_res->channel_id  = 0;
    free(msg_res);
}


size_t cpt_serialize_response(CptRequest * req, uint8_t * buffer) {
    char* binary_version = to_binary_string_8(req->version);
    char* binary_cmd_code = to_binary_string_8(req->cmd_code);
    char* binary_channel_id = to_binary_string_16(req->channel_id);
    char* binary_msg_len = to_binary_string_16(req->msg_len);

    char* version_ptr = strdup(binary_version);
    char* cmd_code_ptr = strdup(binary_cmd_code);
    char* channel_id_ptr = strdup(binary_channel_id);
    char* msg_len_ptr = strdup(binary_msg_len);

    char* string = malloc(sizeof(char) * 48 + req->msg_len);

    strcat(string, version_ptr);
    strcat(string, cmd_code_ptr);
    strcat(string, channel_id_ptr);
    strcat(string, msg_len_ptr);
    strcat(string, req->msg);

    free(binary_version);
    free(binary_cmd_code);
    free(binary_channel_id);
    free(binary_msg_len);
    free(version_ptr);
    free(cmd_code_ptr);
    free(channel_id_ptr);
    free(msg_len_ptr);

    buffer = (uint8_t *) strdup(string);
//    printf("%s", buffer);

    return 6 + req->msg_len;
}



char* to_binary_string_8(uint8_t number) {
    int num_bits = 8;
    char *string = malloc(num_bits + 1);

    for (int i = num_bits - 1; i >= 0; i--) {
        string[i] = (number & 1) + '0';
        number >>= 1;
    }
    string[num_bits] = '\0';
    return string;
}


char* to_binary_string_16(uint16_t number) {
    int num_bits = 16;
    char *string = malloc(num_bits + 1);

    for (int i = num_bits - 1; i >= 0; i--) {
        string[i] = (number & 1) + '0';
        number >>= 1;
    }
    string[num_bits] = '\0';
    return string;
}


/**
 * @brief Parse serialized server response.
 *
 * @param response  Address to a CptResponse object.
 * @param buffer    Serialized response from server.
 * @return Pointer to filled CptResponse.
 */
CptResponse * cpt_parse_response(uint8_t * res_buf, size_t data_size) {
    CptResponse *cpt_res;

}




