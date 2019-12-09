#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tablaTipo.h"


type *crearTipo(char* nombre, int dim, int tipo, int numElem, bool est,symtab *estructura){
    type* nuevo_type = malloc(sizeof(type));
    if(nuevo_type){
        //El id se agrega al momento de insertar a la tabla de tipos 
        strcpy(nuevo_type->nombre, nombre);
        nuevo_type->tb.t.type = tipo;
        nuevo_type->tb.est = est;
        if(est == true){
            nuevo_type->tb.t.estructura = estructura;
        }
        nuevo_type->numElem = numElem;
        nuevo_type->tamBytes = dim * numElem;
        //El espacio en bytes se agrega al momento de insertar a la tabla de tipos
        return nuevo_type;
    }else{
        printf("No hay memoria disponible");
        return NULL;
    }
    return nuevo_type;
}
//Crea e inicialia una tabla de tipos
tipo *crearTipoPrimitivo(int id){
    tipo* base_type = malloc(sizeof(tipo));
    if(base_type){
        base_type->type = id;
    }else{
        printf("No hay memoria disponible\n");
    }
    return base_type;
}

/* Retorna un apuntador a una variable tipo */
tipo *crearTipoStruct(symtab* estructura){
    tipo* base_type = malloc(sizeof(tipo));
    if(base_type){
        base_type->estructura = estructura;
    }else{
            printf("No hay memoria disponible\n");
    }
    return base_type;
}

/* Retorna un apuntador a una variable tipoBase */
tipoBase *crearArqueTipo(bool is_struct, tipo* base_type){
    tipoBase* nuevo = malloc(sizeof(tipoBase));
    if(nuevo){
        nuevo->est = is_struct;
        nuevo->t = *base_type;
    }else{
        printf("No hay memoria disponible\n");
    }
    return nuevo;
}

/* Crear un tipo arreglo */
type *crearTipoArray(int id, char* nombre, tipoBase* tb, int size, int num_elem){
    type* tipo = malloc(sizeof(type));
    if(tipo != NULL){
        tipo->id = id;
        strcpy(tipo->nombre, nombre);
        tipo->tb = *tb;
        tipo->tamBytes = size;
        tipo->numElem = num_elem;
        tipo->next = NULL;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return tipo;
}

/* Crear un tipo nativo */
type *crearTipoNativo(int id, char* nombre, tipoBase* tb, int size){
    type* tipo = malloc(sizeof(type));
    if(tipo != NULL){
        tipo->id = id;
        strcpy(tipo->nombre, nombre);
        tipo->tb = *tb;
        tipo->tamBytes = size;
        tipo->numElem = 0;
        tipo->next = NULL;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return tipo;
}

/*Crea una lista de tipos*/
typetab* crearTypeTab(){
    typetab* tt= malloc(sizeof(typetab));
    tipo *tipo_base;
    tipoBase *arquetipo;
    type *nuevoTipo;

    tt->root=NULL;
    tt->num=0;
    tt->next = NULL;

    
    tipo_base = crearTipoPrimitivo(0);
    arquetipo = crearArqueTipo(false, tipo_base);
    nuevoTipo = crearTipoNativo(0, "sin", arquetipo, 0);
    insertarTipo(tt, nuevoTipo);
    //Crear tipo entero
    tipo_base = crearTipoPrimitivo(1);
    arquetipo = crearArqueTipo(false, tipo_base);
    nuevoTipo = crearTipoNativo(1, "ent", arquetipo, 4);
    insertarTipo(tt, nuevoTipo);

    //Crear tipo real
    tipo_base = crearTipoPrimitivo(2);
    arquetipo = crearArqueTipo(false, tipo_base);
    nuevoTipo = crearTipoNativo(2, "real", arquetipo, 8);
    insertarTipo(tt, nuevoTipo);

    //Crear tipo doble
    tipo_base = crearTipoPrimitivo(3);
    arquetipo = crearArqueTipo(false, tipo_base);
    nuevoTipo = crearTipoNativo(3, "dreal", arquetipo, 16);
    insertarTipo(tt, nuevoTipo);

    //Crear tipo caracter
    tipo_base = crearTipoPrimitivo(4);
    arquetipo = crearArqueTipo(false, tipo_base);
    nuevoTipo = crearTipoNativo(4, "car", arquetipo, 4);
    insertarTipo(tt, nuevoTipo);
    return tt;
}

/* Borra la tabla de tipos, libera memoria */
void borrarTypeTab(typetab *tt){
    while(tt!=NULL){
        borrarTypeTab(tt->next);
        borrarType(tt->root);
        free(tt);
    }
}
void borrarType(type *t){
    while(t!=NULL){
        borrarType(t->next);
        free(t);
    }
    
}

int buscarTipo(typetab* tt, char* nombre){
    if(tt){
        int posicion = 0;
        if(tt->root == NULL){
            return -1; //La tabla esta vacia
        }
        type* tipo_actual = tt->root;
        while (tipo_actual != NULL){
            posicion++;
            if (strcmp(nombre, tipo_actual->nombre) == 0)
                return posicion;
            else
                tipo_actual = tipo_actual->next;
        }
        return -1;  //El simbolo no existe
    }else
        printf("Error: la tabla de tipos no existe\n");
      return -1;
}

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *tt, type *t){
    if(tt){
        int posicion = buscarTipo(tt, t->nombre);
        if(posicion == -1){
            tt->num++;
            if(tt->root == NULL){
                tt->root = t; //es el primer simbolo
            }
            else{
                type* tipo_actual = tt->root;
                while(tipo_actual->next != NULL){
                    tipo_actual = tipo_actual->next;
                }
                tipo_actual->next = t;
            }
            return (tt->num);
        }
        else{
            printf("No guardar nada\n");
            return -1;
        }
    }else
        printf("Error: la tabla de tipos no existe\n");
        return -1;
}

 /* Retorna el tipo base de un tipo
  * En caso de no encontrarlo retorna NULL
  */
 tipoBase* getTipoBase(typetab *tt, int id){
   if(tt){
    if(tt->root){
       type* aux = tt->root;
       int i;
       for(i=0;i<id; i++)
         aux = aux->next;
       if(&aux->tb)
         return &aux->tb;
     }
     return NULL;
   }
   return NULL;
 }
 /* Retorna el numero de bytes de un tipo
  * En caso de no encontrarlo retorna -1
  */
 int getTam(typetab *tt, int id){
    if(tt->root){
        type* aux = tt->root;
        while(aux != NULL){
            if(aux->id == id){
                return aux->tamBytes;
            }
            aux = aux->next;
        }
        return -1;
    }
 }



 /* Retorna el numero de elementos de un tipo
  * En caso de no encontrarlo retorna -1
  */
 int getNumElem(typetab *tt, int id){
    if(tt){
        if(tt->root){
            type* aux = tt->root;
            //Recorre la lista hasta que encuentre el id
            int i;
            for(i=0;i<id; i++)
                aux = aux->next;
            return aux->numElem;
        }
        return -1;
    }
    return -1;
 }

/* Imprime toda la tabla de tipos,
 * distingue entre estructuras, arrays y tipos nativos
*/
char* getNombre(typetab *tt, int id){
    if(tt){
     if(tt->root){
        type* aux = tt->root;
        //Recorre la lista hasta que encuentre el id
        int i;
        for(i=0;i<id; i++)
            aux = aux->next;
        return aux->nombre;
    }
   }
    return NULL;
}
// Imprime la tabla de tipos
void printTablaTipos(typetab *tt){
    type* tipo_actual = tt->root;
    tipoBase* tb;

    printf("###TABLA DE TIPOS###\n");
    printf("ID\tNOMBRE\tNUM_ELEM TAM TIPO_BASE\n");
    while(tipo_actual!=NULL){
        int id = tipo_actual->id;
        printf("%d\t%s\t%d\t%d\t%d\n",id,getNombre(tt,id),getNumElem(tt,id),getTam(tt,id),getTipoBase(tt,id)->t.type);
        tipo_actual = tipo_actual->next;
    }
}