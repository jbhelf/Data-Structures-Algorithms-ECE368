#include<stdio.h>
#include<stdlib.h>
#include "packing.h"

void freeTree(Tree * tr){
    if(tr != NULL){
        freeTree(tr->left);
        freeTree(tr->right);
    }
    free(tr);
}

static void push(Tree * leaf, TOS * s){
    STK * nLay = malloc(sizeof(STK)); //next layer
    if(nLay == NULL){
        printf("\nMalloc failed");
        return;
    }
    nLay->layer = s->top; 
    nLay->lf = leaf;
    s->top = nLay;
}

Tree * pop(TOS * tip){
    Tree * node = tip->top->lf;
    STK * toFree = tip->top;
    tip->top = tip->top->layer;
    free(toFree); //delete the stack layer
    return(node);
}

static void cartesian(Tree * tn){
    if(tn->left == NULL || tn->right == NULL){
        return;
    }
    tn->left->x = tn->x;
    tn->right->y = tn->y;
    if(tn->indc =='V'){
        tn->left->y = tn->y;
        tn->right->x = tn->x + tn->left->w;
    }else if(tn->indc =='H'){
        tn->left->y = tn->y + tn->right->l;
        tn->right->x = tn->x;
    }
    cartesian(tn->left);
    cartesian(tn->right);
}

Tree * treeConstr(char * filename){
    //Builds tree from input 1 given in postorder
    FILE * fhlr = fopen(filename, "r");
    if(fhlr == NULL){
        return NULL;
    }
    int key, ln, wd, c, nxt;
    TOS * head = malloc(sizeof(TOS));
    if(head == NULL){
        printf("\nMalloc failed");
        return NULL;
    }
    while((c = fgetc(fhlr)) != EOF){
        nxt = fgetc(fhlr);
        fseek(fhlr, -1, SEEK_CUR);
        if(c != '\n' && ((c != 'H' && c != 'V') || (nxt != '\n' && nxt != EOF))){ //box nodes
            fseek(fhlr, -1, SEEK_CUR);
            fscanf(fhlr, "%d(%d,%d)", &key, &wd, &ln);
            Tree * leaf = malloc(sizeof(Tree));
            if(leaf == NULL){
                printf("\nMalloc failed");
                return NULL;
            }
            leaf->left = NULL;
            leaf->right = NULL;
            leaf->w = wd;
            leaf->l = ln;
            leaf->indc = key;
            leaf->x = leaf->y = 0;
            push(leaf, head);
            if(head == NULL){
                printf("\nMalloc failed");
                return NULL;
            }
        }else if(c == 'H' || c == 'V'){ //cuts
            Tree * cut = malloc(sizeof(Tree));
            if(cut == NULL){
                printf("\nMalloc failed");
                return NULL;
            }
            cut->right = pop(head);
            cut->left = pop(head); 
            cut->indc = c;
            cut->x = cut->y = 0;
            if(c == 'H'){ 
                cut->l = (cut->left->l + cut->right->l);
                cut->w = (cut->left->w > cut->right->w)?cut->left->w:cut->right->w;
            }else if(c == 'V'){
                cut->w = (cut->left->w + cut->right->w);
                cut->l = (cut->left->l > cut->right->l)?cut->left->l:cut->right->l;
            }
            push(cut, head);
            if(head == NULL){
                printf("\nMalloc failed");
                return NULL;
            }
        }
        if(c == EOF || nxt == EOF){break;}
    }
    fclose(fhlr);
    Tree * rn = pop(head);
    free(head); 

    cartesian(rn);

    return(rn);
}

static void helper(Tree * tr, FILE * fl1, FILE * fl2, FILE * fl3){
    if((tr->indc == 'H' || tr->indc == 'V') && (tr->left != NULL && tr->right != NULL)){
        fprintf(fl1, "%c\n", tr->indc);
    }else{
        fprintf(fl1, "%d(%d,%d)\n",tr->indc,tr->w, tr->l);
        fprintf(fl3, "%d((%d,%d)(%d,%d))\n",tr->indc,tr->w,tr->l,tr->x,tr->y);
    }
    if(tr->left != NULL){
        helper(tr->left, fl1, fl2, fl3);
    }
    if(tr->right != NULL){
        helper(tr->right, fl1, fl2, fl3);
    }
    if((tr->indc == 'H' || tr->indc == 'V')&& (tr->left != NULL && tr->right != NULL)){
        fprintf(fl2, "%c(%d,%d)\n", tr->indc,tr->w, tr->l);
    }else{
        fprintf(fl2, "%d(%d,%d)\n",tr->indc,tr->w, tr->l);
    }
}

void outputer(char * fileone, char * filetwo, char * filethree, Tree * tr){
    //Prints values in pre order fashion (argv[2])
    FILE * fl1 = fopen(fileone, "w");
    FILE * fl2 = fopen(filetwo, "w");
    FILE * fl3 = fopen(filethree, "w");
    if(fl1 != NULL && fl2 != NULL && fl3 != NULL && tr != NULL){
        helper(tr, fl1, fl2, fl3);
        fclose(fl1);
        fclose(fl2);
        fclose(fl3);
        return;
    }
    printf("\nFiles failed to open");
}
