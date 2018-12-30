#ifndef __CDA_INCLUDED__
#define __CDA_INCLUDED__

#include <stdio.h>

typedef struct cda CDA;

extern CDA *newCDA(void (*d)(FILE *,void *),void (*f)(void *)); //creates structure and uses function pointers to display and free generic values 
extern void insertCDAfront(CDA *items,void *value); //inserts the item at the front of the array
extern void insertCDAback(CDA *items,void *value);  //inserts the item at the back of the array
extern void *removeCDAfront(CDA *items);  //removes the item at the front of the array
extern void *removeCDAback(CDA *items); //removes the item at the back of the array
extern void unionCDA(CDA *recipient,CDA *donor);  //appends the second array to the first
extern void *getCDA(CDA *items,int index);  //returns the value located at items[index]
extern void *setCDA(CDA *items,int index,void *value);  //sets the value at items[index] to passed parameter
extern void **extractCDA(CDA *items); //returns the underlying structure
extern int sizeCDA(CDA *items); //returns the number of items stored in array
extern void visualizeCDA(FILE *,CDA *items);  //print array enclosed in [] and prints open slots
extern void displayCDA(FILE *,CDA *items);  //print the items stored in the array
extern void freeCDA(CDA *items);  //frees the objects stored and CDA object

#endif
