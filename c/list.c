#include <stdlib.h>
#include "list.h"

List *lstcreate(){
    List *list = (List *)malloc(sizeof(list));
    list->size = 0;
    list->head = NULL;
}

void *lstinsert()

/* List *lstcreate();
void lstdestroy(List *);
void *lstget(List *, char *);
void listinsert(List *, char *, void *);
void *lstremove(List *, char*);
void lstIsEmpty(List *); */