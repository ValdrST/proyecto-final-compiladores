#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablaSimbol.h"

param* crearParam(int tipo){
    param* parametro= malloc(sizeof(param));
    if(parametro != NULL){
        parametro->tipo = tipo;
        parametro->next = NULL;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return parametro;
}

/* Retorna un apuntador a una variable listParam */
listParam *crearLP(){
    listParam* lista = malloc(sizeof(listParam));
    if(lista != NULL){
        lista->root = NULL;
        lista->num = 0;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return lista;
}

/* Agrega al final de la lista el parametro e incrementa num */
void add_tipo(listParam* lp, int tipo){
    param* parametro = crearParam(tipo);
    if(lp->root == NULL){
        lp->root = parametro;
    }else{
        param* puntero = lp->root;
        while(puntero->next){
            puntero = puntero->next;
        }
        puntero->next = parametro;
    }
    lp->num++;
}
/* Borra toda la lista, libera la memoria */
void borrarListParam(listParam* lp){
    if(lp){
        param* aux;
        while(lp->root){
          aux = lp->root;
          lp->root = lp->root->next;
          free(aux);
        }
        free(lp);
  }else{
    printf("No existe la lista de parametros\n");
  }
}

/* Cuenta el numero de parametros en la linea */
int getNumListParam(listParam *lp){
    return lp->num;
}

/* Retorna un apuntador a una variable symbol */
symbol* crearSymbol(char *id, int tipo, int dir, char* tipoVar){
    symbol* sym_tmp= malloc(sizeof(symbol));
    if(sym_tmp != NULL)
    {
        strcpy(sym_tmp->id, id);
        sym_tmp->tipo = tipo;
        sym_tmp->dir = dir;
        sprintf(sym_tmp->tipoVar, "%s", tipoVar);
        sym_tmp->params = crearLP();
        sym_tmp->next = NULL;
    }
    else
    {
        printf("No hay memoria disponible\n");  //ERROR
    }
 return sym_tmp;

}

void addListParam(symtab* st, listParam *lp, char* id){
    if(st){
        int posicion = 0;
        if(st->root == NULL){
            return; //La tabla esta vacia
        }
        symbol* simbolo_actual = st->root;
        while (simbolo_actual != NULL){
            posicion++;
            if (strcmp(id, simbolo_actual->id) == 0){
                simbolo_actual->params = lp;
                return;
            }else
                simbolo_actual = simbolo_actual->next;
        }
  	}else
  		printf("Error: la tabla de simbolos no existe\n");
}

/* Retorna un apuntador a una variable symtab,
 * inicia contador en 0
 */
symtab* crearSymTab(){
  symtab* st = malloc(sizeof(symtab));
  st->root = NULL;
  st->num = 0;
  st->next = NULL;
  return st;
}

/* Borra toda la lista, libera la memoria */
void borrarSymTab(symtab* st){
    if(st){
        symbol* aux;
        while(st->root){
          aux = st->root;
          st->root = st->root->next;
          borrarListParam(aux->params);
          free(aux);
        }
        free(st);
    }
    else{
        printf("No existe la tabla de simbolos\n");
    }
}

/* Inserta al final de la lista, en caso de insertar incrementa num
 * y retorna la posicion donde inserto. En caso contrario retorna -1
*/
int insertar(symtab* st, symbol* sym){
    if(st){
        int posicion = buscar(st, sym->id);
        if(posicion == -1){
            st->num++;
            if(st->root == NULL){
                st->root = sym; //es el primer simbolo
            }
            else{
                symbol* simbolo_actual = st->root;
                while(simbolo_actual->next != NULL){
                    simbolo_actual = simbolo_actual->next;
                }
                simbolo_actual->next = sym;
            }
            return (st->num);
        }
        else{
            printf("Error: el simbolo ya existe en la posicion: %i\n", posicion);
            return -1;
        }
	}else
        printf("Error: la tabla de simbolos no existe\n");
}

/* Busca en la tabla de simbolos mediante el id
 * En caso de encontrar el id retorna la posicion
 * En caso contrario retorna -1
 */
int buscar(symtab* st, char* id){
    if(st){
        int posicion = 0;
        if(st->root == NULL){
            return -1; //La tabla esta vacia
        }
        symbol* simbolo_actual = st->root;
        while (simbolo_actual != NULL){
            posicion++;
            if (strcmp(id, simbolo_actual->id) == 0)
                return posicion;
            else
                simbolo_actual = simbolo_actual->next;
        }
        return -1;	//El simbolo no existe
  	}else
  		printf("Error: la tabla de simbolos no existe\n");
}

/* Retorna el tipo de dato de un id
 * En caso no encontrarlo retorna -1
 */
int getTipo(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Tipo de dato no encontrado\n");
        return -1;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->tipo);
    }
}

/* Retorna el tipo de variable de un id
 * En caso no encontrarlo retorna -1
 */
char* getTipoVar(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Tipo de variable no encontrado\n");
        return NULL;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->tipoVar);
    }
}

/* Retorna la direccion
 * En caso de no encontrarlo retorna -1
 */
int getDir(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Direccion no encontrada\n");
        return -1;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->dir);
    }
}

/* Retorna la lista de parametros de un id
 * En caso de no encontrarlo retorna NULL
 */
listParam* getListParam(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Lista de parametros no encontrada\n");
        return NULL;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->params);
    }
}

/* Retorna el numero de parametros de un id
 * En caso de no encontrarlo retorna -1
 */
int getNumParam(symtab *st, char *id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Numero de parametros no encontrados\n");
        return -1;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->params->num);
    }
}

void getParams(char *paramsS,param *p){
    while(p){
        char tipo[100];
        sprintf(tipo, " %d", p->tipo);
        strcat(paramsS,tipo);
        p = p->next;
    }
}
// Imprime la tabla de simbolos
void printTablaSimbolos(symtab *st){
    int simbolos = 1;
    int num_params;
    symbol* simbolo_actual = st->root;
    listParam* lista;
    param* param_actual;

    printf("###TABLA DE SIMBOLOS###\n");
    printf("NUM ID TIPO DIR TipoVar Params\n");
    while(simbolos != (st->num)+1){ 
        char tipoVar_v[100];
        if(getTipoVar(st, simbolo_actual->id) == NULL){
            strcpy(tipoVar_v,"Nulo");
        }else{
            strcpy(tipoVar_v,getTipoVar(st, simbolo_actual->id));
        }
        printf("%d %s %d %d %s ",simbolos,simbolo_actual->id,getTipo(st, simbolo_actual->id),getDir(st, simbolo_actual->id),tipoVar_v);
        lista = getListParam(st, simbolo_actual->id);
        if(lista){
            param_actual = lista->root;
            while(param_actual != NULL){
            printf("%d, ",param_actual->tipo);
            param_actual = param_actual->next;
            }
        }else{
                printf("-");
            }
        printf("\n");
        simbolo_actual = simbolo_actual->next;
        simbolos++;
    }
}