#include <stdio.h>
#include <stdlib.h>
#include "integer.h"

struct integer{
  int value;
};

INTEGER *newINTEGER(int x)
    {
    INTEGER *p = malloc(sizeof(INTEGER));
    if (p == 0){
        fprintf(stderr,"out of memory\n");
        exit(-1);
        }
    p->value = x;
    return p;
    }

int getINTEGER(INTEGER *v)
    {
    return v->value;
    }

int setINTEGER(INTEGER *v,int x)
    {
    int old = v->value;
    v->value = x;
    return old;
    }

void displayINTEGER(FILE *fp,void *v)
    {
    if(v == 0)  fprintf(fp,"|NULL|");
    fprintf(fp,"%d",getINTEGER(v));
    }

int
compareINTEGER(void *v,void *w)
    {
    return ((INTEGER *) v)->value - ((INTEGER *) w)->value;
    }

void freeINTEGER(INTEGER *v)
    {
    free(v);
    }
