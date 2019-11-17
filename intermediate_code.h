#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include <string.h>

/* Estructura de una cuadrupla. */
// op - Operacion que se va a realizar.
// arg1 - Argumento 1.
// arg2 - Argumento 2.
// res - Donde se va a almacenar el resultado.
typedef struct _quad{
	char* op;
	char* arg1;
	char* arg2;
	char* res;
} quad;

/* Estructura de la tabla de cuadruplas. */
// items - Lista de cuadruplas almacenadas.
// i - Total de cuadruplas guardadas.
typedef struct _intermediate_code{
	quad* items;
	int i;
} intermediate_code;

typedef struct _label{
	int* items;
	int i;
} label;

/* Tabla que usara el compilador para guardar las cuadruplas. */
intermediate_code CODE;

// Funciones:

void init_code();
int gen_code(char *op , char *arg1, char *arg2, char *res);
label create_list(int l);
label merge(label l1, label l2);
void backpatch(label l, int inst);
void print_code();

#endif
