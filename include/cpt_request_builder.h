//
// Created by toni on 2022-03-23.
//

#ifndef TEMPLATE2_CPT_REQUEST_BUILDER_H
#define TEMPLATE2_CPT_REQUEST_BUILDER_H

#include <netinet/in.h>

#define DEFAULT_CPT_PORT 1111
#define BUFFER_LENGTH    400
#define FALSE              0
#define TRUE               1
#define MSG_MAX_LEN     65536

#define SERVER_NAME     "192.168.1.110"
// 10.0.0.169
// school: 10.65.0.209, 10.65.15.72, 192.168.1.110



typedef struct cpt_request {
    uint8_t version;
    uint8_t cmd_code;
    uint16_t channel_id;
    uint16_t msg_len;
    char *msg;
} CptRequest;

/**
* Initialize cpt struct.
*
* Dynamically allocates a cpt struct and
* initializes all fields.
*
* @return Pointer to cpt struct.
*/
CptRequest *cpt_request_init(void);

/**
 * Free all memory and set fields to null.
 *
 * @param cpt   Pointer to a cpt structure.
*/
void cpt_request_destroy(CptRequest *request);

/**
 * Set major and minor version for the cpt header block.
 *
 * @param cpt           Pointer to a cpt structure.
 * @param version_major From enum version.
 * @param version_minor From enum version.
*/
void cpt_request_version(CptRequest *cpt, uint8_t version_major, uint8_t version_minor);

/**
 * Set the command value for the cpt header block.
 *
 * @param cpt   Pointer to a cpt structure.
 * @param cmd   From enum commands.
*/
void cpt_request_cmd(CptRequest *cpt, uint8_t cmd);

/**
 * Set the message length for the cpt header block.
 *
 * @param cpt       Pointer to a cpt structure.
 * @param msg_len   An 8-bit integer.
*/
void cpt_request_len(CptRequest *cpt, uint16_t msg_len);

/**
 * Set the channel id for the cpt header block.
 *
 * @param cpt           Pointer to a cpt structure.
 * @param channel_id    A 16-bit integer.
*/
void cpt_request_chan(CptRequest *cpt, uint16_t channel_id);

/**
 * Set the MSG field for the cpt packet.
 *
 * Also appropriately updates the MSG_LEN field.
 *
 * @param cpt  Pointer to a cpt structure.
 * @param msg  Pointer to an array of characters.
*/
void cpt_request_msg(CptRequest *cpt, const char *msg);

/**
 * Reset packet parameters.
 *
 * Reset the packet parameters,
 * and free memory for certain params.
 *
 * @param packet    A CptRequest struct.
*/
void cpt_request_reset(CptRequest *packet);

/**
* Serialize a CptRequest struct for transmission.
*
* @param cpt    A CptRequest struct.
* @return       Size of the serialized packet.
*/
size_t cpt_serialize_request(const CptRequest *req, uint8_t *buffer);

/**
* Create a cpt struct from a cpt packet.
*
* @param packet    A serialized cpt protocol message.
* @return A pointer to a cpt struct.
*/
CptRequest *cpt_parse_request(uint8_t *req_buf, int size);

#endif //TEMPLATE2_CPT_REQUEST_BUILDER_H
