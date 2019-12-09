%{

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "yacc_p.tab.h"

%}

%option noyywrap
%option yylineno


digito [0-9]+
ent_def [+-]?{digito}
exp [Ee][+-]?{digito}+
real_def ({digito}.?{digito}{exp}|{digito}?.{digito}{exp}?|{digito}.{digito}?{exp}?)[Ff]
dreal_def ({digito}.?{digito}{exp}|{digito}?.{digito}{exp}?|{digito}.{digito}?{exp}?)[dD]
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




{ent_def}   {yylval.line = yylineno;yylval.num.tipo = 1;yylval.num.ival = atoi(yytext);return NUM;}

{real_def}  {yylval.line = yylineno;yylval.num.tipo = 2;yylval.num.fval = atof(yytext);return NUM;}

{dreal_def} {yylval.line = yylineno; yylval.num.tipo = 3; yylval.num.dval = atof(yytext);return NUM;}

{car_def}   {yylval.line = yylineno;yylval.car.tipo = 4;sprintf(yylval.sval,"%c",yytext[1]);return CARACTER;}

{ent}    {yylval.line = yylineno;return ENT;}

{dreal} {yylval.line = yylineno;return DREAL;}

{real} {yylval.line = yylineno;return REAL;}

{car} {yylval.line = yylineno;return CAR;}

{sin}   {yylval.line = yylineno;return SIN;}

{registro} {yylval.line = yylineno;return REGISTRO;}

{inicio} {yylval.line = yylineno;return INICIO;}

{func}  {yylval.line = yylineno;return FUNC;}

{sino}    {yylval.line = yylineno;return SINO;}

{si}    {yylval.line = yylineno;return SI;}

{devolver} {yylval.line = yylineno;return DEVOLVER;}

{fin}    {yylval.line = yylineno;return FIN;}

{entonces}    {yylval.line = yylineno;return ENTONCES;}

{verdadero} {yylval.line = yylineno;return VERDADERO;}

{falso} {yylval.line = yylineno;return FALSO;}

{mientras}  {yylval.line = yylineno;return MIENTRAS;}

{mientrasq}  {yylval.line = yylineno;return MIENTRAS_QUE;}

{leer}    {yylval.line = yylineno;return LEER;}

{escribir}    {yylval.line = yylineno;return ESCRIBIR;}

"oo"    {yylval.line = yylineno;return OO;}

"yy"    {yylval.line = yylineno;return YY;}

"no"    {yylval.line = yylineno;return NOT;}

"+"	{ yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return MAS; }

"-"	{ yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return MENOS; }

"*"	{ yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return PROD; }

"/"	{ yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return DIV; }

"%"	{ yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return MOD; }

"(" {yylval.line = yylineno;return LPAR; }

")" {yylval.line = yylineno;return RPAR;}

":="   {yylval.line = yylineno;return ASIG;}

"," {yylval.line = yylineno;return COMA;}

"[" {yylval.line = yylineno;return LCOR;}

"]" {yylval.line = yylineno;return RCOR;}

"." {yylval.line = yylineno;return PT;}

"<"	{ yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return SMT; }

">"	{ yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return GRT; }

">=" { yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return GREQ; }

"<=" { yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return SMEQ; }

"<>" { yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return DIF; }

"==" { yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext); return EQEQ; }

{id} { yylval.line = yylineno; sprintf(yylval.sval,"%s",yytext);return ID;}

[ \n\t\r]+	{}



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