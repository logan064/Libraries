#include <stdio.h>

#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

typedef struct real REAL;

extern REAL *newREAL(double); //returns structure wrapping the value
extern double getREAL(REAL *);  //returns the value stored in the structure
extern double setREAL(REAL *,double); //sets the value stored in the structure parameter
extern void displayREAL(FILE *,void *); //displays the wrappped value to the FILE*
extern int compareREAL(void *,void *);  //returns the first value minus the second
extern void freeREAL(REAL *); //frees the memory allocated by newREAL


#endif
