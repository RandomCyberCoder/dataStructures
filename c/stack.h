#include "node.h"

typedef struct Stack{
    int size;
    Node *head;
} Stack;

Stack *stckCreate();
void stckDestory(Stack *);
void *stckpop(Stack *);
void stckpush(Stack *, void *);
void *stcktop(Stack *);
int stckisEmpty(Stack *);
