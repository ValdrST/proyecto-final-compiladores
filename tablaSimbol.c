#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablaSimbol.h"

// Se crea un parametro
param *crearParam(int tipo){
    param *p = (param*)malloc(sizeof(param));
    p->tipo = tipo;
    p->next = NULL;
    return p;
}
// Se borra y libera la memoria elemento a elemento del parametro
void borraParam(param *p){
    while(p!=NULL){
        borraParam(p->next);
        free(p);
    }
}

// Se crea una lista de parametros
listParam *crearLP(){
    listParam *lp = (listParam*)malloc(sizeof(listParam));
    lp->num = 0;
    return lp;
}

// Se añade un parametro a la lista de parametros
void add(listParam lp, int tipo){
    param *p, *p_next;
    p = lp.root;
    while(p != NULL){
        p_next = p->next;
        if(p_next == NULL){
            p->next = crearParam(tipo);
        }
        p = p_next->next;
        
    }
    lp.num++;
}
 
//Se borra  la lista de parametros y se libera la memoria
void borrarListParam(listParam *lp){
    borraParam(lp->root);
    free(lp);
}
// se obtiene el numero de parametros de la lista
int getNumListParam(listParam *lp){
    return lp->num;
}
// Se crea e inicializa un simbolo nuevo
symbol *crearSymbol(){
    symbol *s = (symbol*)malloc(sizeof(symbol));
    s->next=NULL;
    s->params=crearLP();
    return s;
}
// Se elimina y se libera la memoria del simbolo de forma recursiva
void borrarSymbol(symbol *s){
    while(s!=NULL){
        borrarSymbol(s->next);
        free(s);
    }
}
// Crea e inicializa una tabla de simbolos
symtab *crearSymTab(){
    symtab *st = (symtab*)malloc(sizeof(symtab));
    st->next=NULL;
    st->num = 0;
    st->root = NULL;
    return st;
}
// Borra la tabla de simbolos y libera meoria de forma recursiva
void borrarSymTab(symtab *st){
    while(st!=NULL){
        borrarSymTab(st->next);
        borrarSymbol(st->root);
        free(st);
    }
}
// Inserta simbolo en tabla de simbolos
int insertar(symtab *st, symbol *sym){
    symbol *s, *s_next;
    s = st->root;
    while(s != NULL){
        s_next = s->next;
        if(s_next == NULL){
            s->next = sym;
            sym->next = NULL;
            st->num++;
            return st->num;
        }
        s = s_next;
    }
    return -1;
}
// Retorna el id si es que existe de la tabla de simbolos si no retorna -1
int buscar(symtab *st, char *id){
    symbol *s;
    s = st->root;
    int i = 0;
    while(s != NULL){
        if(strcmp(s->id,id)==0){
            return i;
        }
        s = s->next;
        i++;
    }
    return -1;
}
// obtiene el tipo de un id en la tabla si no existe retorna -1
int getTipo(symtab *st, char *id){
    symbol *s;
    s = st->root;
    while(s != NULL){
        if(strcmp(s->id,id)==0){
            return s->tipo;
        }
        s = s->next;
    }
    return -1;
}
// Obtiene el tipo var de la tabla de simbolos si no existe retorna -1
char* getTipoVar(symtab *st, char *id){
    symbol *s;
    s = st->root;
    while(s != NULL){
        if(strcmp(s->id,id)==0){
            return s->tipoVar;
        }
        s = s->next;
    }
    return -1;
}
// Obtiene la direccion de una tabla de simbolos si no existe retorna -1
int getDir(symtab *st, char *id){
    symbol *s;
    s = st->root;
    while(s != NULL){
        if(strcmp(s->id,id)==0){
            return s->dir;
        }
        s = s->next;
    }
    return -1;
}
// Obtiene la lista de parametros de una tabla de simbolos si no existe retorna NULL
listParam *getListParam(symtab *st, char *id){
    symbol *s;
    s = st->root;
    while(s != NULL){
        if(strcmp(s->id,id)==0){
            return s->params;
        }
        s = s->next;
    }
    return NULL;
}

int getNumParam(symtab *st, char *id){
    symbol *s;
    s = st->root;
    while(s != NULL){
        if(strcmp(s->id,id)==0){
            return s->params->num;
        }
        s = s->next;
    }
    return -1;
}

// Retorna una cadena con los parametros 
char* getParams(param *p){
    param *p_next;
    char* param_s = "";
    do{
        char* c = malloc(sizeof(char)*100);
        strcat(param_s," ");
        sprintf(c, "%d", p->tipo);
        strcat(param_s,c);
        p_next = p->next;
    }while(p_next != NULL);
    return param_s;
}
// Imprime la tabla de simbolos
void printTablaSimbolos(symtab *st){
    symbol *s_next;
    char * id;
    if(st!=NULL)
    do{
        if(st->root != NULL){
            id = st->root->id;
            printf("id: %d dir: %d tipo: $d tipoVar: %d params: %s\n",st->root->id,getDir(st,id),getTipo(st,id),getTipoVar(st,id),getParams(st->root->params->root));
            s_next = st->root->next;
        }
    }while(s_next != NULL);
    else{
        printf("No hay simbolos en la tabla\n");
    }
    
}