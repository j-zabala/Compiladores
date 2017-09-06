%{

/*

Pre-Proyecto de Compiladores 2017

Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbol.c"
#include "infostring.c"
#include "infoint.c"
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

%union { int i; char *s; char c; struct nodoArbol *p; struct infoString *infos; struct infoInt *infoi  ;}

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
%token<i> INTRES
%token<i> BOOL
%token<i> WHILE

%token<infos> MAS
%token<infos> MENOS
%token<infos> POR
%token<infos> EXCLAMACION
%token<infos> DIVISION
%token<infos> MOD
%token<infos> COMA
%token<infos> PUNTOYCOMA
%token<infos> PARENTESISABRE
%token<infos> PARENTESISCIERRA
%token<infos> ASIG
%token<infos> EQUALS
%token<infos> MAYORQUE
%token<infos> MENORQUE
%token<infos> AND
%token<infos> OR
%token<infos> LLAVEABRE
%token<infos> LLAVECIERRA




%left LLAVEABRE LLAVECIERRA
%left ASIG
%left OR
%left AND
%left EQUALS
%left MENORQUE MAYORQUE
%left MAS MENOS
%left DIVISION POR MOD
%left PARENTESISABRE PARENTESISCIERRA
%right UNARIO





%%

program: CLASS LLAVEABRE LLAVECIERRA          {printf("TERMINO1\n");}

	| CLASS LLAVEABRE listavar_decl   LLAVECIERRA  {printf("\nTERMINO2");}

  | CLASS LLAVEABRE method_decl  LLAVECIERRA  {printf("\nTERMINO3");}

  | CLASS LLAVEABRE listavar_decl  method_decl  LLAVECIERRA  {printf("\nTERMINO4");}

;

var_decl: type listaID PUNTOYCOMA   {printf("\ndeclaracion de var");};


;

listaID : ID
| listaID COMA ID
;

method_decl: type ID PARENTESISABRE PARENTESISCIERRA block {printf("declaracion de metodo1\n");}

  |type ID PARENTESISABRE param_decl PARENTESISCIERRA block {printf("declaracion de metodo2\n");}

  |VOID ID PARENTESISABRE PARENTESISCIERRA block {printf("declaracion de metodo3\n");}

  |VOID ID PARENTESISABRE param_decl PARENTESISCIERRA block {printf("declaracion de metodo4\n");}

  |method_decl type ID PARENTESISABRE PARENTESISCIERRA block  {printf("declaracion de metodo5\n");}

  |method_decl type ID PARENTESISABRE param_decl PARENTESISCIERRA block  {printf("declaracion de metodo6\n");}

  |method_decl VOID ID PARENTESISABRE PARENTESISCIERRA block  {printf("declaracion de metodo7\n");}

  |method_decl VOID ID PARENTESISABRE param_decl PARENTESISCIERRA block  {printf("declaracion de metodo8\n");}

;

param_decl: type ID   {}
 |param_decl COMA type ID  {}

;


block: LLAVEABRE listavar_decl listastatement LLAVECIERRA    {}

  |LLAVEABRE listavar_decl LLAVECIERRA   {}

  |LLAVEABRE listastatement LLAVECIERRA    {}

  |LLAVEABRE  LLAVECIERRA   {}
;


listavar_decl : var_decl {}
| listavar_decl var_decl {}
;

listastatement : statement {}
| listastatement statement {}
;


type:INTRES    {}

  |BOOL   {}

;








statement :  IF PARENTESISABRE expr PARENTESISCIERRA THEN block   {}
          | IF PARENTESISABRE expr PARENTESISCIERRA THEN block ELSE block  {}
          | WHILE expr block {}
          | RETURN expr PUNTOYCOMA {}
          | RETURN PUNTOYCOMA {}
          | ID ASIG expr PUNTOYCOMA {}
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

expr : expr MAS expr {}
    | expr MENOS expr {}
    | expr POR expr {}
    | expr DIVISION expr {}
    | expr MOD expr {}
    |expr MAYORQUE expr {}
    | expr MENORQUE expr {}
    | expr EQUALS expr {}
    |expr AND expr {}
    | expr OR expr {}
      | MENOS expr %prec UNARIO
      | EXCLAMACION expr %prec UNARIO
      | PARENTESISABRE expr PARENTESISCIERRA
      | ID
      | method_call
      | literal
;



literal: INT {}

    | bool_literal {}
;
bool_literal: TRUE {}

    | FALSE {}

    ;

%%
