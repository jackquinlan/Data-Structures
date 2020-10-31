#include "stdlib.h"
#include "stdio.h"

// 0  -> Highest Priority 
// 15 -> Lowest Priority
#define MAX_PRIORITY 16

// Priority Queue implemented with a "hash table"ish
struct pqueue {
    struct pqueue_list *lists[MAX_PRIORITY];
};

struct pqueue_list {
    struct pqueue_node *head;
    struct pqueue_node *tail;
};

struct pqueue_node {
    unsigned int priority;
    void *data;
    struct pqueue_node *next;
};

/*
 * Create and return a priority queue.
 */ 
struct pq * pq_create(void) {
    int i;
    struct pqueue *pq = malloc(sizeof(struct pqueue));

    for (i = 0; i < MAX_PRIORITY; i++) {
        pq->lists[i] = malloc(sizeof(struct pqueue_list));
        pq->lists[i]->head = NULL;
    }
    return pq;
}

/*
 * Destroy a priority queue if and only if each priority is empty.
 */ 
int pq_destroy(struct pqueue *pq) {
    int i;
    for (i = 0; i < MAX_PRIORITY; i++) {
        if (pq->lists[i]->head != NULL) {
            return -1;
        }
    }
    free(pq);
    return 0;
}

/*
 * Insert a value to the tail of a specific priority.
 */ 
void pq_enqueue(struct pqueue *pq, void *value, unsigned int priority) {
    struct pqueue_node *node = malloc(sizeof(struct pqueue_node));
    node->data = value;
    node->priority = priority;
    node->next = NULL;
    if (pq->lists[priority]->head == NULL) {
        pq->lists[priority]->head = node;
        pq->lists[priority]->tail = node;
    } else {
        pq->lists[priority]->tail->next = node;
        pq->lists[priority]->tail = node;
    }
}

/*
 * Remove the highest priority item and return its value.
 */ 
void *pq_dequeue(struct pqueue *pq) {
    int i;
    int n = -1;
    for (i = 0; i < MAX_PRIORITY; i++) {
        if (pq->lists[i]->head != NULL) {
            n = i;
            break;
        }
    }
    if (n == -1) return NULL;
    struct pqueue_node *temp = pq->lists[n]->head;
    void *value = pq->lists[n]->head->data;
    pq->lists[n]->head = pq->lists[n]->head->next;
    free(temp);
    return value;
}