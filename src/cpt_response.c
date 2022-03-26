#include "cpt_response.h"

CptResponse * cpt_response_init(uint16_t res_code) {
    CptResponse *cpt_res = malloc(sizeof(CptResponse));

    if (cpt_res == NULL) {
        printf("malloc error: cpt_response_init()\n");
    }


    cpt_res->code = (uint8_t) res_code;

    switch (res_code) {
        case SUCCESS:    // 1
            cpt_res->data = (uint8_t *) strdup("Operation was successful\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case MESSAGE:    // 2
            cpt_res->data = (uint8_t *) strdup(
                    "The channel id is in the CHAN_ID, msg contents are a message sub-packet\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case USER_CONNECTED:    // 3
            cpt_res->data = (uint8_t *) strdup("User connected\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case USER_DISCONNECTED: // 4
            cpt_res->data = (uint8_t *) strdup("User is currently disconnected\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case MESSAGE_FAILED:    // 5
            cpt_res->data = (uint8_t *) strdup("Message could not be delivered\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case CHANNEL_CREATED:   // 6
            cpt_res->data = (uint8_t *) strdup("Channel created\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case CHANNEL_CREATION_ERROR:    //7
            cpt_res->data = (uint8_t *) strdup("Channel cannot be created\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case CHANNEL_DESTROYED:    //8
            cpt_res->data = (uint8_t *) strdup("Channel is destroyed\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case USER_JOINED_CHANNEL:   // 9
            cpt_res->data = (uint8_t *) strdup("NEW client joins the channel\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case USER_LEFT_CHANNEL:     // 10
            cpt_res->data = (uint8_t *) strdup("User leaves the channel\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case USER_LIST:     // 11
            cpt_res->data = (uint8_t *) strdup("Current users (Get Users)\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case UKNOWN_CMD:    // 12
            cpt_res->data = (uint8_t *) strdup("Unknown command error\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case LOGIN_FAIL:    // 13
            cpt_res->data = (uint8_t *) strdup("Login failed error\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case UKNOWN_CHANNEL:    // 14
            cpt_res->data = (uint8_t *) strdup("Unknown channel ID error\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case BAD_VERSION:    // 15
            cpt_res->data = (uint8_t *) strdup("Bad CPT Version number error\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case SEND_FAILED:   // 16
            cpt_res->data = (uint8_t *) strdup("Message failed to send\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case CHAN_ID_OVERFLOW:  // 17
            cpt_res->data = (uint8_t *) strdup("Channel ID exceeds limit\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case MSG_OVERFLOW:  // 18
            cpt_res->data = (uint8_t *) strdup("Message size too big\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case MSG_LEN_OVERFLOW:    // 19
            cpt_res->data = (uint8_t *) strdup("Message length too big\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case CHAN_EMPTY:    // 20
            cpt_res->data = (uint8_t *) strdup("No users in channel\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case INVALID_ID:    // 21
            cpt_res->data = (uint8_t *) strdup("Given ID is invalid for any reason\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case UNAUTH_ACCESS:     // 22
            cpt_res->data = (uint8_t *) strdup("Access to resources is forbidden\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case SERVER_FULL:      //23
            cpt_res->data = (uint8_t *) strdup("Server at maximum capacity\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        case 255:      // 255
            cpt_res->data = (uint8_t *) strdup("Reserved for future CMDs\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
            break;
        default:
            cpt_res->data = (uint8_t *) strdup("Server res_code undefined\n");
            cpt_res->data_size = (uint16_t) strlen((const char *) cpt_res->data);
    }

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
    response->data_size = 0;
}


CptMsgResponse * cpt_msg_response_init(uint8_t * msg, uint16_t chan_id, uint16_t user_id) {
    CptMsgResponse *cpt_msg_res = malloc(sizeof(CptMsgResponse));
    if (cpt_msg_res == NULL) {
        printf("malloc error: cpt_msg_response_init()\n");
        return NULL;
    }

    cpt_msg_res->channel_id = chan_id;
    cpt_msg_res->user_id    = user_id;
    cpt_msg_res->msg        = strdup((const char*)msg); // ?
    cpt_msg_res->msg_len    = (uint16_t) strlen(cpt_msg_res->msg);

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


/*********
 * ver. 1 *
 *********/
//size_t cpt_serialize_response(CptResponse * res, uint8_t * buffer) {
//    size_t serialize_res_size;
//    char* binary_code = to_binary_string_8(res->code);
//    char* binary_data = to_binary_string_8(res->data);
//
//    char* code_string = strdup(binary_code);
//    char* data_string = strdup(binary_data);
//
//    char* string = malloc(sizeof(char) * 16);
//
//    strcat(string, code_string);
//    strcat(string, data_string);
//
//    free(binary_code);
//    free(binary_data);
//    free(code_string);
//    free(data_string);
//
//    buffer = (uint8_t *) strdup(string);
//    serialize_res_size = 2;
//
//    return serialize_res_size;
//}
//
//
//size_t cpt_serialize_msg(CptMsgResponse * res, uint8_t * buffer) {
//    size_t serialize_msg_size;
//    char* binary_channel_id = to_binary_string_16(res->channel_id);
//    char* binary_user_id = to_binary_string_16(res->user_id);
//    char* binary_msg_len = to_binary_string_16(res->msg_len);
//
//    char* channel_id_string = strdup(binary_channel_id);
//    char* user_id_string = strdup(binary_user_id);
//    char* msg_len_string = strdup(binary_msg_len);
//
//    char* string = malloc(sizeof(char) * 48 + res->msg_len);
//
//    strcat(string, channel_id_string);
//    strcat(string, user_id_string);
//    strcat(string, msg_len_string);
//    strcat(string, res->msg);
//
//    free(binary_channel_id);
//    free(binary_user_id);
//    free(binary_msg_len);
//    free(channel_id_string);
//    free(user_id_string);
//    free(msg_len_string);
//
//    buffer = (uint8_t *) strdup(string);
////    printf("%s", buffer);
//    serialize_msg_size = 6 + res->msg_len;
//
//    return serialize_msg_size;
//}
//
//
//
//char* to_binary_string_8(uint8_t number) {
//    int num_bits = 8;
//    char *string = malloc(num_bits + 1);
//
//    for (int i = num_bits - 1; i >= 0; i--) {
//        string[i] = (number & 1) + '0';
//        number >>= 1;
//    }
//    string[num_bits] = '\0';
//    return string;
//}
//
//
//char* to_binary_string_16(uint16_t number) {
//    int num_bits = 16;
//    char *string = malloc(num_bits + 1);
//
//    for (int i = num_bits - 1; i >= 0; i--) {
//        string[i] = (number & 1) + '0';
//        number >>= 1;
//    }
//    string[num_bits] = '\0';
//    return string;
//}



/*********
 * ver 2 *
 *********/
size_t cpt_serialize_response(CptResponse * res, uint8_t * buffer) {
    //uint8_t code, uint16_t data_size, uint8_t* data;

    // code 1, data_size 2
    size_t count = 3;
    uint8_t *msg = res->data;
    // Saves the beginning of the buffer.
    uint8_t *temp = buffer;

    *(buffer++) = res->code;

    uint16_t first_half_data_size  = res->data_size;
    first_half_data_size >>= 8;
    uint16_t second_half_data_size  = first_half_data_size & 255;

    *(buffer++) = (uint8_t) first_half_data_size;
    *(buffer++) = (uint8_t) second_half_data_size;

    for (int i = 0; i < res->data_size; ++i)
    {
        *(buffer++) = *msg++;
        count++;
    }

    return count;
}


size_t cpt_serialize_msg(CptMsgResponse * res, uint8_t * buffer) {
    //uint16_t channel_id, uint16_t user_id, uint16_t msg_len, char* msg;

    //channel_id: 2, user_id: 2 , msg_len: 2, char* msg
    size_t count = 6;
    char *msg = res->msg;
    // Saves the beginning of the buffer.
    uint8_t *temp = buffer;

    //channel_id
    uint16_t first_half_channel_id  = res->channel_id;
    first_half_channel_id >>= 8;
    uint16_t second_half_channel_id = first_half_channel_id & 255;

    *(buffer++) = (uint8_t) first_half_channel_id;
    *(buffer++) = (uint8_t) second_half_channel_id;

    //user_id
    uint16_t first_half_user_id  = res->user_id;
    first_half_user_id >>= 8;
    uint16_t second_half_user_id = first_half_user_id & 255;

    *(buffer++) = (uint8_t) first_half_user_id;
    *(buffer++) = (uint8_t) second_half_user_id;


    //msg_len
    uint16_t first_half_msg_len = res->msg_len;
    first_half_msg_len >>= 8;
    uint16_t second_half_msg_len = first_half_msg_len & 255;

    *(buffer++) = (uint8_t) first_half_msg_len;
    *(buffer++) = (uint8_t) second_half_msg_len;

    for (int i = 0; i < res->msg_len; ++i)
    {
        *(buffer++) = (uint8_t) *msg++;
        count++;
    }

    return count;
}





/**
* Create a cpt struct from a cpt packet.
*
* @param packet    A serialized cpt protocol message.
* @return A pointer to a cpt struct.
*/
CptRequest * cpt_parse_request(uint8_t * req_buf, size_t req_size) {

    if (req_buf == NULL) {
        return NULL;
    }

    CptRequest *cpt_req = malloc(req_size);
    CptMsgResponse *cpt_msg_res = malloc(req_size);

    if (cpt_req == NULL) {
        printf("malloc error: cpt_parse_request()\n");
        return NULL;
    }

    else {
        cpt_req->version = *(req_buf++);
        cpt_req->cmd_code = *(req_buf++);

        // channel_id (16)
        uint16_t first_half_channel_id = *req_buf++;
        uint16_t second_half_channel_id = *req_buf++;
        cpt_req->channel_id = first_half_channel_id + second_half_channel_id;

        // msg_len (16)
        uint16_t first_half_msg_len = *req_buf++;
        uint16_t second_half_msg_len = *req_buf++;
        cpt_req->msg_len = first_half_msg_len + second_half_msg_len;

        //msg
        for (int i = 0; i < cpt_req->msg_len; ++i)
        {
            cpt_req->msg[i] = (char) *(req_buf++);
        }
    }

    return cpt_req;
}




