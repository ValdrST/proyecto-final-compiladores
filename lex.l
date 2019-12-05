%{

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "yacc.tab.h"

%}

%option noyywrap
%option yylineno

digito [0-9]
ent_def {digito}+
exp [Ee][+-]?{ent}
real_def ({ent}.?{ent}{exp}|{ent}?.{ent}{exp}?|{ent}.{ent}?{exp}?)[Ff]
dreal_def {ent}.?{ent}{exp}|{ent}?.{ent}{exp}?|{ent}.{ent}?{exp}?
letra [a-zA-Z]
id (_|{letra})((_|{letra}|{digito})){0,31}

car_def '([^'])'
cadena \"([^"]*)\"

registro [Rr][Ee][Gg][Ii][Ss][Tt][Rr][Oo]
inicio [Ii][Nn][Ii][Cc][Ii][Oo]
fin [Ff][Ii][Nn]
ent [Ee][Nn][Tt]
real [Rr][Ee][Aa][Ll]
dreal [Dd][Rr][Ee][Aa][Ll]
car [Cc][Aa][Rr]
sin [Ss][Ii][Nn]
func [Ff][Uu][Nn][Cc]
si [Ss][Ii]
entonces [Ee][Nn][Tt][Oo][Nn][Cc][Ee][Ss]
sino [Ss][Ii][Nn][Oo]
mientras [Mm][Ii][Ee][Nn][Tt][Rr][Aa][Ss]
hacer [Hh][Aa][Cc][Ee][Rr]
mientrasq [Mm][Ii][Ee][Nn][Tt][Rr][Aa][Ss]" "[Qq][Uu][Ee]
escribir [Ee][Ss][Cc][Rr][Ii][Bb][Ii][Rr]
leer [Ll][Ee][Ee][Rr]
devolver [Dd][Ee][Vv][Oo][Ll][Vv][Ee][Rr]
terminar [Tt][Ee][Rr][Mm][Ii][Nn][Aa][Rr]
verdadero [Vv][Ee][Rr][Dd][Aa][Dd][Ee][Rr][Oo]
falso [Ff][Aa][Ll][Ss][Oo]

%x com1
%x com2


%%


{func}  {yylval.line = yylineno;return FUNC;}

{registro} {yylval.line = yylineno;return REGISTRO;}

{inicio} {yylval.line = yylineno;return INICIO;}

{si}    {yylval.line = yylineno;return SI;}

{fin}    {yylval.line = yylineno;return FIN;}

{car}    {yylval.line = yylineno;return CAR;}

{ent}    {yylval.line = yylineno;return ENT;}

{entonces}    {yylval.line = yylineno;return ENTONCES;}

{sino}    {yylval.line = yylineno;return SINO;}

{verdadero} {yylval.line = yylineno;return VERDADERO;}

{falso} {yylval.line = yylineno;return FALSO;}

{mientras}  {yylval.line = yylineno;return MIENTRAS;}

{sin}   {yylval.line = yylineno;return SIN;}

"oo"    {yylval.line = yylineno;return OO;}

"yy"    {yylval.line = yylineno;return YY;}

"no"    {yylval.line = yylineno;return NOT;}

{id} { yylval.line = yylineno;yylval.sval = strdup(yytext);return ID;}



{car_def}   {yylval.line = yylineno;yylval.car.tipo = 4;yylval.car.cval = yytext[1];return CARACTER;}

{ent_def}   {yylval.line = yylineno;yylval.num.tipo = 1;yylval.num.ival = atoi(yytext);return NUM;}

{real_def}  {yylval.line = yylineno;yylval.num.tipo = 2;yylval.num.fval = atof(yytext);return NUM;}

{dreal_def} {yylval.line = yylineno; yylval.num.tipo = 3; yylval.num.dval = atof(yytext);return NUM;}


"+"	{ yylval.line = yylineno; yylval.sval = strdup(yytext); return MAS; }

"-"	{ yylval.line = yylineno; yylval.sval = strdup(yytext); return MENOS; }

"*"	{ yylval.line = yylineno; yylval.sval = strdup(yytext); return PROD; }

"/"	{ yylval.line = yylineno; yylval.sval = strdup(yytext); return DIV; }

"%"	{ yylval.line = yylineno; yylval.sval = strdup(yytext); return MOD; }

"(" {yylval.line = yylineno;return PRA;}

")" {yylval.line = yylineno;return PRC;}

":="    {yylval.line = yylineno;return ASIG;}

"," {yylval.line = yylineno;return COMA;}

"[" {yylval.line = yylineno;return LCOR;}

"]" {yylval.line = yylineno;return DCOR;}



"<"	{ yylval.line = yylineno; yylval.sval = strdup(yytext); return SMT; }

">"	{ yylval.line = yylineno; yylval.sval = strdup(yytext); return GRT; }

">=" { yylval.line = yylineno; yylval.sval = strdup(yytext); return GREQ; }

"<=" { yylval.line = yylineno; yylval.sval = strdup(yytext); return SMEQ; }

"<>" { yylval.line = yylineno; yylval.sval = strdup(yytext); return DIF; }

"==" { yylval.line = yylineno; yylval.sval = strdup(yytext); return EQEQ; }

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