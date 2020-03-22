#include<stdio.h>
#include<stdlib.h>
#include "huffman.h"

static void dumpByte(int* byte, FILE * ou){
	long *conv = malloc(sizeof(long));
	*conv = 0;
	for(int i = 0;i < 8;i++){
		*conv += byte[i] * 2 * (i + 1);
		byte[i] = -1;
	}
	fwrite(conv, 1, 1, ou); //might be flipped numbers
	free(conv);
}

void comFile(char * inp, char * outp, char * cypher, char * toplo, long *topo, long *tUnc){
	FILE * in = fopen(inp, "r");
	FILE * ou = fopen(outp, "wb");
	FILE * cyp = fopen(cypher, "r");
	FILE * toplg = fopen(toplo, "r");
	long *nComp = malloc(sizeof(long));
	*nComp = (2 * 8) + *topo + *tUnc;

	if(ou == NULL || cyp == NULL){
		printf("\nERROR: Compressed file failed to open!\n");
		return;
	}
	int* byte = malloc(8 * sizeof(int));
	for(int i = 0;i < 8;i++){
		byte[i] = -1;
	}
	int let;
	let = fgetc(in);
	char * code = (char*)malloc(sizeof(char));
	int count = 0;
	do{
		fseek(cyp, 0, SEEK_SET);
		do{	
			*code = fgetc(cyp);
		}while(*code != let && *code != EOF);
		if(*code == EOF){
			printf("\nERROR: Code of char not found");
			free(code);
			return;
		}
		*code = fgetc(cyp); //skip over colon
		//printf(" Code:");
		do{
			*code = fgetc(cyp);
			//printf("%c", (char)*code);
			if(*code != '\n'){
				if(count == 8){
					count = 0;
				}
				byte[count] = *code - 48;
				count++;
				//*nComp += 1; //this is off by two
			}
		}while(*code != '\n');
		let = fgetc(in); //get new letter
	}while(let != EOF);

	//RECALCULATE 1ST HEADER NUMBER

	//write all the numbers
	fwrite(nComp, 1, sizeof(long), ou);
	fwrite(topo, 1, sizeof(long), ou);
	fwrite(tUnc, 1, sizeof(long), ou);

	for(int i = 0;i < 8;i++){
		byte[i] = -1;
	}
	count = 0;

	fseek(in, 0, SEEK_SET);
	let = fgetc(in);
	fseek(cyp, 0, SEEK_SET);
	//this part actually writes to out
	char t;
	long * twr = malloc(8 * sizeof(long));
	//long * tbd = malloc(8 * sizeof(long));
	
	do{
		t = fgetc(toplg);
		if(t != EOF){
			if(t == 0 || t == 1){
				twr[count] = t;
				count++;
			}else{
				for(int i = 0;i < 8;i++){
					if(count < 8){
						twr[count] = ((int) t) % 2;
					}else{
						//write
						//printf("");
						//clear the array
						
						//finish writing	
					}
					count++;
					t =(int) t / 2;
				}
			}
				
		}
	}while(t != EOF);

	count = 0;

	do{
		fseek(cyp, 0, SEEK_SET);
		do{	
			*code = fgetc(cyp);
		}while(*code != let && *code != EOF);
		//printf("\nCode for '%c' is: ", (char)*code);
		if(*code == EOF){
			printf("\nERROR: Code of char not found");
			free(code);
			return;
		}
		*code = fgetc(cyp); //skip over colon
		do{
			*code = fgetc(cyp);
			if(*code != '\n'){
				byte[count] = *code - 48;
				//printf("%d", byte[count]);
				count++;
				if(count == 8){
					count = 0;
					dumpByte(byte, ou);
				}
			}
		}while(*code != '\n');
		let = fgetc(in); //get new letter
	}while(let != EOF);

	fclose(cyp);
	fclose(ou);
	fclose(in);
	free(byte);
	free(code);
}

static Tree *popStc(Stack ** fIn){
	Stack *lIn; //'last in' stack
	lIn = *fIn; //temporary is equal to our orig stack
	*fIn = lIn->next; //pushes fwd
	Tree *tbFree = lIn->lay; //to be freed
	free(lIn);
	return(tbFree);
}

static void pshTSt(Stack ** fIn, Tree *leaf){
	Stack *temp = malloc(sizeof(Stack));
	temp->next = (*fIn); //reassigns stack
	temp->lay = leaf; //pushes leaf
	(*fIn) = temp; //reassigns to original
}

int wInorder(Tree * forest, char * filename){
	FILE * fhlr;
	fhlr = fopen(filename, "w");
	long topCou = 1;
	if(fhlr != NULL){
		long val;
		Stack *stc = NULL; //init the stack to be used 
		Tree *temp = forest;
		while(temp != NULL || stc != NULL){ //checks if empty
			if(temp != NULL){
				pshTSt(&stc, temp);
				temp = temp->left;
				if(temp != NULL){
					val = 0;
					topCou++;
					fprintf(fhlr, "%ld", val);
				}
			}else if(stc != NULL){
				temp = popStc(&stc);
				if(temp->letter != 0){	
					val = 1;
					topCou++;
					fprintf(fhlr, "%ld", val);
					topCou += 8;
					fprintf(fhlr, "%c", temp->letter);
				}
				temp = temp->right;
			}
		}
		fclose(fhlr);
	}
	return(topCou);	
}

static void incDir(int * dir, int *size){
	int * temp;
	temp = malloc(sizeof(int) * (*size / 2));
	for(int i = 0;i < (*size / 2);i++){
		temp[i] = dir[i];
	}
	free(dir);
	dir = malloc(sizeof(int) * (*size));
	for(int i = 0;i < (*size);i++){
		if(i >= (*size / 2)){
			dir[i] = -2;
		}else{
			dir[i] = temp[i];
		}
	}
	free(temp);
}

static void wrtStack(int * dir, int size, FILE * fhlr){
	char twrt = ':';
	fprintf(fhlr, "%c", dir[size]);
	fprintf(fhlr, "%c", twrt);
	dir[size] = -2;
	for(int i = 0;i < size;i++){ //assumes letter at size
		fprintf(fhlr, "%d", dir[i]);
	}
	twrt = '\n';
	fprintf(fhlr, "%c", twrt);
}

static int findEmp(int * dir, int *size){
	int i;
	for(i = 0;i < *size;i++){
		if(dir[i] == -2){
			break;
		}
		if(dir[i] != -2 && i == (*size - 1)){
			*size *= 2;
			incDir(dir, size);
			i++;
			break;
		}
	}

	return(i);
}

static void helpEnc(Tree *tree, int *dir, int *size, FILE * fhlr){	
	int i;

	if(tree->letter > 1){ //if there is a letter, print it
		i = findEmp(dir, size);
		dir[i] = (int)tree->letter;
		wrtStack(dir, i, fhlr);
		dir[i] = -2;
	}	

	if(tree->left != NULL){
		i = findEmp(dir, size);
		dir[i] = 0;
		helpEnc(tree->left, dir, size, fhlr);
		dir[i] = -2;
	}
	if(tree->right != NULL){
		i = findEmp(dir, size);
		dir[i] = 1;
		helpEnc(tree->right, dir, size, fhlr);
		dir[i] = -2;
	}
}

int treeEncode(char * filename, Tree * forest, int nLetters){
	FILE * fhlr;
	fhlr = fopen(filename, "wb");
	if(fhlr == NULL){
		printf("\nFile failed to open");
		return 0;
	}

	int *size = malloc(sizeof(int));
	*size = nLetters * 3;

	int *dir;
	dir = malloc(*size * sizeof(int));
	for(int i = 0;i < *size;i++){
		dir[i] = -2;
	}

	helpEnc(forest, dir, size, fhlr);
	free(size);

	free(dir);
	fclose(fhlr);
	return 1;
}

void freeTree(Tree *forest){
	if(forest->left != NULL){
		freeTree(forest->left);
	}else{
		free(forest->left);
	}
	if(forest->right != NULL){
		freeTree(forest->right);
	}else{
		free(forest->right);
	}

	free(forest);
}

long openHuff(char * filename, long *lCount, char *frqFile){
	FILE *fhlr;
	fhlr = fopen(filename, "r");
	FILE *frhlr;
	frhlr = fopen(frqFile, "wb");
	long i, tLetters;
	tLetters = 0;
	if(fhlr != NULL && frhlr){
		i = fgetc(fhlr);
		if(i != EOF){
			do{
				lCount[i] += 1;
				tLetters++;
				i = fgetc(fhlr);
			}while(i != EOF);
		}
		for(i = 0;i < 256;i++){
			fwrite(&lCount[i], 1, sizeof(long), frhlr);
		}	
	}else{
		printf("\nERROR: Input file or .count file failed to open!");
		return -1;
	}

	fclose(frhlr);	
	fclose(fhlr);
	return(tLetters); //returns total amount of letters
}

static int findMin(long * lCount, long * min){
	char mindex = NULL;

	for(int i = 255;i >= 0;i--){
		if(lCount[i]){
			if(lCount[i] < *min){
				mindex = i;
				*min = lCount[i];
			}else if(lCount[i] == *min){
				mindex = i;
			}
		}
	}

	lCount[(int)mindex] = 0; //removes letter from contention

	return(mindex);
}

static Root * buildTree(char maxL, char minL, long freq){
	Root *temp;
	temp = (Root *)malloc(sizeof(Root));
	temp->loc = NULL;
	temp->freq = freq;

	Tree *lessVal;
	lessVal = (Tree *)malloc(sizeof(Tree)); 
	lessVal->left = (Tree *)malloc(sizeof(Tree)); 
	lessVal->left = NULL;
	lessVal->right = (Tree *)malloc(sizeof(Tree)); 
	lessVal->right = NULL;
	lessVal->letter = minL;

	Tree *moreVal;
	moreVal = (Tree *)malloc(sizeof(Tree)); 	
	moreVal->left = (Tree *)malloc(sizeof(Tree)); 
	moreVal->left = NULL;
	moreVal->right = (Tree *)malloc(sizeof(Tree)); 
	moreVal->right = NULL;
	moreVal->letter = maxL;

	Tree *top;
	top = (Tree *)malloc(sizeof(Tree)); 
	top->left = moreVal;
	top->right = lessVal;
	top->letter = 0;

	temp->loc = top;
	return(temp);
}

static void combTree(Root * forest, Root * temp){
	long occ = forest->freq + temp->freq; //total occurances

	Tree *top;
	top = (Tree *)malloc(sizeof(Tree)); 
	if(forest->freq < temp->freq){
		top->left = forest->loc; //higher freq
		top->right = temp->loc; //lower freq
	}else if(forest->freq > temp->freq){	
		top->left = temp->loc; //higher freq
		top->right = forest->loc; //lower freq
	}else if(temp->loc->left->letter > forest->loc->right->letter){
		top->left = forest->loc; //higher freq
		top->right = temp->loc; //lower freq
	}else{
		top->left = temp->loc; //higher freq
		top->right = forest->loc; //lower freq
	}

	top->letter = 0;

	forest->freq = occ;
	forest->loc = top;
}

Root * makeForest(long * lCount){
	long maxF = 0;
	for(int i = 0;i < 256;i++){
		if(lCount[i] >= maxF){
			maxF = lCount[i];
		}
	}

	if(maxF == 0){
		//printf("\nERROR: Empty file");
		return(NULL);
	}

	long * minVal1;
	minVal1 = (long *)malloc(sizeof(long));
	long * minVal2;
	minVal2 = (long *)malloc(sizeof(long));
	char ind1 = 0;
	char ind2 = 0;

	Root *temp;
	temp = (Root *)malloc(sizeof(Root));
	temp->loc = NULL;
	temp->freq = 0;

	Root *forest;
	forest = (Root *)malloc(sizeof(Root));
	forest->loc = NULL;
	forest->freq = 0;

	do{ //LOOP TO MAKE AND COMBINE TREES
		*minVal1 = maxF + 1;
		*minVal2 = maxF + 1;
		ind1 = findMin(lCount, minVal1);
		ind2 = findMin(lCount, minVal2);
		if(ind1 != 0 && ind2 != 0){
			temp = buildTree(ind1, ind2, (*minVal1 + *minVal2));
			if(forest->loc != NULL){ //if forest exists
				combTree(forest, temp); //combines two trees
				temp->loc = NULL;
				temp->freq = 0;
			}else{ //if there was no forest
				forest->loc = temp->loc;
				forest->freq = temp->freq;
				temp->loc = NULL;
				temp->freq = 0;
			}
		}
	}while(ind1 != 0 || ind2 != 0);

	if(ind1 != 0){//in the case of an odd number of letters	
		Tree *finVal;
		finVal = (Tree *)malloc(sizeof(Tree)); 
		finVal->left = NULL;
		finVal->right = NULL;
		finVal->letter = ind1;

		temp->loc = finVal;
		temp->freq = *minVal1;

		combTree(forest, temp);
	}	

	free(minVal1);
	free(minVal2);
	return(forest);	
}
