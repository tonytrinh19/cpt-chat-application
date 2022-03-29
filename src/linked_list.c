//
// Created by Hyung Joon Lee on 2022-03-26.
//

#include "linked_list.h"

// User Linked List
UserLinkedList* create_user_linked_list() {
    UserLinkedList *pReturn = NULL;
    pReturn = (UserLinkedList *)malloc(sizeof(UserLinkedList));

    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(UserLinkedList));
    }

    else {
        printf("ERROR: Memory allocation failed.\n");
        return NULL;
    }

    return pReturn;
}



int add_user_element(UserLinkedList *pList, int position, UserNode element) {
    int ret = FALSE;
    int i = 0;
    UserNode *pPreNode = NULL;
    UserNode *pNewNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position <= pList->user_count) {
            pNewNode = (UserNode *)malloc(sizeof(UserNode));
            if (pNewNode != NULL) {
                *pNewNode = element;
                pNewNode->next = NULL;

                pPreNode = &(pList->header_node);
                for (i = 0; i < position; i++) {
                    pPreNode = (ChannelNode *) pPreNode->next;
                }

                pNewNode->next = pPreNode->next;
                pPreNode->next = pNewNode;

                pList->user_count++;

                ret = TRUE;
            }
            else {
                printf("ERROR: Memory allocation failed : addLLElement()\n");
                return ret;
            }
        }
        else {
            printf("ERROR: [%d] Index out of rage: addLLElement()\n", position);
        }
    }
    return ret;
}


int remove_user_element (UserLinkedList *pList, int position) {
    int ret = FALSE;
    int i = 0;
    int arrayCount = 0;
    UserNode *pPreNode = NULL;
    UserNode *pDelNode = NULL;

    if (pList != NULL) {
        arrayCount = get_user_linked_list_length(pList);
        if (position >= 0 && position < arrayCount) {
            pPreNode = &(pList->header_node);
            for (i = 0; i < position; i++) {
                pPreNode = pPreNode->next;
            }

            pDelNode = pPreNode->next;
            pPreNode->next = pDelNode->next;
            free(pDelNode);

            pList->user_count--;

            ret = TRUE;
        }
        else {
            printf("ERROR: [%d] Index out of rage: deleteLLElement()\n", position);
        }
    }

    return ret;
}


UserNode* get_user_element(UserLinkedList *pList, int position) {
    UserNode *pReturn = NULL;
    UserNode *pNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position < pList->user_count) {
            pNode = &(pList->header_node);
            for (int i = 0; i <= position; i++) {
                pNode = pNode->next;
            }
            pReturn = pNode;
        }
    }
    return pReturn;
}


void delete_user_linked_list(UserLinkedList *pList) {
    int i = 0;

    if (pList != NULL) {
        clear_user_linked_list(pList);
        free(pList);
    }
}


void clear_user_linked_list(UserLinkedList *pList) {
    if (pList != NULL) {
        if(pList->user_count > 0) {
            remove_user_element(pList, 0);
        }
    }
}


int get_user_linked_list_length(UserLinkedList *pList) {
    int ret = 0;

    if (pList != NULL) {
        ret = pList->user_count;
    }

    return ret;
}


int is_user_linked_list_empty(UserLinkedList * pList) {
    int ret = FALSE;

    if (pList != NULL) {
        if (pList->user_count== 0) {
            ret = TRUE;
        }
    }

    return ret;
}


// Channel Linked List
ChannelLinkedList* create_channel_linked_list() {
    ChannelLinkedList *pReturn = NULL;
    pReturn = (ChannelLinkedList *)malloc(sizeof(ChannelLinkedList));

    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(ChannelLinkedList));
    }

    else {
        printf("ERROR: Memory allocation failed.\n");
        return NULL;
    }

    return pReturn;
}



int add_channel_element(ChannelLinkedList *pList, int position, ChannelNode element) {
    int ret = FALSE;
    int i = 0;
    ChannelNode *pPreNode = NULL;
    ChannelNode *pNewNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position <= pList->channel_count) {
            pNewNode = (ChannelNode *)malloc(sizeof(ChannelNode));
            if (pNewNode != NULL) {
                *pNewNode = element;
                pNewNode->next = NULL;

                pPreNode = &(pList->headerNode);
                for (i = 0; i < position; i++) {
                    pPreNode = (ChannelNode *) pPreNode->next;
                }

                pNewNode->next = pPreNode->next;
                pPreNode->next = pNewNode;

                pList->channel_count++;

                ret = TRUE;
            }
            else {
                printf("ERROR: Memory allocation failed : add_channel_element()\n");
                return ret;
            }
        }
        else {
            printf("ERROR: [%d] Index out of rage: add_channel_element()\n", position);
        }
    }
    return ret;
}


int remove_channel_element (ChannelLinkedList *pList, int position) {
    int ret = FALSE;
    int i = 0;
    int arrayCount = 0;
    UserNode *pPreNode = NULL;
    UserNode *pDelNode = NULL;

    if (pList != NULL) {
        arrayCount = get_user_linked_list_length(pList);
        if (position >= 0 && position < arrayCount) {
            pPreNode = &(pList->headerNode);
            for (i = 0; i < position; i++) {
                pPreNode = pPreNode->next;
            }

            pDelNode = pPreNode->next;
            pPreNode->next = pDelNode->next;
            free(pDelNode);

            pList->channel_count--;

            ret = TRUE;
        }
        else {
            printf("ERROR: [%d] Index out of rage: remove_channel_element()\n", position);
        }
    }

    return ret;
}


ChannelNode* get_channel_element(ChannelLinkedList *pList, int position) {
    ChannelNode *pReturn = NULL;
    ChannelNode *pNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position < pList->channel_count) {
            pNode = &(pList->headerNode);
            for (int i = 0; i <= position; i++) {
                pNode = pNode->next;
            }
            pReturn = pNode;
        }
    }
    return pReturn;
}


void delete_channel_linked_list(ChannelLinkedList *pList) {
    int i = 0;

    if (pList != NULL) {
        clear_channel_linked_list(pList);
        free(pList);
    }
}


void clear_channel_linked_list(ChannelLinkedList *pList) {
    if (pList != NULL) {
        if(pList->channel_count > 0) {
            remove_channel_element(pList, 0);
        }
    }
}


int get_channel_linked_list_length(ChannelLinkedList *pList) {
    int ret = 0;

    if (pList != NULL) {
        ret = pList->channel_count;
    }

    return ret;
}


int is_channel_linked_list_empty(ChannelLinkedList * pList) {
    int ret = FALSE;

    if (pList != NULL) {
        if (pList->channel_count== 0) {
            ret = TRUE;
        }
    }
    return ret;
}