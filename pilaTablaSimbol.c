
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tablaSimbol.h"
#include "pilaTablaSimbol.h"
symstack *crearSymStack(){
    symstack *nuevaPTS = malloc(sizeof(symstack));
    if(nuevaPTS){
        nuevaPTS->root = NULL;
        nuevaPTS->num = 0;
    }else{
        printf("No hay memoria disponible");
    }
    return nuevaPTS;
}

void borrarSymStack(symstack *pts){
    if(pts){
        symtab* aux;
        while(pts->root){
          aux = pts->root;
          pts->root = pts->root->next;
          free(aux);
        }
        free(pts);
  }else{
    printf("No existe la pila de tabla de simbolos\n");
  }
}

symtab* getCimaSym(symstack *pts){
    symtab *aux = pts->root;
    return aux;
}

symtab* getFondoSym(symstack *pts){
    symtab *aux = pts->root;
    symtab *aux_next = pts->root->next;
    while(aux_next != NULL){
        aux = aux_next;
        aux_next = aux->next;
    }
        return aux;
}

void insertarSymTab(symstack *pts, symtab *sym_tab){
    if(pts){    //Si existe la pila
        if (pts->root == NULL){     //La pila esta vacia
            pts->root = sym_tab;
        }else{                      //La pila no esta vacia
            symtab *aux = getCimaSym(pts);
            aux->next = sym_tab;
        }
        pts->num++;
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

symtab* sacarSymTab(symstack *pts){
    if(pts){    //Si existe la pila
        if (pts->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de tabla de simbolos esta vacia");
        }else{                      //La pila no esta vacia
            symtab *cima = getCimaSym(pts);
            //symtab *aux = cima;
            pts->root = cima->next;
            pts->num--;
            //free(aux);
            return cima;
        }
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}
