#include "node.h"

typedef struct Queue {
    int size;
    Node *head;
    Node *tail;
} Queue;

Queue *qCreate();
void qDestroy(Queue *);
void *qPop(Queue *);
void qPush(Queue *, void *);