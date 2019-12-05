#include "attribs.h"
#include <stdlib.h>
stack_cad crearStackCad(){
    stack_cad *sc = malloc(sc*sizeof(stack_cad));
    sc->cval = '\0';
    sc->next = NULL;
    return *sc; 
}

void addStackCad(stack_cad *sc,char* cad){
    do{
        stack_cad *aux, *sc_aux;
        sc_aux = sc;
        if(sc_aux->next == NULL){
            sc->next = malloc(sc*sizeof(stack_cad));
            aux = sc->next;
            strcpy(aux->cval,cad);
            break;
        }else
            sc_aux = sc_aux->next;
    }while(sc_aux->next != NULL);
}