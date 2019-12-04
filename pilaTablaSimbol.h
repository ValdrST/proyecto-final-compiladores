#ifndef PILATABLASIMBOL_H_INCLUDED
#include "tablaSimbol.h"

typedef struct _symstack symstack;

struct _symstack{
  symtab *root;
  int num;
};

symstack *crearSymStack();
void borrarSymStack(symstack *ss);
void insertarSymTab(symstack *ss, symtab *sym);
symtab* getCima(symstack *ss);
symtab* sacarSymTab(symstack *ss);
#define PILATABLASIMBOL_H_INCLUDED
#endif