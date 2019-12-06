#ifndef TABLASIMBOL_H_INCLUDED
typedef struct _param param;
struct _param {
  int tipo;
  param *next;
};
typedef struct _listParam listParam;
struct _listParam {
  param *root;
  int num;
};
void borraParam(param *p);
void add(listParam lp, int tipo);
void borrarListParam(listParam *lp);
int getNumListParam(listParam *lp);
typedef struct _symbol symbol;
struct _symbol {
  char id[32];
  int tipo;
  int dir;
  char tipoVar[32];
  listParam *params;
  symbol *next;
};
symbol *crearSymbol();
void borrarSymbol(symbol *s);
typedef struct _symtab symtab;
struct _symtab {
  symbol *root;
  int num;
  symtab *next;
};

/* Retorna un apuntador a una variable Param */
param* crearParam(int tipo);

/* Retorna un apuntador a una variable listParam */
listParam* crearLP();

/* Agrega al final de la lista el parametro e incrementa num */
void add_tipo(listParam* lp, int tipo);

/* Borra toda la lista, libera la memoria */
void borrarListParam(listParam* lp);

/* Cuenta el numero de parametros en la linea */
int getNumListParam(listParam* lp);

/* Retorna un apuntador a una variable symbol */
symbol* crearSymbol(char *id, int tipo, int dir, char* tipoVar);

/* Retorna un apuntador a una variable symtab,
 * inicia contador en 0
 */
symtab* crearSymTab();

void addListParam(symtab* st, listParam *lp, char* id);
/* Borra toda la lista, libera la memoria */
void borrarSymTab(symtab*);

/* Inserta al final de la lista, en caso de insertar incrementa num
 * y retorna la posicion donde inserto. En caso contrario retorna -1
*/
int insertar(symtab* st, symbol* sym);

/* Busca en la tabla de simbolos mediante el id
 * En caso de encontrar el id retorna la posicion
 * En caso contrario retorna -1
 */
int buscar(symtab* st, char* id);

/* Retorna el tipo de dato de un id
 * En caso no encontrarlo retorna -1
 */
int getTipo(symtab* st, char* id);

/* Retorna el tipo de Variable de un id
 * En caso de no encontrarlo retorna -1
 */
char* getTipoVar(symtab* st, char* id);

/* Retorna la direccion de un id
 * En caso de no encontrarlo retorna -1
*/
int getDir(symtab* st, char* id);

/* Retorna la lista de parametros de un id
 * En caso de no encontrarlo retorna NULL
 */
listParam* getListParam(symtab* st, char* id);

/* Retorna el numero de parametros de un id
 * En caso de no encontrarlo retorna -1
 */
int getNumParam(symtab *st, char *id);

void getParams(char *paramsS,param *p);

/* Imprime toda la tabla de simbolos,
 * si contiene parametros los imprime tambien
*/
void printTablaSimbolos(symtab *st);
#define TABLASIMBOL_H_INCLUDED
#endif
