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

/* Retorna un apuntador a una variable type */
tipo *crearTipoPrimitivo(int id);
tipo *crearTipoStruct(symtab* estructura);
tipoBase *crearArqueTipo(bool is_struct, tipo* base_type);
type *crearTipoArray(int id, char* nombre, tipoBase* tb, int size, int num_elem);
type *crearTipoNativo(int id, char* nombre, tipoBase* tb, int size);
type *crearTipo(char* nombre, int dim, int tipo, int numElem, bool est,symtab *estructura);
/* Borra type, libera memoria */
void borrarType(type *t);

/*Crea tabla de tipos*/
typetab* crearTypeTab();

void setSymTab(typetab tt, symtab* st);

/* Borra la tabla de tipos, libera memoria */
void borrarTypeTab(typetab *tt);

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *tt, type *t);

/* Retorna el tipo base de un tipo
 * En caso de no encontrarlo retorna NULL
 */
tipoBase* getTipoBase(typetab *tt, int id);

/* Retorna el numero de bytes de in tipo
 * En caso de no encontrarlo retorna -1
 */
int getTam(typetab* tt, int id);

/* Retorna el numero de elementos de un tipo
 * En caso de no encontrarlo retorna -1
 */
int getNumElem(typetab* tt, int id);

/* Retorna el nombre de un tipo
 * En caso de no encontrarlo retorna NULL
 */
char* getNombre(typetab* tt, int id);
void printTablaTipos(typetab *tt);
#define TABLATIPO_H_INCLUDED
#endif