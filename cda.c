#include "cda.h"
#include <stdio.h>
#include <stdlib.h>

struct cda{
	void **array;	//holds the items
	int size,capacity,factor,front,back;	//factor is used to grow and shrink array //front and back keep track of the index's
	double minRatio;	//minimum ratio before need to shrink array
	void (*display)(FILE *,void *);	//used to display the generic value stored
};

static void growCDA(CDA *items);	//grows array by the factor
static void shrinkCDA(CDA *items);	//shrinks array by the factor
static int correctIndex(int index,CDA *items); //returns the index used in the underlying array

CDA *newCDA(void (*d)(FILE *,void *)){
	CDA *items = malloc(sizeof(CDA));
    if(items == 0){
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->size = 0;
    items->capacity = 1;
    items->array = malloc(sizeof(void*) * items->capacity);
    items->factor = 2;
    items->minRatio = 0.25;
    items->front = 0;
    items->back = 0;
    items->display = d;
    return items;
}

void insertCDAfront(CDA *items,void *value){
	if(items->size == 0){	//empty so add back and return
		insertCDAback(items,value);
		return;
	}
	growCDA(items);
	items->front = correctIndex(items->front - 1,items);	//set front to new index
	items->array[items->front] = value;
	items->size++;
}

void insertCDAback(CDA *items,void *value){
	growCDA(items);
	items->array[items->back] = value;
	items->back = correctIndex(items->back + 1,items);	//set back to new index
	items->size++;
}

void *removeCDAfront(CDA *items){
	void *x;
	if(items->size <= 0)	//nothing to remove
		return 0;
	x = items->array[items->front];	//x is item from front
	items->array[items->front] = 0;	//set value at front to NULL
	items->front = correctIndex(items->front + 1,items);	//set front to new index
	items->size--;
	shrinkCDA(items);
	return x;
}

void *removeCDAback(CDA *items){
	void *x;
	if(items->size <= 0)	//nothing to remove
		return 0;
	items->back = correctIndex(items->back - 1,items);	//set back to new index
	x = items->array[items->back];	//x is item from front
	items->array[items->back] = 0;	//set value at back to NULL
	items->size--;
	shrinkCDA(items);
	return x;
}

void unionCDA(CDA *recipient,CDA *donor){
	int x,z = 0;
	if(donor->size == 0){
		return;
	}
	z = donor->size;
	for(x = 0;x < z;x++){	//insert items from front of donor to back of recipient
		insertCDAback(recipient,removeCDAfront(donor));
	}
}

void *setCDA(CDA *items,int index,void *value){
	void *x;
	if(index == -1){	//index is too small so add at front
		insertCDAfront(items,value);
		return 0;
	}
	else if(index == items->size){	//index is too large so add at back
		insertCDAback(items,value);
		return 0;
	}
	else{	//set items[correctIndex] = value
	x = getCDA(items,index);
	items->array[correctIndex(index + items->front,items)] = value;
	return x;
	}
}

void *getCDA(CDA *items,int index){
	return items->array[correctIndex(index + items->front,items)];
}

void **extractCDA(CDA *items){
	void **temp = malloc(sizeof(void *) * items->size);
	int x,z;
	z = items->size;
	for(x = 0;x < z;x++){	//put items into temp with correct order
		temp[x] = removeCDAfront(items);
	}
	items->capacity = 1;	//make items an empty circular dynamic array
	items->array = malloc(sizeof(void *) * items->capacity);
	return temp;
}

int sizeCDA(CDA *items){
	return items->size;
}

void visualizeCDA(FILE *fp,CDA *items){
	fprintf(fp,"(");	//dispaly items in array
	int x;
	for(x = 0;x < items->size;x++){
		items->display(fp,getCDA(items,x));
		if(x != items->size - 1)
			fprintf(fp,",");
	}
	fprintf(fp,")");
	fprintf(fp,"(");	//display empty number of slots
	fprintf(fp,"%d",items->capacity - items->size);
	fprintf(fp,")");
}

void displayCDA(FILE *fp,CDA *items){
	fprintf(fp,"(");
	int x;
	for(x = 0;x < items->size;x++){
		items->display(fp,getCDA(items,x));
		if(x != items->size - 1)
			fprintf(fp,",");
	}
	fprintf(fp,")");
}

void growCDA(CDA *items){
	void **temp;
	int x;
	if(items->size >= items->capacity){
		temp = malloc(sizeof(void*) * items->size * items->factor);
		for(x = 0;x < items->size;x++){	//move items into right order of new sized array
			temp[x] = getCDA(items,x);
		}
		items->capacity *= items->factor;
		items->array = malloc(sizeof(void*) * items->capacity);	//resize array
		items->array = temp;	//make underlying array equal to temp
		items->front = 0;	//front is at index 0
		items->back = items->size;	//back is first empty slot, so items.size
	}
}

void shrinkCDA(CDA *items){
	void **temp;
	int x;
	double ratio = (double)items->size / (double)items->capacity;
	if(ratio < items->minRatio){
		temp = malloc(sizeof(void*) * (items->capacity / items->factor));
		for(x = 0;x < items->size;x++){	//move items into right order of new sized array
			temp[x] = getCDA(items,x);
		}
		items->capacity /= items->factor;
		if(items->capacity <= 0)
			items->capacity = 1;
		items->array = malloc(sizeof(void*) * items->capacity);	//resize array
		items->array = temp;	//make underlying array equal to temp
		items->front = 0;	//front is at index 0
		items->back = items->size;	//back is first empty slot, so items.size
	}
}

int correctIndex(int index,CDA *items){
	return (index + items->capacity) % items->capacity;
}
