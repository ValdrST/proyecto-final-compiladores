#ifndef ATTRIBS_H_INCLUDED
#include "intermediate_code.h"
#include "tablaSimbol.h"

/* Estructura para el manejo de expresiones. */
typedef struct _expresion{
    int dir;
    char base[10];
    int tipo;
    int tam;
} expresion;

/* Estructura para el manejo de condicionales. */
typedef struct _condition{
    int tipo;
    int dir;
    label *ltrue;
    label *lfalse;  
    int first;  
} condition;

/* Estructura para el manejo de valores numericos. */
typedef struct _num{
    int tipo;
    int ival;
    double dval;
    float fval;
} num;

typedef struct _var{
    int tipo;
    int dir;
    int base[10];
    int tam;
}var;

typedef struct _car{
    int tipo;
    char cval;
} car;

typedef struct _ttype{
    int tipo;
    int dim;
    int base;
}ttype;

typedef struct _stack_cad{
    char cval[100];
    struct _stack_cad *next;
}stack_cad;

typedef struct _stack_dir{
    int dir[100];
    int numDirs;
} stack_dir;

/* Estructura para el manejo de sentencias. */
typedef struct _sentence{
    label *lnext;
    int first;
} sentence;

/* Estructura para el manejo de parametros. */
typedef struct _args_list{
    listParam *lista;
    int total;
} args_list;

stack_cad *crearStackCad();
void addStackCad(stack_cad *sc,char* cad);
stack_dir crearStackDir();
void addStackDir(stack_dir *sd,int dir);
int popStackDir(stack_dir *sd);
#define ATTRIBS_H_INCLUDED
#endif
