
#include <stdlib.h>
#include <string.h>
#include "tablaSimbol.h"
#include "pilaTablaSimbol.h"

/**
 * Crea y regresa un apuntador a una pila de símbolos.
 */
symstack *crearSymStack(){
  symstack* nPila = (symstack*)malloc(sizeof(symstack));
  nPila->num = 0;
  return nPila;
}

/**
 * Libera el espacio del apuntador.
 */
void borrarSymStack(symstack *ss){
  /*
  if(ss->root != NULL)
    borrarSymbol(ss->root);
  */
  free(ss);
}

/**
 * Inserta un símbolo al tope de la pila.
 */
void insertarSymTab(symstack *ss, symtab *sym){
  if(ss->num == 0){
    ss->root = sym;
  } else{
    symtab *aux = ss->root;
    while(aux->next != NULL)
      aux = aux->next;
    aux->next = sym;
  }
  ss->num++;
}

/**
 * Regresa un apuntador al símbolo del tope de la pila.
 */
symtab* getCima(symstack *ss){
  if(ss->num == 0)
    return NULL;
  symtab *aux = ss->root;
  while(aux->next != NULL)
    aux = aux->next;
  return aux;
}

/**
 * Saca (y regresa) el tope de la pila de símbolos.
 */
symtab* sacarSymTab(symstack *ss){
  if(ss->num == 0)
    return NULL;

  symtab *aux = ss->root;
  ss->num = ss->num - 1;

  symtab *cima;

  // Caso especial para la raíz
  if(aux->next == NULL){
    ss->root = NULL;
    return NULL;
  }

  // Los demás casos se tratan igual.
  while(aux->next != NULL){
    if(aux->next->next == NULL){ //El que verificamos que es distinto de vacío es ya la cima
      cima = aux->next;
      aux->next = NULL; //Quitamos su referencia.
      return cima;
    }
    aux = aux->next;
  }
}

