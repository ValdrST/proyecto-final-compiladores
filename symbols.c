#include "symbols.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Inicializa la tabla de simbolos. */
void init_symbols(){
    SYM_TABLE.symbols = malloc(sizeof(symbol) * 1000);
    SYM_TABLE.total = -1;
    SYM_STACK.tables = malloc(sizeof(symbols_table) * 1000);
    *(SYM_STACK.tables) = SYM_TABLE;
    SYM_STACK.total = 0;
}

/* Funcion que obtiene los tipos de la lista pasada como parametros */
// Funcion auxiliar de print_table().
char* get_list_types(int n, int* list){
    char* str_list = malloc(sizeof(char) * 100);
    char* type = malloc(sizeof(char) * 3);
    int j = 0;
    for(int i = n; i > 0; i--){
        sprintf(type, "%d", list[i]);
        strcat(str_list, type);
        strcat(str_list, ",");
    }
    while(str_list[j] != '\0')
        j++;
    str_list[j - 1] = '\0';
    return str_list;
}

/* Funcion que busca el identificador en el mismo alcance. */
int search_scope(char *id){
    printf("\nBuscando %s en el mismo alcance....", id);
    symbols_table* top = SYM_STACK.tables + SYM_STACK.total;
    for(int i = 0; i <= top->total; i++)
        if(strcmp(id, (top->symbols + i)->id) == 0)
            return i;
    return -1;
}

/* Funcion que busca el identificador en todas las tablas. */
int search_global(char *id){
    printf("\nBuscando %s en la tabla de simbolos global....\n", id);
    int j = SYM_STACK.total;
    symbols_table* tabla_actual = SYM_STACK.tables + SYM_STACK.total;
    while(j >= 0){
        for(int i = 0; i <= tabla_actual->total; i++)
            if(strcmp(id, (tabla_actual->symbols + i)->id) == 0)
                return i;
        j--;
        tabla_actual = SYM_STACK.tables + j;
    }
    return -1;
}

/* Funcion encargada de agregar una nueva tabla de simbolos a la pila. */
void create_symbols_table(){
    printf("\nEmpieza un nuevo alcance...Nueva tabla de simbolos creada...");
    symbols_table new_table;
    new_table.symbols = malloc(sizeof(symbol) * 1000);
    new_table.total = -1;
    SYM_STACK.total++;
    *(SYM_STACK.tables + SYM_STACK.total) = new_table;
}

/* Funcion encargada de eliminar la ultima tabla de simbolos de la pila. */
void delete_symbols_table(){
    (SYM_STACK.tables + SYM_STACK.total)->total = -1;
    SYM_STACK.total--;
}

/* Funcion que agrega un simbolo a la tabla de simbolos actual. */
void insert_symbol(symbol sym){
    printf("Agregando %s a la tabla de simbolos...\n", sym.id);
    symbols_table* scope = SYM_STACK.tables + SYM_STACK.total;
    (scope->total)++;
    *(scope->symbols + scope->total) = sym;
}

/* Funcion que agrega un simbolo a la tabla de simbolos global. */
void insert_global_symbol(symbol sym){
    printf("Agregando %s a la tabla de simbolos global....\n", sym.id);
    symbols_table* global = SYM_STACK.tables + 0;
    (global->total)++;
    *(global->symbols + global->total) = sym;
}

/* Funcion que regresa el tipo del identificador pasado como parametro. 
   Busca en todas las tablas de simbolos. */
int get_type(char *id){
    int j = SYM_STACK.total;
    symbols_table* tabla_actual;
    while(j >= 0){
        tabla_actual = SYM_STACK.tables + j;
        for(int i = 0; i <= tabla_actual->total; i++)
            if(strcmp(id, (tabla_actual->symbols + i)->id) == 0)
                return (tabla_actual->symbols + i)->type;
        j--;
    }
    return -1;
}

/* Funcion que regresa la direccion del identificador pasado como parametro. 
   Busca en todas las tablas de simbolos. */
int get_dir(char *id){
    int j = SYM_STACK.total;
    symbols_table* tabla_actual;
    while(j >= 0){
        tabla_actual = SYM_STACK.tables + j;
        for(int i = 0; i <= tabla_actual->total; i++)
            if(strcmp(id, (tabla_actual->symbols + i)->id) == 0)
                return (tabla_actual->symbols + i)->dir;
        j--;
    }
    return -1;
}

/* Funcion que regresa el tipo de identificador pasado como parametro. 
   Busca en todas las tablas de simbolos. */
char* get_var(char *id){
    int j = SYM_STACK.total;
    symbols_table* tabla_actual;
    while(j >= 0){
        tabla_actual = SYM_STACK.tables + j;
        for(int i = 0; i <= tabla_actual->total; i++)
            if(strcmp(id, (tabla_actual->symbols + i)->id) == 0)
                return (tabla_actual->symbols + i)->var;
        j--;
    }
    return "-";
}

/* Funcion que regresa el numero de argumentos del identificador pasado como parametro. 
   Busca en todas las tablas de simbolos. */
int get_num_args(char *id){
    int j = SYM_STACK.total;
    symbols_table* tabla_actual;
    while(j >= 0){
        tabla_actual = SYM_STACK.tables + j;
        for(int i = 0; i <= tabla_actual->total; i++)
            if(strcmp(id, (tabla_actual->symbols + i)->id) == 0)
                return (tabla_actual->symbols + i)->num_args;
        j--;
    }
    return -1;
}

/* Funcion encargada de imprimir la tabla de simbolos global. */
void print_symbols_table(){
    symbols_table* global = SYM_STACK.tables;
    printf("\n*************** TABLA DE SIMBOLOS GLOBAL ***************\n");
    printf("pos\tid\ttipo\tdir\tclase\t#args\ttipo_args\n");
    for(int i = 0; i <= global->total; i++)
        printf("%d\t%s\t%d\t%d\t%s\t%d\t%s\n", i, (global->symbols + i)->id, (global->symbols + i)->type, (global->symbols + i)->dir, (global->symbols + i)->var, (global->symbols + i)->num_args, get_list_types((global->symbols + i)->num_args, ((global->symbols + i)->list_types)));
}

/* Funcion encargada de imprimir la tabla de simbolos de un nuevo alcance. */
void print_symbols_table_2(int pos, char* name){
    symbols_table* top = SYM_STACK.tables + pos;
    printf("\n*************** TABLA DE SIMBOLOS %s ***************\n", name);
    printf("pos\tid\ttipo\tdir\tclase\t#args\ttipo_args\n");
    for(int i = 0; i <= top->total; i++)
        printf("%d\t%s\t%d\t%d\t%s\t%d\t%s\n", i, (top->symbols + i)->id, (top->symbols + i)->type, (top->symbols + i)->dir, (top->symbols + i)->var, (top->symbols + i)->num_args, get_list_types((top->symbols + i)->num_args, ((top->symbols + i)->list_types)));
}