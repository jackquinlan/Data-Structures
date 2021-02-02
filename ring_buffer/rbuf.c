#include <assert.h>
#include <stdlib.h>
#include "rbuf.h"

/**
 * Allocates a new ring buffer with a specified capacity
 * and initializes the values associated with it.
 * 
 * Arguments:
 * - @capacity is the capacity of the new ring buffer.
 * 
 * - return: A new buffer on success, NULL on error.
 */ 
struct rbuf_t *
rbuf_init(int capacity)
{
    struct rbuf_t *rbuf = malloc(sizeof(struct rbuf_t));
    if (!rbuf) {
        /* Something went wrong while allocating memory. Aborting ... */
        return NULL;
    }
    rbuf->capacity = capacity;
    rbuf->count    = 0;
    rbuf->head     = 0;
    rbuf->tail     = 0;
    rbuf->buffer   = malloc(sizeof(rbuf->buffer) * capacity);
    return rbuf;
}

/**
 * Frees the memory associated with a ring buffer.
 * 
 * Notes:
 * - Only free the ring buffer if it is empty.
 * 
 * Arguments:
 * - @rbuf is the passed in ring buffer.
 * 
 * - return: 0 on success, -1 on error.
 */ 
int
rbuf_free(struct rbuf_t *rbuf)
{
    if (rbuf == NULL) return -1;
    if (rbuf_curr_size(rbuf)) {
        return -1;
    }
    free(rbuf);
    return 0;
}

/**
 * Resets the head and tail pointer of a ring buffer to zero.
 * 
 * Arguments:
 * - @rbuf is the passed in ring buffer.
 * 
 * - return: 0 on success.
 */ 
int
rbuf_reset(struct rbuf_t *rbuf)
{
    if (rbuf == NULL) return -1;
    rbuf->head = 0;
    rbuf->tail = 0;
    return 0;
}

/**
 * Get the current size of a ring buffer.
 * 
 * Arguments:
 * - @rbuf is the passed in ring buffer.
 * 
 * - return: the current size of the buffer on success.
 */ 
int
rbuf_curr_size(struct rbuf_t *rbuf)
{
    if (rbuf == NULL) return -1;
    return rbuf->count;
}

/**
 * Add an element to the head pointer of a ring buffer.
 * 
 * Notes:
 * - If the buffer is full, do not add the data.
 * 
 * Arguments:
 * - @rbuf is the passed in ring buffer.
 * - @data is the data to be added to the buffer.
 * 
 * - return: 0 on success, -1 on error.
 */ 
int
rbuf_add(struct rbuf_t *rbuf, short data)
{
    if (rbuf == NULL) return -1;
    if (rbuf->capacity == rbuf_curr_size(rbuf)) {
        return -1;
    }
    rbuf->buffer[rbuf->head] = data;
    rbuf->head = (rbuf->head + 1) % rbuf->capacity;
    rbuf->count++;
    return 0;
}

/**
 * Remove an element from the tail pointer of a ring buffer.
 * 
 * Arguments:
 * - @rbuf is the passed in ring buffer.
 * 
 * - return: the element that was removed, -1 on error.
 */ 
short
rbuf_remove(struct rbuf_t *rbuf)
{
    if (rbuf == NULL) return -1;
    if (rbuf_curr_size(rbuf) == 0) {
        return -1;
    }
    short ret = rbuf->buffer[rbuf->tail];
    if (!ret) {
        return -1;
    }
    rbuf->tail = (rbuf->tail + 1) % rbuf->capacity;
    rbuf->count--;
    return ret;
}


