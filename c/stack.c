#include "stdlib.h"
#include "stack.h"
#include "errno.h"

Stack *stckCreate(){
    Stack *newStack = (Stack *)malloc(sizeof(Stack));
    newStack->head = NULL;
    newStack->size = 0;
}
void stckDestory(Stack *stack){
    if(stack == NULL) return;

    Node *tmp;
    while((tmp = stack->head) != NULL){
        free(stack->head);
    }
    free(stack);    
}

void *stckpop(Stack *stack){
    if(stack == NULL || stack->size == 0) return NULL;
    else{
        Node *tmp = stack->head;
        void *val = tmp->val;
        stack->head = tmp->next;
        free(tmp);
        (stack->size)--;
        return val;
    }
}

void stckpush(Stack *stack, void *val){
    if(stack == NULL) return;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = val;

    if(stack->size == 0){
        newNode->next = NULL;
    }
    else newNode->next = stack->head;

    (stack->size)++;    
    stack->head = newNode;
}

void *stcktop(Stack *stack){
    if(stack == NULL) return NULL;
    return stack->head;
}

int stckisEmpty(Stack *stack){
    if(stack == NULL) return -1;
    else if(stack->size == 0) return 1;
    else return 0;
}