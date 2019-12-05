#ifndef PILATABLATIPO_H_INCLUDED
#include "tablaTipo.h"
typedef struct _typestack typestack;

struct _typestack
{
   typetab *root;
   int num;
};

typestack *crearTypeStack();
void borrarTypeStack(typestack *ptt);
void insertarTypeTab(typestack *ptt, typetab *type_tab);
typetab* getCimaType(typestack *ptt);
typetab* sacarTypeTab(typestack *ptt);
#define PILATABLATIPO_H_INCLUDED
#endif

