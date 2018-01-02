#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>



struct QueueNode 
{
    int key;
    int order;
    struct QueueNode *nextNode;
    void *data;
} QueueNode;


struct queueStruct
{
	struct QueueNode *head;
    struct QueueNode *tail;
    int size;
} queueStruct;


struct QueueNode* newNode(int key, int order)
{
    struct QueueNode *temp  = malloc(sizeof(QueueNode));
    temp->key   = key;
    temp->order = order;
    temp->nextNode  = NULL;

    return temp;
}


struct queueStruct *createQueue()
{
    struct queueStruct *queue = malloc(sizeof(struct queueStruct));
    queue->head = queue->tail = NULL;

    return queue;
}

struct QueueNode *deQueue(struct queueStruct *queue) //delets elements from the queue
{
    if (queue->head == NULL)
    {
    	return NULL;
    }

    struct QueueNode *temp = queue->head;
    queue->head = queue->head->nextNode;

    if (queue->head == NULL)
    {
    	queue->tail = NULL;
    }
    return temp;
}

void enQueue(struct queueStruct *queue, int key, int order) // add elements to the queue 
{
    struct QueueNode *temp = newNode(key, order);

    if (queue->tail == NULL)
    {
        queue->head = queue->tail = temp;
        return;
    }

    queue->tail->nextNode = temp;
    queue->tail       = temp;
}

void push(struct queueStruct *queue, void *data)
{
    struct QueueNode *temp  = malloc(sizeof(QueueNode));
    temp->data = data;
    temp->nextNode = NULL;
    if(queue->head == NULL)
    {
        queue->head = queue->tail = temp;
    }
    else
    {
        queue->tail->nextNode = temp;
        queue->tail = temp;
    }

    queue->size++;
}

void *pop(struct queueStruct *queue)
{
    if(queue->head == NULL)
    {
        return NULL;
    }

    QueueNode *temp = queue->head;
    void *data = queue->head->data;

    queue->head = queue->head->nextNode;
    
    free(temp);
    queue->size--;

    return data;
}

#endif