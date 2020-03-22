#include<stdio.h>
#include<stdlib.h>
#include "packing.h"

int main(int argc, char **argv){
    if(argc != 5){
        return EXIT_FAILURE;
    }

    Tree * rn;
    rn = treeConstr(argv[1]);
    if(rn == NULL){
        return EXIT_FAILURE;
    }

    outputer(argv[2], argv[3], argv[4], rn);
    freeTree(rn);
    return EXIT_SUCCESS;
}