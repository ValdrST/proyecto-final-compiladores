%{

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "attribs.h"
	#include "pilaTablaSimbol.h"
	#include "pilaTablaTipo.h"
	#include "tablaSimbol.h"
	#include "tablaTipo.h"
	#include "intermediate_code.h"

	extern int yylex();
	extern int yyparse();
	extern char *yytext;
	extern FILE *yyin;
	extern FILE *yyout;
	extern int yylineno;
	// Variable que llevara el manejo de direcciones.
	int dir;
	int FuncType;
	int temp;
	bool FuncReturn;
	stack_dir stackDir;
	int tipo_g; 
	symstack *StackTS;
	stack_cad *StackCad;
	typestack *StackTT;
	ttype base;
	typetab *tt_global;
	symtab *ts_global;
	code CODE;
	int indice;
	int label_c;

	int id_tipo;

	// Variable que guardara la direccion cuando se haga un cambio de alcance.
	int dir_aux;
	// Variable que llevara la cuenta de variables temporales.
	int temporales;
	// Variable que indica la siguiente instruccion.
	int siginst;
	// Variable que guarda el tipo heredado.
	int global_tipo;
	// Variable que guardara la dimension heredada.
	int global_dim;
	// Variable que llevara el numero de parametros que tiene una funcion.
	int num_args;
	// Lista que guarda los tipos de los parametros.
	int* list_args;
	// Variable que nos ayuda a saber en que alcance estamos.
	int scope;
	// Variable que dice si hay un registro en camino
	int has_reg;

	void init();
	int busca_main();
	int existe_en_alcance(char*);
	int existe_globalmente(char*);
	char *reducir(char *dir, int t1, int t2);
	char *ampliar(char *dir, int t1, int t2);
	int max(int, int);
	void new_Temp(char*);
	char* newIndex();
	char* newTemp();
	void label_to_char(char* lchar, label l);
	void intToChar(char* out, int i); 
	void print_label(label *l);
	expresion operacion(expresion, expresion, char*);
	expresion numero_entero(int);
	expresion numero_flotante(float);
	expresion numero_doble(double);
	expresion funcion_e(char* f);
	expresion caracter(char);
	expresion variable_v(char* c);
	expresion cadena_s(char* c);
	condition relacional(condition e1, condition e2, char* oprel);

	expresion identificador(char *s);
	label *newLabel();

	void yyerror(char*);

%}

%union{
	int line;
	char sval[32];
	ttype tval;
	expresion eval;
	num num;
	car car;
	var vval;
	args_list args_list;
	condition cond;
	sentence sent;
}

%start programa

%token<sval> ID
%token<num> NUM
%token INICIO
%token FIN
%token ENT
%token REAL
%token DREAL
%token CAR
%token SIN
%token REGISTRO
%token COMA
%token PT
%token FUNC
%token MIENTRAS
%token MIENTRAS_QUE
%token HACER
%token VERDADERO
%token FALSO
%token DEVOLVER
%token SEGUN
%token TERMINAR
%token CASO
%token PREDET
%token<sval> CADENA
%token<car> CARACTER
%token ENTONCES
%token LEER
%token ESCRIBIR
%token SI

/* Precedencia y asociatividad de operadores */
%left ASIG
%left OO
%left YY
%left<sval> EQEQ DIF
%left<sval> GRT SMT GREQ SMEQ
%left<sval> MAS MENOS
%left<sval> PROD DIV MOD
%left NOT
%nonassoc LPAR RPAR  LCOR RCOR
%nonassoc SIX
%nonassoc SINO

/* Tipos */
%type<tval> base tipo tipo_arreglo  tipo_registro declaraciones arg tipo_arg param_arr
%type<args_list> argumentos lista_arg lista_param parametros
%type<eval> expresion arreglo variable
%type<cond> expresion_booleana relacional
%type<sent> sentencias sentencia
%%

/*Estructura de la gramatica, falta agregar todas las reglas semanticas*/
programa: {
		label_c = 0;
		indice = 0;
		temp = 0;
		stackDir = crearStackDir();
		dir = 0;
		id_tipo = 5;
		StackTT = crearTypeStack();
		StackTS = crearSymStack();
		tt_global = crearTypeTab();
		ts_global = crearSymTab();
		insertarTypeTab(StackTT,tt_global);
		insertarSymTab(StackTS,ts_global);
		StackCad = crearStackCad();
	} declaraciones  funciones {
		printPilaSym(StackTS);
		printPilaType(StackTT);
		print_code(&CODE);
	};

declaraciones:
  tipo {tipo_g = $1.tipo;} lista_var  declaraciones
| tipo_registro {tipo_g = $1.tipo;} lista_var declaraciones
| /*epsilon*/ {};

tipo_registro:
  REGISTRO INICIO declaraciones FIN {
	typetab *tt = crearTypeTab();
	symtab *ts = crearSymTab();
	addStackDir(&stackDir,dir);
	dir = 0;
	insertarTypeTab(StackTT,tt);
	insertarSymTab(StackTS,ts);
	dir = popStackDir(&stackDir);
	typetab *tt1 = sacarTypeTab(StackTT);
	symtab *ts1 = sacarSymTab(StackTS);
	dir = popStackDir(&stackDir);
	$$.tipo = insertarTipo(getCimaType(StackTT),crearTipo("registro",0,-1,-1,true,ts1));
	id_tipo++;
	};
tipo:
base {base = $1;} tipo_arreglo {$$ = $3;};

base:
  	ENT {$$.tipo = 1; $$.dim = 4;}
	| REAL {$$.tipo = 2; $$.dim = 8;}
	| DREAL {$$.tipo = 3; $$.dim = 16;}
	| CAR {$$.tipo = 4; $$.dim = 2;}
	| SIN {$$.tipo = 0; $$.dim = 0;}
	;

tipo_arreglo:
  LCOR NUM RCOR tipo_arreglo{
	if($2.tipo == 1 && $2.ival >= 1){
		$$.tipo = insertarTipo(getCimaType(StackTT),crearTipo("array",$4.dim,$4.tipo,$2.ival, false,NULL));
	}
	yyerror("El indice tiene que ser entero y mayor que cero");
	} 
| {
		$$ = base;
	}
	;

lista_var:
  lista_var COMA ID {
	if(buscar(getCimaSym(StackTS),$3) == -1){
		
		symbol *sym = crearSymbol($3, tipo_g, dir, "var");
		insertar(getCimaSym(StackTS),sym);
		dir = dir + getTam(getCimaType(StackTT),tipo_g);
	}else{
		yyerror("el identificador ya fue declarado");
	}
}
| ID {
		if(buscar(getCimaSym(StackTS),$1) == -1){
			symbol *sym = crearSymbol($1, tipo_g, dir, "var");
			insertar(getCimaSym(StackTS),sym);
			dir = dir + getTam(getCimaType(StackTT),tipo_g);
		}else{
			yyerror("el identificador ya fue declarado");
		}

	};

funciones:
  FUNC tipo ID {
	if(buscar(ts_global,$3) != 1 ){
		symbol *sym = crearSymbol($3, tipo_g, -1, "func");
		insertar(ts_global,sym);
		addStackDir(&stackDir,dir);
		FuncType = $2.tipo;
		dir = 0;
	} else{
		yyerror("el identificador ya fue declarado");
	}
} LPAR argumentos{addListParam(getCimaSym(StackTS),$6.lista,$3);} RPAR INICIO  declaraciones {FuncReturn = false;} sentencias FIN funciones {
	{
		insertarSymTab(StackTS,ts_global);
		insertarTypeTab(StackTT,tt_global);
		dir = popStackDir(&stackDir);
		agregar_cuadrupla(&CODE,"label","","",$3);
		label *L = newLabel();
		backpatch(L,$12.lnext);
		char lchar[50];
		label_to_char(lchar,*L);
		agregar_cuadrupla(&CODE,"label","","",lchar);
		sacarSymTab(StackTS);
		sacarTypeTab(StackTT);
		dir = popStackDir(&stackDir);
		if($2.tipo != 0 && FuncReturn == false){
			yyerror("La funcion no tiene valor de retorno");
		}
	}
}
	| /*epsilon*/ {};

argumentos:
  lista_arg { $$.lista = $1.lista; }
| SIN { $$.lista = NULL; };

lista_arg:
  lista_arg arg {
		$$.lista = $1.lista;
		add_tipo($$.lista,$2.tipo);
	}
| arg {
		$$.lista = crearLP();
		add_tipo($$.lista,$1.tipo);
	};

arg:
  tipo_arg ID {
		if(buscar(getCimaSym(StackTS),$2) == -1){
			symbol *sym = crearSymbol($2, base.tipo, dir, "var");
			insertar(getCimaSym(StackTS),sym);
			dir = dir + getTam(getCimaType(StackTT),base.tipo);
		}else{
			yyerror("el identificador ya fue declarado");
		}
	};

tipo_arg:
  base param_arr {
	base.tipo = $1.tipo;
	$$.tipo = $2.tipo;
};

param_arr:
  LCOR RCOR param_arr {
		$$.tipo = insertarTipo(getCimaType(StackTT),crearTipoArray(6,"array",getTipoBase(getCimaType(StackTT),$3.tipo),$3.dim,-1));
	}
| /*epsilon*/ {
		$$.tipo = base.tipo;
		$$.dim = base.dim;
	};

sentencias:
  sentencias sentencia {
	label *L = newLabel();
	if($1.lnext != NULL){
		backpatch(L,$1.lnext);
	}
	$$.lnext = $2.lnext;
	}
| sentencia {$$.lnext = $1.lnext;};

sentencia:
	SI expresion_booleana ENTONCES  sentencias  FIN {
		label *L = newLabel();
		backpatch(L, $2.ltrue);
		$$.lnext = merge($2.lfalse,$4.lnext);
	} %prec SIX
	| SI expresion_booleana  sentencias  SINO  sentencias  FIN {
		label *L = newLabel();
		label *L1 = newLabel();
		backpatch(L, $2.ltrue);
		backpatch(L1, $2.lfalse);
		$$.lnext = merge($3.lnext,$5.lnext);
	}
	| MIENTRAS  expresion_booleana HACER  sentencias  FIN {
		label *L = newLabel();
		label *L1 = newLabel();
		backpatch(L, $4.lnext);
		backpatch(L1, $2.ltrue);
		$$.lnext = $2.lfalse;
		char lchar[50];
		label_to_char(lchar,*L);
		agregar_cuadrupla(&CODE,"goto","","",lchar);
	}
	| HACER  sentencia  MIENTRAS_QUE expresion_booleana {
		label *L = newLabel();
		label *L1 = newLabel();
		backpatch(L, $4.ltrue);
		backpatch(L1, $2.lnext);
		$$.lnext = $4.lfalse;
		char lchar[50];
		label_to_char(lchar,*L);
		agregar_cuadrupla(&CODE,"goto","","",lchar);
	}
	| ID ASIG expresion {
		if(buscar(getCimaSym(StackTS),$1)!=-1){
			int t = getTipo(getCimaSym(StackTS),$1);
			int d = getDir(getCimaSym(StackTS),$1);
			char di[50];
			sprintf(di,"%d",$3.dir);
			char *alfa = reducir(di,$3.tipo,t);
			char res[100];
			sprintf(res,"%s %d","Id",d);
			if(alfa != NULL){
				agregar_cuadrupla(&CODE,"=",alfa,"",res); 
			}else{
				agregar_cuadrupla(&CODE,"=","0","",res);
			}
			$$.lnext = NULL;
		}else{
			yyerror("Variable no declarada");
		}
	}
	| variable ASIG expresion {
		char d[25];
		sprintf(d,"%d",$3.dir);
		char *alfa = reducir(d,$3.tipo,$1.tipo);
		char b[25];
		sprintf(b,"%c",$1.base[$1.dir]);
		agregar_cuadrupla(&CODE,"=",alfa,"",b);
		$$.lnext = NULL;
	}
	| ESCRIBIR expresion {
		char d[100];
		sprintf(d,"%d",$2.dir);
		agregar_cuadrupla(&CODE,"print",d,"","");
		$$.lnext = NULL;
	}
	| LEER variable {
		char d[100];
		sprintf(d,"%d",$2.dir);
		agregar_cuadrupla(&CODE,"scan",d,"",d);
		$$.lnext = NULL;
	}
	| DEVOLVER {
		if ( FuncType == 0 ){
			agregar_cuadrupla(&CODE,"return","","","");
		}else{
			yyerror("La funcion no puede retonar valores");
		}
		$$.lnext = NULL;
	}
	| DEVOLVER expresion {
		if ( FuncType != 0 ){
			char d[10];
			sprintf(d,"%d",$2.dir);
			char *alfa = reducir(d,$2.tipo,FuncType);
			sprintf(d,"%d",$2.dir);
			agregar_cuadrupla(&CODE,"return",d,"","");
			FuncReturn = true;
		}else{
			yyerror("La funcion debe retonar valor no sin");
		}
		$$.lnext = NULL;
	}
	| TERMINAR {
		char *I = newIndex();
		agregar_cuadrupla(&CODE,"goto","","",I);
		$$.lnext = newLabel();
	};

expresion_booleana:
 expresion_booleana OO expresion_booleana { 
	label *L = newLabel();
	backpatch(L, $1.lfalse);
	$$.ltrue = merge($1.ltrue,$3.ltrue);
	$$.lfalse = $3.lfalse;
	char lchar[50];
	label_to_char(lchar,*L);
	agregar_cuadrupla(&CODE,"label","","",lchar);
	}
	|expresion_booleana YY expresion_booleana {
		label *L = newLabel();
		backpatch(L, $1.ltrue);
		$$.ltrue = merge($1.lfalse,$3.lfalse);
		$$.ltrue = $3.ltrue;
		char lchar[50];
		label_to_char(lchar,*L);
		agregar_cuadrupla(&CODE,"label","","",lchar);
	}
	| NOT expresion_booleana {
		$$.ltrue = $2.lfalse;
		$$.lfalse = $2.ltrue;
	}
	| relacional {
		$$.ltrue = $1.ltrue;
		$$.lfalse = $1.lfalse;
	}
	|VERDADERO {
		char* I = newIndex();
		$$.ltrue = NULL;
		$$.ltrue = create_list(atoi(I));
		agregar_cuadrupla(&CODE,"goto","","",I);
		$$.lfalse = NULL;
	}
	| FALSO {
		char* I = newIndex();
		$$.ltrue = NULL;
		$$.lfalse = create_list(atoi(I));
		agregar_cuadrupla(&CODE,"goto","","",I);
	}
	;

relacional:
	relacional GRT relacional { $$ = relacional($1,$3,$2); }
	| relacional SMT relacional { $$ = relacional($1,$3,$2); }
	| relacional GREQ relacional { $$ = relacional($1,$3,$2); }
	| relacional SMEQ relacional { $$ = relacional($1,$3,$2); }
	| relacional DIF relacional { $$ = relacional($1,$3,$2); }
	| relacional EQEQ relacional { $$ = relacional($1,$3,$2); }
	| expresion {
		$$.tipo = $1.tipo;
		$$.dir = $1.dir;
	};

expresion:
  	expresion MAS expresion {$$ = operacion($1,$3,$2);}
	| expresion MENOS expresion {$$ = operacion($1,$3,$2);}
	| expresion PROD expresion {$$ = operacion($1,$3,$2);}
	| expresion DIV expresion {$$ = operacion($1,$3,$2);}
	| expresion MOD expresion {$$ = operacion($1,$3,$2);}
	| LPAR expresion RPAR {$$.dir = $2.dir;$$.tipo=$2.tipo;}
	| variable {
		$$.dir = atoi(newTemp());
		$$.tipo = $1.tipo;
		char d[50];
		sprintf(d,"%d",$$.dir);
		char b[50];
		sprintf(b,"%c",$1.base[$1.dir]);
		agregar_cuadrupla(&CODE, "*",b,"",d);
	}
	| NUM {
		$$.tipo = $1.tipo;
		if($1.tipo == 1)
			$$.dir = $1.ival;
		if($1.tipo == 2)
			$$.dir = $1.fval;
		if($1.tipo == 3)
			$$.dir = $1.dval;
	}
	| CADENA {
		$$.tipo = 7;
		//$$.dir = addStackCad(StackCad,$1);
	}
	| CARACTER {
		$$.tipo = 4;
		//$$.dir = addStackCad(StackCad,$1);
	}
	| ID LPAR parametros RPAR {
		if(buscar(ts_global,$1) != -1){
			if(strcmp(getTipoVar(ts_global,$1), "func")==0){
				listParam *lista = getListParam(ts_global,$1);
				if(getNumListParam(lista) != getNumListParam($3.lista)){
					yyerror("El numero de argumentos no coincide");
				}
				param *p,*pl;
				p = $3.lista->root;
				pl = lista->root;
				for(int i=0; i<getNumListParam($3.lista);i++){
					if(p->tipo != pl->tipo){
						yyerror("El tipo de los parametros no coincide");
					}p = p->next;
					pl = pl->next;
				}
				$$.dir = atoi(newTemp());
				$$.tipo = getTipo(ts_global,$1);
				char *d;
				sprintf(d,"%d",$$.dir);
				agregar_cuadrupla(&CODE,"=","call",$1,d);
			}
		}else{
			yyerror("El identificador no ha sido declarado");
		}
	}
	;

variable:
	ID {
		if(buscar(getCimaSym(StackTS),$1)!=-1){
			$$.dir = getDir(getCimaSym(StackTS),$1);
			$$.tipo = getTipo(getCimaSym(StackTS),$1);
			strcpy($$.base,"");
		}else{
			yyerror("variable ya definida");
		}
	}
	| arreglo {
		$$.dir = $1.dir;
		strcpy($$.base,$1.base);
		$$.tipo = $1.tipo;
	}
	| ID PT ID {
		if(buscar(ts_global,$1)!=-1){
			int t = getTipo(ts_global,$1);
			char *t1 = getNombre(tt_global,t);
			if (strcmp(t1,"registro") == 0 ){
				tipoBase *tb = getTipoBase(tt_global,t);
			}
		}
	};

arreglo:
	ID LCOR expresion RCOR {
		if(buscar(getCimaSym(StackTS),$1) != -1){
			int t = getTipo(getCimaSym(StackTS),$1); 
			if (strcmp(getNombre(getCimaType(StackTT),t),"array") == 0){
				if ($3.tipo == 1){
					strcpy($$.base,$1);
					$$.tipo = getTipoBase(getCimaType(StackTT),t)->t.type;
					$$.tam = getTam(getCimaType(StackTT),$$.tipo);
					$$.dir = atoi(newTemp());
					char tm[10];
					intToChar(tm,$$.tam);
					char dr[10];
					intToChar(dr,$$.dir);
					char dre[10];
					intToChar(dre,$3.dir);
					agregar_cuadrupla(&CODE,"*",dre,tm,dr);
				} else{
					yyerror("La expresion para un indice debe ser entero");
				}
			}else{
				yyerror("El identificador debe ser un arreglo");
			}
		
			}else{
				yyerror("El Identificador no ha sido declarado");
			}
	} 
	| arreglo LCOR expresion RCOR  {
		if(strcmp(getNombre(getCimaType(StackTT),$1.tipo),"array") == 0 ){
			if ($3.tipo == 1){
				strcpy($$.base,$1.base);
				$$.tipo = getTipoBase(getCimaType(StackTT),$1.tipo)->t.type;
				$$.tam = getTam(getCimaType(StackTT),$$.tipo);
				int temp_1 = atoi(newTemp());
				$$.dir = atoi(newTemp());
				char t[10];
				sprintf(t,"%d",temp_1);
				char tm[10];
				sprintf(tm,"%d",$$.tam);
				char d2[10];
				sprintf(d2,"%d",$1.dir);
				agregar_cuadrupla(&CODE,"*",d2,tm,t);
				char d[10];
				sprintf(d,"%d",$$.dir);
				sprintf(d2,"%d",$1.dir);
				agregar_cuadrupla(&CODE,"+",d2,t,d);
			}else{
				yyerror("La expresion para un indice debe ser entero");
			}
		}else{
			yyerror("El arreglo no tiene tantas dimentsiones");
		}
	}
	| {};

parametros:
  lista_param {
		$$.lista = $1.lista;
	}
	| { $$.lista = NULL;
	}
	;

lista_param:
  lista_param COMA expresion {
		$$.lista = $1.lista;
		add_tipo($$.lista,$3.tipo);
		char *d;
		sprintf(d,"%d",$3.dir);
		agregar_cuadrupla(&CODE,"param",d,"","");
	}
	| expresion {
		$$.lista = crearLP();
		add_tipo($$.lista,$1.tipo);
		char *d;
		sprintf(d,"%d",$1.dir);
		agregar_cuadrupla(&CODE,"param",d,"","");
	}
	;

%%


/* Funcion encargada de revisar los tipos, si son correctos toma el de
   mayor rango, e.o.c manda un mensaje de error. 
   void = 0, int = 1, float = 2, double = 3, char = 4, struct = 5*/
int max(int t1, int t2){

	if(t1 == t2) return t1;
	else if (t1 == 1 && t2 == 2) return t1;
	else if (t1 == 2 && t2 == 1) return t2;
	else if (t1 == 1 && t2 == 3) return t1;
	else if (t1 == 3 && t2 == 1) return t2;
	else if (t1 == 1 && t2 == 4) return t1;
	else if (t1 == 4 && t1 == 1) return t2;
	else if (t1 == 3 && t1 == 2) return t1;
	else if (t1 == 2 && t2 == 3) return t2;
	else{ yyerror("Tipos no compatibles"); return -1; }
}

char *ampliar(char *dir, int t1, int t2){
    quad c;
    char *t= (char*) malloc(100*sizeof(char));
    if( t1==t2) {
		return dir;}
    if( t1 ==1 && t2 == 2){
        c.op = "=";
        strcpy(c.arg1, "(float)");
        strcpy(c.arg2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        agregar_cuadrupla(&CODE, c.op,c.arg1,c.arg2,c.res);
        return t;
    }        
    if( t1 ==1 && t2 == 3){
        c.op = "=";
        strcpy(c.arg1, "(double)");
        strcpy(c.arg2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        agregar_cuadrupla(&CODE, c.op,c.arg1,c.arg2,c.res);
        return t;
    }        
    
    if( t1 ==2 && t2 == 3) {
        c.op = "=";
        strcpy(c.arg1, "(double)");
        strcpy(c.arg2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        agregar_cuadrupla(&CODE, c.op,c.arg1,c.arg2,c.res);
        return t;
    }   
    return NULL;         
}

char *reducir(char *dir, int t1, int t2){
    quad c;
    char *t= (char*) malloc(32*sizeof(char));
    if( t1==t2) return dir;
    if( t1 ==1 && t2 == 2){
        c.op = "=";
        strcpy(c.arg1, "(int)");
        strcpy(c.arg2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        agregar_cuadrupla(&CODE, c.op,c.arg1,c.arg2,c.res);
        printf("perdida de información se esta asignando un float a un int En la linea: %d\n",yylineno);
        return t;
    }        
    if( t1 ==1 && t2 == 3){
        c.op = "=";
        strcpy(c.arg1, "(int)");
        strcpy(c.arg2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        agregar_cuadrupla(&CODE, c.op,c.arg1,c.arg2,c.res);
        printf("perdida de información se esta asignando un double a un int En la linea: %d\n",yylineno);
        return t;
    }        
    if( t1 ==2 && t2 == 3) {
        c.op = "=";
        strcpy(c.arg1, "(float)");
        strcpy(c.arg2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        agregar_cuadrupla(&CODE, c.op,c.arg1,c.arg2,c.res);
        printf("perdida de información se esta asignando un double a un float En la linea: %d\n",yylineno);
        return t;
    } 
    return NULL;           
}

char* newTemp(){
	char *temporal= (char*) malloc(32*sizeof(char));
	strcpy(temporal , "t");
	char num[30];
	sprintf(num, "%d", temp);
	strcat(temporal, num);
	temp++;
	return temporal;
}

void intToChar(char* out, int i){
	sprintf(out,"%d",i);
}

/* Funcion encargada de generar el codigo intermedio para una operacion relacional. */
condition relacional(condition e1, condition e2, char* oprel){
	condition c;
	char *I1 = newIndex();
	char *I2 = newIndex();
	c.ltrue = create_list(atoi(I1));
	c.lfalse = create_list(atoi(I2));
	c.tipo = max(e1.tipo,e2.tipo);
	char *d;
	sprintf(d,"%d",e1.dir);
	char *alfa1 = ampliar(d,e1.tipo,c.tipo);
	sprintf(d,"%d",e2.dir);
	char *alfa2 = ampliar(d,e2.tipo,c.tipo);
	agregar_cuadrupla(&CODE,oprel,alfa1,alfa2,I1);
	agregar_cuadrupla(&CODE,"goto","","",I2);
	return c;
}

expresion operacion(expresion e1, expresion e2, char* op){
	expresion e;
	e.tipo = max(e1.tipo,e2.tipo);
	e.dir = atoi(newTemp());
	char d[50];
	sprintf(d,"%d",e1.dir);
	char* alfa1 = ampliar(d,e1.tipo,e.tipo);
	sprintf(d,"%d",e2.dir);
	char* alfa2 = ampliar(d,e2.tipo,e.tipo);
	sprintf(d,"%d",e.dir);
	agregar_cuadrupla(&CODE,op,alfa1,alfa2,d);
}

char* newIndex(){
	char *temporal= (char*) malloc(32*sizeof(char));
	strcpy(temporal , "I");
	char num[30];
	sprintf(num, "%d", indice);
	strcat(temporal, num);
	indice++;
	return temporal;
}

label* newLabel(){
	label *label_new = malloc(sizeof(label));
	label_new->items = malloc(sizeof(int)*100);
	label_c++;
	label_new->i = label_c;
	return label_new;
}


void label_to_char(char* lchar, label l){
	sprintf(lchar,"%s%d","label",l.i);
}


/* Funcion encargada de manejar los errores. */
void yyerror(char *s){
	(void) s;
	fprintf(stderr, "\n****Error: %s. En la linea: %d, token %s\n", s, yylineno, yytext);
}

void print_label(label *l){
	printf("label: %d %d\n",l->i,l->items[0]);
}

/* Funcion principal. */
int main(int argc, char *argv[]){
	yyin = fopen(argv[1], "r");
	yyparse();
	fclose(yyin);
	return 0;
}