#include <assert.h>
#include <stdio.h>
#include "stack.h"

void test01(){
    Stack *stack = NULL;
    stack = stckCreate();
    assert(stack != NULL);
    assert(stack->size == 0);
    assert(stack->head == NULL);

    stckDestory(stack);
}

void test02(){
    Stack *stack = stckCreate();
    stckpush(stack, (void *)1);
    stckpush(stack, (void *)2);
    stckpush(stack, (void *)3);
    assert(stack->head != NULL);
    assert(stack->size == 3);
    assert(!stckisEmpty(stack));
    assert(stckpop(stack) == (void *)3);
    assert(stckpop(stack) == (void *)2);
    assert(stckpop(stack) == (void *)1);
    assert(stckisEmpty(stack));
    assert(stack->head == NULL);
    assert(stack->size == 0);
    stckpush(stack, (void *)1);
    assert(stack->size == 1);
    assert(stckpop(stack) == (void *)1);
    assert(stack->size == 0);
    assert(stckisEmpty(stack));
    assert(stack->head == NULL);


}

int main(void){
    test01();
    test02();
    return 0;
}