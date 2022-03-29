#include "cpt_response.h"
#include "linked_list.h"


CptResponse *cpt_response_init() {
    CptResponse *response = calloc(1, sizeof(CptResponse));

    response->code = 0;
    response->data_size = 0;
    response->data = NULL;

    return response;
}

void cpt_response_code(CptResponse *response, CptRequest *request, uint8_t res_code) {
    response->code = res_code;

    switch (res_code) {
        case SUCCESS:    // 1
        {
            char *data = strdup((char *) request->msg);
            response->data = (uint8_t *) data;
            response->data_size = request->msg_len;
            break;
        }
        case MESSAGE:    // 2
            response->data = (uint8_t *) strdup(
                    "The channel id is in the CHAN_ID, msg contents are a message sub-packet\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case USER_CONNECTED:    // 3
            response->data = (uint8_t *) strdup("User connected\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case USER_DISCONNECTED: // 4
            response->data = (uint8_t *) strdup("User is currently disconnected\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case MESSAGE_FAILED:    // 5
            response->data = (uint8_t *) strdup("Message could not be delivered\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case CHANNEL_CREATED:   // 6
            response->data = (uint8_t *) strdup("Channel created\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case CHANNEL_CREATION_ERROR:    //7
            response->data = (uint8_t *) strdup("Channel cannot be created\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case CHANNEL_DESTROYED:    //8
            response->data = (uint8_t *) strdup("Channel is destroyed\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case USER_JOINED_CHANNEL:   // 9
            response->data = (uint8_t *) strdup("NEW client joins the channel\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case USER_LEFT_CHANNEL:     // 10
            response->data = (uint8_t *) strdup("User leaves the channel\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case USER_LIST:     // 11
            response->data = (uint8_t *) strdup("Current users (Get Users)\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case UKNOWN_CMD:    // 12
            response->data = (uint8_t *) strdup("Unknown command error\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case LOGIN_FAIL:    // 13
            response->data = (uint8_t *) strdup("Login failed error\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case UKNOWN_CHANNEL:    // 14
            response->data = (uint8_t *) strdup("Unknown channel ID error\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case BAD_VERSION:    // 15
            response->data = (uint8_t *) strdup("Bad CPT Version number error\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case SEND_FAILED:   // 16
            response->data = (uint8_t *) strdup("Message failed to send\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case CHAN_ID_OVERFLOW:  // 17
            response->data = (uint8_t *) strdup("Channel ID exceeds limit\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case MSG_OVERFLOW:  // 18
            response->data = (uint8_t *) strdup("Message size too big\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case MSG_LEN_OVERFLOW:    // 19
            response->data = (uint8_t *) strdup("Message length too big\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case CHAN_EMPTY:    // 20
            response->data = (uint8_t *) strdup("No users in channel\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case INVALID_ID:    // 21
            response->data = (uint8_t *) strdup("Given ID is invalid for any reason\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case UNAUTH_ACCESS:     // 22
            response->data = (uint8_t *) strdup("Access to resources is forbidden\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        case SERVER_FULL:      //23
            response->data = (uint8_t *) strdup("Server at maximum capacity\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
            break;
        default:
            response->data = (uint8_t *) strdup("Server res_code undefined\n");
            response->data_size = (uint16_t) strlen((const char *) response->data);
    }
}

void cpt_response_destroy(CptResponse *response) {
    cpt_response_reset(response);
    if (response) free(response);
    response = NULL;
}


void cpt_response_reset(CptResponse *response) {
    response->code = 0;
    if (response->data) free(response->data);
    response->data = NULL;
    response->data_size = 0;
}

size_t cpt_serialize_response(CptResponse *res, uint8_t *buffer) {
    // code 1, data_size 2
    size_t count = 3;
    uint8_t *msg = res->data;
    // Saves the beginning of the buffer.
    uint8_t *temp = buffer;

    *(buffer++) = res->code;

    uint16_t first_half_data_size = res->data_size;
    uint16_t second_half_data_size = first_half_data_size & 255;
    first_half_data_size >>= 8;

    *(buffer++) = (uint8_t) first_half_data_size;
    *(buffer++) = (uint8_t) second_half_data_size;

    for (int i = 0; i < res->data_size; ++i) {
        *(buffer++) = *msg++;
        count++;
    }

    return count;
}

CptResponse *cpt_parse_response(uint8_t *res_buf, size_t res_size) {

    if (res_buf == NULL) {
        return NULL;
    }

    CptResponse *cpt_res = malloc(res_size);

    if (cpt_res == NULL) {
        printf("malloc error: cpt_parse_response()\n");
        return NULL;
    } else {
        cpt_res->code = *(res_buf++);

        //data_size
        uint16_t first_half_data_size = *(res_buf++);
        uint16_t second_half_data_size = *(res_buf++);
        cpt_res->data_size = first_half_data_size + second_half_data_size;


        //msg
        for (int i = 0; i < cpt_res->data_size; ++i) {
            cpt_res->data[i] = *(res_buf++);
        }
    }

    return cpt_res;
}


// server_info will be global variable in server.c (?)
int cpt_login_response(void *server_info, char *name) {
    ServerInfo *SI;
    SI = (ServerInfo *) server_info;

    if (SI != NULL) {
        int user_count = get_user_linked_list_length(SI->channel_linked_list->headerNode.user_linked_list);
        SI->channel_linked_list->headerNode.channel_id = 0;
        UserNode user_node;
        user_node.user_id = (uint8_t *) strdup(name);
//        user_node.user_fd =

        if (user_count == 0) {
            add_user_element(SI->channel_linked_list->headerNode.user_linked_list, 0, user_node);
            return 1;
        } else {
            add_user_element(SI->channel_linked_list->headerNode.user_linked_list, user_count + 1, user_node);
            return 1;
        }
    }

    // response if error
    return 0;
}

int cpt_logout_response(void *server_info) {
    ServerInfo *SI;
    SI = (ServerInfo *) server_info;

    if (SI != NULL) {
    }
}

