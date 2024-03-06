#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"

/* test01: Tests creating dictionaries. */
void test01() {
    Queue *queue = qCreate();

    assert(queue != NULL);
    assert(queue->size == 0);
    assert(queue->head == NULL);
    assert(queue->tail == NULL);

    qDestroy(queue);
}

void test02(){
    Queue *queue = qCreate();

    qPush(queue, (void *)1);
    qPush(queue, (void *)2);
    qPush(queue, (void *)3);
    assert(queue->size == 3);

    assert(qPop(queue) == (void *)1);
    assert(qPop(queue) == (void *)2);
    assert(qPop(queue) == (void *)3);
    assert(queue->size == 0);


    qDestroy(queue);
}

void test03(){
    Queue *queue = qCreate();

    qPush(queue, (void *)1);
    assert(queue->size == 1);

    assert(qPop(queue) == (void *)1);
    assert(queue->size == 0);
    assert(qPop(queue) == NULL);


    qDestroy(queue);

}

int main(void){
    test01();
    test02();
    test03();
    printf("All tests passed\n");

    return 0;
}