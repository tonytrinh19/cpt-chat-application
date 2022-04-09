#include "cpt_response.h"
#include "linked_list.h"
#include "common.h"

CptResponse *cpt_response_init() {
    CptResponse *response = calloc(1, sizeof(CptResponse));

    response->code = 0;
    response->data_size = 0;
    response->data = calloc(1, sizeof(CptSubPacket));

    return response;
}

//typedef struct cpt_sub_packet {
//    uint16_t channel_id;  // 2
//    uint16_t user_fd;     // 2
//    uint16_t msg_len;     // 2
//    char* msg;
//}CptSubPacket;
//
//
//typedef struct cpt_response {
//    uint8_t code;          // 1
//    uint16_t data_size;    // 2
//    CptSubPacket *data;
//} CptResponse;

void cpt_response_code(CptResponse *response, CptRequest *request, uint8_t fds, uint8_t res_code) {
    response->code = res_code;

    switch (res_code) {
        case MESSAGE:
        {
            response->data->channel_id = request->channel_id;
            response->data->user_fd = (uint16_t) fds;
            // 5 for skipping "SEND "
            response->data->msg = strdup(request->msg + 5);
            response->data->msg_len = (uint16_t) strlen(response->data->msg);
            response->data_size = (uint16_t) 2 + 2 + 2 + response->data->msg_len;
            break;
        }
        case LOGIN:    // 7
        {
            response->data->channel_id = request->channel_id;
            response->data->user_fd = (uint16_t) fds;
            response->data->msg = strdup("Login successful\n");
            response->data->msg_len = (uint16_t) strlen(response->data->msg);
            response->data_size = (uint16_t) 2 + 2 + 2 + response->data->msg_len;
            break;
        }
//        case USER_CONNECTED:    // 3
//            response->data = (uint8_t *) strdup("User connected\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case USER_DISCONNECTED: // 4
//            response->data = (uint8_t *) strdup("User is currently disconnected\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case MESSAGE_FAILED:    // 5
//            response->data = (uint8_t *) strdup("Message could not be delivered\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
        case CHANNEL_CREATED:   // 6
        {
            response->data->channel_id = request->channel_id;
            response->data->user_fd = (uint16_t) fds;
            response->data->msg = strdup("Channel created\n");
            response->data->msg_len = (uint16_t) strlen(response->data->msg);
            response->data_size = (uint16_t) 2 + 2 + 2 + response->data->msg_len;
            break;
        }
        case CHANNEL_CREATION_ERROR:    //7
        {
            response->data->channel_id = request->channel_id;
            response->data->user_fd = (uint16_t) fds;
            response->data->msg = strdup("Channel cannot be created\n");
            response->data->msg_len = (uint16_t) strlen(response->data->msg);
            response->data_size = (uint16_t) 2 + 2 + 2 + response->data->msg_len;
            break;
        }
//        case CHANNEL_DESTROYED:    //8
//            response->data = (uint8_t *) strdup("Channel is destroyed\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
        case JOIN_CHANNEL:   // 9
        {
            response->data->channel_id = request->channel_id;
            response->data->user_fd = (uint16_t) fds;
            response->data->msg = strdup("Joined new channel\n");
            response->data->msg_len = (uint16_t) strlen(response->data->msg);
            response->data_size = (uint16_t) 2 + 2 + 2 + response->data->msg_len;
            break;
        }
//        case USER_LEFT_CHANNEL:     // 10
//            response->data = (uint8_t *) strdup("User leaves the channel\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case USER_LIST:     // 11
//            response->data = (uint8_t *) strdup("Current users (Get Users)\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case UKNOWN_CMD:    // 12
//            response->data = (uint8_t *) strdup("Unknown command error\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case LOGIN_FAIL:    // 13
//            response->data = (uint8_t *) strdup("Login failed error\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case UKNOWN_CHANNEL:    // 14
//            response->data = (uint8_t *) strdup("Unknown channel ID error\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case BAD_VERSION:    // 15
//            {
//                char *data = strdup(
//                        "Bad CPT Version number error\n");
//                response->data = (uint8_t *) data;
//                response->data_size = (uint16_t) strlen(data);
//                break;
//            }
//        case SEND_FAILED:   // 16
//            response->data = (uint8_t *) strdup("Message failed to send\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case CHAN_ID_OVERFLOW:  // 17
//            response->data = (uint8_t *) strdup("Channel ID exceeds limit\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case MSG_OVERFLOW:  // 18
//            response->data = (uint8_t *) strdup("Message size too big\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case MSG_LEN_OVERFLOW:    // 19
//            response->data = (uint8_t *) strdup("Message length too big\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case CHAN_EMPTY:    // 20
//            response->data = (uint8_t *) strdup("No users in channel\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case INVALID_ID:    // 21
//            response->data = (uint8_t *) strdup("Given ID is invalid for any reason\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case UNAUTH_ACCESS:     // 22
//            response->data = (uint8_t *) strdup("Access to resources is forbidden\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
//        case SERVER_FULL:      //23
//            response->data = (uint8_t *) strdup("Server at maximum capacity\n");
//            response->data_size = (uint16_t) strlen((const char *) response->data);
//            break;
        default:
            response->data->channel_id = request->channel_id;
            response->data->user_fd = (uint16_t) fds;
            response->data->msg = strdup("This is default\n");
            response->data->msg_len = (uint16_t) strlen(response->data->msg);
            response->data_size = (uint16_t) 2 + 2 + 2 + response->data->msg_len;
            break;
    }
}

void cpt_response_destroy(CptResponse *response) {
    response->code = 0;
    response->data_size = 0;
    response->data->msg_len = 0;
    response->data->channel_id = 0;
    response->data->user_fd = 0;
    free(response->data->msg);
    response->data->msg = NULL;

    free(response->data);
    response->data = NULL;

    free(response);
    response = NULL;
}

void cpt_response_reset(CptResponse *response) {
    response->code = 0;
    if (response->data) free(response->data);
    response->data = NULL;
    response->data_size = 0;
}

size_t cpt_serialize_response(CptResponse *res, uint8_t* buffer, uint16_t data_size, uint16_t channel_id, uint16_t user_id,
                            uint16_t msg_len, uint8_t *msg) {
    size_t res_size;

    *(buffer++) = res->code;

    uint16_t first_half_data_size = data_size;
    uint16_t second_half_data_size = first_half_data_size & 255;
    first_half_data_size >>= 8;
    *(buffer++) = (uint8_t) first_half_data_size;
    *(buffer++) = (uint8_t) second_half_data_size;


    uint16_t first_half_channel_id = channel_id;
    uint16_t second_half_channel_id = first_half_channel_id & 255;
    first_half_channel_id >>= 8;
    *(buffer++) = (uint8_t) first_half_channel_id;
    *(buffer++) = (uint8_t) second_half_channel_id;

    uint16_t first_half_user_id = user_id;
    uint16_t second_half_user_id = first_half_user_id & 255;
    first_half_user_id >>= 8;
    *(buffer++) = (uint8_t) first_half_user_id;
    *(buffer++) = (uint8_t) second_half_user_id;

    uint16_t first_half_msg_len = msg_len;
    uint16_t second_half_msg_len = first_half_msg_len & 255;
    first_half_msg_len >>= 8;

    *(buffer++) = (uint8_t) first_half_msg_len;
    *(buffer++) = (uint8_t) second_half_msg_len;
    for (int i = 0; i < msg_len; ++i) {
        *(buffer++) = *msg++;
    }

    *buffer = '\0';
    res_size = strlen((char*)buffer);

    return res_size;
}

CptResponse *cpt_parse_response(uint8_t *res_buf, size_t res_size) {

    if (res_buf == NULL) {
        return NULL;
    }

    CptResponse *cpt_res = calloc(res_size, sizeof(uint8_t));
    cpt_res->data = calloc(res_size, sizeof(uint8_t));

    cpt_res->code = *(res_buf++);

    //data_size
    uint16_t first_half_data_size = *(res_buf++);
    first_half_data_size <<= 8;
    uint16_t second_half_data_size = *(res_buf++);
    cpt_res->data_size = first_half_data_size | second_half_data_size;

    // channel_id
    uint16_t first_half_channel_id = *(res_buf++);
    first_half_channel_id <<= 8;
    uint16_t second_half_channel_id = *(res_buf++);
    cpt_res->data->channel_id = first_half_channel_id | second_half_channel_id;

    uint16_t first_half_user_id = *(res_buf++);
    first_half_user_id <<= 8;
    uint16_t second_half_user_id = *(res_buf++);
    cpt_res->data->user_fd = first_half_user_id | second_half_user_id;

    uint16_t first_half_msg_len = *(res_buf++);
    first_half_msg_len <<= 8;
    uint16_t second_half_msg_len = *(res_buf++);
    cpt_res->data->msg_len = first_half_msg_len | second_half_msg_len;

    cpt_res->data->msg = malloc(cpt_res->data_size * sizeof(uint8_t));

    for (int i = 0; i < cpt_res->data_size; ++i)
    {
        cpt_res->data->msg[i] = (char) *(res_buf++);
    }

    return cpt_res;
}

// server_info will be global variable in server.c (?)
size_t get_size_for_serialized_response_buffer(CptResponse *res) {
    // always have at least 3 elements. (1 for res_code, 2 for msg_lem/data_size)
    size_t count = 3;
    count += res->data_size;
    return count;
}
