%{

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
  aux->nextlista =null;
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


char *aux;

NodoArbol *first ; //este puntero apunta al primer statement cuando se arma la lista de los statements

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

%type<s> type




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

    program: {inicializar();} clases {eliminarNivelPila();}

clases: CLASS  LLAVEABRE LLAVECIERRA          {printf("TERMINO1\n");}

	| CLASS  LLAVEABRE  listavar_decl   LLAVECIERRA  {printf("\nTERMINO2");}

  | CLASS  LLAVEABRE listamethod_decl  LLAVECIERRA  {printf("\nTERMINO3");}

  | CLASS  LLAVEABRE listavar_decl  listamethod_decl  LLAVECIERRA  {printf("\nTERMINO4");}

;

var_decl: type {aux=$1;} listaID PUNTOYCOMA   {printf("\ndeclaracion de var finalizada");};


;

listaID : ID  {     if(buscarVariableSC($1->info)==NULL){
                      printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable($1->info,aux,$3->linea);
                    }else{
                      printf("linea %i VARIABLE %s YA DECLARADA!!! \n",$1->linea,$1->info  );
                      }

                    }
| listaID COMA ID {
                  if(buscarVariableSC($3->info)==NULL){
                    printf("%s\n","la variable no esta en el scope!!" );
                    nuevaVariable($3->info,aux,$3->linea);
                  }else{
                    printf("linea %i VARIABLE %s YA DECLARADA!!! \n",$3->linea,$3->info  );
                    }
  }
;


listamethod_decl : listamethod_decl method_decl {}
  | method_decl {}


method_decl: type ID PARENTESISABRE PARENTESISCIERRA block {
                printf("declaracion de metodo1\n");
                NodoArbol *aux= malloc(sizeof(NodoArbol));

                aux->tipo=$1;
                aux->tipoNodo=2;
                aux->nombre= $2->info;
                aux->cuerpo = $5;
                aux->nrolinea =$2->linea;
                $$ = aux;
                }

  |type ID PARENTESISABRE param_decl PARENTESISCIERRA block {

                                                  printf("declaracion de metodo2\n");
                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo=$1;
                                                  aux->tipoNodo=2;
                                                  aux->nombre= $2->info;
                                                  aux-cuerpo = $5;
                                                  aux->nrolinea =$2->linea;
                                                  aux->param = variableGlobalPila->lista;

                                                  eliminarNivelPila();

                                                  $$ = aux;
                                                  }

  |VOID ID PARENTESISABRE PARENTESISCIERRA block {
                                                  printf("declaracion de metodo3\n");

                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo=$1->info;
                                                  aux->tipoNodo=2;
                                                  aux->nombre= $2->info;
                                                  aux-cuerpo = $5;
                                                  aux->nrolinea =$2->linea;
                                                  $$ = aux;
                                                  }

  |VOID ID PARENTESISABRE param_decl PARENTESISCIERRA block {
                                                  printf("declaracion de metodo4\n");

                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo=$1->info;
                                                  aux->tipoNodo=2;
                                                  aux->nombre= $2->info;
                                                  aux-cuerpo = $5;
                                                  aux->nrolinea =$2->linea;
                                                  aux->param = variableGlobalPila->lista;

                                                  eliminarNivelPila();


                                                  $$ = aux;
                                                  }

;



param_decl : {nuevoNivelPila();} Nparam_decl

Nparam_decl: type ID   {nuevaVariable($2->info,$1,$2->linea);}
 |Nparam_decl COMA type ID  {nuevaVariable($4->info,$3,$2->linea);}

;

block : {nuevoNivelPila();} Nblock {eliminarNivelPila();}

Nblock: LLAVEABRE listavar_decl listastatement LLAVECIERRA    {}

  |LLAVEABRE listavar_decl LLAVECIERRA   {}

  |LLAVEABRE listastatement LLAVECIERRA    {}

  |LLAVEABRE  LLAVECIERRA   {}
;


listavar_decl : var_decl {
                        $$ = aux;
                      }
| listavar_decl var_decl {}
;

listastatement : statement {first=$1;$$=$1;}
| listastatement statement {$1->next = $2;
                            $$=$2;
                              }
;


type:INTRES    {$$="int";}

  |BOOL   {$$="bool";}

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
