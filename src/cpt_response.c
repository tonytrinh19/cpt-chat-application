#include "cpt_response.h"

CptResponse * cpt_response_init(uint16_t res_code) {
    CptResponse *cpt_res_header_ptr = malloc(sizeof(CptResponse));

    if (cpt_res_header_ptr == NULL) {
        printf("malloc error: cpt_response_init()\n");
    }

    cpt_res_header_ptr->RES_CODE = (uint8_t) res_code;
    switch (res_code) {
        case 1:
            cpt_res_header_ptr->MSG = strdup("Operation was successful\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 2:
            cpt_res_header_ptr->MSG = strdup("The channel id is in the CHAN_ID, msg contents are a message sub-packet\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 3:
            cpt_res_header_ptr->MSG = strdup("User connected\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 4:
            cpt_res_header_ptr->MSG = strdup("User is currently disconnected\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 5:
            cpt_res_header_ptr->MSG = strdup("Message could not be delivered\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 6:
            cpt_res_header_ptr->MSG = strdup("Channel created\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 7:
            cpt_res_header_ptr->MSG = strdup("Channel cannot be created\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 8:
            cpt_res_header_ptr->MSG = strdup("Channel is destroyed\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 9:
            cpt_res_header_ptr->MSG = strdup("NEW client joins the channel\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 10:
            cpt_res_header_ptr->MSG = strdup("User leaves the channel\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 11:
            cpt_res_header_ptr->MSG = strdup("Current users (Get Users)\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 12:
            cpt_res_header_ptr->MSG = strdup("Unknown command error\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 13:
            cpt_res_header_ptr->MSG = strdup("Login failed error\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 14:
            cpt_res_header_ptr->MSG = strdup("Unknown channel ID error\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 15:
            cpt_res_header_ptr->MSG = strdup("Bad CPT Version number error\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 16:
            cpt_res_header_ptr->MSG = strdup("Message failed to send\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 17:
            cpt_res_header_ptr->MSG = strdup("Channel ID exceeds limit\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 18:
            cpt_res_header_ptr->MSG = strdup("Message size too big\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 19:
            cpt_res_header_ptr->MSG = strdup("Message length too big\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 20:
            cpt_res_header_ptr->MSG = strdup("No users in channel\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 21:
            cpt_res_header_ptr->MSG = strdup("Given ID is invalid for any reason\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 22:
            cpt_res_header_ptr->MSG = strdup("Access to resources is forbidden\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 23:
            cpt_res_header_ptr->MSG = strdup("Server at maximum capacity\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 255:
            cpt_res_header_ptr->MSG = strdup("Reserved for future CMDs\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
        default:
            cpt_res_header_ptr->MSG = strdup("Server res_code undefined\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
    }

    return cpt_res_header_ptr;
}


void cpt_response_destroy(CptResponse * response) {
    cpt_response_reset(response);
    free(response);
}


void cpt_response_reset(CptResponse * response) {
    free(response->MSG);
    response->MSG      = NULL;
    response->MSG_LEN  = 0;
    response->RES_CODE = 0;
}


CptMsgResponse * cpt_msg_response_init(uint8_t * msg, uint16_t chan_id, uint16_t user_id) {
    CptMsgResponse *cpt_res_msg_ptr = malloc(sizeof(CptMsgResponse));

    char* msg_ptr;
    msg_ptr = (char*) msg;
    printf("cpt_msg_response_init() : msg = %s\n", msg_ptr);

    if (cpt_res_msg_ptr == NULL) {
        printf("malloc error: cpt_msg_response_init()\n");
    }
    cpt_res_msg_ptr->CHANNEL_ID = chan_id;
    cpt_res_msg_ptr->USER_ID    = user_id;
    cpt_res_msg_ptr->MSG        = strdup(msg_ptr); // ?
    cpt_res_msg_ptr->MSG_LEN    = (uint16_t) strlen(cpt_res_msg_ptr->MSG);

    return cpt_res_msg_ptr;
}


void cpt_msg_response_destroy(CptMsgResponse * msg_res) {
    free(msg_res->MSG);
    msg_res->MSG         = NULL;
    msg_res->MSG_LEN     = 0;
    msg_res->USER_ID     = 0;
    msg_res->CHANNEL_ID  = 0;
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

    char* string = malloc(sizeof(char) * 56 + req->msg_len + 1);

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

    return 64 + req->msg_len;
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
 * Handle a received 'LOGIN' protocol message.
 *
 * Use information in the CptRequest to handle
 * a LOGIN protocol message from a connected client.
 * If successful, the protocol request will be fulfilled,
 * updating any necessary information contained within
 * <server_info>.
 *
 * @param server_info   Server data structures and information.
 * @param name          Name of user in received Packet MSG field.
 * @return              1 if successful, error code on failure.
 */
int cpt_login_response(void* server_info, char* name) {

}



