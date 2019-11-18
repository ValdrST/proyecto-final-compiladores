/* A Bison parser, made by GNU Bison 3.4.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc.y"


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
	int existe_globalmente(char*);
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


#line 126 "yacc.tab.c"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 57 "yacc.y"

	int line;
	char* sval;
	type tval;
	expresion eval;
	num num;
	args_list args_list;
	condition cond;
	sentence sent;

#line 239 "yacc.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  145

#define YYUNDEFTOK  2
#define YYMAXUTOK   313

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   128,   145,   149,   149,   150,   151,   155,
     156,   157,   158,   159,   163,   179,   198,   208,   217,   226,
     217,   252,   257,   258,   262,   262,   286,   286,   293,   294,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   311,   312,   316,   320,   320,   327,   342,   342,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     366,   370,   371,   380,   381,   382,   383,   384,   385,   389,
     390,   391,   392,   393,   394,   395
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "ENTERO", "DOBLE", "FLOTANTE",
  "INT", "FLOAT", "DOUBLE", "CHAR", "VOID", "LLA", "LLC", "COMA", "PYC",
  "DPTS", "PT", "FUNCION", "IF", "WHILE", "DO", "FOR", "RETURN", "SWITCH",
  "BREAK", "CASE", "DEFAULT", "CADENA", "CARACTER", "TRUE", "FALSE",
  "THEN", "WHAT", "REGISTRO", "READ", "WRITE", "ASIG", "OR", "AND", "EQEQ",
  "DIF", "GRT", "SMT", "GREQ", "SMEQ", "MAS", "MENOS", "PROD", "DIV",
  "MOD", "NOT", "PRA", "CTA", "PRC", "CTC", "FIN", "INICIO", "ELSE",
  "$accept", "programa", "$@1", "tipo", "declaraciones", "$@2", "base",
  "lista_var", "tipo_arreglo", "funciones", "$@3", "$@4", "argumentos",
  "arg", "$@5", "lista_arg", "sentencias", "sentencia", "casos",
  "predeterminado", "variable", "$@6", "parte_arreglo", "expresion",
  "parametros", "lista_param", "expresion_booleana", "relacional", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF -49

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-49)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -49,     8,     6,   -49,   -49,   -49,   -49,   -49,   -49,   -25,
     -49,    -9,     1,     6,    54,    73,   -49,    63,   -49,    19,
       1,    55,    56,    17,     6,   -49,    74,   -49,   -49,     1,
     -49,     1,    24,   -49,   -49,    73,   -49,    36,   -49,    73,
      88,    47,   -49,   -49,     6,   100,    89,    57,    57,   100,
      16,    53,   -49,    16,    16,    51,   100,    76,   114,    65,
     -15,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,    57,    16,   -49,   120,    91,   -49,    91,   108,
     120,    16,   120,   120,   -49,   -49,    16,   -49,    16,   -49,
      16,   -49,   102,    16,    16,    16,    16,    16,    57,    57,
     -22,    66,    98,   111,    -9,   120,    92,   120,    78,   119,
     -49,     3,     3,   -49,   -49,   -49,    95,   -49,   100,   100,
     -49,    57,   117,   -49,    65,   -49,    16,    81,    90,   -14,
     140,   118,   -49,   120,   -49,   -49,   -49,   137,   138,    99,
     100,   100,   -49,   -49,   -49
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     8,     1,     9,    10,    11,    12,    13,     0,
       5,    21,    17,     8,     0,     0,     3,     0,     4,     0,
      17,     8,     0,     0,     8,    15,     0,     6,    18,    17,
       7,    17,     0,    16,    14,    23,    24,     0,    27,    22,
       0,     0,    26,    25,     8,     0,    44,     0,     0,     0,
      38,     0,    40,     0,     0,     0,    29,     0,     0,    48,
      44,    56,    57,    58,    67,    68,    73,    74,    70,    69,
      71,    72,     0,     0,    55,    75,     0,    66,     0,     0,
      37,     0,    36,    35,    19,    28,     0,    46,     0,    45,
       0,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    34,     0,    62,     0,    60,
      54,    49,    50,    51,    52,    53,    63,    64,     0,     0,
      32,     0,    42,    20,    48,    59,     0,     0,     0,     0,
       0,     0,    47,    61,    30,    31,    33,     0,     0,     0,
       0,     0,    39,    41,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,   -49,   -17,    14,   -49,   147,   -49,    -8,    59,
     -49,   -49,   -49,   125,   -49,   -49,   -48,   115,   -49,   -49,
     -45,   -49,    48,   -47,   -49,   -49,   -43,   -49
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    10,    11,    14,    12,    21,    18,    16,
      32,   104,    37,    38,    40,    39,    55,    56,   131,   139,
      74,    59,    89,    75,   108,   109,    76,    77
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,    79,    58,    80,    57,    78,    82,    83,     3,    15,
     118,    57,    25,     4,     5,     6,     7,     8,    36,    60,
      61,    33,    36,    34,    98,    99,    92,    19,   100,    91,
     101,    57,    13,    57,   103,    27,   119,    90,    30,   105,
       9,   106,   136,   107,    62,    63,   111,   112,   113,   114,
     115,    95,    96,    97,    17,   116,   117,    20,    45,    28,
      60,    61,     4,     5,     6,     7,     8,    23,    73,    26,
     127,   128,    29,    57,    57,    24,    35,    31,   129,   133,
       4,     5,     6,     7,     8,    62,    63,    64,    65,     9,
      41,    43,   143,   144,    46,    57,    57,    66,    67,    68,
      69,    70,    71,    46,    44,    81,    58,    84,    72,    73,
      47,    48,    49,    86,    50,    51,    52,    87,    88,    47,
      48,    49,   120,    50,    51,    52,    53,    54,   102,    98,
      99,   121,   125,   126,    99,    53,    54,   134,    93,    94,
      95,    96,    97,   130,   137,   138,   135,   124,    93,    94,
      95,    96,    97,   140,   141,   142,   110,    93,    94,    95,
      96,    97,    22,   123,    42,   122,    93,    94,    95,    96,
      97,    85,   132
};

static const yytype_uint8 yycheck[] =
{
      45,    49,    17,    50,    49,    48,    53,    54,     0,    18,
      32,    56,    20,     7,     8,     9,    10,    11,    35,     3,
       4,    29,    39,    31,    38,    39,    73,    13,    76,    72,
      78,    76,    57,    78,    81,    21,    58,    52,    24,    86,
      34,    88,    56,    90,    28,    29,    93,    94,    95,    96,
      97,    48,    49,    50,    53,    98,    99,     3,    44,     3,
       3,     4,     7,     8,     9,    10,    11,     4,    52,    14,
     118,   119,    55,   118,   119,    56,    52,     3,   121,   126,
       7,     8,     9,    10,    11,    28,    29,    30,    31,    34,
      54,     3,   140,   141,     3,   140,   141,    40,    41,    42,
      43,    44,    45,     3,    57,    52,    17,    56,    51,    52,
      19,    20,    21,    37,    23,    24,    25,     3,    53,    19,
      20,    21,    56,    23,    24,    25,    35,    36,    20,    38,
      39,    33,    54,    14,    39,    35,    36,    56,    46,    47,
      48,    49,    50,    26,     4,    27,    56,    55,    46,    47,
      48,    49,    50,    16,    16,    56,    54,    46,    47,    48,
      49,    50,    15,   104,    39,    54,    46,    47,    48,    49,
      50,    56,   124
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,    61,     0,     7,     8,     9,    10,    11,    34,
      62,    63,    65,    57,    64,    18,    68,    53,    67,    63,
       3,    66,    65,     4,    56,    67,    14,    63,     3,    55,
      63,     3,    69,    67,    67,    52,    62,    71,    72,    74,
      73,    54,    72,     3,    57,    63,     3,    19,    20,    21,
      23,    24,    25,    35,    36,    75,    76,    79,    17,    80,
       3,     4,    28,    29,    30,    31,    40,    41,    42,    43,
      44,    45,    51,    52,    79,    82,    85,    86,    85,    75,
      82,    52,    82,    82,    56,    76,    37,     3,    53,    81,
      52,    85,    82,    46,    47,    48,    49,    50,    38,    39,
      75,    75,    20,    82,    70,    82,    82,    82,    83,    84,
      54,    82,    82,    82,    82,    82,    85,    85,    32,    58,
      56,    33,    54,    68,    55,    54,    14,    75,    75,    85,
      26,    77,    81,    82,    56,    56,    56,     4,    27,    78,
      16,    16,    56,    75,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    61,    60,    62,    64,    63,    63,    63,    65,
      65,    65,    65,    65,    66,    66,    67,    67,    69,    70,
      68,    68,    71,    71,    73,    72,    74,    74,    75,    75,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    77,    78,    80,    79,    79,    81,    81,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      83,    84,    84,    85,    85,    85,    85,    85,    85,    86,
      86,    86,    86,    86,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     2,     0,     4,     5,     0,     1,
       1,     1,     1,     1,     4,     2,     4,     0,     0,     0,
      13,     0,     1,     0,     0,     3,     2,     1,     2,     1,
       6,     6,     4,     6,     3,     2,     2,     2,     1,     7,
       1,     4,     0,     3,     0,     3,     3,     4,     0,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     4,
       1,     3,     1,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 128 "yacc.y"
    { 
		printf("\nInicializando las pilas....\n");
		printf("Tabla de simbolos global creada...");
		init(); 
	}
#line 1448 "yacc.tab.c"
    break;

  case 3:
#line 132 "yacc.y"
    {
		if(busca_main() == -1){
			yyerror("Falta definir funcion principal");
			exit(0);
		}
		print_symbols_table(); 
		print_types_table(); 
		print_code(); 
	}
#line 1462 "yacc.tab.c"
    break;

  case 4:
#line 145 "yacc.y"
    { global_tipo = (yyvsp[-1].tval).type; global_dim = (yyvsp[-1].tval).dim; }
#line 1468 "yacc.tab.c"
    break;

  case 5:
#line 149 "yacc.y"
    { global_tipo = (yyvsp[0].tval).type; global_dim = (yyvsp[0].tval).dim; }
#line 1474 "yacc.tab.c"
    break;

  case 8:
#line 151 "yacc.y"
    {}
#line 1480 "yacc.tab.c"
    break;

  case 9:
#line 155 "yacc.y"
    { (yyval.tval).type = 1; (yyval.tval).dim = 2; }
#line 1486 "yacc.tab.c"
    break;

  case 10:
#line 156 "yacc.y"
    { (yyval.tval).type = 2; (yyval.tval).dim = 4; }
#line 1492 "yacc.tab.c"
    break;

  case 11:
#line 157 "yacc.y"
    { (yyval.tval).type = 3; (yyval.tval).dim = 8; }
#line 1498 "yacc.tab.c"
    break;

  case 12:
#line 158 "yacc.y"
    { (yyval.tval).type = 4; (yyval.tval).dim = 1; }
#line 1504 "yacc.tab.c"
    break;

  case 13:
#line 159 "yacc.y"
    { (yyval.tval).type = 0; (yyval.tval).dim = 0; }
#line 1510 "yacc.tab.c"
    break;

  case 14:
#line 163 "yacc.y"
    { 
		if(existe_en_alcance((yyvsp[-1].sval)) == -1){
			symbol sym;
			sym.id = (yyvsp[-1].sval);
			sym.dir = dir;
			sym.type = (yyvsp[0].tval).type;
			sym.var = "var";
			sym.num_args = 0;
			sym.list_types = malloc(sizeof(int));
			if(scope > 0)
				insert_symbol(sym);
			else 
				insert_global_symbol(sym);
			dir += (yyvsp[0].tval).dim;
		} else{ yyerror("Identificadores duplicados en el mismo alcance"); exit(0); }
	}
#line 1531 "yacc.tab.c"
    break;

  case 15:
#line 179 "yacc.y"
    {
		if(existe_en_alcance((yyvsp[-1].sval)) == -1){
			symbol sym;
			sym.id = (yyvsp[-1].sval);
			sym.dir = dir;
			sym.type = (yyvsp[0].tval).type;
			sym.var = "var";
			sym.num_args = 0;
			sym.list_types = malloc(sizeof(int));
			if(scope > 0)
				insert_symbol(sym);
			else
				insert_global_symbol(sym);
			dir += (yyvsp[0].tval).dim;
		} else{ yyerror("Identificadores duplicados en el mismo alcance"); exit(0); }
	}
#line 1552 "yacc.tab.c"
    break;

  case 16:
#line 198 "yacc.y"
    {
		ttype t;
		if((yyvsp[-2].num).type == 1){
			t.type = "array";
			t.dim = (yyvsp[-2].num).ival;
			t.base = (yyvsp[0].tval).type;
			(yyval.tval).type = insert_type(t);
			(yyval.tval).dim = (yyvsp[0].tval).dim * (yyvsp[-2].num).ival;
		} else { yyerror("La dimension del arreglo debe ser entera"); exit(0); }
	}
#line 1567 "yacc.tab.c"
    break;

  case 17:
#line 208 "yacc.y"
    {
		if(global_tipo != 0){
			(yyval.tval).type = global_tipo;
			(yyval.tval).dim = global_dim;
		} else { yyerror("No se pueden declarar variables de tipo void"); exit(0); }
	}
#line 1578 "yacc.tab.c"
    break;

  case 18:
#line 217 "yacc.y"
    {
		num_args = 0;
		list_args = malloc(sizeof(int) * 100);
		create_symbols_table();
		create_types_table();
		scope++;
		dir_aux = dir;
		dir = 0;
	}
#line 1592 "yacc.tab.c"
    break;

  case 19:
#line 226 "yacc.y"
    {
		if(existe_globalmente((yyvsp[-8].sval)) == -1){
			//if(strcpm($2.type, $10.return) == 0){
				ttype t;
				char* tipo = malloc(sizeof(char) * 10);
				sprintf(tipo, "%d", (yyvsp[-9].tval).type);
				t.type = tipo;
				t.base = -1;
				t.dim = 0;

				symbol sym;
				sym.id = (yyvsp[-8].sval);
				sym.dir = -1;
				sym.type = (yyvsp[-9].tval).type; // Falta agregar el tipo t.
				sym.var = "fun";
				sym.num_args = (yyvsp[-5].args_list).total;
				sym.list_types = (yyvsp[-5].args_list).args;
				insert_global_symbol(sym);
			//} else { yyerror("El valor de retorno no coincide"); exit(0); }
		} else { yyerror("Funcion declarada anteriormente"); exit(0); }
		print_symbols_table_2(SYM_STACK.total, (yyvsp[-8].sval));
		scope--;
		dir = dir_aux;
		delete_types_table();
	}
#line 1622 "yacc.tab.c"
    break;

  case 21:
#line 252 "yacc.y"
    {}
#line 1628 "yacc.tab.c"
    break;

  case 22:
#line 257 "yacc.y"
    { (yyval.args_list) = (yyvsp[0].args_list); }
#line 1634 "yacc.tab.c"
    break;

  case 23:
#line 258 "yacc.y"
    { (yyval.args_list).total = 0; }
#line 1640 "yacc.tab.c"
    break;

  case 24:
#line 262 "yacc.y"
    {
		if(global_tipo != 0){
			(yyvsp[0].tval).type = global_tipo;
			(yyvsp[0].tval).dim = global_dim;
		} else { yyerror("No se pueden declarar variables de tipo void"); exit(0); }
	}
#line 1651 "yacc.tab.c"
    break;

  case 25:
#line 267 "yacc.y"
    {
		if(existe_en_alcance((yyvsp[0].sval)) == -1){
			symbol sym;
			sym.id = (yyvsp[0].sval);
			sym.dir = dir;
			sym.type = (yyvsp[-2].tval).type;
			sym.var = "par";
			sym.num_args = 0;
			insert_symbol(sym);
			dir += (yyvsp[-2].tval).dim;
			*(list_args + num_args) = (yyvsp[-2].tval).type;
			num_args++;
		}else{
			yyerror("Parametro duplicado en funcion"); exit(0);
		}
	}
#line 1672 "yacc.tab.c"
    break;

  case 27:
#line 286 "yacc.y"
    {
		(yyval.args_list).total = num_args + 1;
		(yyval.args_list).args = list_args;
	}
#line 1681 "yacc.tab.c"
    break;

  case 42:
#line 312 "yacc.y"
    {}
#line 1687 "yacc.tab.c"
    break;

  case 44:
#line 320 "yacc.y"
    {
		if(existe_globalmente((yyvsp[0].sval)) == -1){
			yyerror("Variable no declarada");
			exit(0);
		}
	}
#line 1698 "yacc.tab.c"
    break;

  case 46:
#line 327 "yacc.y"
    {
		if(existe_globalmente((yyvsp[-2].sval)) != -1){
			int t = get_type((yyvsp[-2].sval));
			if(t == 1 || t == 2 || t == 3 || t == 4){
				yyerror("La variable no es una estructura");
				exit(0);
			}
		} else {
			yyerror("Variable no declarada");
			exit(0);
		}
	}
#line 1715 "yacc.tab.c"
    break;

  case 48:
#line 342 "yacc.y"
    {}
#line 1721 "yacc.tab.c"
    break;

  case 63:
#line 380 "yacc.y"
    { (yyval.cond) = or((yyvsp[-2].cond), (yyvsp[0].cond)); }
#line 1727 "yacc.tab.c"
    break;

  case 64:
#line 381 "yacc.y"
    { (yyval.cond) = and((yyvsp[-2].cond), (yyvsp[0].cond)); }
#line 1733 "yacc.tab.c"
    break;

  case 65:
#line 382 "yacc.y"
    {}
#line 1739 "yacc.tab.c"
    break;

  case 66:
#line 383 "yacc.y"
    {}
#line 1745 "yacc.tab.c"
    break;

  case 67:
#line 384 "yacc.y"
    {}
#line 1751 "yacc.tab.c"
    break;

  case 68:
#line 385 "yacc.y"
    {}
#line 1757 "yacc.tab.c"
    break;

  case 69:
#line 389 "yacc.y"
    { (yyval.sval) = (yyvsp[0].sval); }
#line 1763 "yacc.tab.c"
    break;

  case 70:
#line 390 "yacc.y"
    { (yyval.sval) = (yyvsp[0].sval); }
#line 1769 "yacc.tab.c"
    break;

  case 71:
#line 391 "yacc.y"
    { (yyval.sval) = (yyvsp[0].sval); }
#line 1775 "yacc.tab.c"
    break;

  case 72:
#line 392 "yacc.y"
    { (yyval.sval) = (yyvsp[0].sval); }
#line 1781 "yacc.tab.c"
    break;

  case 73:
#line 393 "yacc.y"
    { (yyval.sval) = (yyvsp[0].sval); }
#line 1787 "yacc.tab.c"
    break;

  case 74:
#line 394 "yacc.y"
    { (yyval.sval) = (yyvsp[0].sval); }
#line 1793 "yacc.tab.c"
    break;


#line 1797 "yacc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 398 "yacc.y"


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
