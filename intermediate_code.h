#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include <string.h>
#include "cMips.h"
#include "intermediate_code.h"
typedef struct _quad quad;
/* Estructura de una cuadrupla. */
// op - Operacion que se va a realizar.
// arg1 - Argumento 1.
// arg2 - Argumento 2.
// res - Donde se va a almacenar el resultado.
struct _quad {
  char *op;
  char *arg1;
  char *arg2;
  char *res;
  quad *next;
};

/* Estructura de la tabla de cuadruplas. */
// items - Lista de cuadruplas almacenadas.
// i - Total de cuadruplas guardadas.
typedef struct _code {
  quad *root;
  int num_instrucciones;
} code;

typedef struct _label {
  struct _label* next;
  int *items;
  int i;
} label;


/* Codigo siendo atributo global. */
code CODE;

// Funciones:

void concat_code(code *c1,code *c2);
void init_code();
quad *crea_quad(char *op, char *arg1, char *arg2, char *res);
code *crea_code();
int gen_code(char *op, char *arg1, char *arg2, char *res);
void agregar_cuadrupla(code *c, char *op, char *arg1, char *arg2, char *res);
label* create_list(int l);
label* merge(label *l1, label *l2);
void backpatch(label *l, label *l2);
void print_code(code *c);
label* newLabel();
#endif
