//
// Created by toni on 2022-03-23.
//

#ifndef TEMPLATE2_CPT_BUILDER_H
#define TEMPLATE2_CPT_BUILDER_H
#include <netinet/in.h>
typedef struct cpt_request CptRequest;
struct cpt_request {
    uint16_t channel_id;
    uint16_t user_id;
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
static struct cpt * cpt_builder_init(void);

#endif //TEMPLATE2_CPT_BUILDER_H
