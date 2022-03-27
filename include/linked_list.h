//
// Created by Hyung Joon Lee on 2022-03-26.
//
#ifndef TEMPLATE2_LINKED_LIST_H
#define TEMPLATE2_LINKED_LIST_H


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
#include "cpt_response.h"

#define TRUE  1
#define FALSE 0


typedef struct user_struct {
    uint8_t user_id;
    uint8_t user_fd;
}User;


typedef struct channel_struct {
    uint16_t channel_id;
}Channel;



typedef struct user_node_struct {
    User data;
    struct user_node *pLink;
}UserNode;


typedef struct user_node_type {
    int user_count;
    UserNode headerNode;
}UserLinkedList;


typedef struct channel_node_struct {
    Channel data;
    struct channel_node *pLink;
}ChannelNode;


typedef struct channel_node_type {
    int channel_count;
    ChannelNode headerNode;
}ChannelLinkedList;


UserLinkedList* create_user_linked_list();
int add_user_element(UserLinkedList *pList, int position, UserNode element);
int remove_user_element (UserLinkedList *pList, int position);
UserNode* get_user_element(UserLinkedList *pList, int position);

void clear_user_linked_list(UserLinkedList *pList);
int get_user_linked_list_length(UserLinkedList *pList);
void delete_user_linked_list(UserLinkedList *pList);
int is_user_linked_list_empty(UserLinkedList * pList);


ChannelLinkedList* create_channel_linked_list();
int add_channel_element(ChannelLinkedList *pList, int position, ChannelNode element);
int remove_channel_element (ChannelLinkedList *pList, int position);
ChannelNode* get_channel_element(ChannelLinkedList *pList, int position);

void clear_channel_linked_list(ChannelLinkedList *pList);
int get_channel_linked_list_length(ChannelLinkedList *pList);
void delete_channel_linked_list(ChannelLinkedList *pList);
int is_channel_linked_list_empty(ChannelLinkedList * pList);


#endif //TEMPLATE2_LINKED_LIST_H
