#include <stdlib.h>
#include "list.h"

List *lstcreate(){
    List *list = (List *)malloc(sizeof(list));
    list->size = 0;
    list->head = NULL;
}

/*return 0 on success and -1 on a failure
  position 0 = to the first position in the list
  position list->size means to insert after last element in the list
  position list-size -1 means to insert before the last element in the list*/
int lstinsert(List *list, void *val, int position){
    if(list == NULL) return -1;
    else if(list->size < position) return -1;
    else if(position == list->size){
        if(list->size)
    }
}

/* List *lstcreate();
void lstdestroy(List *);
void *lstget(List *, char *);
void listinsert(List *, char *, void *);
void *lstremove(List *, char*);
void lstIsEmpty(List *); */