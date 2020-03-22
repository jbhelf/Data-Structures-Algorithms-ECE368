#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hbt.h"

int main(int argc, char **argv){
    if(!strcmp(argv[1], "-e") && argc != 3){
        printf("Improper call\n");
        return EXIT_FAILURE;
    }
    if(!strcmp(argv[1], "-b") && argc != 4){
        printf("Improper call\n");
        return EXIT_FAILURE;
    }
    if(!strcmp(argv[1], "-e") && !strcmp(argv[1], "-b")){
        printf("Improper call\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}