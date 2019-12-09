#include "pilaTablaTipo.h"
#include "tablaTipo.h"
#include <stdio.h>
#include <stdlib.h>


typestack *crearTypeStack(){
    typestack *nuevaPTT = malloc(sizeof(typestack));
    if(nuevaPTT){
        nuevaPTT->root = NULL;
        nuevaPTT->num = 0;
    }else{
        printf("No hay memoria disponible");
    }
    return nuevaPTT;
}

void borrarTypeStack(typestack *ptt){
    if(ptt){
        typetab* aux;
        while(ptt->root){
          aux = ptt->root;
          ptt->root = ptt->root->next;
          free(aux);
        }
        free(ptt);
  }else{
    printf("No existe la pila de tabla de tipos\n");
  }
}

typetab* getCimaType(typestack *ptt){
    typetab *aux = ptt->root;
    return aux;
}

typetab* getFondoType(typestack *ptt){
    typetab *aux = ptt->root;
    typetab *aux_next = ptt->root->next;
    while(aux_next != NULL){
        aux = aux_next;
        aux_next = aux->next;
    }
        return aux;
}

void insertarTypeTab(typestack *ptt, typetab *type_tab){
    if(ptt){    //Si existe la pila
        if (ptt->root == NULL){     //La pila esta vacia
            ptt->root = type_tab;
        }else{                      //La pila no esta vacia
            typetab *aux = getCimaType(ptt);
            aux->next = type_tab;
        }
        ptt->num++;
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

typetab* sacarTypeTab(typestack *ptt){
    if(ptt){    //Si existe la pila
        if (ptt->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de tabla de simbolos esta vacia");
        }else{                      //La pila no esta vacia
            typetab *cima = getCimaType(ptt);
            //typetab *aux = cima;
            ptt->root = cima->next;
            ptt->num--;
            //free(aux);
            return(cima);
        }
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}
