#include "cpt_response.h"
#include "linked_list.h"


CptResponse* cpt_response_init(uint16_t res_code) {
    CptResponse *cpt_res = malloc(sizeof(CptResponse));

    if (cpt_res == NULL) {
        printf("malloc error: cpt_response_init()\n");
    }


    cpt_res->code = (uint8_t) res_code;

    switch (res_code) {
        case SUCCESS:    // 1
            cpt_res->data = (uint8_t *) strdup(" (Operation was successful)");
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


size_t cpt_serialize_response(CptResponse * res, uint8_t * buffer) {
    //uint8_t code, uint16_t data_size, uint8_t* data;

    // code 1, data_size 2
    size_t count = 3;
    uint8_t *msg = res->data;
    // Saves the beginning of the buffer.
    uint8_t *temp = buffer;

    *(buffer++) = res->code;

    uint16_t first_half_data_size  = res->data_size;
    uint16_t second_half_data_size  = first_half_data_size & 255;
    first_half_data_size >>= 8;

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
    uint16_t second_half_channel_id = first_half_channel_id & 255;
    first_half_channel_id >>= 8;

    *(buffer++) = (uint8_t) first_half_channel_id;
    *(buffer++) = (uint8_t) second_half_channel_id;

    //user_id
    uint16_t first_half_user_id  = res->user_id;
    uint16_t second_half_user_id = first_half_user_id & 255;
    first_half_user_id >>= 8;

    *(buffer++) = (uint8_t) first_half_user_id;
    *(buffer++) = (uint8_t) second_half_user_id;


    //msg_len
    uint16_t first_half_msg_len = res->msg_len;
    uint16_t second_half_msg_len = first_half_msg_len & 255;
    first_half_msg_len >>= 8;

    *(buffer++) = (uint8_t) first_half_msg_len;
    *(buffer++) = (uint8_t) second_half_msg_len;

    for (int i = 0; i < res->msg_len; ++i)
    {
        *(buffer++) = (uint8_t) *msg++;
        count++;
    }

    return count;
}


size_t cpt_serialize_packet(CptPacketResponse * res, uint8_t * buffer) {
    // uint8_t code | uint16_t data_size | uint16_t channel_id | uint16_t user_id | uint16_t msg_len | char* msg
    // 1 + 2 + 2 + 2 + 2
    size_t count = 9;
    uint8_t *temp = buffer;
    char *msg = res->msg;

    *(buffer++) = res->code;

    // uint16_t data_size
    uint16_t first_half_data_size  = res->data_size;
    uint16_t second_half_data_size  = first_half_data_size & 255;
    first_half_data_size >>= 8;

    *(buffer++) = (uint8_t) first_half_data_size;
    *(buffer++) = (uint8_t) second_half_data_size;

    // uint16_t channel_id
    uint16_t first_half_channel_id = res->channel_id;
    uint16_t second_half_channel_id  = first_half_channel_id & 255;
    first_half_channel_id >>= 8;

    *(buffer++) = (uint8_t) first_half_channel_id;
    *(buffer++) = (uint8_t) second_half_channel_id;

    // uint16_t user_id
    uint16_t first_half_user_id = res->user_id;
    uint16_t second_half_user_id  = first_half_user_id & 255;
    first_half_user_id >>= 8;

    *(buffer++) = (uint8_t) first_half_user_id;
    *(buffer++) = (uint8_t) second_half_user_id;

    // uint16_t msg_len
    uint16_t first_half_msg_len = res->msg_len;
    uint16_t second_half_msg_len  = first_half_msg_len & 255;
    first_half_msg_len >>= 8;

    *(buffer++) = (uint8_t) first_half_msg_len;
    *(buffer++) = (uint8_t) second_half_msg_len;

    for (int i = 0; i < res->data_size; ++i)
    {
        *(buffer++) = (uint8_t) *msg++;
        count++;
    }

    return count;
}



CptResponse * cpt_parse_response(uint8_t * res_buf, size_t res_size) {

    if (res_buf == NULL) {
        return NULL;
    }

    CptResponse *cpt_res = malloc(res_size);

    if (cpt_res == NULL) {
        printf("malloc error: cpt_parse_response()\n");
        return NULL;
    }

    else {
        cpt_res->code = *(res_buf++);

        //data_size
        uint16_t first_half_data_size = *(res_buf++);
        uint16_t second_half_data_size = *(res_buf++);
        cpt_res->data_size = first_half_data_size + second_half_data_size;


        //msg
        for (int i = 0; i < cpt_res->data_size; ++i)
        {
            cpt_res->data[i] = *(res_buf++);
        }
    }

    return cpt_res;
}


// server_info will be global variable in server.c (?)
int cpt_login_response(void * server_info, char * name) {
    ServerInfo *SI;
    SI = (ServerInfo*) server_info;

    if (SI != NULL) {
        int user_count = get_user_linked_list_length(SI->channel_linked_list->headerNode.user_linked_list);
        SI->channel_linked_list->headerNode.channel_id = 0;
        UserNode user_node;
        user_node.user_id = (uint8_t*) strdup(name);
//        user_node.user_fd =

        if (user_count == 0) {
            add_user_element(SI->channel_linked_list->headerNode.user_linked_list, 0, user_node);
            cpt_response_init(1);
            return 1;
        }
        else {
            add_user_element(SI->channel_linked_list->headerNode.user_linked_list, user_count + 1, user_node);
            return 1;
        }
    }

    // response if error
    return 0;
}


/**
 * Handle a received 'LOGOUT' protocol message.
 *
 * Uses information in a received CptRequest to handle
 * a LOGOUT protocol message from a connected client.
 *
 * If successful, will remove any instance of the user
 * specified by the user <id> from the GlobalChannel
 * and any other relevant data structures.
 *
 * @param server_info   Server data structures and information.
 * @return Status Code (SUCCESS if successful, other if failure).
 */
int cpt_logout_response(void * server_info) {
    ServerInfo *SI;
    SI = (ServerInfo*) server_info;

    if (SI != NULL) {
    }
}

/**
 * Handle a received 'SEND' protocol message.
 *
 * Uses information in a received CptRequest to handle
 * a SEND protocol message from a connected client.
 *
 * If successful, function will send the message in the
 * MSG field of the received packet to every user in the
 * CHAN_ID field of the received packet.
 *
 * @param server_info   Server data structures and information.
// * @param name          Name of user in received Packet MSG field.
 * @return Status Code (0 if successful, other if failure).
 */
//int cpt_send_response(void * server_info) {
//
//}




ServerInfo* server_info_init() {
    ServerInfo *server_info = malloc(sizeof(ServerInfo));

    if (server_info == NULL) {
        printf("malloc error: server_info_init()\n");
    }

    return server_info;
}
