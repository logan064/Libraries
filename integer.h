#include <stdio.h>

#ifndef __INTEGER_INCLUDED__
#define __INTEGER_INCLUDED__

typedef struct integer INTEGER;

extern INTEGER *newINTEGER(int);  //returns structure wrapping the value
extern int getINTEGER(INTEGER *); //returns the value stored in the structure
extern int setINTEGER(INTEGER *,int); //sets the value stored in the structure parameter
extern void displayINTEGER(FILE *,void *);  //displays the wrappped value to the FILE*
extern int compareINTEGER(void *,void *); //returns the first value minus the second
extern void freeINTEGER(INTEGER *); //frees the memory allocated by newINTEGER


#endif
