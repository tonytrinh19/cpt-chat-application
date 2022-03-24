//
// Created by Hyung Joon Lee on 2022-03-23.
//
#ifndef TEMPLATE2_CPT_RESPONSE_H
#define TEMPLATE2_CPT_RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef struct cpt_response {
    uint8_t RES_CODE;
    uint16_t MSG_LEN;
    char* MSG;
} CptResponse;


typedef struct cpt_msg_response {
    uint16_t CHANNEL_ID;
    uint16_t USER_ID;
    uint16_t MSG_LEN;
    char* MSG;
} CptMsgResponse;


//CPT Server Response Codes
#define SUCCESS 1                // Operation was successful
#define MESSAGE 2                // The channel id is in the CHAN_ID, msg contents are a message sub-packet
#define USER_CONNECTED 3         // The ID of the connected user, msg contents are the username
#define USER_DISCONNECTED 4      // The ID of the disconnected user, msg contents are the username
#define MESSAGE_FAILED 5         // Message could not be delivered, could be followed by a USER_DISCONNECTED
#define CHANNEL_CREATED 6        // Response sent to requestee, if the channel is created it provides the channel ID in the <CHAN_ID> section
#define CHANNEL_CREATION_ERROR 7 // Response sent to requestee, if the channel cannot be created
#define CHANNEL_DESTROYED 8      // Response sent to all members of channel when it is destroyed
#define USER_JOINED_CHANNEL 9    // Response sent to all members when a new client joins the channel
#define USER_LEFT_CHANNEL 10     // Response sent to all members when a member leaves the channel
#define USER_LIST 11             // A response message from GET_USERS
#define UKNOWN_CMD 12            // Unknown command error
#define LOGIN_FAIL 13            // Login failed error
#define UKNOWN_CHANNEL 14        // Unknown channel ID error
#define BAD_VERSION 15           // Bad CPT Version number error
#define SEND_FAILED 16           // Message failed to send
#define CHAN_ID_OVERFLOW 17      // Channel ID exceeds limit
#define MSG_OVERFLOW 18          // Message size too big
#define MSG_LEN_OVERFLOW 19      // Message length too big
#define CHAN_EMPTY 20            // No users in channel
#define INVALID_ID 21            // Given ID is invalid for any reason
#define UNAUTH_ACCESS 22         // Access to resources is forbidden
#define SERVER_FULL 23           // Server at maximum capacity
#define RESERVED = 255           // Reserved for future CMDs



/**
 * Initialize CptResponse server-side packet.
 *
 * Initializes a CptResponse by initializing data
 * members, and returning a dynamically allocated
 * pointer to a CptResponse struct.
 *
 * @param res_code    Received client-side packet.
 * @return CptResponse object.
 */
CptResponse * cpt_response_init(uint16_t res_code);


/**
 * Destroy CptResponse object.
 *
 * Destroys CptResponse object, freeing any allocated memory
 * and setting all pointers to null.
 *
 * @param response  Pointer to a CptResponse object.
 */
void cpt_response_destroy(CptResponse * response);


/**
 * Reset packet parameters.
 *
 * Reset the response parameters,
 * and free memory for certain params.
 *
 * @param response    A CptResponse struct.
*/
void cpt_response_reset(CptResponse * response);


/**
 * Initialize CptMsgResponse server-side sub-packet.
 *
 * @param packet    Received client-side packet.
 * @param data      Data being sent to client.
 * @return          CptResponse object.
 */
CptMsgResponse * cpt_msg_response_init(uint8_t * msg, uint16_t chan_id, uint16_t user_id);


/**
 * Destroy CptMsgResponse object.
 *
 * Destroys CptMsgResponse object, freeing any allocated memory
 * and setting all pointers to null.
 *
 * @param msg_res  Pointer to a CptResponse object.
 */
void cpt_msg_response_destroy(CptMsgResponse * msg_res);


#endif //TEMPLATE2_CPT_RESPONSE_H
