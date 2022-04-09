#ifndef MORSE_COMMON_H
#define MORSE_COMMON_H

/*
 * This file is part of dc_dump.
 *
 *  dc_dump is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dc_dump.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <inttypes.h>

extern uint16_t current_channel;

enum server_res_code {
    SEND = 1,
    LOGOUT,
    GET_USERS,
    CREATE_CHANNEL,
    JOIN_CHANNEL,
    LEAVE_CHANNEL,
    LOGIN,
    MESSAGE,
    USER_CONNECTED,
    USER_DISCONNECTED,
    MESSAGE_FAILED,
    CHANNEL_CREATED,
    CHANNEL_CREATION_ERROR,
    CHANNEL_DESTROYED,
    USER_JOINED_CHANNEL,
    USER_LEFT_CHANNEL,
    USER_LIST,
    UKNOWN_CMD,
    LOGIN_FAIL,
    UKNOWN_CHANNEL,
    BAD_VERSION,
    SEND_FAILED,
    CHAN_ID_OVERFLOW,
    MSG_OVERFLOW,
    MSG_LEN_OVERFLOW,
    CHAN_EMPTY,
    INVALID_ID,
    UNAUTH_ACCESS,
    SERVER_FULL
};

#endif // TEMPLATE_COMMON_H
