#include<stdio.h>
#include<stdlib.h>
#include "hbt.h"
#include "bt.h"

/*static void hhelp(Tnode * rn, int h){
    if(rn->left != NULL){//if can go left
        hhelp(rn->left, h + 1);
        rn->balance = h;
    }
    if(rn->right != NULL){//if can go right
        hhelp(rn->right, h + 1);
        rn->balance = h;
    }
    if(rn->left == NULL && rn->right == NULL){//if leaf node
        rn->balance = 0;
    }
}

static void detbal(Tnode * rn){
    if(rn->left != NULL){//if can go left
        detbal(rn->left);
    }
    if(rn->right != NULL){//if can go right
        detbal(rn->right);
    }
    if(rn->left != NULL && rn->right != NULL){
        rn->balance = rn->left - rn->right;
    }
    if(rn->left != NULL && rn->right == NULL){
        rn->balance = rn->left;
    }
    if(rn->left == NULL && rn->right != NULL){
        rn->balance = -(rn->right);
    }
}

void bal(Tnode * rn){
    hhelp(rn, 0);
    detbal(rn);
}*/

static Tnode * helpBuild(FILE * fhlr){

}

Tnode * consTree(char * filename){
    FILE * fhlr = fopen(filename, "r");
    if(fhlr == NULL){
        return NULL;
    }
    Tnode * rn = malloc(sizeof(Tnode));
    rn = helpBuild(fhlr);
    return rn;
}