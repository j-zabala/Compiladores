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



void imprimirNodo(NodoArbol *nodo){
  printf("nodo en la direccion: %p \n",nodo);
  printf("TIPO NODO= %i \n", nodo->tipoNodo);

  if(nodo->tcondicion!=NULL){
    imprimirNodo(nodo->tcondicion);
  }
  if(nodo->tthen!=NULL){
    imprimirNodo(nodo->tthen);
  }
  if(nodo->telse!=NULL){
    imprimirNodo(nodo->telse);
  }
  if(nodo->expresion!=NULL){
    imprimirNodo(nodo->expresion);
  }

  if(nodo->param!=NULL){
    imprimirNodo(nodo->param);
  }
  if(nodo->call_params!=NULL){
    imprimirNodo(nodo->call_params);
  }
  if(nodo->call_metodo!=NULL){
    imprimirNodo(nodo->call_metodo);
  }
  if(nodo->first!=NULL){
    printf("dir de mem del first %p \n",nodo->first);
  }
  if(nodo->tipo!=NULL){
    printf("TIPO= %s\n", nodo->tipo);
  }
  if(nodo->nombre!=NULL){
    printf("NOMBRE= %s\n", nodo->nombre);
  }
  if(nodo->valorExpresion!=NULL){
    imprimirNodo(nodo->valorExpresion);
  }
  if(nodo->op1!=NULL){
    imprimirNodo(nodo->op1);
  }
  if(nodo->op2!=NULL){
    imprimirNodo(nodo->op2);
  }
  if(nodo->valor!=NULL){
    printf("VALOR= %i\n", nodo->valor);
  }
  if(nodo->nrolinea!=NULL){
    printf("NUMERO DE LINEA= %i\n", nodo->nrolinea);
  }

  printf("el next de este nodo es %p \n",nodo->next);

}

void imprimirmetodos(){
  printf("imprimir metodos \n");

  NodoArbol *metodo = listametodos ;
  NodoArbol *recorrido = metodo->cuerpo ;
  while(metodo!=NULL){

    while (recorrido != NULL) {
      printf("recorrido = %p\n",recorrido );
      imprimirNodo(recorrido);
      //recorrido=recorrido->next;

    }

    metodo=metodo->nextlista;
    recorrido = metodo->cuerpo;
  }
}


void nuevoNivelPila(){
 NodoPila *aux = malloc(sizeof(NodoPila));
 aux->lista = NULL;
 aux->nodoInferior=variableGlobalPila;
 printf("se crea nivel nuevo (dir: %p), inferior %p \n ", aux, variableGlobalPila);
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
  //listametodos=malloc(sizeof(NodoArbol));
  listametodos=NULL;

  variableGlobalPila = (NodoPila*) malloc(sizeof(NodoPila));
  variableGlobalPila->nodoInferior=NULL;
  printf("dir de mem del inferior al global %p \n",variableGlobalPila->nodoInferior);
  //nuevoNivelPila();

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

  printf("VAMOS A IMPRIMIR LA TABLA DE VARIABLES\n");

  NodoPila *scope = variableGlobalPila;
  NodoArbol *recorrido = scope->lista;
  while(scope != NULL){
    printf("NIVEL CON PUNTERO: %p\n",scope );
    while(recorrido != NULL){
     printf("%s %s | ",recorrido->tipo,recorrido->nombre);
     recorrido = recorrido->nextlista;
    }
    printf("\n------------------------------------------\n" );
    scope=scope->nodoInferior;
    if (scope !=NULL){
      recorrido = scope->lista;
    }

  }
  printf("termino de impriir la tabla");
  scope = variableGlobalPila;
  recorrido = scope->lista;
while(scope != NULL){
  while(recorrido != NULL){
    printf("se va a buscar la variable %s",param);
   printf("se va a comparar %s con %s ",param,recorrido->nombre);
   if(strcmp(recorrido->nombre,param)==0){
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

%type<p> listaID
%type<p> block
%type<p> Nblock
%type<p> listastatement
%type<p> statement
%type<p> method_call
%type<p> method_decl
%type<p> param_call
%type<p> ultparam_call
%type<p> expr
%type<p> literal
%type<p> bool_literal







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

    program: {inicializar();} clases {eliminarNivelPila();imprimirmetodos();}

clases: CLASS  LLAVEABRE LLAVECIERRA          {printf("TERMINO1\n");}

	| CLASS  LLAVEABRE  listavar_decl   LLAVECIERRA  {printf("\nTERMINO2");}

  | CLASS  LLAVEABRE listamethod_decl  LLAVECIERRA  {printf("\nTERMINO3");}

  | CLASS  LLAVEABRE listavar_decl  listamethod_decl  LLAVECIERRA  {printf("\nTERMINO4");}

;

var_decl: type  listaID PUNTOYCOMA   {printf("\ndeclaracion de var finalizada");};
;

listaID : ID  {     if(buscarVariableSC($1->info)==NULL){
                      printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable($1->info,aux,$1->linea);
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


listamethod_decl : method_decl {$1->nextlista=listametodos;listametodos=$1;}
| listamethod_decl method_decl {$2->nextlista=listametodos;listametodos=$2;}


method_decl: type ID PARENTESISABRE param_decl PARENTESISCIERRA block {

  printf("declaracion de metodo2\n");
  NodoArbol *aux= malloc(sizeof(NodoArbol));

  aux->tipo=$1;
  aux->tipoNodo=2;
  aux->nombre= $2->info;
  aux->cuerpo = $6;
  aux->nrolinea =$2->linea;
  aux->param = variableGlobalPila->lista;

  eliminarNivelPila();
  if(verificarMetodoDeclarado(aux->nombre)==1){
    printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
    exit(0);
  };
  $$ = aux;
}
|type ID PARENTESISABRE PARENTESISCIERRA block {
                printf("declaracion de metodo1\n");
                NodoArbol *aux= malloc(sizeof(NodoArbol));

                aux->tipo=$1;
                aux->tipoNodo=2;
                aux->nombre= $2->info;
                aux->cuerpo = $5;
                aux->nrolinea =$2->linea;
                if(verificarMetodoDeclarado(aux->nombre)==1){
                  printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                  exit(0);
                };
                $$ = aux;
                }


  |VOID ID PARENTESISABRE param_decl PARENTESISCIERRA block {
                                                    printf("declaracion de metodo4\n");

                                                    NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                    aux->tipo=NULL;
                                                    aux->tipoNodo=2;
                                                    aux->nombre= $2->info;
                                                    aux->cuerpo = $6;
                                                    aux->nrolinea =$2->linea;
                                                    aux->param = variableGlobalPila->lista;
                                                    if(verificarMetodoDeclarado(aux->nombre)==1){
                                                      printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                      exit(0);
                                                    };
                                                    eliminarNivelPila();


                                                    $$ = aux;

                                                  }
  |VOID ID PARENTESISABRE PARENTESISCIERRA block {
                                                  printf("declaracion de metodo3\n");

                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo=NULL;
                                                  aux->tipoNodo=2;
                                                  aux->nombre= $2->info;
                                                  aux->cuerpo = $5;
                                                  aux->nrolinea =$2->linea;
                                                  if(verificarMetodoDeclarado(aux->nombre)==1){
                                                    printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                    exit(0);
                                                  };
                                                  $$ = aux;
                                                  }


;



param_decl : {nuevoNivelPila();} Nparam_decl

Nparam_decl: type ID   {nuevaVariable($2->info,$1,$2->linea);}
 |Nparam_decl COMA type ID  {nuevaVariable($4->info,$3,$2->linea);}

;

block : {nuevoNivelPila();} Nblock {eliminarNivelPila(); $$=$2;}

Nblock: LLAVEABRE listavar_decl listastatement LLAVECIERRA    {$$=$3->first;}

  |LLAVEABRE listavar_decl LLAVECIERRA   {}

  |LLAVEABRE listastatement LLAVECIERRA    {$$=$2->first;}

  |LLAVEABRE  LLAVECIERRA   {}
;


listavar_decl : var_decl {}
| listavar_decl var_decl {}
;

listastatement : statement {$1->first=$1;$$=$1;}
| listastatement statement {$1->next = $2;
                            nodoauxiliar=$2;
                            nodoauxiliarAnt =nodoauxiliar;
                            while(nodoauxiliar!=NULL){
                              nodoauxiliar->first = $1->first; // mantenemos el primero de la lista en el atributo first
                              //para evitar una variable global, pq seria reescrita al haber
                              //bloques anidados, el ciclo permite el agregado de los statements de un bloque interno
                              nodoauxiliarAnt =nodoauxiliar;
                              nodoauxiliar=nodoauxiliar->next;
                            }

                            $$=nodoauxiliarAnt;
                              }
;


type:INTRES    {
                aux="int";
                $$=aux;
                }

  |BOOL   {
                  aux="bool";
                  $$=aux;
                  }

;








statement :  IF PARENTESISABRE expr PARENTESISCIERRA THEN block   {
                                                              NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                                              nuevo->tipoNodo=3;
                                                              nuevo->tcondicion = $3;
                                                              nuevo->tthen = $6;
                                                              nuevo->nrolinea =$1;
                                                              $$=nuevo;
                                                            }
          | IF PARENTESISABRE expr PARENTESISCIERRA THEN block ELSE block  {
                                                                        NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                                        nuevo->tipoNodo=4;
                                                                        nuevo->tcondicion = $3;
                                                                        nuevo->tthen = $6;
                                                                        nuevo->telse = $8;
                                                                        nuevo->nrolinea =$1;
                                                                        $$=nuevo;
                                                                      }

          | WHILE expr block {          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=5;
                                        nuevo->tcondicion = $2;
                                        nuevo->cuerpo = $3;
                                        nuevo->nrolinea =$1;
                                        $$=nuevo;
                                      }

          | RETURN expr PUNTOYCOMA {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=6;
                                        nuevo->expresion = $2;
                                        nuevo->nrolinea =$1;
                                        $$=nuevo;
                                      }
          | RETURN PUNTOYCOMA {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=7;
                                        nuevo->nrolinea =$1;
                                        $$=nuevo;
                                      }
          | ID ASIG expr PUNTOYCOMA {   NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=8;
                                        nuevo->nombre=$1->info;
                                        nuevo->expresion = $3;
                                        nuevo->nrolinea =$2->linea;
                                        $$=nuevo;
                                      }
          | method_call PUNTOYCOMA {$$=$1;}

          | PUNTOYCOMA {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=10;
                                        nuevo->nrolinea =$1->linea;
                                        $$=nuevo;
                                      }
          | block {$$=$1;}
;
method_call: ID PARENTESISABRE PARENTESISCIERRA {
                                                NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                nuevo->tipoNodo=9;
                                                nuevo->call_metodo = buscarMetodo($1->info);
                                                nuevo->nrolinea =$1->linea;
                                                if(nuevo->call_metodo == NULL){
                                                  printf("ERROR en linea %i : llamada metodo no declarado previamente \n",nuevo->nrolinea );
                                                  exit(0);
                                                }
                                                nuevo->tipo=(nuevo->call_metodo)->tipo;
                                                $$=nuevo;

                                                }
            | ID PARENTESISABRE param_call PARENTESISCIERRA {
                                                NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                                nuevo->tipoNodo=9;
                                                nuevo->call_metodo = buscarMetodo($1->info);
                                                nuevo->nrolinea =$1->linea;
                                                if(nuevo->call_metodo == NULL){
                                                  printf("ERROR en linea %i : llamada metodo no declarado previamente \n",nuevo->nrolinea );
                                                  exit(0);
                                                }
                                                nuevo->call_params =$3;
                                                nuevo->tipo=nuevo->call_metodo->tipo;
                                                $$=nuevo;

                                                }

;

param_call : ultparam_call {$$=$1->first;}

;


ultparam_call : expr   { $1->first=$1; $$=$1;  }
         | ultparam_call COMA expr {$3->first=$1->first; $1->next = $3; $$=$3;  }

;

expr : expr MAS expr {
                      NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                      nuevo->tipoNodo=14;
                      nuevo->nrolinea =$2->linea;
                      nuevo->nombre= $2->info;
                      nuevo->op1 = $1;
                      nuevo->op2 = $3;
                      int error = mismoTipoINT($1,$3);
                      if(error == 0){
                        nuevo->tipo = "int";
                      }else{
                          printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                          exit(0);
                      }
                      $$=nuevo;
                      }
    | expr MENOS expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;
                          int error = mismoTipoINT($1,$3);
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          $$=nuevo;
                          }
    | expr POR expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;
                          int error = mismoTipoINT($1,$3);
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          $$=nuevo;
                          }
    | expr DIVISION expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;
                          int error = mismoTipoINT($1,$3);
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          $$=nuevo;
                          }
    | expr MOD expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;
                          int error = mismoTipoINT($1,$3);
                          if(error == 0){
                            nuevo->tipo = "int";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          $$=nuevo;
                          }
    |expr MAYORQUE expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;
                          int error = mismoTipoINT($1,$3);
                          if(error == 0){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          $$=nuevo;
                          }
    | expr MENORQUE expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;
                          int error = mismoTipoINT($1,$3);
                          if(error == 0){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          $$=nuevo;
                          }
    | expr EQUALS expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;

                          if(mismoTipoINT($1,$3) == 0 ||mismoTipoBOOL($1,$3) == 0 ){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : operandos de distintos tipos \n",nuevo->nrolinea);
                              exit(0);
                          }
                          $$=nuevo;
                          }
    |expr AND expr {
                          NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                          nuevo->tipoNodo=14;
                          nuevo->nrolinea =$2->linea;
                          nuevo->nombre= $2->info;
                          nuevo->op1 = $1;
                          nuevo->op2 = $3;
                          int error = mismoTipoBOOL($1,$3);
                          if(error == 0){
                            nuevo->tipo = "bool";
                          }else{
                              printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                              exit(0);
                          }
                          $$=nuevo;
                          }
    | expr OR expr {
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=14;
                                  nuevo->nrolinea =$2->linea;
                                  nuevo->nombre= $2->info;
                                  nuevo->op1 = $1;
                                  nuevo->op2 = $3;
                                  int error = mismoTipoBOOL($1,$3);
                                  if(error == 0){
                                    nuevo->tipo = "bool";
                                  }else{
                                      printf("ERROR en linea %i : error de tipo en operando  %i° \n",nuevo->nrolinea,error );
                                      exit(0);
                                  }
                                  $$=nuevo;
                                  }

    | MENOS expr %prec UNARIO {
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=15;
                                  nuevo->nrolinea =$1->linea;
                                  nuevo->nombre= $1->info;
                                  nuevo->op1 = $2;


                                  if(strcmp($2->tipo,"int") == 0){
                                    nuevo->tipo = "int";
                                  }else{
                                      printf("ERROR en linea %i : error de tipo en operando (no es un entero)   \n",nuevo->nrolinea);
                                      exit(0);
                                  }
                                  $$=nuevo;
                                  }
    | EXCLAMACION expr %prec UNARIO{
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=15;
                                  nuevo->nrolinea =$1->linea;
                                  nuevo->nombre= $1->info;
                                  nuevo->op1 = $2;


                                  if(strcmp($2->tipo,"bool") == 0){
                                    nuevo->tipo = "bool";
                                  }else{
                                      printf("ERROR en linea %i : error de tipo en operando (no es un booleano)   \n",nuevo->nrolinea);
                                      exit(0);
                                  }
                                  $$=nuevo;
                                  }
    | PARENTESISABRE expr PARENTESISCIERRA {$$=$2;}
    | ID{
                                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                  nuevo->tipoNodo=16;
                                  nuevo->nrolinea =$1->linea;
                                  nuevo->op1 = buscarVariable($1->info);
                                  if(nuevo->op1 == NULL){
                                    printf("ERROR en linea %i : variable %s no declarada  \n",nuevo->nrolinea,$1->info);
                                    exit(0);
                                  }
                                  nuevo->tipo = nuevo->op1->tipo;
                                  $$=nuevo;
                                  }
    | method_call{$$=$1;}
    | literal{$$=$1;}
;



literal: INT {
              NodoArbol *nuevo= malloc(sizeof(NodoArbol));
              nuevo->tipo="int";
              nuevo->tipoNodo=12;
              nuevo->valor= $1->info;
              nuevo->nrolinea =$1->linea;
              $$=nuevo;
              }

    | bool_literal {$$=$1;}
;
bool_literal: TRUE {
                    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                    nuevo->tipo="bool";
                    nuevo->tipoNodo=13;
                    nuevo->valor= 1;
                    nuevo->nrolinea =$1;
                    $$=nuevo;
                  }

    | FALSE {
                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                  nuevo->tipo="bool";
                  nuevo->tipoNodo=13;
                  nuevo->valor=0;
                  nuevo->nrolinea =$1;
                  $$=nuevo;
                }

    ;

%%
