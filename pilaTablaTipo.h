#ifndef PILATABLATIPO_H_INCLUDED

typedef struct _typetack typetack;

struct _typetack
{
   typetab *root;
   int num;
};

typetack *crearTypeStack();

void borrarTypeStack(typetack *st);

void insertarTypeTab(typetack *ts, typetab *sym);

typetab* getCimaType(typetack *ts);

typetab* sacarTypeTab(typetack *ts);
#define PILATABLATIPO_H_INCLUDED
#endif

