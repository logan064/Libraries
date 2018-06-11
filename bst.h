#ifndef __BST_INCLUDED__
#define __BST_INCLUDED__

#include <stdio.h>

typedef struct bstnode BSTNODE;

extern void *getBSTNODE(BSTNODE *); //returns underlying value in node
extern void    setBSTNODE(BSTNODE *,void *);  //sets underlying value in node to parameter
extern BSTNODE *getBSTNODEleft(BSTNODE *);  //return the nodes left pointer
extern void    setBSTNODEleft(BSTNODE *,BSTNODE *); //sets the nodes left pointer to parameter
extern BSTNODE *getBSTNODEright(BSTNODE *); //return the nodes right pointer
extern void    setBSTNODEright(BSTNODE *,BSTNODE *);  //sets the nodes right pointer to parameter
extern BSTNODE *getBSTNODEparent(BSTNODE *);  //return the nodes parent pointer
extern void    setBSTNODEparent(BSTNODE *,BSTNODE *); //sets the nodes parent pointer to parameter

typedef struct bst BST;

extern BST *newBST( //creates tree structure and caches function pointers, then returns the structure
    void (*)(FILE *,void *),            //display
    int (*)(void *,void *),             //comparator
    void (*)(BSTNODE *,BSTNODE *));     //swapping function, use NULL if you use BST
extern void    setBSTroot(BST *,BSTNODE *); //set root pointer to parameter
extern BSTNODE *getBSTroot(BST *);  //return pointer to the root node
extern BSTNODE *insertBST(BST *,void *);  //inserts node normally and returns the inserted node
extern BSTNODE *findBST(BST *,void *);  //return the node that matches the parameter
extern BSTNODE *deleteBST(BST *,void *);  //findBST then swapToLeafBST then pruneLeafBST and return node
extern BSTNODE *swapToLeafBST(BST *,BSTNODE *); //swaps node to leaf, prefer predecessor
extern void    pruneLeafBST(BST *,BSTNODE *); //disconnect node from the tree
extern int     sizeBST(BST *);  //return the number of nodes in the tree
extern void    statisticsBST(FILE *,BST *); //prints size,minDepth, and maxDepth
extern void    displayBST(FILE *,BST *);  //prints tree using level order traversal
#endif
