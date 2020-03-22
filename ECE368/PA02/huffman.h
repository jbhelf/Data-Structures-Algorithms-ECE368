#ifndef __huffman_h__
#define __huffman_h__

typedef struct temp{
	struct temp * right;
	struct temp * left;
	char letter;
} Tree;

typedef struct root_{
	Tree * loc; //starting root location
	int freq; 
} Root;

typedef struct stk{
	struct stk * next;
	Tree * lay;
} Stack;

long openHuff(char * filename, long *lCount, char * frqFile);
Root * makeForest(long * lCount);
void freeTree(Tree * forest);
int treeEncode(char * filename, Tree * root, int nLetters);
int wInorder(Tree * forest, char * filename);
void comFile(char * inp, char * outp, char * cypher, char * toplo, long *topo, long *tUnc);

#endif
