#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "rbuf.h"

#define VALUE 7
#define CAPACITY 3

/**
 * Test a specific part of the ring buffer against an expected output.
 * 
 * Notes:
 * - If the specific test fails, an immediate assert message will be printed to the terminal.
 * - If the test passes, nothing will be printed to the terminal.
 * 
 * Arguments:
 * - @st is what is being tested.
 * - @exp is the expected result.
 * 
 */ 
#define ASSERT(st, exp)       \
do {                          \
    (st);                     \
    assert(exp);              \
} while(0);

int
main(int argc, char **argv)
{
    int ret;
    int i;      
    struct rbuf_t *rbuf;

    printf("--------------------------------\n");
    printf("RUNNING RING BUFFER TESTS...\n");
    printf("--------------------------------\n");
    sleep(2);
    ASSERT(ret = rbuf_curr_size(NULL), ret == -1);
    ASSERT(ret = rbuf_add(NULL, VALUE), ret == -1);
    ASSERT(ret = rbuf_remove(NULL), ret == -1);
    ASSERT(rbuf_free(NULL), 1);
    ASSERT(ret = rbuf_reset(NULL), ret == -1);
    printf("[PASSED] Test null safety.\n");
    sleep(2);

    ASSERT(rbuf = rbuf_init(CAPACITY), rbuf != NULL);
    ASSERT(ret = rbuf_curr_size(rbuf), ret == 0);
    ASSERT(ret = rbuf_remove(rbuf), ret == -1);
    ASSERT(ret = rbuf_add(rbuf, VALUE), ret == 0);
    ASSERT(ret = rbuf_remove(rbuf), ret == VALUE);
    printf("[PASSED] Test basic functionality.\n");
    sleep(2);

    for (i = 0; i < CAPACITY; i++) {
        ASSERT(ret = rbuf_add(rbuf, VALUE + i), ret == 0);
        ASSERT(ret = rbuf_curr_size(rbuf), ret == i + 1);
    }
    ASSERT(ret = rbuf_add(rbuf, VALUE + CAPACITY), ret == -1);
    printf("[PASSED] Test filling up the buffer.\n");
    sleep(2);

    for (i = 0; i < CAPACITY; i++) {
        ASSERT(ret = rbuf_curr_size(rbuf), ret == CAPACITY - i);
        ASSERT(ret = rbuf_remove(rbuf), ret == VALUE + i);
    }
    ASSERT(ret = rbuf_remove(rbuf), ret == -1);
    printf("[PASSED] Test emptying up the buffer.\n");
    sleep(2);

    ASSERT(ret = rbuf_free(rbuf), ret == 0);
    printf("[PASSED] Test freeing the buffer.\n");
    sleep(2);

    printf("--------------------------------\n");
    printf("[PASSED] All tests completed with 0 errors.\n");
}

