//
// Created by toni on 2022-03-29.
//

#ifndef TEMPLATE2_CPT_SERVER_H
#define TEMPLATE2_CPT_SERVER_H
#include <dc_application/config.h>

struct application_settings
{
    struct dc_opt_settings opts;
    struct dc_setting_string *hostname;
    struct dc_setting_uint16 *port;
};

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err);

static int
destroy_settings(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings **psettings);

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings);


#endif //TEMPLATE2_CPT_SERVER_H
