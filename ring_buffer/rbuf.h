/**
 * A simple API implementation for a ring buffer in C.
 * 
 * Implementation:
 * - This file contains the APIs structs and function prototypes.
 * - The API is implemented in the file `rbuf.c`.
 * - The API is tested in the file `rbuf_test.c`.
 * 
 * Notes:
 * - This specific implementation uses short values in the buffer
 *   which can easily be swapped for any data type you require.
 *   This could include int, double, char, char *, void *, etc.
 * - The main documentation for this implementation is located in `rbuf.c`.
 * 
 */ 

struct rbuf_t {
    unsigned int head;     // Next index to be written to
    unsigned int tail;     // Next index to read from
    unsigned int count;    // Current size of the buffer
    unsigned int capacity; // Maximum capacity of the buffer
    short *buffer;         // Array containing buffer values
};

struct rbuf_t *rbuf_init(int capacity);
int rbuf_free(struct rbuf_t *buffer);
int rbuf_reset(struct rbuf_t *buffer);
int rbuf_curr_size(struct rbuf_t *buffer);
int rbuf_add(struct rbuf_t *buffer, short data);
short rbuf_remove(struct rbuf_t *buffer);




