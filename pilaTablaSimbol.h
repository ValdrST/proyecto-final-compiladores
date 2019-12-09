#ifndef PILATABLASIMBOL_H_INCLUDED
#include "tablaSimbol.h"

typedef struct _symstack symstack;

struct _symstack{
  symtab *root;
  int num;
};

symstack *crearSymStack();
void borrarSymStack(symstack *pts);
void insertarSymTab(symstack *pts, symtab *sym_tab);
symtab* getCimaSym(symstack *pts);
symtab* getFondoSym(symstack *pts);
symtab* sacarSymTab(symstack *pts);
void printPilaSym(symstack *pts);
#define PILATABLASIMBOL_H_INCLUDED
#endif