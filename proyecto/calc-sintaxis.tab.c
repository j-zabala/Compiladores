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

void nuevaVariable(char* param_nombre, char* param_tipo,int numeroLinea){
  NodoArbol *aux = malloc(sizeof(NodoArbol));
  aux->tipoNodo = 1;
  aux->nombre=param_nombre;
  aux->tipo = param_tipo;
  aux->nextlista =NULL;
  aux->nrolinea = numeroLinea;

  if (variableGlobalPila->lista !=NULL){
    NodoArbol *reco = variableGlobalPila->lista; //segundo o mas de la lista
    while (reco->nextlista != NULL){
      reco = reco->nextlista;
    }
    reco->nextlista=aux;
  }else{
    variableGlobalPila->lista = aux; //primer elemento de la lista
  }

}
void inicializar (){
  variableGlobalPila = (NodoPila*) malloc(sizeof(NodoPila));
  listametodos=malloc(sizeof(NodoArbol));
  listametodos=NULL;
  nuevoNivelPila();

}

NodoArbol* buscarVariableSC (char* param ) {
  NodoArbol *recorrido = variableGlobalPila->lista;
  while(recorrido != NULL){
   if (strcmp(recorrido->nombre,param)==0){
     return recorrido;
   }
   recorrido = recorrido->nextlista;
  }
  return NULL;
}


NodoArbol* buscarVariable (char* param ) {
  NodoPila *scope = variableGlobalPila;
  NodoArbol *recorrido = scope->lista;
while(recorrido != NULL){
  while(recorrido != NULL){
   if (strcmp(recorrido->nombre,param)==0){
     return recorrido;
   }
   recorrido = recorrido->nextlista;
  }
  scope=scope->nodoInferior;
  recorrido = scope->lista;
}
  return NULL;
}

NodoArbol* buscarMetodo (char* param ) {
  NodoArbol *recorrido = listametodos;
  while(recorrido != NULL){
   if (strcmp(recorrido->nombre,param)==0){
     return recorrido;
   }
   recorrido = recorrido->nextlista;
  }
  return NULL;
}
int mismoTipoINT (NodoArbol *a,NodoArbol* b){
  int res =0;
  if(strcmp(b->tipo,"int")!=0){
    res=2;
  }
  if(strcmp(a->tipo,"int")!=0){
    res=1;
  }
  return res;

}

int mismoTipoBOOL (NodoArbol *a,NodoArbol* b){
  int res =0;
  if(strcmp(b->tipo,"bool")!=0){
    res=2;
  }
  if(strcmp(a->tipo,"bool")!=0){
    res=1;
  }
  return res;

}

int verificarMetodoDeclarado(char* n) {
  if(buscarMetodo(n)!=NULL){
    return 1;
  }
return 0;

}


char *aux;

NodoArbol *nodoauxiliar ; //este puntero apunta al primer statement cuando se arma la lista de los statements
NodoArbol *nodoauxiliarAnt ; // lo usamos para guardar el nodo anterior al nodoauxiliar

#line 213 "calc-sintaxis.tab.c" /* yacc.c:339  */

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
#line 148 "calc-sintaxis.y" /* yacc.c:355  */
 int i; char *s; char c; struct nodoArbol *p; struct infoString *infos; struct infoInt *infoi  ;

#line 292 "calc-sintaxis.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 309 "calc-sintaxis.tab.c" /* yacc.c:358  */

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
#define YYLAST   273

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

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
       0,   223,   223,   223,   225,   227,   229,   231,   235,   238,
     246,   257,   258,   261,   280,   297,   318,   340,   340,   342,
     343,   347,   347,   349,   351,   353,   355,   359,   360,   363,
     364,   380,   385,   399,   408,   418,   426,   432,   437,   444,
     446,   451,   453,   466,   483,   488,   489,   493,   509,   525,
     541,   557,   573,   589,   605,   621,   637,   654,   670,   686,
     687,   699,   700,   705,   714,   716,   725
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
  "UNARIO", "$accept", "program", "$@1", "clases", "var_decl", "listaID",
  "listamethod_decl", "method_decl", "param_decl", "$@2", "Nparam_decl",
  "block", "$@3", "Nblock", "listavar_decl", "listastatement", "type",
  "statement", "method_call", "param_call", "ultparam_call", "expr",
  "literal", "bool_literal", YY_NULLPTR
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
     -54,     4,    19,   -54,   -23,   -54,     0,    28,   -54,   -54,
     -54,   -54,    25,   -54,   116,    40,    36,   -54,   -54,    49,
     -54,   -54,   123,    42,    18,     3,    42,   -54,    47,    71,
     -54,   -54,    55,    50,   -54,    57,   -54,   -54,    51,   -54,
      65,    81,   -54,   -54,    56,   -54,   -54,    50,   -54,   -54,
      10,    64,   101,   124,   -54,   -54,   -54,    62,    75,    88,
     -54,    74,    99,    97,   124,   124,   -54,    85,   -54,   -54,
     124,   124,   -54,   124,   -54,   134,   -54,   -54,   198,   -54,
      90,   -54,   -54,   -54,   -54,   -54,   -54,    87,    93,   198,
     150,   166,   -54,   -54,   182,   124,   124,   124,   124,   124,
     -54,   124,   124,   124,   124,   124,   -54,   -54,   -54,   124,
     -54,   110,   -54,     9,     9,   -54,   -54,   -54,   243,   249,
     249,   229,   214,   198,   -54,   111,   -54,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     0,    31,    32,
       4,    27,     0,    11,     0,     0,     0,     6,    12,     0,
       5,    28,     0,     9,     0,    17,     0,     7,    17,     0,
       8,    21,     0,     0,    21,     0,    10,    16,     0,    21,
      18,     0,    14,    21,    21,    22,    15,     0,    19,    13,
       0,     0,     0,     0,    40,    26,    41,    21,    21,     0,
      29,     0,     0,     0,     0,     0,    63,    60,    65,    66,
       0,     0,    37,     0,    61,     0,    62,    64,    21,    24,
      21,    25,    30,     9,    39,    20,    42,     0,    44,    45,
       0,     0,    57,    58,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,    35,    23,    43,     0,
      38,     0,    59,    47,    48,    49,    50,    51,    54,    52,
      53,    55,    56,    46,    21,    33,    21,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -54,   -54,   -12,   -54,   118,    -3,   105,   -54,
     -54,   -31,   -54,   -54,    95,    83,   -11,   -53,   -37,   -54,
     -54,   -47,   -54,   -54
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,    11,    24,    12,    13,    32,    33,
      40,    56,    38,    45,    14,    58,    15,    60,    74,    87,
      88,    75,    76,    77
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      37,    19,    21,    42,     3,    82,    78,    61,    46,    18,
       6,    19,    49,     7,     8,     9,    89,    90,    91,    18,
      61,    61,    41,    92,    93,     4,    94,    82,    97,    31,
      98,    99,    16,    59,    10,    63,    62,    64,     7,     8,
       9,    29,    30,    61,    23,    21,    59,   106,   113,   114,
     115,   116,   117,    26,   118,   119,   120,   121,   122,    17,
      50,    25,   123,    51,     8,     9,    50,    28,    52,    51,
       8,     9,    53,    34,    52,    36,     8,     9,    53,    50,
      54,    39,    51,    43,    44,    48,    54,    52,    47,    65,
      55,    53,    83,   125,    50,   127,    79,    51,    84,    54,
      66,    67,    52,    85,    66,    67,    53,    68,    69,    81,
      63,    68,    69,   108,    54,    70,   109,    71,   124,    70,
     126,    71,    73,    86,   107,    72,    73,    66,    67,     7,
       8,     9,    22,    35,    68,    69,     7,     8,     9,    57,
      80,     0,    70,     0,    71,     0,     0,     0,     0,    73,
      20,    95,    96,    97,     0,    98,    99,    27,   100,     0,
       0,     0,   101,   102,   103,   104,   105,    95,    96,    97,
       0,    98,    99,     0,   110,     0,     0,     0,   101,   102,
     103,   104,   105,    95,    96,    97,     0,    98,    99,     0,
       0,     0,   111,     0,   101,   102,   103,   104,   105,    95,
      96,    97,     0,    98,    99,     0,     0,     0,   112,     0,
     101,   102,   103,   104,   105,    95,    96,    97,     0,    98,
      99,     0,     0,     0,     0,     0,   101,   102,   103,   104,
     105,    95,    96,    97,     0,    98,    99,     0,     0,     0,
       0,     0,   101,   102,   103,   104,    95,    96,    97,     0,
      98,    99,     0,     0,     0,     0,     0,   101,   102,   103,
      95,    96,    97,     0,    98,    99,    95,    96,    97,     0,
      98,    99,   102,   103
};

static const yytype_int8 yycheck[] =
{
      31,    12,    14,    34,     0,    58,    53,    44,    39,    12,
      33,    22,    43,    13,    14,    15,    63,    64,    65,    22,
      57,    58,    33,    70,    71,     6,    73,    80,    19,    26,
      21,    22,     4,    44,    34,    25,    47,    27,    13,    14,
      15,    23,    24,    80,     4,    57,    57,    78,    95,    96,
      97,    98,    99,     4,   101,   102,   103,   104,   105,    34,
       4,    25,   109,     7,    14,    15,     4,    25,    12,     7,
      14,    15,    16,    26,    12,     4,    14,    15,    16,     4,
      24,    26,     7,    26,    33,     4,    24,    12,    23,    25,
      34,    16,     4,   124,     4,   126,    34,     7,    24,    24,
       3,     4,    12,     4,     3,     4,    16,    10,    11,    34,
      25,    10,    11,    26,    24,    18,    23,    20,     8,    18,
       9,    20,    25,    26,    34,    24,    25,     3,     4,    13,
      14,    15,    14,    28,    10,    11,    13,    14,    15,    44,
      57,    -1,    18,    -1,    20,    -1,    -1,    -1,    -1,    25,
      34,    17,    18,    19,    -1,    21,    22,    34,    24,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    17,    18,    19,
      -1,    21,    22,    -1,    24,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    17,    18,    19,    -1,    21,    22,    -1,
      -1,    -1,    26,    -1,    28,    29,    30,    31,    32,    17,
      18,    19,    -1,    21,    22,    -1,    -1,    -1,    26,    -1,
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
      34,    40,    42,    43,    50,    52,     4,    34,    43,    52,
      34,    40,    42,     4,    41,    25,     4,    34,    25,    23,
      24,    26,    44,    45,    26,    44,     4,    47,    48,    26,
      46,    52,    47,    26,    33,    49,    47,    23,     4,    47,
       4,     7,    12,    16,    24,    34,    47,    50,    51,    52,
      53,    54,    52,    25,    27,    25,     3,     4,    10,    11,
      18,    20,    24,    25,    54,    57,    58,    59,    57,    34,
      51,    34,    53,     4,    24,     4,    26,    55,    56,    57,
      57,    57,    57,    57,    57,    17,    18,    19,    21,    22,
      24,    28,    29,    30,    31,    32,    47,    34,    26,    23,
      24,    26,    26,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,     8,    47,     9,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    38,    37,    39,    39,    39,    39,    40,    41,
      41,    42,    42,    43,    43,    43,    43,    45,    44,    46,
      46,    48,    47,    49,    49,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    54,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    58,    58,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     3,     4,     4,     5,     3,     1,
       3,     1,     2,     6,     5,     6,     5,     0,     2,     2,
       4,     0,     2,     4,     3,     3,     2,     1,     2,     1,
       2,     1,     1,     6,     8,     3,     3,     2,     4,     2,
       1,     1,     3,     4,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1
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
#line 223 "calc-sintaxis.y" /* yacc.c:1646  */
    {inicializar();}
#line 1501 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 223 "calc-sintaxis.y" /* yacc.c:1646  */
    {eliminarNivelPila();}
#line 1507 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 225 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("TERMINO1\n");}
#line 1513 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 227 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\nTERMINO2");}
#line 1519 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 229 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\nTERMINO3");}
#line 1525 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 231 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\nTERMINO4");}
#line 1531 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 235 "calc-sintaxis.y" /* yacc.c:1646  */
    {printf("\ndeclaracion de var finalizada");}
#line 1537 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 238 "calc-sintaxis.y" /* yacc.c:1646  */
    {     if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
                      printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
                    }else{
                      printf("linea %i VARIABLE %s YA DECLARADA!!! \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info  );
                      }

                    }
#line 1550 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 246 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
                    printf("%s\n","la variable no esta en el scope!!" );
                    nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
                  }else{
                    printf("linea %i VARIABLE %s YA DECLARADA!!! \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info  );
                    }
  }
#line 1563 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 257 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1569 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 258 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1575 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 261 "calc-sintaxis.y" /* yacc.c:1646  */
    {

  printf("declaracion de metodo2\n");
  NodoArbol *aux= malloc(sizeof(NodoArbol));

  aux->tipo=(yyvsp[-5].s);
  aux->tipoNodo=2;
  aux->nombre= (yyvsp[-4].infos)->info;
  aux->cuerpo = (yyvsp[0].p);
  aux->nrolinea =(yyvsp[-4].infos)->linea;
  aux->param = variableGlobalPila->lista;

  eliminarNivelPila();
  if(verificarMetodoDeclarado(aux->nombre)==1){
    printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
    exit(0);
  };
  (yyval.p) = aux;
}
#line 1599 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 280 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                printf("declaracion de metodo1\n");
                NodoArbol *aux= malloc(sizeof(NodoArbol));

                aux->tipo=(yyvsp[-4].s);
                aux->tipoNodo=2;
                aux->nombre= (yyvsp[-3].infos)->info;
                aux->cuerpo = (yyvsp[0].p);
                aux->nrolinea =(yyvsp[-3].infos)->linea;
                if(verificarMetodoDeclarado(aux->nombre)==1){
                  printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                  exit(0);
                };
                (yyval.p) = aux;
                }
#line 1619 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 297 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                    printf("declaracion de metodo4\n");

                                                    NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                    aux->tipo=NULL;
                                                    aux->tipoNodo=2;
                                                    aux->nombre= (yyvsp[-4].infos)->info;
                                                    aux->cuerpo = (yyvsp[0].p);
                                                    aux->nrolinea =(yyvsp[-4].infos)->linea;
                                                    aux->param = variableGlobalPila->lista;
                                                    if(verificarMetodoDeclarado(aux->nombre)==1){
                                                      printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                      exit(0);
                                                    };
                                                    eliminarNivelPila();


                                                    (yyval.p) = aux;

                                                  }
#line 1645 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 318 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                  printf("declaracion de metodo3\n");

                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo=NULL;
                                                  aux->tipoNodo=2;
                                                  aux->nombre= (yyvsp[-3].infos)->info;
                                                  aux->cuerpo = (yyvsp[0].p);
                                                  aux->nrolinea =(yyvsp[-3].infos)->linea;
                                                  if(verificarMetodoDeclarado(aux->nombre)==1){
                                                    printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                    exit(0);
                                                  };
                                                  (yyval.p) = aux;
                                                  }
#line 1666 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 340 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevoNivelPila();}
#line 1672 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 342 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevaVariable((yyvsp[0].infos)->info,(yyvsp[-1].s),(yyvsp[0].infos)->linea);}
#line 1678 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 343 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevaVariable((yyvsp[0].infos)->info,(yyvsp[-1].s),(yyvsp[-2].infos)->linea);}
#line 1684 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 347 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevoNivelPila();}
#line 1690 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 347 "calc-sintaxis.y" /* yacc.c:1646  */
    {eliminarNivelPila(); (yyval.p)=(yyvsp[0].p);}
#line 1696 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 349 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p)->first;}
#line 1702 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 351 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1708 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 353 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p)->first;}
#line 1714 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 355 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1720 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 359 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1726 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 360 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 1732 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 363 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->first=(yyvsp[0].p);(yyval.p)=(yyvsp[0].p);}
#line 1738 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 364 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[-1].p)->next = (yyvsp[0].p);
                            nodoauxiliar=(yyvsp[0].p);
                            nodoauxiliarAnt =nodoauxiliar;
                            while(nodoauxiliar!=NULL){
                              nodoauxiliar->first = (yyvsp[-1].p)->first; // mantenemos el primero de la lista en el atributo first
                              //para evitar una variable global, pq seria reescrita al haber
                              //bloques anidados, el ciclo permite el agregado de los statements de un bloque interno
                              nodoauxiliarAnt =nodoauxiliar;
                              nodoauxiliar=nodoauxiliar->next;
                            }

                            (yyval.p)=nodoauxiliarAnt;
                              }
#line 1756 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 380 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                aux="int";
                (yyval.s)=aux;
                }
#line 1765 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 385 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  aux="bool";
                  (yyval.s)=aux;
                  }
#line 1774 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 399 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                              NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                                              nuevo->tipoNodo=3;
                                                              nuevo->tcondicion = (yyvsp[-3].p);
                                                              nuevo->tthen = (yyvsp[0].p);
                                                              nuevo->nrolinea =(yyvsp[-5].i);
                                                              (yyval.p)=nuevo;
                                                            }
#line 1788 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 408 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                                        NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                                        nuevo->tipoNodo=4;
                                                                        nuevo->tcondicion = (yyvsp[-5].p);
                                                                        nuevo->tthen = (yyvsp[-2].p);
                                                                        nuevo->telse = (yyvsp[0].p);
                                                                        nuevo->nrolinea =(yyvsp[-7].i);
                                                                        (yyval.p)=nuevo;
                                                                      }
#line 1802 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 418 "calc-sintaxis.y" /* yacc.c:1646  */
    {          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=5;
                                        nuevo->tcondicion = (yyvsp[-1].p);
                                        nuevo->cuerpo = (yyvsp[0].p);
                                        nuevo->nrolinea =(yyvsp[-2].i);
                                        (yyval.p)=nuevo;
                                      }
#line 1814 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 426 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=6;
                                        nuevo->expresion = (yyvsp[-1].p);
                                        nuevo->nrolinea =(yyvsp[-2].i);
                                        (yyval.p)=nuevo;
                                      }
#line 1825 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 432 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=7;
                                        nuevo->nrolinea =(yyvsp[-1].i);
                                        (yyval.p)=nuevo;
                                      }
#line 1835 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 437 "calc-sintaxis.y" /* yacc.c:1646  */
    {   NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=8;
                                        nuevo->nombre=(yyvsp[-3].infos)->info;
                                        nuevo->expresion = (yyvsp[-1].p);
                                        nuevo->nrolinea =(yyvsp[-2].infos)->linea;
                                        (yyval.p)=nuevo;
                                      }
#line 1847 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 444 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p);}
#line 1853 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 446 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=10;
                                        nuevo->nrolinea =(yyvsp[0].infos)->linea;
                                        (yyval.p)=nuevo;
                                      }
#line 1863 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 451 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 1869 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 453 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                nuevo->tipoNodo=9;
                                                nuevo->call_metodo = buscarMetodo((yyvsp[-2].infos)->info);
                                                nuevo->nrolinea =(yyvsp[-2].infos)->linea;
                                                if(nuevo->call_metodo == NULL){
                                                  printf("ERROR en linea %i : llamada metodo no declarado previamente \n",nuevo->nrolinea );
                                                  exit(0);
                                                }
                                                nuevo->tipo=(nuevo->call_metodo)->tipo;
                                                (yyval.p)=nuevo;

                                                }
#line 1887 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 466 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                nuevo->tipoNodo=9;
                                                nuevo->call_metodo = buscarMetodo((yyvsp[-3].infos)->info);
                                                nuevo->nrolinea =(yyvsp[-3].infos)->linea;
                                                if(nuevo->call_metodo == NULL){
                                                  printf("ERROR en linea %i : llamada metodo no declarado previamente \n",nuevo->nrolinea );
                                                  exit(0);
                                                }
                                                nuevo->call_params =(yyvsp[-1].p);
                                                nuevo->tipo=nuevo->call_metodo->tipo;
                                                (yyval.p)=nuevo;

                                                }
#line 1906 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 483 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p)->first;}
#line 1912 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 488 "calc-sintaxis.y" /* yacc.c:1646  */
    { (yyvsp[0].p)->first=(yyvsp[0].p); (yyval.p)=(yyvsp[0].p);  }
#line 1918 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 489 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->first=(yyvsp[-2].p)->first; (yyvsp[-2].p)->next = (yyvsp[0].p); (yyval.p)=(yyvsp[0].p);  }
#line 1924 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 493 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                      NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                      nuevo->tipoNodo=14;
                      nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                      nuevo->nombre= (yyvsp[-1].infos)->info;
                      nuevo->op1 = (yyvsp[-2].p);
                      nuevo->op2 = (yyvsp[0].p);
                      int error = mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p));
                      if(error == 0){
                        nuevo->tipo = "int";
                      }else{
                          printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                          exit(0);
                      }
                      (yyval.p)=nuevo;
                      }
#line 1945 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 509 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);
                          int error = mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p));
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 1966 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 525 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);
                          int error = mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p));
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 1987 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 541 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);
                          int error = mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p));
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 2008 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 557 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);
                          int error = mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p));
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 2029 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 573 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);
                          int error = mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p));
                          if(error == 0){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 2050 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 589 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);
                          int error = mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p));
                          if(error == 0){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 2071 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 605 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);

                          if(mismoTipoINT((yyvsp[-2].p),(yyvsp[0].p)) == 0 ||mismoTipoBOOL((yyvsp[-2].p),(yyvsp[0].p)) == 0 ){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : operandos de distintos tipos \n",nuevo->nrolinea);
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 2092 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 621 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                          nuevo->nombre= (yyvsp[-1].infos)->info;
                          nuevo->op1 = (yyvsp[-2].p);
                          nuevo->op2 = (yyvsp[0].p);
                          int error = mismoTipoBOOL((yyvsp[-2].p),(yyvsp[0].p));
                          if(error == 0){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          (yyval.p)=nuevo;
                          }
#line 2113 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 637 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=14;
                                  nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                                  nuevo->nombre= (yyvsp[-1].infos)->info;
                                  nuevo->op1 = (yyvsp[-2].p);
                                  nuevo->op2 = (yyvsp[0].p);
                                  int error = mismoTipoBOOL((yyvsp[-2].p),(yyvsp[0].p));
                                  if(error == 0){
                                    nuevo->tipo = "bool";
                                  }else{
                                      printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                                      exit(0);
                                  }
                                  (yyval.p)=nuevo;
                                  }
#line 2134 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 654 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=15;
                                  nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                                  nuevo->nombre= (yyvsp[-1].infos)->info;
                                  nuevo->op1 = (yyvsp[0].p);


                                  if(strcmp((yyvsp[0].p)->tipo,"int") == 0){
                                    nuevo->tipo = "int";
                                  }else{
                                      printf("ERROR en linea %i : error de tipo en operando (no es un entero)   \n",nuevo->nrolinea);
                                      exit(0);
                                  }
                                  (yyval.p)=nuevo;
                                  }
#line 2155 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 670 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=15;
                                  nuevo->nrolinea =(yyvsp[-1].infos)->linea;
                                  nuevo->nombre= (yyvsp[-1].infos)->info;
                                  nuevo->op1 = (yyvsp[0].p);


                                  if(strcmp((yyvsp[0].p)->tipo,"bool") == 0){
                                    nuevo->tipo = "bool";
                                  }else{
                                      printf("ERROR en linea %i : error de tipo en operando (no es un booleano)   \n",nuevo->nrolinea);
                                      exit(0);
                                  }
                                  (yyval.p)=nuevo;
                                  }
#line 2176 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 686 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p);}
#line 2182 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 687 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=16;
                                  nuevo->nrolinea =(yyvsp[0].infos)->linea;
                                  nuevo->op1 = buscarVariable((yyvsp[0].infos)->info);
                                  if(nuevo->op1 == NULL){
                                    printf("ERROR en linea %i : variable %s no declarada  \n",nuevo->nrolinea,(yyvsp[0].infos)->info);
                                    exit(0);
                                  }
                                  nuevo->tipo = nuevo->op1->tipo;
                                  (yyval.p)=nuevo;
                                  }
#line 2199 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 699 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 2205 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 700 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 2211 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 705 "calc-sintaxis.y" /* yacc.c:1646  */
    {
              NodoArbol *nuevo= malloc(sizeof(NodoArbol));
              nuevo->tipo="int";
              nuevo->tipoNodo=12;
              nuevo->valor= (yyvsp[0].infoi)->info;
              nuevo->nrolinea =(yyvsp[0].infoi)->linea;
              (yyval.p)=nuevo;
              }
#line 2224 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 714 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 2230 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 716 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                    nuevo->tipo="bool";
                    nuevo->tipoNodo=13;
                    nuevo->valor= 1;
                    nuevo->nrolinea =(yyvsp[0].i);
                    (yyval.p)=nuevo;
                  }
#line 2243 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 725 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                  nuevo->tipo="bool";
                  nuevo->tipoNodo=13;
                  nuevo->valor=0;
                  nuevo->nrolinea =(yyvsp[0].i);
                  (yyval.p)=nuevo;
                }
#line 2256 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;


#line 2260 "calc-sintaxis.tab.c" /* yacc.c:1646  */
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
#line 736 "calc-sintaxis.y" /* yacc.c:1906  */

