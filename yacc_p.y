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
	char* label_to_char(label l);
	void intToChar(char* out, int i); 
	expresion operacion(expresion, expresion, char*);
	expresion numero_entero(int);
	expresion numero_flotante(float);
	expresion numero_doble(double);
	expresion funcion_e(char* f);
	expresion caracter(char);
	expresion variable_v(char* c);
	expresion cadena_s(char* c);
	condition relacional(condition e1, condition e2, char* oprel);
	condition and(condition, condition);
	condition or(condition, condition);

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
%token DCOR
%token LCOR
%token SI
%token SL


/* Precedencia y asociatividad de operadores */
%left ASIG
%left OO
%left YY
%left<sval> EQEQ DIF
%left<sval> GRT SMT GREQ SMEQ
%left<sval> MAS MENOS
%left<sval> PROD DIV MOD
%left NOT
%nonassoc PRA LCOR PRC DCOR CTA CTC
%nonassoc SIX
%nonassoc SINO

%%

/* programa -> declaraciones funciones */
programa: declaraciones SL 
funciones {printf("P->D \n F");}
	;


/* declaraciones -> tipo lista_var \n declaraciones 
	| tipo_registro lista_var declaraciones | epsilon */
declaraciones: tipo lista_var SL declaraciones  {printf("D->T L_V \n D\n");}
	| tipo_registro lista_var SL declaraciones  {printf("D->T_R L_V \n D\n");}
	|  {printf("D->epsilon\n");}
	;

/* tipo_registro -> registro inicio declaraciones fin */
tipo_registro: REGISTRO SL INICIO declaraciones SL FIN {printf("T_R->REGISTRO \n INICIO D \n FIN\n");};
	

tipo: base tipo_arreglo {printf("B->T_A\n");};

base: SIN  {printf("B->SIN\n");}
	| ENT {printf("B->ENT\n");}
	| REAL {printf("B->REAL\n");}
	| DREAL {printf("B->DREAL\n");}
	| CAR {printf("B->CAR\n");}
    ;


/* tipo_arreglo -> [num] tipo_arreglo | epsilon */
tipo_arreglo: LCOR NUM DCOR tipo_arreglo {printf("T_A->[NUM] T_A\n");}
	| {printf("T_A->epsilon\n");}
	;

/* lista_var -> lista_var, id tipo_arreglo | id tipo_arreglo */
lista_var: 	lista_var COMA ID {printf("L_V->L_V, ID\n");}
	| ID {printf("L_V->ID\n");}
	;


funciones: FUNC tipo ID PRA argumentos PRC SL
 INICIO declaraciones sentencias SL
  FIN SL
    funciones{printf("F->T ID (A) \n INICIO D Ss \n FIN \n F \n");} | {}
	;

argumentos:	lista_arg {printf("A->L_A\n");}
	| SIN {printf("A->SIN\n");}
	;

/* lista_arg -> lista_arg arg | arg */
lista_arg:	lista_arg arg {printf("L_A->L_A Ar\n");}
	| arg {printf("L_A->Ar\n");}
	;

/* arg -> tipo_arg id  */
arg: tipo_arg ID {printf("Ar->T_A ID\n");}
	;

/* tipo_arg -> base param_arr | epsilon */
tipo_arg: base param_arr {printf("T_A->B P_A\n");}

/* param_arr -> [] param_arr | epsilon */
param_arr: LCOR DCOR param_arr {printf("P_A->[] P_A\n");}
	| {printf("P_A->epsilon\n");}


/* sentencias->sentencias sentencia | sentencias */
sentencias: sentencias SL sentencia {printf("Ss->Ss \n S\n");}
	| sentencia {printf("Ss->S\n");}
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
sentencia: 	SI expresion_booleana sentencias ENTONCES SL sentencias SL FIN {printf("S->SI E_B Ss ENTONCES \n Ss \n FIN\n");} %prec SIX
	| SI expresion_booleana sentencias SL SINO sentencias SL FIN {printf("S->SI E_B Ss \n SINO Ss \n FIN\n");}
	| MIENTRAS SL expresion_booleana HACER SL sentencias SL FIN {printf("S->MIENTRAS \n E_B HACER \n Ss \n FIN\n");}
	| HACER SL sentencias SL MIENTRAS_QUE expresion_booleana {printf("S->HACER \n Ss \n MIENTRAS QUE E_B\n");}
	| ID ASIG expresion {printf("S->ID := E \n");}
	| variable ASIG expresion {printf("S->V := E\n");}
	| ESCRIBIR expresion {printf("S->ESCRIBIR E\n");}
	| LEER variable {printf("S->LEER V\n");}
	| DEVOLVER {printf("S->DEVOLVER\n");}
	| DEVOLVER expresion {printf("S->DEVOLVER E\n");}
	| TERMINAR {printf("S->TERMINAR\n");}
	;

/* expresion_booleana->expresion_booleana||expresion_booleana|expresion_booleana&&expresion_booleana| !expresion_booleana| (expresion_booleana) | expresion R expresion | true | false */
expresion_booleana: expresion_booleana OO expresion_booleana {printf("E_B->E_B OO E_B\n");}
	|expresion_booleana YY expresion_booleana {printf("E_B->E_B YY E_B\n");}
	| NOT expresion_booleana {printf("E_B->NOT E_B\n");}
	| relacional {printf("E_B->R\n");}
	| VERDADERO {printf("E_B->VERDADERO\n");}
	| FALSO {printf("E_B->FALSO\n");}
	;


/* R -> < | > | >= | <= | != | == */
relacional:	relacional SMT relacional {printf("R->R < R\n");}
	| relacional GRT relacional {printf("R->R > R\n");}
	| relacional GREQ relacional {printf("R->R >= R\n");}
	| relacional SMEQ relacional {printf("R->R <= R\n");}
	| relacional EQEQ relacional {printf("R->R == R\n");}
	| relacional DIF relacional {printf("R->R <> R\n");}
	| expresion {printf("R->E\n");}
	;


/* expresion -> expresion + expresion | 
expresion - expresion | 
expresion * expresion | 
expresion / expresion | 
expresion % expresion | (expresion) 
variable | num | cadena  | caracter | id ( parametros ) */

expresion: expresion MAS expresion {printf("E-> E + E\n");}
	| expresion MENOS expresion {printf("E-> E - E\n");}
	| expresion PROD expresion {printf("E-> E * E\n");}
	| expresion DIV expresion {printf("E-> E / E\n");}
	| expresion MOD expresion {printf("E-> E % E\n");}
	| PRA expresion PRC {printf("E->(E)\n");}
	| variable {printf("E-> V\n");}
	| NUM {printf("E-> NUM\n");}
	| CADENA {printf("E-> CADENA\n");}
	| CARACTER {printf("E-> CARACTER\n");}
	| ID PRA parametros PRC {printf("E-> I(P)\n");}
	;

/* variable -> id | parte_arreglo | id . id */
variable: arreglo {printf("V->A\n");}
	| ID PT ID {printf("V-> ID.ID\n");}
	;


/* parte_arreglo -> id [ expresion ] arreglo | epsilon */
arreglo: ID LCOR expresion DCOR {printf("Arr-> ID [E]\n");} 
	| arreglo LCOR expresion DCOR  {printf("Arr-> Arr [E]\n");}
	;

/*parametros -> lista_param | epsilon*/
parametros: lista_param {printf("P-> L_P\n");}
	| {{printf("P-> epsilon\n");}}
	;

/* lista_param -> lista_param, expresion | expresion */
lista_param: lista_param COMA expresion {{printf("L_P-> L_P, E\n");}}
	| expresion {{printf("L_P-> E\n");}}
	;

%%

/* Funcion encargada de manejar los errores. */
void yyerror(char *s){
	(void) s;
	fprintf(stderr, "\n****Error: %s. En la linea: %d, token %s\n", s, yylineno, yytext);
}

/* Funcion principal. */
int main(int argc, char *argv[]){
	yyin = fopen(argv[1], "r");
	yyparse();
	fclose(yyin);
	return 0;
}