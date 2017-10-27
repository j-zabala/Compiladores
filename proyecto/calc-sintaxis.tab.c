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
#include "nodosIntermedio.c"
#include <time.h>
#include <stdbool.h>


NodoPila *variableGlobalPila;
NodoArbol *listametodos;

NodoInt* codigoIntermedio;
NodoInt* ultcodigoIntermedio;

int cantidadTemporales;
int cantidadLabels;

void imprimirNodo(NodoArbol *nodo);//como el forward de pascal

NodoArbol* pasarACodIntermedio(NodoArbol* nodo);


void agregarCodIntermedio(NodoInt* nuevo);



void loadParametros(NodoArbol* parameters){
  if(parameters==NULL){ return; }
  NodoInt* aux=malloc(sizeof(NodoInt));
  aux->operacion="LOADP";
  aux->nombre=parameters->nombre;
  aux->op1=pasarACodIntermedio(parameters);
  agregarCodIntermedio(aux);
  loadParametros(parameters->nextlista);
}

void agregarCodIntermedio(NodoInt* nuevo){
  if(nuevo==NULL){
    return;
  }
  if (codigoIntermedio==NULL){
    codigoIntermedio = nuevo;

  }else{
    ultcodigoIntermedio->next=nuevo;
  }

  ultcodigoIntermedio = nuevo;

}

void metodoAIntermedio(NodoArbol* nodo){
  if(nodo==NULL){
    return;
  }
  if(nodo->tipoNodo!=2){
    printf("ERROR EL NODO PASADO NO ES UN METODO\n");
    exit(0);
  }
  NodoInt* nuevo = malloc(sizeof(NodoInt));
  nuevo->nombre = nodo->nombre;
  nuevo->operacion = "METODO";
  agregarCodIntermedio(nuevo);

  pasarACodIntermedio(nodo->cuerpo);

  nuevo = malloc(sizeof(NodoInt));
  nuevo->nombre = nodo->nombre;
  nuevo->operacion = "ENDMETODO";
  agregarCodIntermedio(nuevo);


}

char* nuevoLabel(char* info){
  char* aux;
  aux=(char*)malloc(sizeof(char)*20);
  sprintf(aux,"LAB%d%s",cantidadLabels++,info);
  return aux;
}


NodoArbol* nuevaVariableTemporal(char* tipo){
  NodoArbol* nuevo = malloc(sizeof(NodoArbol));
  nuevo->nombre=(char*)malloc(sizeof(char)*10);
  sprintf(nuevo->nombre,"T%d",cantidadTemporales);
  cantidadTemporales++;
  nuevo->tipo=tipo;
  printf("SE CREO LA VARIABLE %s tipo %s\n",nuevo->nombre,nuevo->tipo );
  return nuevo;
}


NodoArbol* pasarACodIntermedio(NodoArbol* nodo){
  if(nodo == NULL){
    printf("null pasarACodIntermedio\n");
    return NULL;}
  printf("despues del null en pasarACodIntermedio\n");
  imprimirNodo(nodo);
  NodoInt* nuevo;
  char* lab1;
  char* lab2;
  if(nodo->tipoNodo==2){ //declaracion de funcion
    metodoAIntermedio(nodo);
  }
  if(nodo->tipoNodo==3||nodo->tipoNodo==4){
    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion = "JMPFalso";
    nuevo->op1 = pasarACodIntermedio(nodo->tcondicion);
    char* labELSE = nuevoLabel("ELSE");
    char* labF = nuevoLabel("ENDIF");
    nuevo->nombre = labELSE;
    agregarCodIntermedio(nuevo);

    pasarACodIntermedio(nodo->tthen); //agrega cod intermedio del then

    nuevo = malloc(sizeof(NodoInt));
    nuevo->operacion = "JMP";        //agrega el JMP al final de el if
    nuevo->nombre =labF;
    agregarCodIntermedio(nuevo);

    nuevo = malloc(sizeof(NodoInt));
    nuevo->operacion = "LABEL"; // agrega el label al que se salta por si no cumple la cond
    nuevo->nombre =labELSE;
    agregarCodIntermedio(nuevo);

    pasarACodIntermedio(nodo->telse);//agrega cod intermedio del else

    nuevo = malloc(sizeof(NodoInt));
    nuevo->operacion = "LABEL"; // agrega el label que marca el fin del if
    nuevo->nombre =labF;
    agregarCodIntermedio(nuevo);
  }


  if(nodo->tipoNodo==5){
    lab1 = nuevoLabel("WHILE");
    lab2 = nuevoLabel("ENDWHILE");
    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion="LABEL";
    nuevo->nombre = lab1;
    agregarCodIntermedio(nuevo);

    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion = "JMPFalso";
    nuevo->op1 = pasarACodIntermedio(nodo->tcondicion);
    nuevo->nombre= lab2;
    agregarCodIntermedio(nuevo);

    pasarACodIntermedio(nodo->cuerpo);

    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion = "JMP";
    nuevo->nombre= lab1;
    agregarCodIntermedio(nuevo);

    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion="LABEL";
    nuevo->nombre = lab2;
    agregarCodIntermedio(nuevo);
  }

  if(nodo->tipoNodo==6||nodo->tipoNodo==7){
    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion = "RETURN";
    if(nodo->tipoNodo==6){
      nuevo->op1 = pasarACodIntermedio(nodo->expresion);
    }

    agregarCodIntermedio(nuevo);
  }

  if(nodo->tipoNodo==8){
    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion = "MOV";
    nuevo->op2 = pasarACodIntermedio(nodo->expresion);
    nuevo->op1= nodo->op1;
    agregarCodIntermedio(nuevo);
  }

  if(nodo->tipoNodo==9){
    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion = "CALL";
    printf("\nhacemos el nodo call: el nombre del nodo es :%s\n",nodo->nombre);
    nuevo->nombre= (nodo->call_metodo)->nombre;
    //ver si apuntamos al metodo
    loadParametros(nodo->call_params);
    agregarCodIntermedio(nuevo);
  }
  //literal entero
  if(nodo->tipoNodo==12||nodo->tipoNodo==13){
    NodoArbol *temp=nuevaVariableTemporal(nodo->tipo);
    nuevo= malloc(sizeof(NodoInt));
    nuevo->operacion = "MOV";
    nuevo->op1 = temp;
    nuevo->op2 = nodo;
    agregarCodIntermedio(nuevo);
    return temp;
  }

if(nodo->tipoNodo==14){
    NodoArbol* temp1 = pasarACodIntermedio(nodo->op1);
    NodoArbol* temp2 = pasarACodIntermedio(nodo->op2);
    NodoArbol* res = nuevaVariableTemporal(nodo->tipo);
    nuevo= malloc(sizeof(NodoInt));

    nuevo->op1=temp1;
    nuevo->op2=temp2;
    nuevo->op3=res;

    if(strcmp("*",nodo->nombre)==0){
      nuevo->operacion="MULT";
    }
    if(strcmp("+",nodo->nombre)==0){
      nuevo->operacion="SUM";
    }
    if(strcmp("/",nodo->nombre)==0){
      nuevo->operacion="DIV";
    }
    if(strcmp("%",nodo->nombre)==0){
      nuevo->operacion="MOD";
    }
    if(strcmp(">",nodo->nombre)==0){
      nuevo->operacion="MAYORQUE";
    }
    if(strcmp("<",nodo->nombre)==0){
      nuevo->operacion="MENORQUE";
    }
    if(strcmp("==",nodo->nombre)==0){
      nuevo->operacion="IGUAL";
    }
    agregarCodIntermedio(nuevo);
    return res;
}
  if(nodo->tipoNodo==15){
    NodoArbol* temp1 = pasarACodIntermedio(nodo->op1);
    NodoArbol* res = nuevaVariableTemporal(nodo->tipo);
    nuevo= malloc(sizeof(NodoInt));
    nuevo->op1=temp1;
    nuevo->op3=res;
    if(strcmp("!",nodo->nombre)==0){
      nuevo->operacion="NEGBOOL";
    }
    if(strcmp("-",nodo->nombre)==0){
      nuevo->operacion="NEGINT";
    }
    agregarCodIntermedio(nuevo);
    return res;

  }
  if(nodo->tipoNodo==16){
    return nodo->op1;

  }
  //avanza a la siguiente sentencia
  if(nodo->next!=NULL){
    pasarACodIntermedio(nodo->next);
  }
/*  if(nodo->next==NULL){ //guarda la ultima instruccion de la list de codigo intermedio
    ultcodigoIntermedio=nodo;
  }*/
  return NULL;
};

void imprimirLista(NodoInt* nodo){
  printf("\n");
  if(nodo!=NULL){
    //   printf("DENTRO DE IMPRIMIR\n");
    //  if(nodo->tipoNodo!=NULL){
    //    printf("TIPO NODO: %i\n", nodo->tipoNodo);
    //  }

    // if(nodo->tipo!=NULL){
    //   printf("TIPO: %s\n", nodo->tipo);
    // }
    if(nodo->operacion!=NULL){
      printf("%s ", nodo->operacion);
    }
    if(nodo->nombre!=NULL){
      printf("(%s) ", nodo->nombre);
    }
    if(nodo->op1!=NULL){
        printf(" ");
        imprimirNodo(nodo->op1);
    }
    if(nodo->op2!=NULL){
        printf(" ");
        imprimirNodo(nodo->op2);
    }
    if(nodo->op3!=NULL){
        printf(" ");
        imprimirNodo(nodo->op3);
    }
    if (nodo->next!=NULL){
      imprimirLista(nodo->next);
    }
  }
}




void imprimirNodo(NodoArbol *nodo){
  // printf("nodo en la direccion: %p \n",nodo);
  // printf("TIPO NODO= %i \n", nodo->tipoNodo);

  // if(nodo->tcondicion!=NULL){
  //
  //   imprimirNodo(nodo->tcondicion);
  // }
  // if(nodo->tthen!=NULL){
  //   imprimirNodo(nodo->tthen);
  // }
  // if(nodo->telse!=NULL){
  //   imprimirNodo(nodo->telse);
  // }
  // if(nodo->expresion!=NULL){
  //   imprimirNodo(nodo->expresion);
  // }
  //
  // if(nodo->param!=NULL){
  //   imprimirNodo(nodo->param);
  // }
  // if(nodo->call_params!=NULL){
  //   imprimirNodo(nodo->call_params);
  // }
  // if(nodo->call_metodo!=NULL){
  //   imprimirNodo(nodo->call_metodo);
  // }
  // if(nodo->first!=NULL){
  //   printf("dir de mem del first %p \n",nodo->first);
  // }
  // if(nodo->tipo!=NULL){
  //   printf("TIPO= %s\n", nodo->tipo);
  // }
  if(nodo->nombre!=NULL){
    printf(" %s", nodo->nombre);
  }
  // if(nodo->valorExpresion!=NULL){
  //   imprimirNodo(nodo->valorExpresion);
  // }
  // if(nodo->op1!=NULL){
  //   imprimirNodo(nodo->op1);
  // }
  // if(nodo->op2!=NULL){
  //   imprimirNodo(nodo->op2);
  // }
  if((nodo->valor)!=NULL){
    printf(" %i", nodo->valor);
  }
  // if((nodo->nrolinea)!=NULL){
  //   printf("NUMERO DE LINEA= %i\n", nodo->nrolinea);
  // }
  //
  // printf("el next de este nodo es %p \n",nodo->next);

}

void imprimirmetodos(){
  printf("imprimir metodos \n");

  NodoArbol *metodo = listametodos ;
  NodoArbol *recorrido = metodo->cuerpo ;
  while(metodo!=NULL){
    printf("vamos a imprimir metodo con nombre: %s\n",metodo->nombre);
    while (recorrido != NULL) {
      printf("recorrido = %p\n",recorrido );
      imprimirNodo(recorrido);
      recorrido = recorrido->next;
    }

    metodo=metodo->nextlista;
    if (metodo !=NULL){
      recorrido = metodo->cuerpo;

    }
  }
}


void nuevoNivelPila(){
 NodoPila *aux = malloc(sizeof(NodoPila));
 aux->lista = NULL;
 aux->nodoInferior=variableGlobalPila;
 //printf("se crea nivel nuevo (dir: %p), inferior %p \n ", aux, variableGlobalPila);
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
  cantidadTemporales=0;
  cantidadLabels=0;
  listametodos=NULL;

  variableGlobalPila = (NodoPila*) malloc(sizeof(NodoPila));
  variableGlobalPila->nodoInferior=NULL;
  //printf("dir de mem del inferior al global %p \n",variableGlobalPila->nodoInferior);


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

  // printf("VAMOS A IMPRIMIR LA TABLA DE VARIABLES\n");

  NodoPila *scope = variableGlobalPila;
  NodoArbol *recorrido = scope->lista;
  while(scope != NULL){
    // printf("NIVEL CON PUNTERO: %p\n",scope );
    while(recorrido != NULL){
    //  printf("%s %s | ",recorrido->tipo,recorrido->nombre);
     recorrido = recorrido->nextlista;
    }
    // printf("\n------------------------------------------\n" );
    scope=scope->nodoInferior;
    if (scope !=NULL){
      recorrido = scope->lista;
    }

  }
  // printf("termino de impriir la tabla\n");
  scope = variableGlobalPila;
  recorrido = scope->lista;
while(scope != NULL){
  while(recorrido != NULL){
    // printf("se va a buscar la variable %s\n",param);
  //  printf("se va a comparar %s con %s \n",param,recorrido->nombre);
   if(strcmp(recorrido->nombre,param)==0){
     return recorrido;
   }
   recorrido = recorrido->nextlista;
  }
  scope=scope->nodoInferior;
  if (scope !=NULL){
    recorrido = scope->lista;
  }
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



int verifTipos(char* param_tipo,char* nombre_metodo,NodoArbol* primernodo);

int verifTiposif(char* paramtipo,char* nombre_metodo,NodoArbol* nodo){
  if(strcmp((nodo->tcondicion)->tipo,"bool")!=0){
    printf("ERROR linea %i: la condicion del if no es una expresion booleana \n",nodo->nrolinea);
  }
  if(verifTipos(paramtipo,nombre_metodo,nodo->tthen)>0 &&verifTipos(paramtipo,nombre_metodo,nodo->telse)>0 ){return 1;}


}

int verifTiposRet(char* paramtipo,char* nombre_metodo,NodoArbol* nodo){
  if(strcmp(nodo->tipo,paramtipo)!=0){
    printf("ERROR linea %i: el tipo del return no coincide con el de la funcion \n",nodo->nrolinea);
    exit(0);
  }
  return 1;
}
int verifTipos(char* param_tipo,char* nombre_metodo,NodoArbol* primernodo){
  int cant_ret_correctos=0;
  NodoArbol* recorrido = primernodo;
  // printf("recorrido de statements en el main \n ");
  while(recorrido!=NULL){
    // printf("nodo actual es:%i \n",recorrido->tipoNodo);
    if(recorrido->tipoNodo==4){
      // printf("va a verificar en los if\n" );
      cant_ret_correctos=cant_ret_correctos+verifTiposif(param_tipo,nombre_metodo,recorrido);
    }
    if(recorrido->tipoNodo==6||recorrido->tipoNodo==7){
      cant_ret_correctos=cant_ret_correctos+verifTiposRet(param_tipo,nombre_metodo,recorrido);
    }
    recorrido=recorrido->next;
  }

  if (cant_ret_correctos==0){
    printf("ERROR: la funcion %s posee flujos de ejecucion sin return\n", nombre_metodo);
    exit(0);
  }
  return cant_ret_correctos;
}


void controlTiposMetod(){
  NodoArbol* metodo = listametodos;
  while(metodo!=NULL){
    verifTipos(metodo->tipo,metodo->nombre,metodo->cuerpo);
    //metodo=metodo->nextlista;
    metodo=NULL;
  }


}

void verificarTipoParametros(NodoArbol* nodo){
    NodoArbol* metodo = nodo->call_metodo;

    NodoArbol *recorridollamada = nodo->call_params;
    NodoArbol *recorridodecl = metodo->param;
    while(recorridollamada!=NULL && recorridodecl!=NULL){
      if(strcmp(recorridodecl->tipo,recorridollamada->tipo)!=0){
        printf("ERROR linea %i : un parametro no es del tipo correcto\n",nodo->nrolinea );
        exit(0);
      }
      recorridollamada=recorridollamada->next;
      recorridodecl=recorridodecl->nextlista;
    }
    if(recorridodecl!=recorridollamada){
      printf("ERROR linea %i : no se esta llamando a la funcion con la cantidad de parametros correcta\n",nodo->nrolinea );
      exit(0);
    }

}

void codIntermedio(NodoArbol* nodo){
  NodoArbol* aux=nodo;
  while (aux!=NULL) {
    pasarACodIntermedio(aux);
    printf("aux:%p \n",aux );
    aux=aux->nextlista;
  }
}

bool verficarMain(NodoArbol* listMeth){
  NodoArbol* recorrido=listMeth;
  int cantMain=0;
  while (recorrido!=NULL) {
    if(strcmp(recorrido->nombre,"main")==0){
      cantMain++;
    }
    recorrido=recorrido->nextlista;
  }
  if(cantMain==0){
    printf("ERROR: el programa no tiene definido un metodo 'main', y debe tener unicamente uno.\n");
    exit(0);
  }
}


char *aux;

NodoArbol *nodoauxiliar ; //este puntero apunta al primer statement cuando se arma la lista de los statements
NodoArbol *nodoauxiliarAnt ; // lo usamos para guardar el nodo anterior al nodoauxiliar

#line 708 "calc-sintaxis.tab.c" /* yacc.c:339  */

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
#line 643 "calc-sintaxis.y" /* yacc.c:355  */
 int i; char *s; char c; struct nodoArbol *p; struct infoString *infos; struct infoInt *infoi  ;

#line 787 "calc-sintaxis.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 804 "calc-sintaxis.tab.c" /* yacc.c:358  */

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
#define YYLAST   291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

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
       0,   718,   718,   718,   731,   735,   739,   743,   749,   754,
     762,   773,   774,   777,   796,   813,   834,   856,   856,   858,
     859,   863,   863,   865,   867,   869,   871,   875,   876,   879,
     880,   896,   901,   915,   924,   934,   943,   950,   956,   974,
     976,   981,   983,   998,  1016,  1021,  1022,  1026,  1042,  1058,
    1074,  1090,  1106,  1122,  1138,  1154,  1170,  1187,  1203,  1219,
    1220,  1233,  1234,  1239,  1248,  1250,  1259
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

#define YYPACT_NINF -55

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-55)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -55,     2,    17,   -55,   -12,   -55,    18,    22,   -55,   -55,
     -55,   -55,    25,   -55,   125,    32,     9,   -55,   -55,    54,
     -55,   -55,   128,    37,    30,    39,    37,   -55,    40,    59,
     -55,   -55,    41,    15,   -55,    42,   -55,   -55,    44,   -55,
      51,    76,   -55,   -55,    57,   -55,   -55,    15,   -55,   -55,
      -5,    64,   108,    74,   -55,   -55,   -55,    71,    72,    78,
     -55,    79,   100,    97,   126,   126,   -55,    84,   -55,   -55,
     126,   126,   -55,   126,   -55,   136,   -55,   -55,   126,   -55,
      86,   -55,   -55,   -55,   -55,   -55,   -55,    87,    91,   216,
     152,   168,   -55,   -55,   184,   126,   126,   126,   126,   126,
     -55,   126,   126,   126,   126,   126,   200,   -55,   -55,   126,
     -55,   113,   -55,   -15,   -15,   -55,   -55,   -55,   261,   267,
     267,   247,   232,   -55,   216,   -55,   -55,   107,   -55,   -55
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
       0,     0,    37,     0,    61,     0,    62,    64,     0,    24,
      21,    25,    30,     9,    39,    20,    42,     0,    44,    45,
       0,     0,    57,    58,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,    23,    43,     0,
      38,     0,    59,    47,    48,    49,    50,    51,    54,    52,
      53,    55,    56,    21,    46,    21,    35,    33,    21,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -55,   -55,    -1,   -55,   110,     6,    99,   -55,
     -55,   -31,   -55,   -55,    81,    77,    13,   -53,   -43,   -55,
     -55,   -54,   -55,   -55
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
      37,    61,     3,    42,    97,    82,    98,    99,    46,    89,
      90,    91,    49,    21,    61,    61,    92,    93,    18,    94,
      63,     6,    64,     4,   106,    19,    16,    82,    18,     8,
       9,     7,     8,     9,    25,    19,    23,    61,     7,     8,
       9,   113,   114,   115,   116,   117,    41,   118,   119,   120,
     121,   122,    10,    29,    30,   124,    21,    59,    26,    17,
      62,    50,    28,    36,    51,    31,    34,    39,    43,    52,
      59,     8,     9,    53,    47,    50,    50,    44,    51,    51,
      48,    54,    83,    52,    52,     8,     9,    53,    53,    65,
      50,    55,   126,    51,   127,    54,    54,   129,    52,    78,
      66,    67,    53,    84,    85,    79,    81,    68,    69,    63,
      54,    66,    67,   108,   109,    70,   128,    71,    68,    69,
     107,   125,    73,    86,    22,    57,    70,    35,    71,    66,
      67,     0,    72,    73,    80,     0,    68,    69,     7,     8,
       9,     7,     8,     9,    70,     0,    71,     0,     0,     0,
       0,    73,     0,    95,    96,    97,     0,    98,    99,    20,
     100,     0,    27,     0,   101,   102,   103,   104,   105,    95,
      96,    97,     0,    98,    99,     0,   110,     0,     0,     0,
     101,   102,   103,   104,   105,    95,    96,    97,     0,    98,
      99,     0,     0,     0,   111,     0,   101,   102,   103,   104,
     105,    95,    96,    97,     0,    98,    99,     0,     0,     0,
     112,     0,   101,   102,   103,   104,   105,    95,    96,    97,
       0,    98,    99,     0,     0,     0,   123,     0,   101,   102,
     103,   104,   105,    95,    96,    97,     0,    98,    99,     0,
       0,     0,     0,     0,   101,   102,   103,   104,   105,    95,
      96,    97,     0,    98,    99,     0,     0,     0,     0,     0,
     101,   102,   103,   104,    95,    96,    97,     0,    98,    99,
       0,     0,     0,     0,     0,   101,   102,   103,    95,    96,
      97,     0,    98,    99,    95,    96,    97,     0,    98,    99,
     102,   103
};

static const yytype_int16 yycheck[] =
{
      31,    44,     0,    34,    19,    58,    21,    22,    39,    63,
      64,    65,    43,    14,    57,    58,    70,    71,    12,    73,
      25,    33,    27,     6,    78,    12,     4,    80,    22,    14,
      15,    13,    14,    15,    25,    22,     4,    80,    13,    14,
      15,    95,    96,    97,    98,    99,    33,   101,   102,   103,
     104,   105,    34,    23,    24,   109,    57,    44,     4,    34,
      47,     4,    25,     4,     7,    26,    26,    26,    26,    12,
      57,    14,    15,    16,    23,     4,     4,    33,     7,     7,
       4,    24,     4,    12,    12,    14,    15,    16,    16,    25,
       4,    34,   123,     7,   125,    24,    24,   128,    12,    25,
       3,     4,    16,    24,     4,    34,    34,    10,    11,    25,
      24,     3,     4,    26,    23,    18,     9,    20,    10,    11,
      34,     8,    25,    26,    14,    44,    18,    28,    20,     3,
       4,    -1,    24,    25,    57,    -1,    10,    11,    13,    14,
      15,    13,    14,    15,    18,    -1,    20,    -1,    -1,    -1,
      -1,    25,    -1,    17,    18,    19,    -1,    21,    22,    34,
      24,    -1,    34,    -1,    28,    29,    30,    31,    32,    17,
      18,    19,    -1,    21,    22,    -1,    24,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    17,    18,    19,    -1,    21,
      22,    -1,    -1,    -1,    26,    -1,    28,    29,    30,    31,
      32,    17,    18,    19,    -1,    21,    22,    -1,    -1,    -1,
      26,    -1,    28,    29,    30,    31,    32,    17,    18,    19,
      -1,    21,    22,    -1,    -1,    -1,    26,    -1,    28,    29,
      30,    31,    32,    17,    18,    19,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    17,
      18,    19,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    17,    18,    19,    -1,    21,    22,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    17,    18,
      19,    -1,    21,    22,    17,    18,    19,    -1,    21,    22,
      29,    30
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
      18,    20,    24,    25,    54,    57,    58,    59,    25,    34,
      51,    34,    53,     4,    24,     4,    26,    55,    56,    57,
      57,    57,    57,    57,    57,    17,    18,    19,    21,    22,
      24,    28,    29,    30,    31,    32,    57,    34,    26,    23,
      24,    26,    26,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    26,    57,     8,    47,    47,     9,    47
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
       2,     1,     1,     6,     8,     5,     3,     2,     4,     2,
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
#line 718 "calc-sintaxis.y" /* yacc.c:1646  */
    {
      inicializar();}
#line 2001 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 719 "calc-sintaxis.y" /* yacc.c:1646  */
    {eliminarNivelPila();
        controlTiposMetod();
        verficarMain(listametodos);
        printf("ANTES DE CODIGO intermedio\n");
        if(listametodos==NULL){
          printf("listametodos es NULL\n");
        }
        codIntermedio(listametodos);
        printf("DESPUES DE CODIGO intermedio\n");
        imprimirLista(codigoIntermedio);
    }
#line 2017 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 731 "calc-sintaxis.y" /* yacc.c:1646  */
    {
  // printf("TERMINO1\n");
}
#line 2025 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 735 "calc-sintaxis.y" /* yacc.c:1646  */
    {
    // printf("\nTERMINO2");
}
#line 2033 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 739 "calc-sintaxis.y" /* yacc.c:1646  */
    {
    // printf("\nTERMINO3");
  }
#line 2041 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 743 "calc-sintaxis.y" /* yacc.c:1646  */
    {
    // printf("\nTERMINO4");
  }
#line 2049 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 749 "calc-sintaxis.y" /* yacc.c:1646  */
    {
  // printf("\ndeclaracion de var finalizada");
}
#line 2057 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 754 "calc-sintaxis.y" /* yacc.c:1646  */
    {     if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
                      // printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
                    }else{
                      printf("ERROR linea %i; la variable %s ya esta declarada \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info  );
                      }

                    }
#line 2070 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 762 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
                  //  printf("%s\n","la variable no esta en el scope!!" );
                    nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
                  }else{
                    printf("ERROR linea %i; la variable %s ya esta declarada \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info  );
                    }
  }
#line 2083 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 773 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->nextlista=listametodos;listametodos=(yyvsp[0].p);}
#line 2089 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 774 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->nextlista=listametodos;listametodos=(yyvsp[0].p);}
#line 2095 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 777 "calc-sintaxis.y" /* yacc.c:1646  */
    {

  // printf("declaracion de metodo2\n");
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
#line 2119 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 796 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                // printf("declaracion de metodo1\n");
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
#line 2139 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 813 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                    // printf("declaracion de metodo4\n");

                                                    NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                    aux->tipo="void";
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
#line 2165 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 834 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                  // printf("declaracion de metodo3\n");

                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo="void";
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
#line 2186 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 856 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevoNivelPila();}
#line 2192 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 858 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevaVariable((yyvsp[0].infos)->info,(yyvsp[-1].s),(yyvsp[0].infos)->linea);}
#line 2198 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 859 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevaVariable((yyvsp[0].infos)->info,(yyvsp[-1].s),(yyvsp[-2].infos)->linea);}
#line 2204 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 863 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevoNivelPila();}
#line 2210 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 863 "calc-sintaxis.y" /* yacc.c:1646  */
    {eliminarNivelPila(); (yyval.p)=(yyvsp[0].p);}
#line 2216 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 865 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p)->first;}
#line 2222 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 867 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2228 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 869 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p)->first;}
#line 2234 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 871 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2240 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 875 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2246 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 876 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2252 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 879 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->first=(yyvsp[0].p);(yyval.p)=(yyvsp[0].p);}
#line 2258 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 880 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2276 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 896 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                aux="int";
                (yyval.s)=aux;
                }
#line 2285 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 901 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  aux="bool";
                  (yyval.s)=aux;
                  }
#line 2294 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 915 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                              NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                                              nuevo->tipoNodo=3;
                                                              nuevo->tcondicion = (yyvsp[-3].p);
                                                              nuevo->tthen = (yyvsp[0].p);
                                                              nuevo->nrolinea =(yyvsp[-5].i);
                                                              (yyval.p)=nuevo;
                                                            }
#line 2308 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 924 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                                        NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                                        nuevo->tipoNodo=4;
                                                                        nuevo->tcondicion = (yyvsp[-5].p);
                                                                        nuevo->tthen = (yyvsp[-2].p);
                                                                        nuevo->telse = (yyvsp[0].p);
                                                                        nuevo->nrolinea =(yyvsp[-7].i);
                                                                        (yyval.p)=nuevo;
                                                                      }
#line 2322 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 934 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                      NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=5;
                                        nuevo->tcondicion = (yyvsp[-2].p);
                                        nuevo->cuerpo = (yyvsp[0].p);
                                        nuevo->nrolinea =(yyvsp[-4].i);
                                        (yyval.p)=nuevo;
                                      }
#line 2335 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 943 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=6;
                                        nuevo->tipo=(yyvsp[-1].p)->tipo;
                                        nuevo->expresion = (yyvsp[-1].p);
                                        nuevo->nrolinea =(yyvsp[-2].i);
                                        (yyval.p)=nuevo;
                                      }
#line 2347 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 950 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=7;
                                        nuevo->nrolinea =(yyvsp[-1].i);
                                        nuevo->tipo="void";
                                        (yyval.p)=nuevo;
                                      }
#line 2358 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 956 "calc-sintaxis.y" /* yacc.c:1646  */
    {   NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=8;
                                        nuevo->nombre=(yyvsp[-3].infos)->info;
                                        //printf("asignacion, nombre variable %s \n",$1->info);
                                        nuevo->op1=buscarVariable((yyvsp[-3].infos)->info);
                                        //printf("volvio de buscar la variable");
                                        if(nuevo->op1==NULL){
                                          printf("ERROR linea %i : variable %s no declarada\n",(yyvsp[-2].infos)->linea,(yyvsp[-3].infos)->info);
                                          exit(0);
                                        }
                                        nuevo->expresion = (yyvsp[-1].p);
                                        if(strcmp((nuevo->op1)->tipo,(nuevo->expresion)->tipo)!=0){
                                          printf("ERROR linea %i : se esta asignando una expr %s a una variable %s \n",(yyvsp[-2].infos)->linea,(nuevo->op1)->tipo,(nuevo->expresion)->tipo);
                                          exit(0);
                                        }
                                        nuevo->nrolinea =(yyvsp[-2].infos)->linea;
                                        (yyval.p)=nuevo;
                                      }
#line 2381 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 974 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p);}
#line 2387 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 976 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=10;
                                        nuevo->nrolinea =(yyvsp[0].infos)->linea;
                                        (yyval.p)=nuevo;
                                      }
#line 2397 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 981 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 2403 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 983 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                nuevo->tipoNodo=9;
                                                nuevo->call_metodo = buscarMetodo((yyvsp[-2].infos)->info);
                                                nuevo->nrolinea =(yyvsp[-2].infos)->linea;
                                                if(nuevo->call_metodo == NULL){
                                                  printf("ERROR en linea %i : llamada metodo no declarado previamente \n",nuevo->nrolinea );
                                                  exit(0);
                                                }
                                                verificarTipoParametros(nuevo);
                                                nuevo->tipo=(nuevo->call_metodo)->tipo;

                                                (yyval.p)=nuevo;

                                                }
#line 2423 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 998 "calc-sintaxis.y" /* yacc.c:1646  */
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
                                                verificarTipoParametros(nuevo);
                                                nuevo->tipo=nuevo->call_metodo->tipo;
                                                (yyval.p)=nuevo;

                                                }
#line 2443 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1016 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p)->first;}
#line 2449 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1021 "calc-sintaxis.y" /* yacc.c:1646  */
    { (yyvsp[0].p)->first=(yyvsp[0].p); (yyval.p)=(yyvsp[0].p);  }
#line 2455 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1022 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->first=(yyvsp[-2].p)->first; (yyvsp[-2].p)->next = (yyvsp[0].p); (yyval.p)=(yyvsp[0].p);  }
#line 2461 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1026 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2482 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1042 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2503 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1058 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2524 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1074 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2545 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1090 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2566 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1106 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2587 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1122 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2608 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1138 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2629 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1154 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2650 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1170 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2671 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1187 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2692 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1203 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2713 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1219 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p);}
#line 2719 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1220 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=16;

                                  nuevo->nrolinea =(yyvsp[0].infos)->linea;
                                  nuevo->op1 = buscarVariable((yyvsp[0].infos)->info);
                                  if(nuevo->op1 == NULL){
                                    printf("ERROR en linea %i : variable %s no declarada  \n",nuevo->nrolinea,(yyvsp[0].infos)->info);
                                    exit(0);
                                  }
                                    nuevo->tipo = (nuevo->op1)->tipo;
                                    (yyval.p)=nuevo;
                                  }
#line 2737 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1233 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 2743 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1234 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 2749 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1239 "calc-sintaxis.y" /* yacc.c:1646  */
    {
              NodoArbol *nuevo= malloc(sizeof(NodoArbol));
              nuevo->tipo="int";
              nuevo->tipoNodo=12;
              nuevo->valor= (yyvsp[0].infoi)->info;
              nuevo->nrolinea =(yyvsp[0].infoi)->linea;
              (yyval.p)=nuevo;
              }
#line 2762 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1248 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 2768 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1250 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                    nuevo->tipo="bool";
                    nuevo->tipoNodo=13;
                    nuevo->valor= 1;
                    nuevo->nrolinea =(yyvsp[0].i);
                    (yyval.p)=nuevo;
                  }
#line 2781 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1259 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                  nuevo->tipo="bool";
                  nuevo->tipoNodo=13;
                  nuevo->valor=0;
                  nuevo->nrolinea =(yyvsp[0].i);
                  (yyval.p)=nuevo;
                }
#line 2794 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;


#line 2798 "calc-sintaxis.tab.c" /* yacc.c:1646  */
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
#line 1270 "calc-sintaxis.y" /* yacc.c:1906  */

