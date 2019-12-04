#ifndef TABLATIPO_H_INCLUDED
#include <stdbool.h>
#include "tablaSimbol.h"
typedef struct _type type;
typedef struct _tipoBase tipoBase;
typedef union _tipo tipo;

union _tipo{
int type;
symtab *estructura;
};

struct _tipoBase{
bool est;
tipo t;
};

struct _type{
int id;
char nombre [10];
tipoBase tb;
int tamBytes;
int numElem;
type *next;
};

typedef struct _typetab typetab;
struct _typetab{
type *root;
int num;
typetab *next;
};

typetab *crearTypeTab();
type *crearTipo(int id,char* nombre,int tam, int numElem);
void borrarType(type *t);
void printTablaTipos(typetab *tt);
void borrarTypeTab(typetab *tt);
int insertarTipo(typetab *tt, type *t);
tipoBase getTipoBase(typetab *tt , int id);
int getTam(typetab *tt, int id);
int getNumElem(typetab *tt, int id);
char* getNombre(typetab *tt, int id);
#define TABLATIPO_H_INCLUDED
#endif