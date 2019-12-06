#include <stdlib.h>
#include <string.h>
#include "attribs.h"
stack_cad* crearStackCad(){
    stack_cad *sc = malloc(sizeof(stack_cad));
    strcpy(sc->cval,"\0");
    sc->next = NULL;
    return sc; 
}

void addStackCad(stack_cad *sc,char* cad){

    stack_cad *aux, *sc_aux;
    sc_aux = sc;
    do{
        
        if(sc_aux->next == NULL){
            sc->next = malloc(sizeof(stack_cad));
            aux = sc->next;
            strcpy(aux->cval,cad);
            break;
        }else
            sc_aux = sc_aux->next;
    }while(sc_aux->next != NULL);
}

void addStackDir(stack_dir *sd,int dir){
    sd->dir[sd->numDirs] = dir;
    sd->numDirs++;
}

stack_dir crearStackDir(){
    stack_dir sd;
    sd.numDirs = 0;
    return sd;
}

int popStackDir(stack_dir *sd){
    int num = sd->numDirs;
    sd->numDirs--;  
    return sd->dir[num];
}