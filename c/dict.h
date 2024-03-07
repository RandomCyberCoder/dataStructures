#include "node.h"

typedef struct Dict {
    int cap;
    Node **arr;
    int size;
} Dict;

Dict *dctcreate();
void dctdestroy(Dict *);
void *dctget(Dict *, char *);
void dctinsert(Dict *, char *, void *);
void *dctremove(Dict *, char *);
char **dctkeys(Dict *);
Node **nodeList(Dict *); 

