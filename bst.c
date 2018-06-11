#include "bst.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

static BSTNODE *insertNode(BST *t,BSTNODE *x,BSTNODE *n); //helper to handle recursion
static BSTNODE *newBSTNODE(void *v);  //creates and returns node structure
static int isLeft(BSTNODE *x);  //returns 1 if node is a left child
static void swapBSTNODE(BSTNODE *x,BSTNODE *y); //swaps the underlying values of the nodes
static int minDepth(BSTNODE *); //returns minimum depth to a leaf
static int maxDepth(BSTNODE *); //returns maximum depth to a leaf
static int min(int,int);  //returns min value
static int max(int,int);  //returns max value

///Public//////////////////////////////////////////BSTNODE/////////////////////
struct bstnode{
  struct bstnode *left;
  struct bstnode *right;
  struct bstnode *parent;
  void *value;
};

void *getBSTNODE(BSTNODE *x){
  if(x != 0){
    return x->value;
  }
  return 0;
}

void setBSTNODE(BSTNODE *x,void *v){
  if(x != 0){
    x->value = v;
  }
}

BSTNODE *getBSTNODEleft(BSTNODE *x){
  if(x != 0){
    return x->left;
  }
  return 0;
}

void setBSTNODEleft(BSTNODE *x,BSTNODE *y){
  if(x != 0){
    x->left = y;
  }
}

BSTNODE *getBSTNODEright(BSTNODE *x){
  if(x != 0){
    return x->right;
  }
  return 0;
}

void setBSTNODEright(BSTNODE *x,BSTNODE *y){
  if(x != 0){
    x->right = y;
  }
}

BSTNODE *getBSTNODEparent(BSTNODE *x){
  if(x != 0){
    return x->parent;
  }
  return 0;
}

void setBSTNODEparent(BSTNODE *x,BSTNODE *y){
  if(x != 0){
    x->parent = y;
  }
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///Private/////////////////////////////////////////BSTNODE/////////////////////
static BSTNODE *newBSTNODE(void *v){
  BSTNODE *x = malloc(sizeof(BSTNODE));
  if(x == 0){
    fprintf(stderr, "%s\n", "Out of memory.");
    exit(-2);
  }
  x->left = 0;
  x->right = 0;
  x->parent = 0;
  x->value = v;
  return x;
}

static void swapBSTNODE(BSTNODE *x,BSTNODE *y){
	void *z =	x->value;
	x->value = y->value;
	y->value = z;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///Public//////////////////////////////////////////////BST/////////////////////
struct bst{
  BSTNODE *root;
  int size;
  void (*display)(FILE *,void *); //displays the generic void * value
  int (*compare)(void *,void *);  //compares the generic void * value
  void (*swap)(BSTNODE *,BSTNODE *);  //swaps the node values
};

BST *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *),void (*s)(BSTNODE *,BSTNODE *)){
  BST *tree = malloc(sizeof(BST));
  if(tree == 0){
    fprintf(stderr, "%s\n","Out of memory.");
    exit(-1);
  }
  tree->root = 0;
  tree->size = 0;
  tree->display = d;
  tree->compare = c;
  if(s != 0)
    tree->swap = s; //used for tree other than BST
  else
    tree->swap = swapBSTNODE; //NULL swap function so must be BST
  return tree;
}

void setBSTroot(BST *t,BSTNODE *x){
  if(t != 0){
    t->root = x;
  }
}

BSTNODE *getBSTroot(BST *t){
  if(t != 0){
    return t->root;
  }
  return 0;
}

BSTNODE *insertBST(BST *t,void *v){
  if(t->root == 0){ //empty tree so make node the root
    setBSTroot(t,newBSTNODE(v));
		t->size++;
    return t->root;
  }
  t->size++;  //else insert node recursively
  return insertNode(t,t->root,newBSTNODE(v));
}

BSTNODE *findBST(BST *t,void *x){
  BSTNODE *n = t->root;
  while(n != 0){
    if(t->compare(x,n->value) == 0) //node found, return it
      return n;
    else if(t->compare(x,n->value) > 0) //recur right
      n = n->right;
    else  //recur left
      n = n->left;
  }
  return 0; //reached leaf, value not found
}

BSTNODE *deleteBST(BST *t,void *x){
  BSTNODE *y = findBST(t,x);
  if(y == 0){ //value is not in tree
    fprintf(stdout, "Value ");
    t->display(stdout,x);
    fprintf(stdout, " not found.\n");
    return 0;
  }
  y = swapToLeafBST(t,y);
  pruneLeafBST(t,y);
  return y;
}

BSTNODE *swapToLeafBST(BST *t,BSTNODE *x){
  BSTNODE *n = x;
  if(getBSTNODEleft(n) == 0 && getBSTNODEright(n) == 0){  //node is leaf
		return n;
  }
	else if(getBSTNODEleft(n) != 0){ //find predecessor
		n = getBSTNODEleft(n);
		while(getBSTNODEright(n) != 0)
			n = getBSTNODEright(n);
		t->swap(n,x);
	}
	else{  //find successor
		n = getBSTNODEright(n);
		while(getBSTNODEleft(n) != 0)
			n = getBSTNODEleft(n);
		t->swap(n,x);
	}
	return swapToLeafBST(t,n); //recur
}

void pruneLeafBST(BST *t,BSTNODE *x){
	if(t->root == 0) //nothing to prune from
    return;
  else if(t->root == x)
    t->root = 0;
  else if(isLeft(x))
    setBSTNODEleft(getBSTNODEparent(x),0);
  else
    setBSTNODEright(getBSTNODEparent(x),0);
  t->size--;
}

int sizeBST(BST *t){
  if(t != 0)
    return t->size;
  else
    return 0;
}

void statisticsBST(FILE *fp,BST *t){
  fprintf(fp,"Nodes: %d\n",sizeBST(t));
  fprintf(fp,"Minimum depth: %d\n",minDepth(t->root));
  fprintf(fp,"Maximum depth: %d\n",maxDepth(t->root));
}

void displayBST(FILE *fp,BST *t){
  if(t->root == 0){
    fprintf(fp, "EMPTY\n");
    return;
  }
  BSTNODE *x;
  QUEUE *buffer = newQUEUE(t->display);
  enqueue(buffer,t->root);
  enqueue(buffer,0);
  fprintf(fp, "0: ");
  int i = 1;
  while(sizeQUEUE(buffer) != 0){
    x = dequeue(buffer);
    if(x == 0){
      if(sizeQUEUE(buffer) >= 1){
        fprintf(fp, "\n%d: ", i++);
        enqueue(buffer,0);
      }
    }
    else{
      if(getBSTNODEright(x) == 0 && getBSTNODEleft(x) == 0){
        fprintf(fp, "="); //leaf
      }
      t->display(fp,getBSTNODE(x));
      if(getBSTNODEparent(x) != 0){
        fprintf(fp, "(");
        t->display(fp,getBSTNODE(getBSTNODEparent(x)));
        fprintf(fp, ")");
      }
      else{
        fprintf(fp, "(");
        t->display(fp,getBSTNODE(x));
        fprintf(fp, ")");
      }
      if(x == t->root){
        fprintf(fp, "-");
      }
      else if(isLeft(x)){
        fprintf(fp, "-l");
      }
      else{
        fprintf(fp, "-r");
      }
      if(peekQUEUE(buffer) != 0){
        fprintf(fp, " ");
      }
      if(getBSTNODEleft(x) != 0){
        enqueue(buffer,getBSTNODEleft(x));
      }
      if(getBSTNODEright(x) != 0){
        enqueue(buffer,getBSTNODEright(x));
      }
    }
  }
  fprintf(fp, "\n");
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///Private/////////////////////////////////////////////BST/////////////////////
static BSTNODE *insertNode(BST *t,BSTNODE *x,BSTNODE *n){
  if(t->compare(n->value,x->value) < 0){
    if(x->left != 0){
      return insertNode(t,x->left,n);
    }
    else{
      setBSTNODEleft(x,n);
      setBSTNODEparent(n,x);
    }
  }
  else if(t->compare(n->value,x->value) > 0){
    if(x->right != 0){
      return insertNode(t,x->right,n);
    }
    else{
      setBSTNODEright(x,n);
      setBSTNODEparent(n,x);
    }
  }
  return n;
}

static int isLeft(BSTNODE *x){
  if(x == 0)
    return 0;
  BSTNODE *t = getBSTNODEparent(x);
  if(t == 0)
    return 1;
  else if(getBSTNODEleft(t) == x)
    return 1;
  else
    return 0;
}

static int minDepth(BSTNODE *root){
  if(root == 0)
    return 0;
  int ldepth = minDepth(getBSTNODEleft(root));
  int rdepth = minDepth(getBSTNODEright(root));
  return min(ldepth,rdepth) + 1;
}

static int maxDepth(BSTNODE *root){
  if(root == 0)
    return 0;
  int ldepth = maxDepth(root->left);
  int rdepth = maxDepth(root->right);
  return max(ldepth,rdepth) + 1;
}

static int min(int a, int b){
  if(a < b)
    return a;
  else
    return b;
}

static int max(int a, int b){
  if(a < b)
    return b;
  else
    return a;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
