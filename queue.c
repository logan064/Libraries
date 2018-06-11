#include "queue.h"
#include "cda.h"
#include <stdio.h>
#include <stdlib.h>


struct queue{
	CDA *store;
	void (*display)(FILE *,void *);
};


QUEUE *newQUEUE(void (*d)(FILE *,void *)){
	QUEUE *items = malloc(sizeof(QUEUE));
	if(items == 0){
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->display = d;
    items->store = newCDA(d);	//creates circular dynamic array to implement queue operations
    return items;
}

void enqueue(QUEUE *items,void *value){
	insertCDAback(items->store,value);	//insert value at the back of the circular dynamic array
}

void *dequeue(QUEUE *items){
	return removeCDAfront(items->store);	//return and remove the first value in the queue
}

void *peekQUEUE(QUEUE *items){
	return getCDA(items->store,0);	//return the first value in the queue
}

int sizeQUEUE(QUEUE *items){
	return sizeCDA(items->store);
}

void displayQUEUE(FILE *fp,QUEUE *items){
	fprintf(fp,"<");
	int x;
	for(x =  0;x < sizeQUEUE(items);x++){
		items->display(fp,getCDA(items->store,x));
		if(x != sizeQUEUE(items) - 1)
			fprintf(fp, ",");
	}
	fprintf(fp,">");
}

void visualizeQUEUE(FILE *fp,QUEUE *items){
	displayCDA(fp,items->store);
}
