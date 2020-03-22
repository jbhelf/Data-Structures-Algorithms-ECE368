#ifndef __packing_h__
#define __packing_h__

typedef struct _tree{
    struct _tree * left;
    struct _tree * right;
    int l, w, x, y, indc;
}Tree;

typedef struct temp__{
	Tree * lf;
	struct temp__ * layer;
}STK;

typedef struct{
	STK * top;
}TOS;

Tree * treeConstr(char * filename);
void outputer(char * fileone, char * filetwo, char * filethree, Tree * tr);
void freeTree(Tree * rt);

#endif
