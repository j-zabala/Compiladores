%{

/*

Pre-Proyecto de Compiladores 2017

Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbol.c"
#include <time.h>
#include <stdbool.h>

NodoArbol *lista =NULL;


/*
devuelve true o false segun si la variable (nombre pasado como parametro), si esta en la lista
o no
*/
bool findInLista(char *name){
  NodoArbol *aux = lista;
  while(aux != NULL){
    if (strcmp(aux->nombre,name) == 0){
      return true;
    }
    aux=aux->hIzq;

  }
  return false;
}

/* devuelve el valor de la variable (pasando como parametro el nombre de la misma) almacenado
en la lista
 */
int findVariableInLista(char *name){
  NodoArbol *aux = lista;
  while(aux != NULL){
    if (strcmp(aux->nombre,name) == 0){
      return aux->valor;
    }
    aux=aux->hIzq;

  }
  return 0;
}

/*esta funcion retorna el resultado entero del nodo que se le pasa como parametro, si el nodo
 es una constante devuelve su valor, si es una variable devuelve el valor de la misma (buscando
en la lista de variables) y si es nodo de tipo operacion devuelve el resultado de la operacion
aplicada a sus hijos
*/


int resolver(NodoArbol *raiz){
  if(raiz->tipo ==0){
    return raiz->valor;
  }
  if(raiz->tipo ==1){
    return findVariableInLista(raiz->nombre);
  }
  if(raiz->tipo ==2){
    return resolverOperacion(raiz);
  }
return 0;


}

// esta funcion dado un nodo de tipo "operacion", retorna el resultado de aplicar la operacion
// siendo los dos hijos del nodo los operandos


int resolverOperacion(NodoArbol *nodoop){

  if(strcmp(nodoop->nombre,"*")==0){
    return (resolver(nodoop->hIzq) * resolver(nodoop->hDer));
  }
  if(strcmp(nodoop->nombre,"+")==0){
    return (resolver(nodoop->hIzq) + resolver(nodoop->hDer));
  }
}









%}

%union { int i; char *s; char c; struct nodoArbol *p; struct infoString *infos, struct infoInt *infoi  }

%token<infoi> INT
%token<infos> ID
%token VAR

%token<i> CLASS
%token<i> IF
%token<i> THEN
%token<i> ELSE
%token<i> TRUE
%token<i> FALSE
%token<i> RETURN
%token<i> VOID
%token<i> INT
%token<i> BOOL
%token<i> WHILE

%token<infos> MAS
%token<infos> MENOS
%token<infos> POR
%token<infos> EXCLAMACION
%token<infos> DIVISION
%token<infos> MOD
%token<infos> PUNTOYCOMA
%token<infos> PARENTESISABRE
%token<infos> PARENTESISCIERRA
%token<infos> IGUAL
%token<infos> MAYORQUE
%token<infos> MENORQUE
%token<infos> AMPERSAND
%token<infos> BARRAVERT
%token<infos> LLAVEABRE
%token<infos> LLAVECIERRA







%left MAS MENOS
%left DIVISION POR MOD


%%

program: CLASS LLAVEABRE LLAVECIERRA          {printf("TERMINO");}

	| CLASS LLAVEABRE var_decl PUNTOYCOMA  LLAVECIERRA  {printf("TERMINO");}

  | CLASS LLAVEABRE method_decl  LLAVECIERRA  {printf("TERMINO");}

  | CLASS LLAVEABRE var_decl PUNTOYCOMA method_decl  LLAVECIERRA  {printf("TERMINO");}

;

var_decl: type ID               {printf("declaracion de var");};

  |var_decl COMA type ID                 {printf("declaracion de var");}

;

method_decl: type id PARENTESISABRE PARENTESISCIERRA block {}

  |type ID PARENTESISABRE param_decl PARENTESISCIERRA block {}

  |VOID ID PARENTESISABRE PARENTESISCIERRA block {}

  |VOID ID PARENTESISABRE param_decl PARENTESISCIERRA block {}

  |method_decl type ID PARENTESISABRE PARENTESISCIERRA block  {}

  |method_decl type ID PARENTESISABRE param_decl PARENTESISCIERRA block  {}

  |method_decl VOID ID PARENTESISABRE PARENTESISCIERRA block  {}

  |method_decl VOID ID PARENTESISABRE param_decl PARENTESISCIERRA block  {}

;

param_decl: type ID   {}
 |param_decl COMA type ID  {}

;

bin_op: arith_op {}
    
    | rel_op {}

    | cond_op {}
;

arith_op: expr MAS expr {}

    | expr MENOS expr {}

    | expr POR expr {}

    | expr DIVISION expr {}

    | expr MOD expr {}
;

rel_op: expr MAYORQUE expr {}

    | expr MENORQUE expr {}

    | expr IGUAL expr {}
;

cond_op: expr AMPERSAND AMPERSAND expr {}

    | expr BARRAVERT BARRAVERT expr {}
;

literal: INT {}

    | bool_literal {}
;
 

block:LLAVEABRE var_decl statament LLAVECIERRA    {}

  |LLAVEABRE var_decl LLAVECIERRA   {}

  |LLAVEABRE statament LLAVECIERRA    {}

  |LLAVEABRE  LLAVECIERRA   {}

;

type:INT    {}

  |BOOL   {}

;




bool_literal: TRUE {}

    | FALSE {}

    ;



statement :  IF PARENTESISABRE expr PARENTESISCIERRA THEN block   {}
          | IF PARENTESISABRE expr PARENTESISCIERRA THEN block ELSE block  {}
          | WHILE expr block {}
          | RETURN block PUNTOYCOMA {}
          | RETURN PUNTOYCOMA {}
          | ID IGUAL expr PUNTOYCOMA {}
          | method_call PUNTOYCOMA {}
          | PUNTOYCOMA {}
          | block {}
;
method_call: ID PARENTESISABRE PARENTESISCIERRA
            | ID PARENTESISABRE param_call PARENTESISCIERRA

;

param_call : expr
         | param_call COMA expr

;

expr : expr bin_op expr
      | MENOS expr
      | EXCLAMACION expr
      | PARENTESISABRE expr PARENTESISCIERRA
      | ID
      | method_call
      | literal
;



%%
