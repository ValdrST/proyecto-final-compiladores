#ifndef TYPE_TABLE_H
#define TYPE_TABLE_H

#include <stdio.h>
#include <string.h>

/* Estructura de un tipo. */
// type - 
// dim- Dimension del tipo.
// base - Tipo base del tipo.
typedef struct _type_{
	char* type;
	int dim;
	int base;
} ttype;

/* Estructura del la tabla de tipos. */
// types - Lista de tipos.
// total - Total de tipos guardados.
typedef struct _types_table{
	ttype* types;
	int total;
} types_table;

/* Estructura de la pila de tipos. */
// tables - Lista de tablas guardadas.
// total - Total de tablas guardadas.
typedef struct _types_stack{
	types_table* tables;
	int total;
} types_stack;

/* Pila de tipos donde se guardaran todas las tablas de tipos. */
types_stack TYP_STACK;

// Funciones:

void init_types();
void create_types_table();
void delete_types_table();
int insert_type(ttype);
int insert_type_global(ttype);
void print_types_table();

#endif