#include <stdlib.h>
#include "queue.h"

Queue *qCreate(){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}
void qDestroy(Queue *queue){
    if(queue == NULL){
        return;
    }
    else{
        Node *tmp = NULL;
        while(queue->head != NULL){
            tmp = queue->head->next;
            free(queue->head);
            queue->head = tmp;
        }
        free(queue);
    }
}
void *qPop(Queue *queue){
    if(queue == NULL || queue->size == 0){
        return NULL;
    }
    else if(queue->size == 1){
        void *ret = queue->head->val;
        free(queue->head);
        queue->head = NULL;
        queue->tail = NULL;
        (queue->size)--;
        return ret;
    }
    else{
        void *ret = queue->head->val;
        Node *tmp = queue->head;
        queue->head = queue->head->next;
        free(tmp);
        (queue->size)--;
        return ret;
    }
}
void qPush(Queue *queue, void *valAdd){
    if(queue == NULL){
        return;
    }
    Node *ndAdd = (Node *)malloc(sizeof(Node));
    ndAdd->next = NULL;
    ndAdd->val = valAdd;
    ndAdd->key = NULL;
    if(queue->size == 0){
        queue->head = ndAdd;
        queue->tail = ndAdd;
    }
    else{
        queue->tail->next = ndAdd;
        queue->tail = ndAdd;
    }
    (queue->size)++;
}