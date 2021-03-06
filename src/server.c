#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <dc_application/command_line.h>
#include <dc_application/options.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_string.h>
#include <getopt.h>
#include <inttypes.h>
#include <linked_list.h>

#include "cpt_response.h"
#include "cpt_server.h"
#include "common.h"


int main(int argc, char *argv[]) {
    dc_posix_tracer tracer;
    dc_error_reporter reporter;
    struct dc_posix_env env;
    struct dc_error err;
    struct dc_application_info *info;
    int ret_val;

    tracer = NULL;
    dc_posix_env_init(&env, tracer);
    reporter = dc_error_default_error_reporter;
    dc_error_init(&err, reporter);
    info = dc_application_info_create(&env, &err, "CPT Chat Application");
    ret_val = dc_application_run(&env, &err, info, create_settings, destroy_settings, run, dc_default_create_lifecycle,
                                 dc_default_destroy_lifecycle,
                                 "~/.dcecho.conf",
                                 argc, argv);
    dc_application_info_destroy(&env, &info);
    dc_error_reset(&err);

    return ret_val;
}

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err) {
    static const uint16_t default_port = DEFAULT_CPT_PORT;
    struct application_settings *settings;

    settings = dc_malloc(env, err, sizeof(struct application_settings));

    if (settings == NULL) {
        return NULL;
    }

    settings->opts.parent.config_path = dc_setting_path_create(env, err);
    settings->port = dc_setting_uint16_create(env, err);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeclaration-after-statement"
    struct options opts[] =
            {
                    {(struct dc_setting *) settings->opts.parent.config_path, dc_options_set_path,   "config", required_argument, 'c', "CONFIG", dc_string_from_string, NULL,   dc_string_from_config, NULL},
                    {(struct dc_setting *) settings->port,                    dc_options_set_uint16, "port",   required_argument, 'p', "PORT",   dc_uint16_from_string, "port", dc_uint16_from_config, &default_port},
            };
#pragma GCC diagnostic pop

    // note the trick here - we use calloc and add 1 to ensure the last line is all 0/NULL
    settings->opts.opts = dc_calloc(env, err, (sizeof(opts) / sizeof(struct options)) + 1, sizeof(struct options));
    dc_memcpy(env, settings->opts.opts, opts, sizeof(opts));
    settings->opts.flags = "c:p:";
    settings->opts.env_prefix = "CPT_CHAT_";

    return (struct dc_application_settings *) settings;
}

static int destroy_settings(const struct dc_posix_env *env, __attribute__ ((unused)) struct dc_error *err,
                            struct dc_application_settings **psettings) {
    struct application_settings *app_settings;

    app_settings = (struct application_settings *) *psettings;
    dc_setting_uint16_destroy(env, &app_settings->port);
    dc_free(env, app_settings->opts.opts, app_settings->opts.opts_size);
    dc_free(env, app_settings, sizeof(struct application_settings));

    if (env->null_free)
    {
        *psettings = NULL;
    }

    return 0;
}

static int run(const struct dc_posix_env *env, __attribute__ ((unused)) struct dc_error *err,
               struct dc_application_settings *settings) {
    struct application_settings *app_settings;
    in_port_t port;
    int ret_val;
    int len, rc, on = 1;
    int listen_sd = -1, new_sd = -1;
    int end_server = FALSE, compress_array = FALSE;
    int close_conn;
    char buffer[MSG_MAX_LEN];
    struct sockaddr_in6 addr;
    int timeout;
    struct pollfd fds[SOMAXCONN];
    int nfds = 1, current_size = 0, i, j;
    uint8_t *res_packet;
    size_t size_buf;
    app_settings = (struct application_settings *) settings;
    port = dc_setting_uint16_get(env, app_settings->port);
    ret_val = 0;


    // Default Channel Linked List Create
    UserLinkedList *user_linked_list[65535];

    // Default(Channel 0) User Linked List Create
    user_linked_list[0] = create_user_linked_list();
    UserNode user_node;
    uint16_t current_channel;


    /* Create an AF_INET6 stream socket to receive incoming      */
    /* connections on                                            */
    listen_sd = socket(AF_INET6, SOCK_STREAM, 0);
    if (listen_sd < 0) {
        perror("socket() failed");
        exit(-1);
    }

    /* Allow socket descriptor to be reuseable                   */
    rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR,
                    (char *) &on, sizeof(on));
    if (rc < 0) {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }

    rc = ioctl(listen_sd, FIONBIO, (char *) &on);
    if (rc < 0) {
        perror("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
    addr.sin6_port = htons(port);
    rc = bind(listen_sd,
              (struct sockaddr *) &addr, sizeof(addr));
    if (rc < 0) {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }

    rc = listen(listen_sd, SOMAXCONN);
    if (rc < 0) {
        perror("listen() failed");
        close(listen_sd);
        exit(-1);
    }

    memset(fds, 0, sizeof(fds));

    fds[0].fd = listen_sd;
    fds[0].events = POLLIN;

    /* Set to -1 to wait forever until an event occurs */
    timeout = (3 * 60 * 1000);

    /* Loop waiting for incoming connects or for incoming data   */
    /* on any of the connected sockets.                          */
    do {
        /* Call poll() and wait 3 minutes for it to complete.      */
        printf("Waiting on poll()...\n");
        rc = poll(fds, nfds, timeout);

        /* Check to see if the poll call failed.                   */
        if (rc < 0) {
            perror("  poll() failed");
            break;
        }

        /* Check to see if the time-out expired.          */
        if (rc == 0) {
            printf("  poll() timed out.  End program.\n");
            break;
        }

        /* One or more descriptors are readable.  Need to          */
        /* determine which ones they are.                          */
        current_size = nfds;
        for (i = 0; i < current_size; i++) {
            /* Loop through to find the descriptors that returned    */
            /* POLLIN and determine whether it's the listening       */
            /* or the active connection.                             */
            if (fds[i].revents == 0)
                continue;

            /* If revents is not POLLIN, it's an unexpected result,  */
            /* log and end the server.                               */
            if (fds[i].revents != POLLIN) {
                printf("  Error! revents = %d\n", fds[i].revents);
                end_server = TRUE;
                break;
            }

            if (fds[i].fd == listen_sd) {
                /* Listening descriptor is readable.                   */
                printf("  Listening socket is readable\n");

                /* Accept all incoming connections that are            */
                /* queued up on the listening socket before we         */
                /* loop back and call poll again.                      */
                do {
                    new_sd = accept(listen_sd, NULL, NULL);
                    if (new_sd < 0) {
                        if (errno != EWOULDBLOCK) {
                            perror("  accept() failed");
                            end_server = TRUE;
                        }
                        break;
                    }

                    printf("  New incoming connection - %d\n", new_sd);

                    // ALL THE CLIENTS ARE HERE
                    // Set the channel_id and stuff here
                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                    /* Loop back up and accept another incoming          */
                    /* connection                                        */
                } while (new_sd != -1);
            } else {
                printf("  Descriptor %d is readable\n", fds[i].fd);
                close_conn = FALSE;
                /* Receive all incoming data on this socket            */
                /* before we loop back and call poll again.            */
                do
                {
                    /* Receive data on this connection until the         */
                    /* recv fails with EWOULDBLOCK. If any other         */
                    /* failure occurs, we will close the                 */
                    /* connection.                                       */
                    rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (rc < 0)
                    {
                        if (errno != EWOULDBLOCK) {
                            perror("  recv() failed");
                            close_conn = TRUE;
                        }
                        break;
                    }

                    /* Check to see if the connection has been           */
                    /* closed by the client                              */
                    if (rc == 0)
                    {
                        printf("  Connection closed\n");
                        close_conn = TRUE;
                        break;
                    }

                    /* Data was received                                 */
                    len = rc;
                    CptRequest *req  = cpt_parse_request((uint8_t *) buffer, len);
                    CptResponse *res = cpt_response_init();

                    user_node.user_fd = (uint8_t) fds[i].fd;

                    if (req->cmd_code == SEND) {
                        char *parse_message;
                        char *temp = strdup(req->msg);
                        parse_message = strtok(temp, " ");

                        display_user_linked_list(user_linked_list[0]);
                        cpt_response_code(res, req, (uint8_t) fds[i].fd, SEND);
                        size_buf = get_size_for_serialized_response_buffer(res);
                        res_packet = calloc(size_buf, sizeof(uint8_t));
                        cpt_serialize_response(res, res_packet, res->data_size, res->data->channel_id,
                                               user_node.user_fd, res->data->msg_len, res->data->msg);

                        rc = send(user_node.user_fd, res_packet, size_buf, 0);

                        if (rc < 0) {
                            perror("  send() failed");
                            close_conn = TRUE;
                        }
                        for (int conn = 1; conn < current_size; ++conn) {
                            printf("inside\n");
                            // response_code will be MESSAGE
                            if (conn != i) {
                                int user_id = fds[conn].fd;
                                cpt_response_code(res, req, fds[i].fd, MESSAGE);
                                size_buf = get_size_for_serialized_response_buffer(res);
                                res_packet = calloc(size_buf, sizeof(uint8_t));
                                cpt_serialize_response(res, res_packet, res->data_size, res->data->channel_id,
                                                       (uint16_t) fds[i].fd, res->data->msg_len, (uint8_t *)res->data->msg);
                                rc = send(user_id, res_packet, size_buf, 0);
                                if (rc < 0) {
                                    perror("  send() failed");
                                    close_conn = TRUE;
                                    break;
                                }
                                free(res_packet);
                            }
                        }
                        free(temp);
                        break;
                    }

                    if (req->cmd_code == LOGIN) {
                        char *parse_username;
                        user_node.user_fd = (uint8_t) fds[i].fd;
                        user_node.channel = 0;
                        add_user_element(user_linked_list[0], i - 1, user_node);
                        display_user_linked_list(user_linked_list[0]);

                        cpt_response_code(res, req, (uint8_t) fds[i].fd, LOGIN);
                        size_buf = get_size_for_serialized_response_buffer(res);
                        res_packet = calloc(size_buf, sizeof(uint8_t));
                        cpt_serialize_response(res, res_packet, res->data_size, res->data->channel_id,
                                               user_node.user_fd, res->data->msg_len, (uint8_t*) res->data->msg);
                        rc = send(user_node.user_fd, res_packet, size_buf, 0);

                        if (rc < 0) {
                            perror("  send() failed");
                            close_conn = TRUE;
                        }
                        free(res_packet);
                        break;
                    } else if (req->cmd_code == CREATE_CHANNEL) {
                        char *parse_channel;
                        parse_channel = strtok(req->msg, " ");
                        parse_channel = strtok(NULL, " ");
                        int new_channel = (int) strtol(parse_channel, NULL, 10);
                        if (new_channel > 65535 || new_channel < 0) {
                            cpt_response_code(res, req, (uint8_t) fds[i].fd, CHANNEL_CREATION_ERROR);
                        } else {
                            user_linked_list[new_channel] = create_user_linked_list();
                            cpt_response_code(res, req, (uint8_t) fds[i].fd, CHANNEL_CREATED);
                        }

                        size_buf = get_size_for_serialized_response_buffer(res);
                        res_packet = calloc(size_buf, sizeof(uint8_t));
                        cpt_serialize_response(res, res_packet, res->data_size, res->data->channel_id,
                                               user_node.user_fd, res->data->msg_len, (uint8_t *) res->data->msg);

                        rc = send(user_node.user_fd, res_packet, size_buf, 0);

                        if (rc < 0) {
                            perror("  send() failed");
                            close_conn = TRUE;
                        }
                        free(res_packet);
                        break;
                    }
                    else if (req->cmd_code == JOIN_CHANNEL) {
                        char *parse_channel;
                        parse_channel = strtok(req->msg, " ");
                        parse_channel = strtok(NULL, " ");
                        printf("New channel %s\n", parse_channel);
                        int new_channel = (int) strtol(parse_channel, NULL, 10);

                        if (new_channel > 65535 || new_channel < 0) {
                            cpt_response_code(res, req, (uint8_t) fds[i].fd, UKNOWN_CHANNEL);
                        } else {
                            int index_delete = 0;

                            UserNode target;
                            /** REMOVE USER FROM PREVIOUS CHANNEL AND ADD USER TO A NEW CHANNEL **/
                            while (get_user_element(user_linked_list[res->data->channel_id], index_delete)->user_fd !=
                                   fds[i].fd) {
                                index_delete++;
                            }
                            if (get_user_element(user_linked_list[res->data->channel_id], index_delete)->user_fd ==
                                fds[i].fd) {
                                target.user_fd = get_user_element(user_linked_list[res->data->channel_id],
                                                                  index_delete)->user_fd;
                                target.channel = (uint16_t) new_channel;
//                                remove_user_element(user_linked_list[0], index_delete);
                            }

                            int index = get_user_linked_list_length(user_linked_list[new_channel]);
                            if (index == 0) {
                                add_user_element(user_linked_list[new_channel], 0, target);
                            } else {
                                for (int j = 0; j < index; j++) {
                                    if (get_user_element(user_linked_list[new_channel], j)->user_fd != target.user_fd) {
                                        printf("user_fd = %d\n",
                                               get_user_element(user_linked_list[new_channel], j)->user_fd);
                                        printf("target_fd = %d\n",
                                               get_user_element(user_linked_list[new_channel], j)->user_fd);
                                        add_user_element(user_linked_list[new_channel], index, target);
                                    }
                                }
                            }
                            display_user_linked_list(user_linked_list[new_channel]);
                            cpt_response_code(res, req, target.user_fd, JOIN_CHANNEL);
                        }

                        size_buf = get_size_for_serialized_response_buffer(res);
                        res_packet = calloc(size_buf, sizeof(uint8_t));
                        cpt_serialize_response(res, res_packet, res->data_size, (uint16_t) new_channel,
                                               user_node.user_fd, res->data->msg_len, (uint8_t *)res->data->msg);

                        rc = send(user_node.user_fd, res_packet, size_buf, 0);

                        if (rc < 0)
                        {
                            perror("  send() failed");
                            close_conn = TRUE;
                        }
                        free(res_packet);
                        break;
                    }

                    cpt_request_destroy(req);
                    cpt_response_destroy(res);
                } while (FALSE);

                if (close_conn) {
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    compress_array = TRUE;
                }
            }  /* End of existing connection is readable             */
        } /* End of loop through pollable descriptors              */

        if (compress_array) {
            compress_array = FALSE;
            for (i = 0; i < nfds; i++) {
                if (fds[i].fd == -1) {
                    for (j = i; j < nfds; j++) {
                        fds[j].fd = fds[j + 1].fd;
                    }
                    i--;
                    nfds--;
                }
            }
        }

    } while (end_server == FALSE); /* End of serving running.    */

    /* Clean up all of the sockets that are open                 */
    for (i = 0; i < nfds; i++)
    {
        if (fds[i].fd >= 0)
            close(fds[i].fd);
    }
    return ret_val;
}
