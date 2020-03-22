#ifndef __HBT_TREE__
#define __HBT_TREE__

typedef struct _Tnode {
   int key;
   char balance;   
   struct _Tnode *left;
   struct _Tnode *right;
} Tnode;

#endif