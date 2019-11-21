#ifndef ATTRIBS_H
#define ATTRIBS_H

#include "intermediate_code.h"

/* Estructura para el manejo de expresiones. */
typedef struct _expresion{
    char* dir;
    int type;
    int first;
} expresion;

/* Estructura para el manejo de condicionales. */
typedef struct _condition{
    label ltrue;
    label lfalse;  
    int first;
} condition;

/* Estructura para el manejo de valores numericos. */
typedef struct _num{
    int type;
    int ival;
    double dval;
    float fval;
} num;

/* Estructura para el manejo de sentencias. */
typedef struct _sentence{
    label lnext; 
    int retorno;
} sentence;

/* Estructura para el manejo de tipos. */
typedef struct _type{
    int type;
    int dim;
} type;

/* Estructura para el manejo de parametros. */
typedef struct _args_list{
    int* args;
    int total;
} args_list;

#endif
