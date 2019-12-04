#include "pilaTablaTipo.h"
#include "tablaTipo.h"
#include <stdio.h>
#include <stdlib.h>

// Se crea una nueva pila de tablas de tipos y se inicializa
typestack *crearTypeStack() {
  typestack *ts = malloc(sizeof(typestack));
  ts->num = 0;
  ts->root = NULL;
  return ts;
}
// Elimina la pila y limpia la memoria elemento a elemento
void borrarTypeStack(typestack *ts) {
  if (ts != NULL) {
    borrarTypeTab(ts->root);
    free(ts);
  }
}
// Inserta una tabla de simbolos y aumenta el contador
void insertarTypeTab(typetack *ts, typetab *t) {
  if (ts->root == NULL) {
    ts->root = t;
  } else {
    typetab *i = ts->root;
    while (i->next) {
      i = i->next;
    }
    i->next = t;
  }
  ts->num++;
}
// Se obtiene el elemento que esta en la cima de la tabla de simbolo
typetab *getCimaType(typetack *ts) { return ts->root; }

// Hace operacion pop en la pila
typetab *sacarTypeTab(typestack *ts) {
  typetab *ts_aux, *ts_next, *tt;
  tt = (typetab *)malloc(sizeof(typetab));
  ts_aux = ts->root;
  while (ts_aux != NULL) {
    ts_next = ts_aux->next;
    if (ts_next == NULL) {
      *tt = (*ts_aux);
      free(ts_aux);
      return tt;
    }
    ts_aux = ts_next;
  }
  return NULL;
}

void print_types_table(typestack *STT) {
  typestack global = STT->root;
  printf("\n*************** TABLA DE TIPOS GLOBAL ***************\n");
  printf("pos\ttipo\tdim\tbase\n");
  for (int i = 0; i <= global->num; i++)
    printf("%d\t%s\t%d\t%d\n", i, (global->root + i)->type,
           (global->root + i)->dim, (global->root + i)->base);
}