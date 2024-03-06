typedef struct Node2 {
    char *key;
    void *val;
    struct Node2 *next;
} Node2;

/* Represents a collection of key-value pairs. */
typedef struct Queue {
    int size;
    Node2 *head;
    Node2 *tail;
} Queue;

Queue *qCreate();
void qDestroy(Queue *);
void *qPop(Queue *);
void qPush(Queue *, void *);