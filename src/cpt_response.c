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
            cpt_res_header_ptr->MSG = strdup("he channel id is in the CHAN_ID, msg contents are a message sub-packet\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 3:
            cpt_res_header_ptr->MSG = strdup("The ID of the connected user, msg contents are the username\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 4:
            cpt_res_header_ptr->MSG = strdup("The ID of the disconnected user, msg contents are the username\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 5:
            cpt_res_header_ptr->MSG = strdup("Message could not be delivered, could be followed by a USER_DISCONNECTED\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 6:
            cpt_res_header_ptr->MSG = strdup(
                    "Response sent to requestee, if the channel is created it provides the channel ID in the <CHAN_ID> section\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 7:
            cpt_res_header_ptr->MSG = strdup("Response sent to requestee, if the channel cannot be created\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 8:
            cpt_res_header_ptr->MSG = strdup("Response sent to all members of channel when it is destroyed\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 9:
            cpt_res_header_ptr->MSG = strdup("Response sent to all members when a new client joins the channel\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 10:
            cpt_res_header_ptr->MSG = strdup("Response sent to all members when a member leaves the channel\n");
            cpt_res_header_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_header_ptr->MSG);
            break;
        case 11:
            cpt_res_header_ptr->MSG = strdup("A response message from GET_USERS\n");
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
    free(response->MSG);
    response->MSG = NULL;
    response->MSG_LEN = 0;
    response->RES_CODE = 0;
}


// Need to check what it actually does
void cpt_response_reset(CptResponse * response) {
    cpt_response_destroy(response);
    free(response);
}


/**
 * Initialize CptMsgResponse server-side sub-packet.
 *
 * @param packet    Received client-side packet.
 * @param data      Data being sent to client.
 * @return          CptResponse object.
 */
CptMsgResponse * cpt_msg_response_init(uint8_t * msg, uint16_t chan_id, uint16_t user_id) {
    CptMsgResponse *cpt_res_msg_ptr = malloc(sizeof(CptMsgResponse));

    char* msg_ptr;
    msg_ptr = (char*) msg;

    if (cpt_res_msg_ptr == NULL) {
        printf("malloc error: cpt_msg_response_init()\n");
    }
    cpt_res_msg_ptr->CHANNEL_ID = chan_id;
    cpt_res_msg_ptr->USER_ID = user_id;
    cpt_res_msg_ptr->MSG = strdup(msg_ptr); // ?
    cpt_res_msg_ptr->MSG_LEN = (uint16_t) strlen(cpt_res_msg_ptr->MSG);

    return cpt_res_msg_ptr;
}




