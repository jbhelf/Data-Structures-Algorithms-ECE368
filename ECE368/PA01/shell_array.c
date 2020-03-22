#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shell_array.h"

int Array_Save_To_File(char *filename, long *array, int size){
	FILE *fhlr;
	fhlr = fopen(filename, "wb");
	
	int wnm = 0;

	if(fhlr != NULL){
		for(int i = 0;i < size;i++){
			wnm = fwrite(&array[i], sizeof(*array), 1, fhlr);
			if(wnm != 1){
				size = 1 + i;
				break;
			}
		}
	}
	
	fclose(fhlr);
	return(size);
}

long *Array_Load_From_File(char *filename, int *size){
	FILE *fhlr;
	fhlr = fopen(filename, "rb");
		
	long *array;
	if(fhlr != NULL){
		while(fgetc(fhlr) != EOF){
			(*size)++;
		}
		*size /= sizeof(long);
		array = (long *)malloc((*size) * sizeof(long));
		
		if(fseek(fhlr, 0, SEEK_SET) != 0){
			fclose(fhlr);
			return NULL;
		}
		
		fread(array, sizeof(long), *size, fhlr);
	}	

	fclose(fhlr);
	return(array);
}

void Array_Shellsort(long *array, int size, long *n_comp){	

	for(long h = ((size - 1) / 3);h > 0;h--){
		long shell = 3 * h + 1;
		for(long i = shell;i < size;i++){
			long temp = array[i];
			long j;
			for(j = i;(j >= shell) && (array[j - shell] > temp);(j -= shell) & (*n_comp += 1)){
				array[j] = array[j - shell];
			}
			array[j] = temp;
		}
	}

	long min;
	long mindex;

	for(long i = 0;i < size;i++){ //insertion sort
		min = array[i];
		mindex = i;
		for(long j = (i + 1);j < size;j++){
			*n_comp += 1;
			if(min > array[j]){
				mindex = j;
				min = array[j];
			}
		}
		array[mindex] = array[i];
		array[i] = min;
	}

	printf("%ld\n", *n_comp);
	
	return;

}
