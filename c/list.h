#include "node.h"

typedef struct List{
    int size;
    Node *head;
    Node *tail;
} List;

List *lstcreate();
void lstdestroy(List *);
int lstinsert(List *, void *, int);
void *lstremove(List *, char*);
void *lstget(List *, int);
void lstIsEmpty(List *);