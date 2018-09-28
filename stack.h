#include "da.h"

#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

#include <stdio.h>

typedef struct stack STACK;

extern STACK *newSTACK(void (*d)(FILE *,void *),void (*f)(void *)); //returns structure stack is based upon and takes display fn
extern void push(STACK *items,void *value); //adds the value to the top of the stack
extern void *pop(STACK *items); //returns the top value on the stack and removes it from the stack
extern void *peekSTACK(STACK *items); //return value on top of the stack, but leaves the value on stack
extern int sizeSTACK(STACK *items); //return number of items on stack
extern void displaySTACK(FILE *,STACK *items);  //prints the values stored on stack from top to bottom
extern void visualizeSTACK(FILE *,STACK *items);  //prints the underlying structure
void freeSTACK(STACK *items);

#endif
