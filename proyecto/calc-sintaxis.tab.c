/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "calc-sintaxis.y" /* yacc.c:339  */


/*

Pre-Proyecto de Compiladores 2017

Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilaVariables.c"
//#include "listaVariables.c"
#include "infostring.c"
#include "infoint.c"
#include "arbol.c"
#include <time.h>
#include <stdbool.h>


NodoPila *variableGlobalPila;
NodoArbol *listametodos;





void nuevoNivelPila(){
 NodoPila *aux = malloc(sizeof(NodoPila));
 aux->lista = NULL;
 aux->nodoInferior=variableGlobalPila;
 variableGlobalPila = aux;

}

void eliminarNivelPila(){
variableGlobalPila = variableGlobalPila->nodoInferior;

}

void nuevaVariable(char* param_nombre, char* param_tipo){
  NodoArbol *aux = malloc(sizeof(NodoArbol));
  aux->tipoNodo = 1;
  aux->nombre=param_nombre;
  aux->tipo = param_tipo;

 aux->nextlista = variableGlobalPila->lista;
  variableGlobalPila->lista=aux;

}
void inicializar (){
  variableGlobalPila = (NodoPila*) malloc(sizeof(NodoPila));
  listametodos=malloc(sizeof(NodoArbol));
  listametodos=NULL;
  nuevoNivelPila();

}

char *aux;



#line 132 "calc-sintaxis.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "calc-sintaxis.tab.h".  */
#ifndef YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED
# define YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED
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
    INT = 258,
    ID = 259,
    VAR = 260,
    CLASS = 261,
    IF = 262,
    THEN = 263,
    ELSE = 264,
    TRUE = 265,
    FALSE = 266,
    RETURN = 267,
    VOID = 268,
    INTRES = 269,
    BOOL = 270,
    WHILE = 271,
    MAS = 272,
    MENOS = 273,
    POR = 274,
    EXCLAMACION = 275,
    DIVISION = 276,
    MOD = 277,
    COMA = 278,
    PUNTOYCOMA = 279,
    PARENTESISABRE = 280,
    PARENTESISCIERRA = 281,
    ASIG = 282,
    EQUALS = 283,
    MAYORQUE = 284,
    MENORQUE = 285,
    AND = 286,
    OR = 287,
    LLAVEABRE = 288,
    LLAVECIERRA = 289,
    UNARIO = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 67 "calc-sintaxis.y" /* yacc.c:355  */
 int i; char *s; char c; struct nodoArbol *p; struct infoString *infos; struct infoInt *infoi  ;

#line 211 "calc-sintaxis.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 228 "calc-sintaxis.tab.c" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   126,   128,   130,   132,   134,   138,   138,
     143,   151,   161,   163,   165,   167,   169,   171,   173,   175,
     179,   180,   185,   187,   189,   191,   195,   196,   199,   200,
     204,   206,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   227,   228,   232,   233,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   257,   259,   261,   263
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "VAR", "CLASS", "IF",
  "THEN", "ELSE", "TRUE", "FALSE", "RETURN", "VOID", "INTRES", "BOOL",
  "WHILE", "MAS", "MENOS", "POR", "EXCLAMACION", "DIVISION", "MOD", "COMA",
  "PUNTOYCOMA", "PARENTESISABRE", "PARENTESISCIERRA", "ASIG", "EQUALS",
  "MAYORQUE", "MENORQUE", "AND", "OR", "LLAVEABRE", "LLAVECIERRA",
  "UNARIO", "$accept", "program", "$@1", "clases", "var_decl", "$@2",
  "listaID", "method_decl", "param_decl", "block", "listavar_decl",
  "listastatement", "type", "statement", "method_call", "param_call",
  "expr", "literal", "bool_literal", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -54,     6,     5,   -54,   -20,   -54,    14,    29,   -54,   -54,
     -54,   -54,    39,    99,    37,    -7,    42,   -54,    46,   -54,
     -54,   140,    36,    68,    67,    49,    51,   -54,   145,   -54,
      21,    62,    -6,   100,   158,   206,    62,    97,   101,   -54,
      63,   -54,    70,    62,   -54,    62,   120,    62,   144,   -54,
      62,   -54,   -23,    83,   127,   138,   -54,   -54,   -54,    76,
      82,   -54,   -54,    98,   117,   -54,   -54,    62,   -54,    62,
     -54,   114,   138,   138,   -54,   102,   -54,   -54,   138,   138,
     -54,   138,   -54,   164,   -54,   -54,   147,   -54,    95,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   177,   228,   180,   196,
     -54,   -54,   212,   138,   138,   138,   138,   138,   -54,   138,
     138,   138,   138,   138,   -54,   -54,   138,   -54,   -54,   118,
     -54,    18,    18,   -54,   -54,   -54,   273,   279,   279,   259,
     244,   228,    62,   126,    62,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     0,    30,    31,
       4,    26,     0,     0,     0,     0,     0,     6,     0,     5,
      27,     0,     0,     0,     0,     0,     0,     7,     0,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
       0,    14,     0,     0,    20,     0,     0,     0,     0,    12,
       0,    11,     0,     0,     0,     0,    39,    25,    40,     0,
       0,     8,    28,     0,     0,    15,    18,     0,    16,     0,
      13,     0,     0,     0,    61,    58,    63,    64,     0,     0,
      36,     0,    59,     0,    60,    62,     0,    23,     0,    24,
      29,    38,    21,    19,    17,    41,     0,    43,     0,     0,
      55,    56,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,     0,     0,    34,    22,     0,    42,    37,     0,
      57,    45,    46,    47,    48,    49,    52,    50,    51,    53,
      54,    44,     0,    32,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -54,   -54,   -12,   -54,   -54,   123,   -25,   -31,
     104,    91,     9,   -53,   -17,   -54,   -47,   -54,   -54
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,    11,    23,    30,    12,    32,    58,
      13,    60,    33,    62,    82,    96,    83,    84,    85
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    20,    71,    37,    72,    49,     3,    90,    86,    46,
      48,     4,    65,     6,    66,    14,    68,    42,    24,    70,
      43,    18,    14,    63,    97,    98,    99,     7,     8,     9,
      18,   100,   101,    15,   102,    90,    93,   105,    94,   106,
     107,    22,    63,    63,    38,    39,    25,    20,    10,    61,
      26,    64,    16,     8,     9,   114,   121,   122,   123,   124,
     125,    28,   126,   127,   128,   129,   130,    52,    61,   131,
      53,    63,    29,    17,    34,    54,    35,     8,     9,    55,
      52,     8,     9,    53,     8,     9,    52,    56,    54,    53,
       8,     9,    55,    31,    54,    40,    40,    57,    55,    52,
      56,   133,    53,   135,    44,    51,    56,    54,    73,    40,
      87,    55,     7,     8,     9,    40,    89,    74,    75,    56,
      42,    92,    91,    50,    76,    77,   132,    71,    40,   115,
      74,    75,    78,    19,    79,   134,    21,    76,    77,    81,
      95,    74,    75,    42,    59,    78,    67,    79,    76,    77,
      88,    80,    81,    16,     8,     9,    78,     0,    79,     8,
       9,     0,     0,    81,   103,   104,   105,    42,   106,   107,
      69,    36,     8,     9,    27,   109,   110,   111,   112,   113,
      40,   103,   104,   105,    45,   106,   107,     0,   108,     0,
       0,     0,   109,   110,   111,   112,   113,   103,   104,   105,
     116,   106,   107,   117,   118,     0,     0,     0,   109,   110,
     111,   112,   113,   103,   104,   105,     0,   106,   107,     0,
       8,     9,   119,     0,   109,   110,   111,   112,   113,   103,
     104,   105,    47,   106,   107,     0,     0,     0,   120,     0,
     109,   110,   111,   112,   113,   103,   104,   105,     0,   106,
     107,     0,     0,     0,     0,     0,   109,   110,   111,   112,
     113,   103,   104,   105,     0,   106,   107,     0,     0,     0,
       0,     0,   109,   110,   111,   112,   103,   104,   105,     0,
     106,   107,     0,     0,     0,     0,     0,   109,   110,   111,
     103,   104,   105,     0,   106,   107,   103,   104,   105,     0,
     106,   107,   110,   111
};

static const yytype_int16 yycheck[] =
{
      31,    13,    25,    28,    27,    36,     0,    60,    55,    34,
      35,     6,    43,    33,    45,     6,    47,    23,    25,    50,
      26,    12,    13,    40,    71,    72,    73,    13,    14,    15,
      21,    78,    79,     4,    81,    88,    67,    19,    69,    21,
      22,     4,    59,    60,    23,    24,     4,    59,    34,    40,
       4,    42,    13,    14,    15,    86,   103,   104,   105,   106,
     107,    25,   109,   110,   111,   112,   113,     4,    59,   116,
       7,    88,     4,    34,    25,    12,    25,    14,    15,    16,
       4,    14,    15,     7,    14,    15,     4,    24,    12,     7,
      14,    15,    16,    26,    12,    33,    33,    34,    16,     4,
      24,   132,     7,   134,     4,     4,    24,    12,    25,    33,
      34,    16,    13,    14,    15,    33,    34,     3,     4,    24,
      23,     4,    24,    26,    10,    11,     8,    25,    33,    34,
       3,     4,    18,    34,    20,     9,    13,    10,    11,    25,
      26,     3,     4,    23,    40,    18,    26,    20,    10,    11,
      59,    24,    25,    13,    14,    15,    18,    -1,    20,    14,
      15,    -1,    -1,    25,    17,    18,    19,    23,    21,    22,
      26,    26,    14,    15,    34,    28,    29,    30,    31,    32,
      33,    17,    18,    19,    26,    21,    22,    -1,    24,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    17,    18,    19,
      23,    21,    22,    26,    24,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    17,    18,    19,    -1,    21,    22,    -1,
      14,    15,    26,    -1,    28,    29,    30,    31,    32,    17,
      18,    19,    26,    21,    22,    -1,    -1,    -1,    26,    -1,
      28,    29,    30,    31,    32,    17,    18,    19,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    17,    18,    19,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    17,    18,    19,    -1,
      21,    22,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      17,    18,    19,    -1,    21,    22,    17,    18,    19,    -1,
      21,    22,    29,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,     0,     6,    39,    33,    13,    14,    15,
      34,    40,    43,    46,    48,     4,    13,    34,    48,    34,
      40,    43,     4,    41,    25,     4,     4,    34,    25,     4,
      42,    26,    44,    48,    25,    25,    26,    44,    23,    24,
      33,    45,    23,    26,     4,    26,    44,    26,    44,    45,
      26,     4,     4,     7,    12,    16,    24,    34,    45,    46,
      47,    48,    49,    50,    48,    45,    45,    26,    45,    26,
      45,    25,    27,    25,     3,     4,    10,    11,    18,    20,
      24,    25,    50,    52,    53,    54,    52,    34,    47,    34,
      49,    24,     4,    45,    45,    26,    51,    52,    52,    52,
      52,    52,    52,    17,    18,    19,    21,    22,    24,    28,
      29,    30,    31,    32,    45,    34,    23,    26,    24,    26,
      26,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,     8,    45,     9,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    38,    37,    39,    39,    39,    39,    41,    40,
      42,    42,    43,    43,    43,    43,    43,    43,    43,    43,
      44,    44,    45,    45,    45,    45,    46,    46,    47,    47,
      48,    48,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    53,    53,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     3,     4,     4,     5,     0,     4,
       1,     3,     5,     6,     5,     6,     6,     7,     6,     7,
       2,     4,     4,     3,     3,     2,     1,     2,     1,     2,
       1,     1,     6,     8,     3,     3,     2,     4,     2,     1,
       1,     3,     4,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
| yyreduce -- Do a reduction.  |
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
#line 126 "calc-sintaxis.y" /* yacc.c:1646  */
    {inicializar();}
#line 1426 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 126 "calc-sintaxis.y" /* yacc.c:1646  */
    {eliminarNivelPila();}
#line 1432 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 128 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("TERMINO1\n");}
#line 1438 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 130 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\nTERMINO2");}
#line 1444 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 132 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\nTERMINO3");}
#line 1450 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 134 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\nTERMINO4");}
#line 1456 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 138 "calc-sintaxis.y" /* yacc.c:1646  */
    {aux=(yyvsp[0].s);}
#line 1462 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 138 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\ndeclaracion de var finalizada");}
#line 1468 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 143 "calc-sintaxis.y" /* yacc.c:1646  */
    {     if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
                      printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable((yyvsp[0].infos)->info,aux);
                    }else{
                      printf("linea %i VARIABLE %s YA DECLARADA!!! \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info  );
                      }

                    }
#line 1481 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 151 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
                    printf("%s\n","la variable no esta en el scope!!" );
                    nuevaVariable((yyvsp[0].infos)->info,aux);
                  }else{
                    printf("linea %i VARIABLE %s YA DECLARADA!!! \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info  );
                    }
  }
#line 1494 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 161 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo1\n");}
#line 1500 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 163 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo2\n");}
#line 1506 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 165 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo3\n");}
#line 1512 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 167 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo4\n");}
#line 1518 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 169 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo5\n");}
#line 1524 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 171 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo6\n");}
#line 1530 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 173 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo7\n");}
#line 1536 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 175 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("declaracion de metodo8\n");}
#line 1542 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 179 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1548 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 180 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1554 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 185 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1560 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 187 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1566 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 189 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1572 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 191 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1578 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 195 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1584 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 196 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1590 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 199 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1596 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 200 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1602 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 204 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.s)="int";}
#line 1608 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 206 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.s)="bool";}
#line 1614 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 217 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1620 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 218 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1626 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 219 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1632 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 220 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1638 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 221 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1644 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 222 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1650 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 223 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1656 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 224 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1662 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 225 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1668 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 237 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1674 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 238 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1680 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 239 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1686 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 240 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1692 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 241 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1698 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 242 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1704 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 243 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1710 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 244 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1716 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 245 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1722 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 246 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1728 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 257 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1734 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 259 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1740 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 261 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1746 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 263 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1752 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;


#line 1756 "calc-sintaxis.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
#line 267 "calc-sintaxis.y" /* yacc.c:1906  */

