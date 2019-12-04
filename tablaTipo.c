#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tablaTipo.h"
//Crea e inicialia una tabla de tipos
typetab *crearTypeTab(){
    typetab *tt = (typetab*)malloc(sizeof(typetab));
    tt->root = NULL;
    tt->num = 0;
    tt->next=NULL;
    return tt;
}
// Crea un tipo de acuerdo a los parametros dados
type *crearTipo(int id,char* nombre,int tam, int numElem){
    type *t = (type*)malloc(sizeof(type));
    strcpy(t->nombre,nombre);
    t->id = id;
    t->tamBytes = tam;
    t->numElem = numElem;
    t->next = NULL;
    return t;
}
// Borra y libera la memoria de una tabla de tipos de forma recursiva
void borrarTypeTab(typetab *tt){
    while(tt!=NULL){
        borrarTypeTab(tt->next);
        borrarType(tt->root);
        free(tt);
    }
}
// Borra y libera memoria de forma recursiva
void borrarType(type *t){
    while(t!=NULL){
        borrarType(t->next);
        free(t);
    }
}
// Inserta un tipo en la tabla de tipos y aumenta el contador
int insertarTipo(typetab *tt, type *t){
    type t_aux, *t_next;
    t_aux = tt->root;
    do{
        if(t_aux == NULL){
            t_aux = t;
            tt->num++;
            return tt->num;
        }
        t_aux = t_aux->next;
        t_next = t_aux->next;
        
    }while(t_aux != NULL);
    return -1;
}
// Obtiene el tipo base de un id
tipoBase getTipoBase(typetab *tt , int id){
    type *t;
    t = tt->root;
    while(t != NULL){
        if(t->id==id){
            return t->tb;
        }
        t = t->next;
    }
    tipoBase tb;
    tb.est = false;
    return tb;
}
// Obtiene el tamaño de un tipo de acuerdo a su id
int getTam(typetab *tt, int id){
    type *t;
    t = tt->root;
    while(t != NULL){
        if(t->id==id){
            return t->tamBytes;
        }
        t = t->next;
    }
    return -1;
}
// Obtiene el numero de elementos de un tipo de acuerdo a su id
int getNumElem(typetab *tt, int id){
type *t;
    t = tt->root;
    while(t != NULL){
        if(t->id==id){
            return t->numElem;
        }
        t = t->next;
    }
    return -1;
}
// Obtiene el nombre de un tipo de acuerdo a su id
char* getNombre(typetab *tt, int id){
    type *t;
    t = tt->root;
    while(t != NULL){
        if(t->id==id){
            return t->nombre;
        }
        t = t->next;
    }
    return NULL;
}
// Imprime la tabla de tipos
void printTablaTipos(typetab *tt){
    type *t_next;
    if(tt != NULL){
        if(tt->root != NULL){
            do{
                printf("id: %d nombre: %s numero elementos: %d tamaño: %d tipo base: %d\n",tt->root->id,getNombre(tt,tt->root->id),getNumElem(tt,tt->root->id),getTam(tt,tt->root->id),getTipoBase(tt,tt->root->id).t.type);
                printTablaSimbolos(getTipoBase(tt,tt->root->id).t.estructura);
                t_next = tt->root->next;
            }while(t_next!=NULL);
        }else
            printf("No hay tipos en la tabla\n");
    }else{
        printf("No hay tabla de tipos\n");
    }
    
}