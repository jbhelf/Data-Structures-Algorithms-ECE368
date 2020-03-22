#include<stdio.h>
#include<stdlib.h>
#include "huffman.h"

int main(int argc, char **argv){
	if(argc != 6){
		printf("\nERROR: Incorrect input(s)\nExpected 6 inputs, but recieved %d", argc);
		return EXIT_FAILURE;
	}

	/*
 	 *argv[1] = input to be compressed
	 *argv[2] = output file with frequency of occurrances
	 *argv[3] = output with topology information (preorder)
	 *argv[4] = output with the huffman code
	 *argv[5] = output with compressed file (uses the above concepts)
	*/

	long *tLetters = malloc(sizeof(long)); //total amount of letters
	long *lCount; //array of counts of all ASCII characters
	lCount = (long *)malloc(sizeof(long) * 256);
	for(int i = 0;i < 256;i++){
		lCount[i] = 0;
	}
	
	*tLetters = openHuff(argv[1], lCount, argv[2]); //counts frequencies and stores

	if(*tLetters < 0){
		free(lCount);
		//fREEEEEEEEEE
		printf("\nERROR: File opening failed");
		return EXIT_FAILURE;
	}
	
	Root *forest;
	forest = (Root *)malloc(sizeof(Root));
	forest->loc = NULL;
	forest->freq = 0;
	forest = makeForest(lCount);
	int nLetters = 0;
	free(lCount);
	for(int i = 0;i < 256;i++){
		if(lCount[i] != 0){
			nLetters++;
		}
	}

	if(/*nLetters == 0*/ forest == NULL){ //special EMPTY case
		FILE *fl3 = fopen(argv[3], "wb");
		FILE *fl4 = fopen(argv[4], "wb");
		FILE *fl5 = fopen(argv[5], "wb");

		
		long *headFo = malloc(sizeof(long));
		*headFo = 24;
		fwrite(headFo, 1, sizeof(long), fl5);
		*headFo = 0;
		fwrite(headFo, 1, sizeof(long), fl5);
		fwrite(headFo, 1, sizeof(long), fl5);
		free(headFo);

		fclose(fl3);
		fclose(fl4);
		fclose(fl5);
		return EXIT_SUCCESS;
	}
	if(forest->loc == NULL){
		free(forest);
		printf("\nERROR: Forest failed to be built");
		return EXIT_FAILURE;
	}

	long *topNum = malloc(sizeof(long));
	*topNum = wInorder(forest->loc, argv[3]);

	if(!(treeEncode(argv[4], forest->loc, nLetters))){
		printf("\nERROR: Failed to encode tree");
		return EXIT_FAILURE;
	}

	freeTree(forest->loc);

	*topNum /= 8;

	comFile(argv[1], argv[5], argv[4], argv[3], topNum, tLetters);

	free(topNum);
	free(tLetters);
	return EXIT_SUCCESS;
}
