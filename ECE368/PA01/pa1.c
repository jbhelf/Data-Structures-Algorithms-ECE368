#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char **argv){
	if(argc != 4){
		return EXIT_FAILURE;
	}

	if(argv[1] == "-a"){
		int size = 0;
		long *array;
		array = Array_Load_From_File(argv[2], &size);
		if(size == 0 && array == NULL){
			return EXIT_FAILURE;
		}

		long *n_comp;
		Array_Shellsort(array, size, n_comp);

		if(Array_Save_To_File(argv[3], array, size) != size){
			free(array);
			return EXIT_FAILURE;
		}

		free(array);
	}else{
		Node * head = NULL;
		head = List_Load_From_File(argv[2]);

		long *n_comp;
		n_comp = (long *)malloc(sizeof(long));
		*n_comp = 0;

		Node * temp = NULL;
		temp = (Node *)malloc(sizeof(Node));

		List_Shellsort(head, n_comp);	

		free(n_comp);

		long size = 0;
		FILE *fhlr;
		fhlr = fopen(argv[2], "rb");
		while(fgetc(fhlr) != EOF){
			size++;
		}	

		size /= sizeof(long);
		fclose(fhlr);

		temp = head;

		if(List_Save_To_File(argv[3], head) != size){
			for(int i = 0;i < size;i++){
				temp = head->next;
				free(head);
				head = temp;
			}
			return EXIT_FAILURE;
		}

		for(int i = 0;i < size;i++){
			temp = head->next;
			free(head);
			head = temp;
		}
	}

	return EXIT_SUCCESS;
}
