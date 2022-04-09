//
// Created by toni on 2022-03-25.
//

#ifndef TEMPLATE2_CPT_CLIENT_H
#define TEMPLATE2_CPT_CLIENT_H

#include <dc_application/options.h>
#include "cpt_request_builder.h"

struct application_settings
{
    struct dc_opt_settings opts;
    struct dc_setting_string *hostname;
    struct dc_setting_uint16 *port;
    struct dc_setting_string *cmd;
    struct dc_setting_string *username;
    struct dc_setting_uint16 *channel;
};

size_t get_size_for_serialized_request_buffer(const CptRequest *request);

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err);

static int
destroy_settings(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings **psettings);

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings);

void login(CptRequest *request, int sd);

#endif //TEMPLATE2_CPT_CLIENT_H
