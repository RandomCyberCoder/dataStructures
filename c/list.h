#include "node.h"

typedef struct List{
    int size;
    Node *head;
} List;

List *lstcreate();
void lstdestroy(List *);
void *lstget(List *, char *);
void lstinsert(List *, char *, void *);
void *lstremove(List *, char*);
void lstIsEmpty(List *);