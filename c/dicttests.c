/* Tests functions for implementing a dictionary.
 * CSC 357, Assignment 3
 * Given tests, Winter '24 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "dict.h"

/* test01: Tests creating dictionaries. */
void test01() {
    Dict *dct = dctcreate();

    assert(dct != NULL);
    assert(dct->cap >= 1);
    assert(dct->arr != NULL);
    assert(dct->size == 0);

    dctdestroy(dct);
}

/* test02: Tests inserting into dictionaries. */
void test02() {
    Dict *dct = dctcreate();

    dctinsert(dct, "a", (void *)1);
    dctinsert(dct, "b", (void *)3);
    dctinsert(dct, "f", (void *)2);

    assert(dct->size == 3);
    assert(dctget(dct, "a") == (void *)1);
    assert(dctget(dct, "b") == (void *)3);
    assert(dctget(dct, "f") == (void *)2);

    dctdestroy(dct);
}

/* test03: Tests removing from dictionaries. */
void test03() {
    Dict *dct = dctcreate();

    dctinsert(dct, "a", (void *)1);
    dctinsert(dct, "b", (void *)3);
    dctinsert(dct, "f", (void *)2);
    dctremove(dct, "b");
    dctinsert(dct, "c", (void *)2);

    assert(dct->size == 3);
    assert(dctget(dct, "a") == (void *)1);
    assert(dctget(dct, "c") == (void *)2);
    assert(dctget(dct, "f") == (void *)2);
    assert(dctget(dct, "b") == NULL);

    dctdestroy(dct);
}

/* test04: Tests enumerating keys in dictionaries. */
void test04() {
    char **keys;
    Dict *dct = dctcreate();

    dctinsert(dct, "a", (void *)1);
    dctinsert(dct, "b", (void *)3);
    dctinsert(dct, "f", (void *)2);
    dctremove(dct, "b");
    dctinsert(dct, "c", (void *)2);

    /* NOTE: Dictionaries are unordered, and my tests will not assume any
     *       particular arrangement of keys within the enumerating array. */

    keys = dctkeys(dct);
    assert(
     (!strcmp(keys[0], "a") && !strcmp(keys[1], "c") && !strcmp(keys[2], "f"))||
     (!strcmp(keys[0], "a") && !strcmp(keys[1], "f") && !strcmp(keys[2], "c"))||
     (!strcmp(keys[0], "c") && !strcmp(keys[1], "a") && !strcmp(keys[2], "f"))||
     (!strcmp(keys[0], "c") && !strcmp(keys[1], "f") && !strcmp(keys[2], "a"))||
     (!strcmp(keys[0], "f") && !strcmp(keys[1], "a") && !strcmp(keys[2], "c"))||
     (!strcmp(keys[0], "f") && !strcmp(keys[1], "c") && !strcmp(keys[2], "a")));
    free(keys);

    dctdestroy(dct);
}

void test05() {
    Dict *dct = dctcreate();


    assert(dct != NULL);
    assert(dct->size == 0);

    dctinsert(dct, "test", NULL);
    assert(dctget(dct, "test") == NULL);
    dctremove(dct, "test");

    dctinsert(dct, "", "empty");
    assert(strcmp(dctget(dct, ""), "empty") == 0);
    assert(dct->size == 1);
    dctremove(dct, "");

    assert(dctget(dct, "none") == NULL);

    assert(dctremove(dct, "none") == NULL);
    assert(dctremove(dct, NULL) == NULL);
    assert(dct->size == 0);
    
    assert(dctget(NULL, "test") == NULL);
    printf("made it to here\n");
    assert(dctremove(NULL, "test") == NULL);
    printf("made it to here\n");

    dctdestroy(dct);
}
void test06() {
    Dict *dct1 = dctcreate();
    Dict *dct2 = dctcreate();
    Dict *innerDict = dctcreate();
    Dict *retrievedDict;

    assert(dct1 != NULL);
    assert(dct2 != NULL);
    assert(innerDict != NULL);

    dctinsert(dct1, "w1", (void *)1);
    dctinsert(dct1, "w2", (void *)1);

    dctinsert(dct2, "ww1", (void *)1);
    dctinsert(dct2, "ww2", (void *)1);
    dctinsert(dct2, "ww3", (void *)1);

    assert(dct1->size == 2);
    assert(dct2->size == 3);

    dctinsert(innerDict, "1", (void *)1);
    dctinsert(innerDict, "2", (void *)2);

    dctinsert(dct1, "innerDict", innerDict);
    assert(dct1->size == 3);
    dctinsert(dct2, "dict1", dct1);
    assert(dct2->size == 4);

    retrievedDict = dctget(dct1, "innerDict");
    assert(retrievedDict == innerDict);
    assert(dctget(retrievedDict, "1") == (void *)1);
    assert(dctget(retrievedDict, "2") == (void *)2);
    assert(dctget(dct2, dctget(dct1, "innterDict")) == NULL);
    assert(dctget(dctget(dct2, "dict1"), "innerDict") == innerDict);

    dctdestroy(innerDict);
    dctdestroy(dct1);
    dctdestroy(dct2);
}

int main(void) {

    test01();
    test02();
    test03();
    test04();
    printf("complete 4\n");
    test05();
    printf("complete 5\n");
    test06();
    printf("complete 6\n");

    return 0;
}
