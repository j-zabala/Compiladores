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

%union { int i; char *s; char c; struct nodoArbol *p;}

%token<i> INT
%token<s> ID
%token VAR


%type<p> expr


%left '+'
%left '*'

%%

prog: expr ';'          {
                        printf("Resultado: %d \n",resolver($1)); 
                        }

	| asignacion ';' expr ';' {printf("Resultado: %d\n",resolver($3));}
    ;

  expr: INT               {
                          NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                          nuevo->tipo =0;
                          nuevo->valor = $1;

                          $$ = nuevo;
                          
                        }

     | ID                 {
               if(findInLista($1)==false){
                 printf("ERROR: Variable no declarada : %s \n",$1);
                 exit(-1);
                  }
               NodoArbol *nuevo =malloc(sizeof(NodoArbol));
               nuevo->tipo =1;
               nuevo->nombre = $1;

               $$ = nuevo;
							}


    | expr '+' expr     {
                          NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                          nuevo->tipo =2;
                          nuevo->nombre = "+";
                          nuevo->hIzq = $1;
                          nuevo->hDer = $3;

                          $$ = nuevo;
                        }
    | expr '*' expr     { 
                           NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                           nuevo->tipo =2;
                           nuevo->nombre = "*";
                           nuevo->hIzq = $1;
                           nuevo->hDer = $3;

                           $$ = nuevo;
                        }
    | '(' expr ')'              { $$ =  $2; }


    ;

 asignacion : VAR ID '=' INT {
                              
                               NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                               nuevo->hIzq=lista;
                               nuevo->nombre = $2;
                               nuevo->valor= $4;
                               nuevo->tipo=1;
                               lista= nuevo;
                               
                            }

	| asignacion ';' VAR ID '=' INT {
                                    if(findInLista($4)){
                                      printf("ERROR: Variable declarada mas de una vez: %s\n",$4);
                                      exit(-1);
                                    }

                                     NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                                     nuevo->hIzq=lista;
                                     nuevo->nombre = $4;
                                     nuevo->valor= $6;
                                     nuevo->tipo=1;
                                     lista= nuevo;
                                     
                                }

	;


%%
