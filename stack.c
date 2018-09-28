#include "stack.h"
#include "da.h"
#include <stdio.h>
#include <stdlib.h>


struct stack{
	DA *store;
	void (*display)(FILE *,void *);
	void (*free)(void *);
};

STACK *newSTACK(void (*d)(FILE *,void *),void (*f)(void *)){
	STACK *items = malloc(sizeof(STACK));
	if(items == 0){
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->display = d;
	items->free = f;
    items->store = newDA(d,f);	//creates dynamic array to implement stack operations
    return items;
}

void push(STACK *items,void *value){
	insertDA(items->store,value);	//add the value to back of dynamic array
}

void *pop(STACK *items){
	return removeDA(items->store);	//remove and return last value of dynamic array
}

void *peekSTACK(STACK *items){
	return getDA(items->store,sizeDA(items->store) - 1);	//return value at the back of the dynamic array
}

int sizeSTACK(STACK *items){
	return sizeDA(items->store);	//return the number of values stored in the stack
}

void displaySTACK(FILE *fp,STACK *items){
	fprintf(fp,"|");
	int x;
	for(x = sizeDA(items->store) - 1;x >= 0;x--){
		items->display(fp,getDA(items->store,x));
		if(x != 0)
			fprintf(fp,",");
	}
	fprintf(fp,"|");
}

void visualizeSTACK(FILE *fp,STACK *items){
	displayDA(fp,items->store);
}

void freeSTACK(STACK *items){
	freeDA(items->store);
	free(items);
}
