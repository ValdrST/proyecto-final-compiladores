%{

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "attribs.h"
	#include "symbols.h"
	#include "types.h"
	#include "intermediate_code.h"

	extern int yylex();
	extern int yyparse();
	extern char *yytext;
	extern FILE *yyin;
	extern FILE *yyout;
	extern int yylineno;

	// Variable que llevara el manejo de direcciones.
	int dir;
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

	void init();
	int busca_main();
	int existe_en_alcance(char*);
	int existe_globalmnete(char*);
	int max(int, int);
	void new_Temp(char*);
	expresion operacion(expresion, expresion, char*);
	expresion numero_entero(int);
	expresion numero_flotante(float);
	expresion numero_doble(double);
	expresion caracter(char);
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
	type tval;
	expresion eval;
	num num;
	args_list args_list;
	condition cond;
	sentence sent;
}

%start programa

%token<sval> ID
%token<num> ENTERO
%token<num> DOBLE
%token<num> FLOTANTE
%token INT
%token FLOAT
%token DOUBLE
%token CHAR
%token VOID
%token LLA
%token LLC
%token COMA
%token PYC
%token DPTS
%token PT
%token FUNCION
%token IF
%token WHILE
%token DO
%token FOR
%token RETURN
%token SWITCH
%token BREAK
%token CASE
%token DEFAULT
%token CADENA
%token CARACTER
%token TRUE
%token FALSE
%token THEN
%token WHAT
%token REGISTRO

/* Presedencia y asociatividad de operadores */
%left ASIG
%left OR
%left AND
%left<sval> EQEQ DIF
%left<sval> GRT SMT GREQ SMEQ
%left<sval> MAS MENOS
%left<sval> PROD DIV MOD
%left NOT
%nonassoc PRA CTA PRC CTC
%left IF
%left ELSE


/* Tipos */
%type<tval> tipo declaraciones C I
%type<sval> R
%type<args_list> argumentos lista_arg
%type<cond> expresion_booleana

%%

/* programa -> declaraciones funciones */
programa: 	{ 
		printf("\nInicializando las pilas....\n");
		printf("Tabla de simbolos global creada...");
		init(); 
	} declaraciones funciones {
		if(busca_main() == -1){
			yyerror("Falta definir funcion principal");
			exit(0);
		}
		print_symbols_table(); 
		print_types_table(); 
		print_code(); 
	}
	;


/* declaraciones -> tipo lista_var declaraciones | registro inicio declaraciones fin epsilon*/
declaraciones: 	tipo lista_var 
	declaraciones { global_tipo = $1.type; global_dim = $1.dim;}
	| REGISTRO INICIO declaraciones FIN declaraciones
	| {}
	;

/* tipo-> base tipo_arreglo 
tipo: base tipo_arreglo
	;

/* base -> ent | real | dreal | car | sin */
base: 	INT { $$.type = 1; $$.dim = 2; }
	| FLOAT { $$.type = 2; $$.dim = 4; }
	| DOUBLE { $$.type = 3; $$.dim = 8; }
	| CHAR { $$.type = 4; $$.dim = 1; }
	| VOID { $$.type = 0; $$.dim = 0; }
	;

/* lista_var -> lista_var, id tipo_arreglo | id C */
lista_var: 	lista_var COMA ID tipo_arreglo { 
		if(existe_en_alcance($3) == -1){
			symbol sym;
			sym.id = $3;
			sym.dir = dir;
			sym.type = $4.type;
			sym.var = "var";
			sym.num_args = 0;
			sym.list_types = malloc(sizeof(int));
			if(scope > 0)
				insert_symbol(sym);
			else 
				insert_global_symbol(sym);
			dir += $4.dim;
		} else{ yyerror("Identificadores duplicados en el mismo alcance"); exit(0); }
	}
	| ID tipo_arreglo {
		if(existe_en_alcance($1) == -1){
			symbol sym;
			sym.id = $1;
			sym.dir = dir;
			sym.type = $2.type;
			sym.var = "var";
			sym.num_args = 0;
			sym.list_types = malloc(sizeof(int));
			if(scope > 0)
				insert_symbol(sym);
			else
				insert_global_symbol(sym);
			dir += $2.dim;
		} else{ yyerror("Identificadores duplicados en el mismo alcance"); exit(0); }
	}
	;

/* tipo_arreglo -> [numero] tipo_arreglo | epsilon */
tipo_arreglo:	CTA ENTERO CTC tipo_arreglo {
		ttype t;
		if($2.type == 1){
			t.type = "array";
			t.dim = $2.ival;
			t.base = $4.type;
			$$.type = insert_type(t);
			$$.dim = $4.dim * $2.ival;
		} else { yyerror("La dimension del arreglo debe ser entera"); exit(0); }
	}
	| {
		if(global_tipo != 0){
			$$.type = global_tipo;
			$$.dim = global_dim;
		} else { yyerror("No se pueden declarar variables de tipo void"); exit(0); }
	}
	;

/* func tipo id (argumentos) { declaraciones S } funciones | epsilon */
funciones:	FUNCION tipo ID {
		num_args = 0;
		list_args = malloc(sizeof(int) * 100);
		create_symbols_table();
		create_types_table();
		scope++;
		dir_aux = dir;
		dir = 0;
	}
	PRA argumentos PRC INICIO declaraciones sentencias FIN {
		if(existe_globalmente($3) == -1){
			//if(strcpm($2.type, $10.return) == 0){
				ttype t;
				char* tipo = malloc(sizeof(char) * 10);
				sprintf(tipo, "%d", $2.type);
				t.type = tipo;
				t.base = -1;
				t.dim = 0;

				symbol sym;
				sym.id = $3;
				sym.dir = -1;
				sym.type = $2.type; // Falta agregar el tipo t.
				sym.var = "fun";
				sym.num_args = $6.total;
				sym.list_types = $6.args;
				insert_global_symbol(sym);
			//} else { yyerror("El valor de retorno no coincide"); exit(0); }
		} else { yyerror("Funcion declarada anteriormente"); exit(0); }
		print_symbols_table_2(SYM_STACK.total, $3);
		scope--;
		dir = dir_aux;
		delete_types_table();
	}
	funciones
	| {}
	;


/* argumentos -> lista_arg | epsilon */
argumentos:	lista_arg { $$ = $1; }
	| { $$.total = 0; }
	;

/* arg -> tipo id I */
arg: tipo {
		global_tipo = $1.type;
		global_dim = $1.dim;
	}
	ID {
		if(existe_en_alcance($2) == -1){
			symbol sym;
			sym.id = $2;
			sym.dir = dir;
			sym.type = $2.type;
			sym.var = "par";
			sym.num_args = 0;
			insert_symbol(sym);
			dir += $2.dim;
			*(list_args + num_args) = $2.type;
			num_args++;
			$$.total = num_args + 1;
			$$.args = list_args;
		} else { yyerror("Parametro duplicado en funcion"); exit(0); }
	}
	;

/* lista_arg -> lista_arg | arg */
lista_arg:	lista_arg arg 
		| arg
	;


/* sentencias->sentencia sentencia | sentencias */
sentencias: sentencia sentencia
			| sentencia
			;
/* sentencia -> si ( expresion_booleana ) entonces sentencias | if ( expresion_booleana ) S else S | while ( B ) S | do S while ( B ) ; | for ( S ; B ; S ) S | U = E ; | return E ; | return ; | { S } | switch ( E ) { J K } | break ; | print E ; */
sentencia: 	IF expresion_booleana sentencias THEN sentencias FIN
	| IF expresion_booleana sentencias ELSE sentencias FIN
	| WHILE expresion_booleana sentencias FIN
	| DO sentencias WHILE WHAT expresion_booleana FIN
	| U ASIG expresion 
	| WRITE expresion
	| READ expresion
	| RETURN expresion 
	| RETURN 
	| SWITCH PRA expresion PRC casos predeterminado FIN
	| BREAK
	;

/* casos -> case : numero S J | epsilon */
casos:	CASE ENTERO DPTS sentencias 
	| CASE ENTERO DPTS sentencias
	;

/* predeterminado -> predet : setencias | epsilon */
predeterminado:	DEFAULT DPTS setencias
	;

/* variable -> id parte_arreglo | id . id */
variable:	ID parte_arreglo{
		if(existe_globalmente($1) == -1){
			yyerror("Variable no declarada");
			exit(0);
		}	
	}
	| ID PT ID {
		if(existe_globalmente($1) != -1){
			int t = get_type($1);
			if(t == 1 || t == 2 || t == 3 || t ==4){
				yyerror("La variable no es una estructura");
				exit(0);
			}
		} else {
			yyerror("Variable no declarada");
			exit(0);
		}
	}
	;

/* parte_arreglo -> [ expresion ] parte_arreglo | epsilon */
parte_arreglo:	CTA expresion CTC parte_arreglo
	;

/* expresion -> expresion + expresion |
	expresion - expresion | 
	expresion * expresion |
	expresion / expresion | 
	expresion % expresion |
	( expresion ) |
	variable |
	num | cadena | caracter |
	id (parametros)

	 U | cadena | numero | caracter | id ( H ) */
expresion:	expresion MAS expresion
	| expresion MENOS expresion
	| expresion PROD expresion
	| expresion DIV expresion
	| expresion MOD expresion
	| PRA expresion PRC
	| variable
	| ENTERO 
	| CADENA 
	| CARACTER 
	| ID PRA parametros PRC 
	;

/* lista_param -> lista_param , expresion | expresion */
lista_param:	lista_param COMA expresion
	| expresion
	;

/* expresion_booleana -> expresion_booleana oo expresion_booleana |
	expresion_booleana yy expresion_booleana | 
	no expresion_booleana | 
	relacional | 
	verdadero | 
	falso */
expresion_booleana: expresion_booleana OR expresion_booleana { $$ = or($1, $3); }
	| expresion_booleana AND expresion_booleana { $$ = and($1, $3); }
	| NOT expresion_booleana {}
	| relacional {}
	| TRUE {}
	| FALSE {}
	;

/* relacional -> < | > | >= | <= | == | <> */
relacional:	SMT { $$ = $1; }
	| GRT { $$ = $1; }
	| GREQ { $$ = $1; }
	| SMEQ { $$ = $1; }
	| EQEQ { $$ = $1; }
	| DIF { $$ = $1; }
	| relacional
	;

%%

/* Funcion encargada de iniciar las variables, la tabla de simbolos,  
   la pila de simbolos y la pila de tipos. */
void init(){
	dir = 0;
	temporales = 0;
	num_args = 0;
	scope = 0;
	list_args = malloc(sizeof(int) * 100);
	init_symbols();
	init_types();
}

/* Funcion encargada de buscar que exista la funcion principal. */
int busca_main(){
	return search_global("main");
}

/* Funcion encarda de decirnos si un identificador ya fue declarado en
   el mismo alcance. */
int existe_en_alcance(char* id){
	return search_scope(id);
}

/* Funcion encargada de decirnos si un identificador ya fue declarado globalmente. */
int existe_globalmente(char* id){
	return search_global(id);
}

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

/* Funcion encargada de generar una nueva variable temporal. */
void new_Temp(char* dir){
	char* temp;
	char* num;
	strcpy(temp, "t");
	sprintf(num, "%d", temporales);
	temporales++;
	strcat(temp, num);
	strcpy(dir, temp);
}

/* Funcion encargada de generar el codigo para las operaciones de expresiones. */
expresion operacion(expresion e1, expresion e2, char* op){
	expresion new_exp;
	new_exp.type = max(e1.type, e2.type);
	new_Temp(new_exp.dir);
	siginst = gen_code(op, e1.dir, e2.dir, new_exp.dir);
	if(e1.first != -1)
		new_exp.first = e1.first;
	else{
		if(e2.first != -1)
			new_exp.first = e2.first;
		else
			new_exp.first = siginst;
	}
	return new_exp;
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