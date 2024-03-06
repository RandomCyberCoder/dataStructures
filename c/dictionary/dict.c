/* Defines functions for implmenting a dictionary.
 * CSC 357, Assignment 3
 * Given code, Winter '24 */

/*cast void(*) to long*/
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#define DEFAULT_CAP 2

/* dcthash: Hashes a string key.
 * NOTE: This is certainly not the best known string hashing function, but it
 *       is reasonably performant and easy to predict when testing. */
static unsigned long int dcthash(char *key) {
    unsigned long int code = 0, i;

    for (i = 0; i < 8 && key[i] != '\0'; i++) {
        code = key[i] + 31 * code;
    }

    return code;
}

/* recursive */
static void deleteNodeChain(Node * dltMe){
    if(dltMe != NULL){
        deleteNodeChain(dltMe->next);
        free(dltMe->key);
        free(dltMe);
    }
    return;
}

/* recursive: called from rehash */
static void rehashChain(Node * node, Node ** newArr, int newCap){
    unsigned long int hashCode;
    if(node != NULL){
        rehashChain(node->next, newArr, newCap);
        hashCode = dcthash(node->key) % newCap;
        
        node->next = newArr[hashCode];
        newArr[hashCode] = node;
    }
    return;
}

/*rehash needs rehashChain to rehash a chain of nodes*/
static void rehash(Dict * dct, Node* addTo){
    int index;
    unsigned long int hashCode;
    /* int nodeIndex; */
    int newCap = (dct->cap) * 2 + 1;
    /* Node *node = NULL; */
    Node ** newArr = (Node **)malloc(sizeof(Node * ) * (newCap));

    

    /*everything int the new arr dict will be set to NULL*/
    for(index = 0; index < newCap; index++){
        newArr[index] = NULL;
    }
    
    /*hash addTo into dict arr*/
    hashCode = dcthash(addTo->key) % newCap;
    newArr[hashCode] = addTo;
    addTo->next = NULL;

    /*rehash the old arr dict*/
    for(index = 0; index < dct->cap; index++){
        if(dct->arr[index] != NULL){
            rehashChain(dct->arr[index], newArr, newCap);
            dct->arr[index] = NULL;
        }
    }

    /* deallocate old arr
       pass arr the new arr */
    free(dct->arr);
    dct->arr = newArr;
    dct->cap = newCap;

    return;
}

/*used in dctget()*/
static void *findKey(Node *node, char *key){
    /* base case: key not found */
    if(node == NULL){
        return NULL;
    }
    /*we found the node*/
    else if(!strcmp(node->key,key)){
        return node->val;
    }
    /*we didn't find the node yet*/
    else{
        return findKey(node->next, key);
    }

    return NULL;
}

/*use in dctremove()*/
static void *removeKey(Node *prev, Node *current, char *key){
    void *retThis;
    /*key is not in the dict*/
    if(current == NULL){
        return NULL;
    }
    /*if we found the key in the dict*/
    else if(!strcmp(current->key, key)){
        retThis = current->val;
        prev->next = current->next;
        free(current->key);
        free(current);
        return retThis;
    }
    /*if we haven't found it*/
    else{
        return removeKey(current, current->next, key);
    }

    return NULL;
}


/* dctcreate: Creates a new empty dictionary.
 * TODO: Implement this function. It should return a pointer to a newly
 *       dynamically allocated dictionary with an empty backing array. */
Dict *dctcreate() {
    int index;

    Dict *create = (Dict *)malloc(sizeof(Dict));
    create->size = 0;
    create->cap = DEFAULT_CAP;
    create->arr = (Node **)malloc(sizeof(Node *) * DEFAULT_CAP);

    for(index = 0; index < DEFAULT_CAP; index++){
        create->arr[index] = NULL;
    }

    return create;
}

/* dctdestroy: Destroys an existing dictionary.
 * TODO: Implement this function. It should deallocate a dictionary, its
 *       backing array, and all of its nodes. */
void dctdestroy(Dict *dct) {
    int index;
    if(dct == NULL){
        return;
    }
    /*loop thorugh array delete nodes*/
    for(index = 0; index < dct->cap; index++){
        if(dct->arr[index] != NULL){
            deleteNodeChain(dct->arr[index]);
            dct->arr[index] = NULL;
        }
    }
    free(dct->arr);
    free(dct);
    dct = NULL;

    return;
}

/* dctget: Gets the value to which a key is mapped.
 * TODO: Implement this function. It should return the value to which "key" is
 *       mapped, or NULL if it does not exist. */
void *dctget(Dict *dct, char *key) {
    unsigned long int hashCode;
    if(dct == NULL || key == NULL){
        return NULL;
    }
    hashCode = dcthash(key) % dct->cap;
    if(dct->arr[hashCode] == NULL){
        return NULL;
    }
    else{
        return findKey(dct->arr[hashCode], key);
    }

    return NULL;
}

/* dctinsert: Inserts a key, overwriting any existing value.
 * TODO: Implement this function. It should insert "key" mapped to "val".
 * NOTE: Depending on how you use this dictionary, it may be useful to insert a
 *       dynamically allocated copy of "key", rather than "key" itself. Either
 *       implementation is acceptable, as long as there are no memory leaks. */
void dctinsert(Dict *dct, char *key, void *val) {
    unsigned long int mapTo;
    Node *insert;
    char *string;
    Node *current;
    if(dct == NULL || key == NULL || val == NULL){
        return;
    }
    mapTo = dcthash(key) % (dct->cap);
    insert = (Node *)malloc(sizeof(Node));
    current = dct->arr[mapTo];

    insert->val = val;
    insert->next = NULL;

    /*if not in dict arr but will be the first node in linked list*/
    if(current == NULL){
        dct->size += 1;
        string = (char *)malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(string, key);
        insert->key = string;

        if(dct->size > dct->cap / 2){
            rehash(dct, insert);
        }
        else{
            dct->arr[mapTo] = insert;
            insert->next = NULL; 
        }
        
    }
    else{
        while((current->next != NULL) && strcmp(current->key, key)){
            current = current->next;
        }
        /* if not in dict */
        if(strcmp(current->key, key)){
            dct->size += 1;

            string = (char *)malloc(sizeof(char) * (strlen(key) + 1));
            strcpy(string, key);
            insert->key = string; 
            if(dct->size > dct->cap /2){
                rehash(dct, insert);
            }
            else{
                insert->next = current->next;
                current->next = insert;
            }
        }
        /* if in dict */
        else{ 
            current->val = val;
            free(insert);
        }
    }
    return;
}

/* dctremove: Removes a key and the value to which it is mapped.
 * TODO: Implement this function. It should remove "key" and return the value
 *       to which it was mapped, or NULL if it did not exist. */
void *dctremove(Dict *dct, char *key) {
    unsigned long int hashCode;
    void *retThis;
    Node *current;
    if(key == NULL || dct == NULL){
        return NULL;
    }
    hashCode = dcthash(key) % dct->cap;
    current = dct->arr[hashCode];
    /*start of linked list doesn't point to a Node so *key is not in the dict*/
    if(current == NULL){
        return NULL;
    }
    /*if key is in the first node of linked list*/
    else if(!strcmp(current->key, key)){
        dct->size -= 1;
        retThis = current->val;
        dct->arr[hashCode] = current->next;
        free(current->key);
        free(current);
        return retThis;
    }
    else{
        retThis = removeKey(current, current->next, key);
        if(retThis != NULL){
            dct->size -= 1;
        }
        return retThis;
    }
    return NULL;
}

void addKeys(Node *current, char **arrCh,int *charIndex){
    if(current!=NULL){
        addKeys(current->next, arrCh, charIndex);
        arrCh[*charIndex] = current->key;
        *charIndex += 1;
    }
}
/* dctkeys: Enumerates all of the keys in a dictionary.
 * TODO: Implement this function. It should return a dynamically allocated array
 *       of pointers to the keys, in no particular order, or NULL if empty. */
char **dctkeys(Dict *dct) {
    char **retThis;
    int *charIndex;
    int arrIndex;
    if(dct == NULL){
        return NULL;
    }
    charIndex = (int *)malloc(sizeof(int));
    retThis = (char **)malloc(sizeof(char *) * dct->size);
    *charIndex = 0;

    if(dct->size == 0){
        return NULL;
    }

    for(arrIndex = 0; arrIndex < dct->cap; arrIndex++){
        if(dct->arr[arrIndex] != NULL){
            addKeys(dct->arr[arrIndex], retThis, charIndex);
        }
    }

    free(charIndex);
    return retThis;
}

/*called only from nodelist*/
void addToList(Node **list, int *listIndex, Node *node){
    if(node != NULL){
        addToList(list, listIndex, node->next);
        list[*listIndex] = node;
        *listIndex += 1;
    }
}


Node **nodeList(Dict *dct){
    int *indexList;
    Node **retThis;
    int index;
    if(dct->size == 0){
        return NULL;
    }
    indexList = (int *)malloc(sizeof(int));
    retThis = (Node **)malloc(sizeof(Node *) * dct->size);
    *indexList = 0;

    for(index = 0; index < dct->cap; index++){
        if(dct->arr[index] != NULL){
            addToList(retThis, indexList,  dct->arr[index]);
        }
    }
    
    free(indexList);
    /*free retThis in the caller function*/
    return retThis;
} 