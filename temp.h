#include "attribs.h"
/* A Bison parser, made by GNU Bison 3.4.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    ENTERO = 259,
    DOBLE = 260,
    FLOTANTE = 261,
    INT = 262,
    FLOAT = 263,
    DOUBLE = 264,
    CHAR = 265,
    VOID = 266,
    LLA = 267,
    LLC = 268,
    COMA = 269,
    PYC = 270,
    DPTS = 271,
    PT = 272,
    FUNCION = 273,
    IF = 274,
    WHILE = 275,
    DO = 276,
    FOR = 277,
    RETURN = 278,
    SWITCH = 279,
    BREAK = 280,
    CASE = 281,
    DEFAULT = 282,
    CADENA = 283,
    CARACTER = 284,
    TRUE = 285,
    FALSE = 286,
    THEN = 287,
    WHAT = 288,
    REGISTRO = 289,
    READ = 290,
    WRITE = 291,
    ASIG = 292,
    OR = 293,
    AND = 294,
    EQEQ = 295,
    DIF = 296,
    GRT = 297,
    SMT = 298,
    GREQ = 299,
    SMEQ = 300,
    MAS = 301,
    MENOS = 302,
    PROD = 303,
    DIV = 304,
    MOD = 305,
    NOT = 306,
    PRA = 307,
    CTA = 308,
    PRC = 309,
    CTC = 310,
    FIN = 311,
    INICIO = 312,
    ELSE = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 58 "yacc.y"

	int line;
	char* sval;
	type tval;
	expresion eval;
	num num;
	char* cadena;
	char car;
	args_list args_list;
	condition cond;
	sentence sent;

#line 129 "yacc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */
