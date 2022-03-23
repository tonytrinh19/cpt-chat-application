//
// Created by toni on 2022-03-23.
//

#include <stdlib.h>
#include "cpt_builder.h"

static struct cpt * cpt_builder_init(void)
{
    struct cpt * packet = calloc(1, sizeof(struct cpt));
    packet->channel_id = 0;
    packet->user_id = 0;
    packet->msg_len = 0;
    packet->msg = NULL;
    return packet;
}
