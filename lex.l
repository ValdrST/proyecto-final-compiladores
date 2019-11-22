%{

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "yacc.tab.h"

%}

%option noyywrap
%option yylineno

id [a-zA-Z][a-zA-Z0-9_]*
int	[0-9]+
double [0-9]+("."[0-9]+)?
float [0-9]+("."[0-9]+)?[fF]
char '[^\']'
cadena \"[^\"]*\"

%x com1
%x com2


%%

{int}				{ yylval.line = yylineno; yylval.num.ival = atoi(yytext); yylval.num.type = 1; return ENTERO; }

{double}			{ yylval.line = yylineno; yylval.num.dval = atof(yytext); yylval.num.type = 3; return DOBLE; }

{float}				{ yylval.line = yylineno; yylval.num.fval = atof(yytext); yylval.num.type = 2; return FLOTANTE; }

{char}				{ yylval.line = yylineno; return CARACTER; }

{cadena}			{ yylval.line = yylineno; return CADENA; }

ent					{ yylval.line = yylineno; return INT; }

dreal				{ yylval.line = yylineno; return DOUBLE; }

real				{ yylval.line = yylineno; return FLOAT; }

car				{ yylval.line = yylineno; return CHAR; }

sin				{ yylval.line = yylineno; return VOID; }

func				{ yylval.line = yylineno; return FUNCION; }

si 					{ yylval.line = yylineno; return IF; }

sino 				{ yylval.line = yylineno; return ELSE; }

entonces					{ yylval.line = yylineno; return THEN; }

mientras				{ yylval.line = yylineno; return WHILE; }

que				{ yylval.line = yylineno; return WHAT; }

hacer 					{ yylval.line = yylineno; return DO; }

for					{ yylval.line = yylineno; return FOR; }

devolver				{ yylval.line = yylineno; return RETURN; }

segun				{ yylval.line = yylineno; return SWITCH; }

caso				{ yylval.line = yylineno; return CASE; }

registro 			{ yylval.line = yylineno; return REGISTRO; }

predet				{ yylval.line = yylineno; return DEFAULT; }

inicio				{ yylval.line = yylineno; return INICIO; }

fin					{ yylval.line = yylineno; return FIN; }

terminar				{ yylval.line = yylineno; return BREAK; }

verdadero 				{ yylval.line = yylineno; return TRUE; }

falso				{ yylval.line = yylineno; return FALSE; }

{id}				{ yylval.line = yylineno; yylval.sval = strdup(yytext); return ID; }

"+"					{ yylval.line = yylineno; yylval.sval = strdup(yytext); return MAS; }

"-"					{ yylval.line = yylineno; yylval.sval = strdup(yytext); return MENOS; }

"*"					{ yylval.line = yylineno; yylval.sval = strdup(yytext); return PROD; }

"/"					{ yylval.line = yylineno; yylval.sval = strdup(yytext); return DIV; }

"%"					{ yylval.line = yylineno; yylval.sval = strdup(yytext); return MOD; }

"(" 				{ yylval.line = yylineno; return PRA; }

")" 				{ yylval.line = yylineno; return PRC; }

"["					{ yylval.line = yylineno; return CTA; }

"]"					{ yylval.line = yylineno; return CTC; }

"{"					{ yylval.line = yylineno; return LLA; }	

"}"					{ yylval.line = yylineno; return LLC; }	

":="				{ yylval.line = yylineno; return ASIG; }	

":"					{ yylval.line = yylineno; return DPTS; }	

","					{ yylval.line = yylineno; return COMA; }

\.					{ yylval.line = yylineno; return PT; }

"no"				{ yylval.line = yylineno; return NOT; }	

"oo"				{ yylval.line = yylineno; return OR; }	

"yy"				{ yylval.line = yylineno; return AND; }	

"<"					{ yylval.line = yylineno; yylval.sval = strdup(yytext); return SMT; }

">"					{ yylval.line = yylineno; yylval.sval = strdup(yytext); return GRT; }

">="				{ yylval.line = yylineno; yylval.sval = strdup(yytext); return GREQ; }

"<="				{ yylval.line = yylineno; yylval.sval = strdup(yytext); return SMEQ; }

"<>"				{ yylval.line = yylineno; yylval.sval = strdup(yytext); return DIF; }

"=="				{ yylval.line = yylineno; yylval.sval = strdup(yytext); return EQEQ; }

[ \n\t\r]			{}

"/*"				{ BEGIN(com1); }

<com1>\n    		{ yylval.line = yylineno; }

<com1>[^*\n]*		{}

<com1>"*"+[^*/\n]*	{}

<com1>"*"+"/"		{ BEGIN(INITIAL); }

"//"				{ BEGIN(com2); }

<com2>[^*\n]*		{}

<com2>\n  			{ BEGIN(INITIAL); }

.					{ printf("\n****Error lexico en la linea: %d\n", yylineno);}

%%