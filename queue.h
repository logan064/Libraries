#include "cda.h"

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

#include <stdio.h>

typedef struct queue QUEUE;

extern QUEUE *newQUEUE(void (*d)(FILE *,void *),void (*f)(void *)); //returns structure queue is based upon and takes display & free fns
extern void enqueue(QUEUE *items,void *value);  //inserts the item to back of queue
extern void *dequeue(QUEUE *items); //remove and return first value on queue
extern void *peekQUEUE(QUEUE *items); //return first value on queue
extern int sizeQUEUE(QUEUE *items); // returns the number of values in queue
extern void displayQUEUE(FILE *,QUEUE *items);  //print items on queue from first to last
extern void visualizeQUEUE(FILE *,QUEUE *items);  //prints the underlying structure
extern void freeQUEUE(QUEUE *items);  //frees all memory of the itemsqueue

#endif
