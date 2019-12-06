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

	stack_dir stackDir;
	int tipo_g; 
	symstack *StackTS;
	stack_cad StackCad;
	typestack *StackTT;
	ttype base;
	typetab *tt_global;
	symtab *ts_global;
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

	int max(int, int);
	void new_Temp(char*);
	expresion operacion(expresion, expresion, char*);
	expresion numero_entero(int);
	expresion numero_flotante(float);
	expresion numero_doble(double);
	expresion funcion_e(char* f);
	expresion caracter(char);
	expresion variable_v(char* c);
	expresion cadena_s(char* c);
	condition relacional(expresion, expresion, char*);
	condition and(condition, condition);
	condition or(condition, condition);

	expresion identificador(char *s);
	void newLabel(char *s);

	void yyerror(char*);

%}

%union{
	int line;
	char* sval;
	ttype tval;
	expresion eval;
	num num;
	car car;
	args_list args_list;
	condition cond;
	sentence sent;
}

%start programa

%token<sval> ID
%token<num> NUM
%token ENT
%token REAL
%token CAR
%token DREAL
%token SIN
%token REGISTRO
%token LLA
%token LLC
%token COMA
%token DPTS
%token PT
%token FUNC
%token SI
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
%token TRUE
%token FALSE
%token ENTONCES
%token WHAT
%token LEER
%token ESCRIBIR
%token DCOR
%token LCOR

/* Presedencia y asociatividad de operadores */
%left ASIG
%left OO
%left YY
%left<sval> EQEQ DIF
%left<sval> GRT SMT GREQ SMEQ
%left<sval> MAS MENOS
%left<sval> PROD DIV MOD
%left NOT
%nonassoc PRA CTA PRC CTC INICIO FIN
%left SI
%left SINO

/* Tipos */
%type<tval> base tipo tipo_arreglo tipo_registro declaraciones
%type<sval> variable
%type<args_list> argumentos lista_arg lista_param
%type<eval> expresion
%type<cond> expresion_booleana relacional
%type<sent> sentencias sentencia
%%

/* programa -> declaraciones funciones */
programa:{ 
		stackDir = crearStackDir();
		dir = 0;
		StackTT = crearTypeStack();
		StackTS = crearSymStack();
		typetab *tt = crearTypeTab();
		symtab *ts = crearSymTab();
		insertarTypeTab(StackTT,tt);
		insertarSymTab(StackTS,ts);
		StackCad = crearStackCad();
	} declaraciones funciones {
		//print_symbols_table(); 
		//print_types_table(); 
		//print_code();
	}
	;


/* declaraciones -> tipo lista_var declaraciones 
	| tipo_registro lista_var declaraciones | epsilon */
declaraciones: tipo  lista_var declaraciones {tipo_g = $1.tipo;}
	| tipo_registro  lista_var declaraciones {tipo_g = $1.tipo;}
	| {}
	;

/* tipo_registro -> registro inicio declaraciones fin */
tipo_registro: REGISTRO INICIO declaraciones FIN{
	typetab *tt = crearTypeTab();
	symtab *ts = crearSymTab();
	addStackDir(&stackDir,dir);
	dir = 0;
	insertarTypeTab(StackTT,tt);
	insertarSymTab(StackTS,ts);
	dir = popStackDir(&stackDir);
	typetab *tt1 = sacarTypeTab(StackTT);
	//setTT(getCimaSym(StackTS),tt1);
	symtab *ts1 = sacarSymTab(StackTS);
	dir = popStackDir(&stackDir);
	$$.tipo = insertarTipo(getCimaType(StackTT),crearTipoNativo(0,"registro",crearArqueTipo(true,crearTipoStruct(ts1)),-1));};

tipo: base tipo_arreglo{
	base = $1;
	$$ = $2;
};


/* tipo -> int | float | double | char | void | REGISTRO INICIO declaraciones FIN */
base: ENT {$$.tipo = 1; $$.dim = 4;}
	| REAL {$$.tipo = 2; $$.dim = 8;}
	| DREAL {$$.tipo = 3; $$.dim = 16;}
	| CAR {$$.tipo = 4; $$.dim = 2;}
	| SIN {$$.tipo = 0; $$.dim = 0;}


/* tipo_arreglo -> [num] tipo_arreglo | epsilon */
tipo_arreglo:	CTA NUM CTC tipo_arreglo {
	if($2.tipo == 1 && $2.ival > 0){
		$$.tipo =  insertarTipo(getCimaType(StackTT),crearTipoArray(6,"array",getTipoBase(getCimaType(StackTT),tipo_g),base.dim,$2.ival));
	}
	yyerror("El indice tiene que ser entero y mayor que cero\n");
}
	| {
		$$ = base;
	}
	;

/* lista_var -> lista_var, id tipo_arreglo | id tipo_arreglo */
lista_var: 	lista_var COMA ID {
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

	}
	;


/* func tipo id (argumentos) { declaraciones S } funciones | epsilon */
funciones: FUNC tipo ID PRA argumentos PRC INICIO 
	declaraciones sentencias 
	FIN {
		if(buscar(getFondoSym(StackTS),$3) != 1 ){

		}
	}
	funciones | {}
	;

/* A -> G | epsilon */
argumentos:	lista_arg { $$ = $1; }
	| SIN { $$.total = 0; }
	;

/* lista_arg -> lista_arg arg | arg */
lista_arg:	lista_arg arg
	| arg
	;

/* arg -> tipo_arg id  */
arg: tipo_arg ID
	;

/* tipo_arg -> base param_arr | epsilon */
tipo_arg: base param_arr | {}


/* param_arr -> [] param_arr | epsilon */
param_arr: LCOR DCOR param_arr | {}


/* sentencias->sentencias sentencia | sentencias */
sentencias: sentencias sentencia {$$ = $1;}
			| sentencia {$$ = $1;}
			;

/* sentencia→si expresion_booleana entonces
	sentencia fin | 
	si expresion_booleana
	sentencias 
	sino
	sentencias
	fin|
	mientras expresion_booleana hacer
	sentencias
	fin|
	hacer
	sentencia
	mientras que expresion_booleana |
	id :=expresion | escribir expresion|leer variable|devolver|devolver expresion|
	segun (expresion)
	casos predeterminado
	fin|terminar */
sentencia: 	SI expresion_booleana sentencias ENTONCES sentencias FIN
	| SI expresion_booleana sentencias SINO sentencias FIN
	| MIENTRAS expresion_booleana HACER sentencias FIN
	| HACER sentencias MIENTRAS_QUE expresion_booleana
	| ID ASIG expresion 
	| ESCRIBIR expresion
	| LEER variable
	| DEVOLVER
	| DEVOLVER expresion 
	| TERMINAR
	;

/* expresion_booleana->expresion_booleana||expresion_booleana|expresion_booleana&&expresion_booleana| !expresion_booleana| (expresion_booleana) | expresion R expresion | true | false */
expresion_booleana: expresion_booleana OO expresion_booleana { $$ = or($1, $3); }
	|expresion_booleana YY expresion_booleana { $$ = and($1, $3); }
	| NOT expresion_booleana {}
	| relacional {}
	| TRUE {}
	| FALSE {}
	;


/* R -> < | > | >= | <= | != | == */
relacional:	relacional SMT relacional { $$ = $1; }
	| relacional GRT relacional { $$ = $1; }
	| relacional GREQ relacional { $$ = $1; }
	| relacional SMEQ relacional { $$ = $1; }
	| relacional EQEQ relacional { $$ = $1; }
	| relacional DIF relacional { $$ = $1; }
	| expresion {}
	;


/* expresion -> expresion + expresion | 
expresion - expresion | 
expresion * expresion | 
expresion / expresion | 
expresion % expresion | (expresion) 
variable | num | cadena  | caracter | id ( parametros ) */

expresion: expresion MAS expresion
	| expresion MENOS expresion 
	| expresion PROD expresion 
	| expresion DIV expresion 
	| expresion MOD expresion 
	| PRA expresion PRC
	| variable
	| NUM
	| CADENA 
	| CARACTER 
	| ID PRA parametros PRC
	;

/* variable -> id | parte_arreglo | id . id */
variable: ID arreglo
	| ID PT ID 
	;


/* parte_arreglo -> id [ expresion ] arreglo | epsilon */
arreglo: ID LCOR expresion DCOR arreglo  
	| {}
	;

/*parametros -> lista_param | epsilon*/
parametros: lista_param 
	|
	;

/* lista_param -> lista_param, expresion | expresion */
lista_param:	lista_param COMA expresion {
	*(list_args + num_args) = $3.type;
	num_args++;
	}
	| expresion {
		*(list_args + num_args) = $1.type;
		num_args++;
		$$.total = num_args + 1;
		$$.args = list_args;
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

/* Funcion encargada de tomar un numero entero y guardarlo como expresion. */
expresion numero_entero(int num){
	expresion new_exp;
	sprintf(new_exp.dir, "%d", num);
	new_exp.type = 1;
	new_exp.first = -1;
	return new_exp;
}

/* Funcion encargada de tomar un numero flotante y guardarlo como expresion. */
expresion numero_flotante(float num){
	expresion new_exp;
	sprintf(new_exp.dir, "%.3f", num);
	new_exp.type = 2;
	new_exp.first = -1;
	return new_exp;
}

/* Funcion encargada de tomar un numero doble y guardarlo como expresion. */
expresion numero_doble(double num){
	expresion new_exp;
	sprintf(new_exp.dir, "%.3f", num);
	new_exp.type = 3;
	new_exp.first = -1;
	return new_exp;
}

/* Funcion encargada de tomar un caracter y guardarlo como expresion. */
expresion caracter(char c){
	expresion new_exp;
	sprintf(new_exp.dir, "%c", c);
	new_exp.type = 4;
	new_exp.first = -1;
	return new_exp;
}

/* Funcion encargada de generar el codigo intermedio para una operacion relacional. */
condition relacional(expresion e1, expresion e2, char* oprel){
	condition c;
	char* arg1 = malloc(sizeof(char) * 50);
	sprintf(arg1, "%s %s %s", e1.dir, oprel, e2.dir);
	siginst = gen_code("if", arg1, "goto", "");
	c.ltrue = create_list(siginst);
	siginst = gen_code("goto", "", "", "");
	c.lfalse = create_list(siginst);
	if(e1.first != -1)
		c.first = e1.first;
	else if(e2.first != -1)
		c.first = e2.first;
	else
		c.first = siginst - 1;
	return c;
}

/* Funcion encargada de tomar un operacion OR y guardarla como condicion. */
condition or(condition c1, condition c2){
	condition c;
	backpatch(c1.lfalse, c2.first);
	c.ltrue = merge(c1.ltrue, c2.ltrue);
	c.lfalse = c2.lfalse;
	return c;
}

/* Funcion encargada de tomar un operacion AND y guardarla como condicion. */
condition and(condition c1, condition c2){
    condition c;
    backpatch(c1.ltrue, c2.first);
    c.ltrue= c2.ltrue;
    c.lfalse = merge(c1.lfalse,c2.lfalse);
    return c;
}

/* Funcion encargada de manejar los errores. */
void yyerror(char *s){
	(void) s;
	fprintf(stderr, "\n****Error: %s. En la linea: %d\n", s, yylineno);
}

/* Funcion principal. */
int main(int argc, char *argv[]){
	yyin = fopen(argv[1], "r");
	yyparse();
	fclose(yyin);
	return 0;
}