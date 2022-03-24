//
// Created by toni on 2022-03-23.
//

#ifndef TEMPLATE2_CPT_REQUEST_BUILDER_H
#define TEMPLATE2_CPT_REQUEST_BUILDER_H
#include <netinet/in.h>

typedef struct cpt_request CptRequest;

struct cpt_request {
    uint8_t version;
    uint8_t cmd_code;
    char channel_type;
    uint16_t channel_id;
    uint16_t msg_len;
    char *msg;
};

/**
* Initialize cpt struct.
*
* Dynamically allocates a cpt struct and
* initializes all fields.
*
* @return Pointer to cpt struct.
*/
static CptRequest * cpt_request_init(void);

/**
 * Free all memory and set fields to null.
 *
 * @param cpt   Pointer to a cpt structure.
*/
static void cpt_request_destroy(CptRequest * request);

/**
 * Set major and minor version for the cpt header block.
 *
 * @param cpt           Pointer to a cpt structure.
 * @param version_major From enum version.
 * @param version_minor From enum version.
*/
static void cpt_request_version(CptRequest * cpt, uint8_t version_major, uint8_t version_minor);

/**
 * Set the command value for the cpt header block.
 *
 * @param cpt   Pointer to a cpt structure.
 * @param cmd   From enum commands.
*/
static void cpt_request_cmd(CptRequest * cpt, uint8_t cmd);

/**
 * Set the message length for the cpt header block.
 *
 * @param cpt       Pointer to a cpt structure.
 * @param msg_len   An 8-bit integer.
*/
static void cpt_request_len(CptRequest * cpt, uint16_t msg_len);

/**
 * Set the channel id for the cpt header block.
 *
 * @param cpt           Pointer to a cpt structure.
 * @param channel_id    A 16-bit integer.
*/
static void cpt_request_chan(CptRequest * cpt, uint16_t channel_id);

/**
 * Set the MSG field for the cpt packet.
 *
 * Also appropriately updates the MSG_LEN field.
 *
 * @param cpt  Pointer to a cpt structure.
 * @param msg  Pointer to an array of characters.
*/
static void cpt_request_msg(CptRequest * cpt, char * msg);

/**
 * Reset packet parameters.
 *
 * Reset the packet parameters,
 * and free memory for certain params.
 *
 * @param packet    A CptRequest struct.
*/
static void cpt_request_reset(CptRequest * packet);

#endif //TEMPLATE2_CPT_REQUEST_BUILDER_H
