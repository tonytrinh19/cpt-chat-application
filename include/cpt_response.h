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
#include <stdbool.h>
#include <dc_util/bits.h>
#include "linked_list.h"


typedef struct cpt_response {
    uint8_t code;
    uint16_t data_size;
    uint8_t* data;
} CptResponse;


typedef struct cpt_msg_response {
    uint16_t channel_id;
    uint16_t user_id;
    uint16_t msg_len;
    char* msg;
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


/**
* Serialize a CptRequest struct for transmission.
*
* @param req    A CptRequest struct.
* @param buffer A pointer that will store serialized string
* @return       Size of the serialized packet.
*/
size_t cpt_serialize_response(CptResponse * req, uint8_t * buffer);


/**
* Serialize a CptMsgResponse response sub-packet object.
*
* @param cpt    A CptResponse object.
* @return       Size of the serialized packet.
*/
size_t cpt_serialize_msg(CptMsgResponse * msg_res, uint8_t * buffer);


/**
* Create a cpt struct from a cpt packet.
*
* @param packet    A serialized cpt protocol message.
* @return A pointer to a cpt struct.
*/
CptResponse * cpt_parse_response(uint8_t * req_buf, size_t req_size);


/**
 * Change number to binary string (8 bit form).
 *
 * @param number A 8 bits number
 * @return       String filled with binary
 */
char* to_binary_string_8(uint8_t number);


/**
 * Change number to binary string (16 bit form).
 *
 * @param number A 16 bits number
 * @return       String filled with binary
 */
char* to_binary_string_16(uint16_t number);


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
int cpt_login_response(void * server_info, char * name);


/**
 * Handle a received 'LOGOUT' protocol message.
 *
 * Use information in the CptRequest to handle
 * a LOGOUT protocol message from a connected client.
 * If successful, will remove any instance of the user
 * specified by the user <id> from the GlobalChannel
 * and any other relevant data structures.
 *
 * @param server_info   Server data structures and information.
 * @return Status Code 1 if successful, other if failure.
 */
int cpt_logout_response(void * server_info);


/**
 * Handle a received 'GET_USERS' protocol message.
 *
 * Retrieves all users in the specified <chan_id>,
 * placing them in a buffer for the CptResponse packet
 * in the format:
 *      < user_id >< whitespace >< username >< newline >
 *
 * Example given:
 *      1 'Clark Kent'
 *      2 'Bruce Wayne'
 *      3 'Fakey McFakerson'
 *
 * @param server_info   Server data structures and information.
 * @return Status Code (0 if successful, other if failure).
 */
int cpt_get_users_response(void * server_info, int chan_id);


/**
 * Handle a received 'CREATE_CHANNEL' protocol message.
 *
 * If a <user_list> was received in the GET_CHANNEL body,
 * function will also parse the <user_list> string and attempt
 * to add the requested user IDs to the channel.
 *
 * If <id_list> is NULL, function will create a new channel with
 * only the requesting user within it.
 *
 * @param server_info   Server data structures and information.
 * @return Status Code (0 if successful, other if failure).
 */
int cpt_create_channel_response(void * server_info, char * id_list);


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
int cpt_send_response(void * server_info);


#endif //TEMPLATE2_CPT_RESPONSE_H
