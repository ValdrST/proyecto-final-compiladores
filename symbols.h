#ifndef SYMBOLS_H
#define SYMBOLS_H

/* Estructura de un simbolo */
// id - Identificador
// var - Clase de simbolo (variable, funcion, paramentro).
// type - Tipo del simbolo.
// dir - Direccion donde se encentra.
// num_args - Numero de parametros, si es que tiene.
// list_types - Lista con los tipos de parametros.
typedef struct _symbol{
    char* id;
    char* var;
    int type;
    int dir;
    int num_args;
    int* list_types;
} symbol;

/* Estructura de la tabla de simbolos. */
// symbols - Lista de simbolos.
// total - Total de simbolos guardados.
typedef struct _symbols_table{
    symbol* symbols;
    int total;
} symbols_table;

/* Pila que guardara las tablas de simbolos. */
// tables - Lista de tablas.
// total - Total de tablas guardadas.
typedef struct _symbols_stack symbols_stack;
struct _symbols_stack{
	symbols_table* tables;
	int total;
};

/* Tabla de simbolos global del compilador */
symbols_table SYM_TABLE;

/* Pila de tabla de simbolos del compilador */
symbols_stack SYM_STACK;

// FUNCIONES:

void init_symbols();
char* get_List_Types(int, int*);
int search_scope(char*);
int search_global(char*);
void create_symbols_table();
void delete_symbols_table();
void insert_symbol(symbol); 
void insert_global_symbol(symbol);
int get_type(char*);
int get_dir(char*);
char* get_var(char*);
void print_symbols_table();
void print_symbols_table_2(int, char*);

#endif
