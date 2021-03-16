#ifndef IZ1_LIST_H
#define IZ1_LIST_H

#include "stdbool.h"

//Структура "узел списка".
typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

//Структура "список".
typedef struct List {
    Node *head;
} List;

//Вставка элемента в начало списка.
void push_front(List *lst, int value);

//Удаление элемента.
void delete_node(List *lst, Node *node_to_delete);

//Очистка списка.
void clear_list(List *lst);

//Проверка, являются ли два списка равными по значениям.
_Bool lists_are_equal(List* lst_1, List* lst_2);

#endif //IZ1_LIST_H
