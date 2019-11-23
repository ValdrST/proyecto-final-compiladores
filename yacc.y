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
	type tval;
	expresion eval;
	num num;
	char car;
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
%token STRUCT
%token LLA
%token LLC
%token COMA
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
%token PRINT
%token CASE
%token DEFAULT
%token<sval> CADENA
%token<car> CARACTER
%token TRUE
%token FALSE
%token THEN
%token WHAT
%token REGISTRO
%token READ
%token WRITE

/* Presedencia y asociatividad de operadores */
%left ASIG
%left OR
%left AND
%left<sval> EQEQ DIF
%left<sval> GRT SMT GREQ SMEQ
%left<sval> MAS MENOS
%left<sval> PROD DIV MOD
%left NOT
%nonassoc PRA CTA PRC CTC INICIO FIN
%left IF
%left ELSE

/* Tipos */
%type<tval> tipo tipo_arreglo I
%type<sval> variable
%type<args_list> argumentos lista_arg lista_param
%type<eval> expresion
%type<cond> expresion_booleana relacional
%type<sent> sentencias sentencia
%%

/* programa -> declaraciones funciones */
programa: { 
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


/* declaraciones -> tipo lista_var declaraciones | epsilon*/
declaraciones: 	tipo { global_tipo = $1.type; global_dim = $1.dim; } lista_var declaraciones
	| {}
	;

/* tipo -> int | float | double | char | void | REGISTRO INICIO declaraciones FIN */
tipo: INT { $$.type = 1; $$.dim = 2; }
	| FLOAT { $$.type = 2; $$.dim = 4; }
	| DOUBLE { $$.type = 3; $$.dim = 8; }
	| CHAR { $$.type = 4; $$.dim = 1; }
	| VOID { $$.type = 0; $$.dim = 0; }
	| REGISTRO {
		create_symbols_table();
		create_types_table();
		dir_aux = dir;
		dir = 0;
		scope++;
		has_reg = 1;
	}  INICIO declaraciones FIN { 
		ttype t;
		t.type = "registro";
		t.dim = 0;
		t.base = -1;
		$$.type = insert_type_global(t);
		$$.dim = dir;
		print_symbols_table_2(SYM_STACK.total, "struct");
		scope--;
		dir = dir_aux;
		delete_types_table();
	}
	;

/* lista_var -> lista_var, id tipo_arreglo | id tipo_arreglo */
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
funciones: FUNCION tipo ID {
		num_args = 0;
		list_args = malloc(sizeof(int) * 100);
		create_symbols_table();
		create_types_table();
		scope++;
		dir_aux = dir;
		dir = 0;
		has_reg = 0;
		if($2.type == 0){
			yyerror("No se pueden declarar variables sin dentro de funciones"); exit(0);
		}
	}
	PRA argumentos PRC INICIO declaraciones sentencias FIN {
		if(existe_globalmente($3) == -1){
			if(has_reg == 1){
				yyerror("No se pueden declarar registros dentro de funciones"); exit(0);
			}
			if($2.type != 1 && $2.type != 2 && $2.type != 3 && $2.type != 4 && $2.type != 0){
				yyerror("Las funciones no pueden devolver registros"); exit(0);
			}
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
				sym.type = $2.type;
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

/* A -> G | epsilon */
argumentos:	lista_arg { $$ = $1; }
	| { $$.total = 0; }
	;

/* G -> G , T id I | T id I */
lista_arg:	lista_arg COMA tipo {
		global_tipo = $3.type;
		global_dim = $3.dim;
	}
	ID I {
		if(existe_en_alcance($5) == -1){
			symbol sym;
			sym.id = $5;
			sym.dir = dir;
			sym.type = $6.type;
			sym.var = "par";
			sym.num_args = 0;
			insert_symbol(sym);
			dir += $6.dim;
			*(list_args + num_args) = $6.type;
			num_args++;
		} else { yyerror("Parametro duplicado en funcion"); exit(0); }
	}
	| tipo {
		global_tipo = $1.type;
		global_dim = $1.dim;
	}
	ID I {
		if(existe_en_alcance($3) == -1){
			symbol sym;
			sym.id = $3;
			sym.dir = dir;
			sym.type = $4.type;
			sym.var = "par";
			sym.num_args = 0;
			insert_symbol(sym);
			dir += $4.dim;
			*(list_args + num_args) = $4.type;
			num_args++;
			$$.total = num_args + 1;
			$$.args = list_args;
		} else { yyerror("Parametro duplicado en funcion"); exit(0); }
	}
	;

/* I -> [] I | epsilon */
I:	CTA CTC I {
		ttype t;
		t.type = "array";
		t.dim = $3.dim;
		t.base = $3.type;
		$$.type = insert_type(t);
		$$.dim = $3.dim;
	}
	| {
		if(global_tipo != 0){
			$$.type = global_tipo;
			$$.dim = global_dim;
		} else { yyerror("No se pueden declarar variables de tipo void"); exit(0); }
	}
	;

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
sentencia: 	IF expresion_booleana sentencias THEN sentencias FIN
	| IF expresion_booleana sentencias ELSE sentencias FIN
	| WHILE expresion_booleana sentencias FIN
	| DO sentencias WHILE WHAT expresion_booleana FIN
	| variable ASIG expresion 
	| WRITE expresion
	| READ expresion 
	| RETURN expresion 
	| RETURN
	| SWITCH PRA expresion PRC casos predeterminado FIN
	| BREAK
	;
/* casos -> case : numero S J | epsilon */
casos:	CASE ENTERO DPTS ENTERO sentencias
	|	casos CASE ENTERO DPTS sentencias
	;

/* predeterminado -> predet : setencias | epsilon */
predeterminado:	DEFAULT DPTS sentencias |
	;


/* variable -> id | parte_arreglo | id . id */
variable: ID {
		if(existe_globalmente($1) == -1){
			yyerror("Variable no declarada");
			exit(0);
			$$ = $1;
		}	
	}
	| parte_arreglo
	| ID PT ID {
		if(existe_globalmente($1) != -1){
			int t = get_type($1);
			if(t == 1 || t == 2 || t == 3 || t ==4){
				yyerror("La variable no es un registro");
				exit(0);
			}
			$$ = $1;
		} else {
			yyerror("Variable no declarada");
			exit(0);
		}
	}
	;

/* parte_arreglo -> id [ expresion ] | parte_arreglo [ expresion ] */
parte_arreglo:	ID CTA expresion CTC {
		if(existe_globalmente($1) != -1){
			int t = get_type($1);
			if(t == 1 || t == 2 || t == 3 || t ==4){
				yyerror("La variable no es un arreglo");
				exit(0);
			}
		} else {
			yyerror("Variable no declarada");
			exit(0);
		}
	}
	| parte_arreglo CTA expresion CTC
	;

/* expresion -> expresion + expresion | expresion - expresion | expresion * expresion | expresion / expresion | expresion % expresion | U | cadena | numero | caracter | id ( H ) */
expresion:	expresion MAS expresion {$$ = operacion($1,$3,"+");}
	| expresion MENOS expresion {$$ = operacion($1,$3,"-");}
	| expresion PROD expresion {$$ = operacion($1,$3,"*");}
	| expresion DIV expresion {$$ = operacion($1,$3,"/");}
	| expresion MOD expresion {$$ = operacion($1,$3,"%");}
	| variable {$$ = variable_v($1);}
	| CADENA {$$ = cadena_s($1);}
	| ENTERO {$$ = numero_entero($1.ival);}
	| DOBLE {$$ = numero_doble($1.dval);}
	| FLOTANTE {$$ = numero_flotante($1.fval);}
	| CARACTER {$$ = caracter($1);}
	| ID PRA lista_param PRC {
		if(existe_globalmente($1)){
			if(strcmp(get_var($1),"fun") == 0){
				int *list_args_f = get_list_type($1);
				num_args = 0;
				list_args = malloc(sizeof(int) * 100);
				if(get_num_args($1) == $3.total){
				for(int i=0;i<$3.total;i++){
					if($3.args[i] != list_args_f[i]){
						yyerror("El tipo de argumento no coincide");
						exit(0);
					}
					$$ = funcion_e($1);
				}
				}else{
					yyerror("El numero de argumentos no coincide con el de la funcion");
					exit(0);
				}
			}else{
				yyerror("No es una funcion");
				exit(0);
			}
		}else{
			yyerror("Funcion no declarada");
			exit(0);
		}
	}
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

/* expresion_booleana->expresion_booleana||expresion_booleana|expresion_booleana&&expresion_booleana| !expresion_booleana| (expresion_booleana) | expresion R expresion | true | false */
expresion_booleana: expresion_booleana OR expresion_booleana { $$ = or($1, $3); }
	|expresion_booleana AND expresion_booleana { $$ = and($1, $3); }
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
	| expresion
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
	printf("Nueva variable temporar\n");
	/* temporales++;
	temp_var = realloc(temp_var,temporales*sizeof(expresion));
	(temp_var+temporales-1)->dir = malloc(sizeof(char)*strlen(dir));
	strcpy(temp_var->dir,dir);*/
	/*
	char* temp = (*char)malloc(sizeof(char)*100);
	char* num =  (*char)malloc(sizeof(char)*100);
	strcpy(temp, "t");
	sprintf(num, "%d", temporales);
	temporales++;
	strcat(temp, num);
	strcpy(dir, temp);*/
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

expresion funcion_e(char* f){
	expresion new_exp;
	sprintf(new_exp.dir, "%d", get_dir(f));
	new_exp.type = get_type(f);
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

/* Funcion de guardar cadenas */
expresion cadena_s(char* c){
	ttype t;
	expresion new_exp;
	sprintf(new_exp.dir, "%s", c);
	t.type = "cad";
	t.dim = strlen(c);
	t.base = 4;
	new_exp.type = insert_type(t);;
	new_exp.first = -1;
	return new_exp;
}

/* Funcion para guardar variables */
expresion variable_v(char* c){
	expresion new_exp;
	sprintf(new_exp.dir, "%d", get_dir(c));
	new_exp.type =  get_type(c);
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