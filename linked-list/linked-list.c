#include "stdlib.h"
#include "stdio.h"

struct linked_list {
    struct node *head;
    struct node *tail;
};

struct node {
    void *data;
    struct node *next;
};

/*
 * Creates a new linked list and returns it.
 */
struct linked_list *list_create(void) {
    struct linked_list *ll = malloc(sizeof(struct linked_list));
    ll->head = NULL;
    return ll;
}

/*
 * Deletes a linked list if and only if it is empty.
 */
int list_destroy(struct linked_list *ll) {
    if (list_length(ll) != 0) return 0;
    free(ll);
    return 1;
}

/*
 * Returns the integer length of a linked list.
 */
int list_length(struct linked_list *ll) {
    if (ll->head == NULL) return 0;
    int length = 1;
    struct node *it = ll->head;
    while (it->next != NULL) {
        length++;
        it = it->next;
    }
    return length;
}

/*
 * Insert a node at the tail of a linked list.
 */ 
void list_insert(struct linked_list *ll, void *data) {
    struct node *node = malloc(sizeof(struct node));
    node->data = data;
    node->next = NULL;
    if (ll->head == NULL) {
        ll->head = node;
        ll->tail = node;
    } else {
        ll->tail->next = node;
        ll->tail = node;
    }
}

/*
 * Removes an item from the head of a linked list and returns the value.
 */
void *list_remove(struct linked_list *ll) {
    if (ll->head == NULL) return NULL;
    struct node *temp = ll->head;
    void* value = temp->data;
    ll->head = ll->head->next;
    free(temp);
    return value;
}
