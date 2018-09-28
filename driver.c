#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "da.h"
#include "cda.h"
#include "stack.h"
#include "queue.h"
#include "bst.h"

int main(int argc, char const *argv[]) {
  if(argc < 1){
    fprintf(stderr, "Not enough arguments.\n");
    exit(-1);
  }
  FILE *out = stdout;
  //FILE *in = stdin;
  fprintf(out,"Testing the executable: %s\n",argv[0]);

/*  //integer testing
  INTEGER *number1 = newINTEGER(1);
  INTEGER *number2 = newINTEGER(2);
  displayINTEGER(out,number1);
  setINTEGER(number1,3);
  displayINTEGER(out,number1);
  fprintf(out, "%d\n",compareINTEGER(number1,number2));
  //should print 131
  freeINTEGER(number1);
  freeINTEGER(number2);

  //real testing
  REAL *real1 = newREAL(1.0);
  REAL *real2 = newREAL(2.0);
  displayREAL(out,real1);
  setREAL(real1,3.0);
  displayREAL(out,real1);
  fprintf(out, "%d\n",compareREAL(real1,real2));
  //should print 1.0000003.0000001
  freeREAL(real1);
  freeREAL(real2);

  //string testing
  STRING *str1 = newSTRING("ONE");
  STRING *str2 = newSTRING("TWO");
  displaySTRING(out,str1);
  displaySTRING(out,str2);
  printf("\n");
  freeSTRING(str1);
  freeSTRING(str2);
  //should print ONETWO1
*/

  //dynamic array testing
  DA *list = newDA(displayINTEGER,freeINTEGER);
  insertDA(list,newINTEGER(1));
  insertDA(list,newINTEGER(2));
  insertDA(list,newINTEGER(3));
  DA *list1 = newDA(displayINTEGER,freeINTEGER);
  insertDA(list1,newINTEGER(4));
  insertDA(list1,newINTEGER(5));
  insertDA(list1,newINTEGER(6));
  insertDA(list1,newINTEGER(7));
  displayDA(stdout,list);
  fprintf(out,"\n");
  displayDA(stdout,list1);
  fprintf(out,"\n");
  unionDA(list,list1);
  displayDA(stdout,list);
  fprintf(out,"\n");
  displayDA(stdout,list1);
  fprintf(out,"\n");
  //should print [1,2,3][1,2,3][1][1,2,3,4,5,100][2]
  freeDA(list);
  freeDA(list1);

/*  //circular dynamic array testing
  CDA *ring = newCDA(displaySTRING);
  insertCDAback(ring,newSTRING("b"));
  insertCDAback(ring,newSTRING("c"));
  insertCDAfront(ring,newSTRING("a"));
  CDA *ring1 = newCDA(displaySTRING);
  insertCDAback(ring1,newSTRING("e"));
  insertCDAback(ring1,newSTRING("f"));
  insertCDAfront(ring1,newSTRING("d"));
  unionCDA(ring,ring1);
  setCDA(ring,sizeCDA(ring)-1,newSTRING("z"));
  displayCDA(out,ring);
  visualizeCDA(out,ring);
  fprintf(out,"\n");
  //should print (a,b,c,d,e,z)(a,b,c,d,e,z)(2)
*/
  //stack testing
  STACK *s = newSTACK(displayINTEGER,freeINTEGER);
  push(s,newINTEGER(1));
  push(s,newINTEGER(2));
  displaySTACK(out,s);
  fprintf(out,"\n");
  //should print |2,1|
  freeSTACK(s);
/*
  //queue Testing
  QUEUE *q = newQUEUE(displayREAL);
  enqueue(q,newREAL(1.0));
  enqueue(q,newREAL(1.5));
  enqueue(q,newREAL(2.0));
  enqueue(q,newREAL(2.5));
  dequeue(q);
  displayQUEUE(out,q);
  fprintf(out,"\n");
  //should print <1.000000,1.500000,2.000000>

  //bst Testing
  BST *t = newBST(displayINTEGER,compareINTEGER,0);
  insertBST(t,newINTEGER(5));
  insertBST(t,newINTEGER(1));
  insertBST(t,newINTEGER(9));
  insertBST(t,newINTEGER(3));
  insertBST(t,newINTEGER(7));
  insertBST(t,newINTEGER(0));
  insertBST(t,newINTEGER(10));
  displayBST(out,t);
  deleteBST(t,newINTEGER(10));
  displayBST(out,t);

*/

  /*should print
  0: 5(5)-
  1: 1(5)-l 9(5)-r
  2: =0(1)-l =3(1)-r =7(9)-l =10(9)-r
  0: 5(5)-
  1: 1(5)-l 9(5)-r
  2: =0(1)-l =3(1)-r =7(9)-l
  */

  return 0;
}
