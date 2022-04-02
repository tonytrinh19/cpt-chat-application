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
                    pPreNode = (UserNode *) pPreNode->next;
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


void display_user_linked_list(UserLinkedList* pList) {
    int i = 0;

    if (pList != NULL) {
        printf("Current number of element: %d \n", pList->user_count);

        for (i = 0; i < pList->user_count; i++) {
            printf("[%d] : %s\n", i, get_user_element(pList, i)->user_id);
        }
    }
    else {
        printf("No element.\n");
    }
}




