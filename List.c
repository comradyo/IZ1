#include <stdlib.h>
#include "List.h"

void push_front(List *lst, int value) {
    Node *tmp = (Node *) malloc(sizeof(struct Node));
    tmp->value = value;
    if (lst->head == NULL) {
        tmp->next = NULL;
        tmp->prev = NULL;
    } else {
        tmp->next = lst->head;
        lst->head->prev = tmp;
        tmp->prev = NULL;
    }
    lst->head = tmp;
}

void delete_node(List *lst, Node *node_to_delete) {
    if (node_to_delete != NULL) {
        if (node_to_delete == lst->head) {
            if (node_to_delete->next != NULL)
                node_to_delete->next->prev = NULL;
            lst->head = node_to_delete->next;
        } else {
            if (node_to_delete->next != NULL)
                node_to_delete->next->prev = node_to_delete->prev;
            node_to_delete->prev->next = node_to_delete->next;
        }
        free(node_to_delete);
        node_to_delete = NULL;
    }
}

void clear_list(List *lst) {
    Node *prev = NULL;
    while (lst->head != NULL) {
        prev = lst->head;
        prev->prev = NULL;
        lst->head = lst->head->next;
        free(prev);
    }
    free(lst->head);
    lst->head = NULL;
}

_Bool lists_are_equal(List *lst_1, List *lst_2) {
    if (lst_1 == NULL && lst_2 != NULL || lst_1 != NULL && lst_2 == NULL) return 0;
    if (lst_1 == NULL && lst_2 == NULL) return 1;
    Node *temp_1 = lst_1->head;
    Node *temp_2 = lst_2->head;
    if (temp_1 == NULL && temp_2 != NULL || temp_1 != NULL && temp_2 == NULL) return 0;
    while (temp_1 != NULL && temp_2 != NULL) {
        if (temp_1->value == temp_2->value) {
            temp_1 = temp_1->next;
            temp_2 = temp_2->next;
        } else return 0;
        if (temp_1 == NULL && temp_2 != NULL || temp_1 != NULL && temp_2 == NULL) return 0;
    }
    return 1;
}