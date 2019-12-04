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
param *crearParam(int tipo);
void borraParam(param *p);
listParam *crearLP();
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
symbol *crearSymbol();
symtab *crearSymTab();
char *getParams(param *p);
void printTablaSimbolos(symtab *st);
void borrarSymTab(symtab *st);
int insertar(symtab *st, symbol *sym);
int buscar(symtab *st, char *id);
int getTipo(symtab *st, char *id);
char* getTipoVar(symtab *st, char *id);
int getDir(symtab *st, char *id);
listParam *getListParam(symtab *st, char *id);
int getNumParam(symtab *st, char *id);
#define TABLASIMBOL_H_INCLUDED
#endif
