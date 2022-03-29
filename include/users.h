//
// Created by toni on 2022-03-25.
//

#ifndef TEMPLATE2_USERS_H
#define TEMPLATE2_USERS_H

typedef struct user_list Users;

struct user_list
{
    int user_id;
    Users * next;
};


#endif //TEMPLATE2_USERS_H
