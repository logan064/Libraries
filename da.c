#include "da.h"
#include <stdio.h>
#include <stdlib.h>

struct da{
	void **array;	//holds items
	int size;	//keeps count of items
	int capacity;	//keeps track of slots in array
	int factor;	//factor to grow array by
	double minRatio;	//if ratio is below this then grow array
	void (*display)(FILE *,void *);	//used to display the generic value stored
};

static void growDA(DA *items);	//grows array by the factor
static void shrinkDA(DA *items);	//shrinks the array down to the actual size

DA *newDA(void (*d)(FILE *,void *)){
	DA *items = malloc(sizeof(DA));
    if(items == 0){
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->size = 0;
    items->capacity = 1;
    items->array = malloc(sizeof(void*) * items->capacity);
    items->factor = 2;	//doubling array when grown
    items->minRatio = 0.25;
    items->display = d;
    return items;
}

void insertDA(DA *items,void *value){
	growDA(items);	//grow if no open slots
	items->array[items->size++] = value;	//place value at back of array
}

void growDA(DA *items){
	if(items->size >= items->capacity){//size == capacity so create space and increase capacity
		items->capacity *= items->factor;
		items->array = realloc(items->array,sizeof(void*) * items->capacity);
	}
}

void shrinkDA(DA *items){
	double ratio = (double)items->size / (double)items->capacity;
	if(ratio < items->minRatio){	//ratio is less than minRatio so decrease capacity
		items->capacity /= items->factor;
		if(items->capacity <= 0)
			items->capacity = 1;
		items->array = realloc(items->array,sizeof(void*) * items->capacity);
	}
}

void *removeDA(DA *items){
	void *x;
	if(items->size == 0)	//nothing in array
		return 0;
	x = items->array[items->size-1];	//set x to last item in array
	items->array[--items->size] = 0;	//set last item in array to NULL
	shrinkDA(items);
	return x;
}

void unionDA(DA *recipient,DA *donor){
	int x;
	if(donor->size == 0){	//nothing to append to recipient
		return;
	}
	for(x = 0;x < donor->size;x++){	//add each element from donor to recipient in order
		insertDA(recipient,donor->array[x]);
	}
	donor->size = 0;	//make donor empty dynamic array
	donor->capacity = 1;
	donor->array = 0;
	donor->array = malloc(sizeof(void *));
}

void *getDA(DA *items,int index){
	return items->array[index];
}

void *setDA(DA *items,int index,void *value){
	if(index == items->size){	//index is not valid so add it to the back
		insertDA(items,value);
		return 0;
	}
	else{	//set value at the index to the parameter passed
		void *x = items->array[index];
		items->array[index] = value;
		return x;
	}
}

void **extractDA(DA *items){
	shrinkDA(items);
	void **temp = items->array;	//temp = standard underlying 2d c array
	items->size = 0;	//make items an empty dynamic array
	items->capacity = 1;
	items->array = 0;
	items->array = malloc(sizeof(void *));
	return temp;
}

int sizeDA(DA *items){
	if(items == 0)	return 0;
	return items->size;
}

void visualizeDA(FILE *fp,DA *items){
	fprintf(fp,"[");	//print items in array
	int x;
	for(x = 0;x < items->size;x++){
		items->display(fp,getDA(items,x));
		if(x != items->size - 1)
			fprintf(fp,",");
	}
	fprintf(fp,"]");
	fprintf(fp,"[");	//print the number of empty slots
	fprintf(fp,"%d",items->capacity - items->size);
	fprintf(fp,"]");
}

void displayDA(FILE *fp,DA *items){
	fprintf(fp,"[");	//print items in array
	int x;
	for(x = 0;x < items->size;x++){
		items->display(fp,items->array[x]);
		if(x != items->size - 1)
			fprintf(fp,",");
	}
	fprintf(fp,"]");
}
