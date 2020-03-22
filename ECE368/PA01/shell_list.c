#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shell_list.h"

static int sizeOfList(Node *list){
	int size = 0;
	while(list->next != NULL){
		list = list->next;
		size++;
	}
	return(size);
}

Node *List_Load_From_File(char *filename){
	FILE *fhlr;
	fhlr = fopen(filename, "rb");

	Node *head = NULL;
	head = (Node *)malloc(sizeof(Node));
	Node *temp = NULL;
	temp = (Node *)malloc(sizeof(Node));
	head = temp;

	while(fread(&temp->value, sizeof(long), 1, fhlr) == 1){
		temp->next = NULL;
		temp->next = (Node *)malloc(sizeof(Node));
		temp = temp->next;
	}
	fclose(fhlr);
	return(head);
}

int List_Save_To_File(char *filename, Node *list){
	FILE *fhlr;
	fhlr = fopen(filename, "wb");

	int nSaved = 0;

	if(fhlr != NULL){
		do{ 
			fwrite(&list->value, sizeof(long) , 1, fhlr);
			nSaved++;		
			list = list->next;
		}while(list->next != NULL);
	}

	fclose(fhlr);
	return(nSaved);
}

static Node * curLink(Node * list, int i){
	//printf("\ncurLink:");
	for(int j = 0;j < i;j++){
		list = list->next;
		//printf("\nAddress: 0x%ld", list);
		//printf(" -> %ld", list->value);
	}
	return(list);
}

static long retVal(Node * list, int i){
	//printf("\nretVal:");
	for(int j = 0;j < i;j++){
		list = list->next;
		//printf("\nAddress: 0x%ld", list);
		//printf(" -> %ld", list->value);
	}
	return(list->value);
}

Node* List_Shellsort(Node *list, long *n_comp){
	Node * temp1 = NULL;
	temp1 = (Node *)malloc(sizeof(Node));

	Node * head = NULL;
	head = (Node *)malloc(sizeof(Node));
	head = list;
	long size = sizeOfList(list) - 1;

	for(long h = ((size - 1) / 3); h > 0;h--){
		long shell = 3 * h + 1;
		for(long i = shell;i <= size;i++){
			long temp = retVal(list, i);
			long j;
			for(j = i;(j >= shell) && (retVal(list, j - shell) > temp);(j -= shell) & (*n_comp += 1)){
				temp1 = curLink(list, j);
				temp1->value = retVal(list, j - shell);
			}
			temp1 = curLink(list, j);
			temp1->value = temp;
		}
	}

	long min;
	long mindex;

	for(long i = 0;i <= size;i++){
		min = retVal(list, i);
		mindex = i;
		for(long j = (i + 1);j <= size;j++){
			*n_comp += 1;
			if(min > retVal(list, j)){
				mindex = j;
				min = retVal(list, j);
			}
		}
		temp1 = curLink(list, mindex);
		temp1->value = retVal(list, i);
		temp1 = curLink(list, i);
		temp1->value = min;		
	}

	printf("%ld\n", *n_comp);

	return(head);
}
