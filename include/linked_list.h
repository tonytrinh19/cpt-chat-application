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

#define TRUE  1
#define FALSE 0


typedef struct user_node {
    uint8_t user_fd;
    uint8_t *user_id;
    struct user_node *next;
}UserNode;


typedef struct user_linked_list {
    int user_count;
    UserNode header_node;
}UserLinkedList;



UserLinkedList* create_user_linked_list();
int add_user_element(UserLinkedList *pList, int position, UserNode element);
int remove_user_element (UserLinkedList *pList, int position);
UserNode* get_user_element(UserLinkedList *pList, int position);

void clear_user_linked_list(UserLinkedList *pList);
int get_user_linked_list_length(UserLinkedList *pList);
void delete_user_linked_list(UserLinkedList *pList);
int is_user_linked_list_empty(UserLinkedList * pList);
void display_user_linked_list(UserLinkedList* pList);
int search(UserNode * head, uint8_t user_fd);


#endif //TEMPLATE2_LINKED_LIST_H