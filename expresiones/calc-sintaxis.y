%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbol.c"
#include <time.h>
#include <stdbool.h>

NodoArbol *lista =NULL;

bool findInLista(char *name){
  NodoArbol *aux = lista;
  while(aux != NULL){
    if (strcmp(aux->nombre,name) == 0){
      printf("SE enconntro la variable en l lista!!!!!!!!!!!!!!!!!!!!!!!!!");
      return true;
    }
    aux=aux->hIzq;

  }
  return false;
}





%}

%union { int i; char *s; char c; struct NodoArbol *p;}

%token<i> INT
%token<s> ID
%token VAR


%type<p> expr


%left '+'
%left '*'

%%

prog: expr ';'          {
                        //printf("%s%d\n", "Resultado: ",$1); }
                        }

	| asignacion ';' expr ';' {printf("este programa tiene asignaciones");}
    ;

  expr: INT               {
                          NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                          nuevo->tipo =0;
                          nuevo->valor = $1;

                          $$ = nuevo;
                          printf("se detecto un INT, SE GENERA EL SIGUIENTE NODO");
                          printf ("nodo: direccion:%p nombre: %s tipo: %i valor: %i hIzq %p\n",nuevo,nuevo->nombre,nuevo->tipo,nuevo->valor,nuevo->hIzq);
                          printf("%s%d\n","Constante entera:",$1);
                        }

     | ID                 {
               NodoArbol *nuevo =malloc(sizeof(NodoArbol));
               nuevo->tipo =1;
               nuevo->nombre = $1;

               $$ = nuevo;
							printf("la gramatica detecto un id dentro de la expresion");
							}


    | expr '+' expr     { //$$ = $1 + $3;
                           //printf("%s,%d,%d,%d\n","Operador Suma\n",$1,$3,$1+$3);
                          NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                          nuevo->tipo =2;
                          nuevo->nombre = $2;
                          nuevo->hIzq = $1;
                          nuevo->hDer = $3;

                          $$ = nuevo;
                        }
    | expr '*' expr     { //$$ = $1 * $3;
                           //printf("%s,%d,%d,%d\n","Operador Producto\n",$1,$3,$1*$3);
                           NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                           nuevo->tipo =2;
                           nuevo->nombre = $2;
                           nuevo->hIzq = $1;
                           nuevo->hDer = $3;

                           $$ = nuevo;
                        }
    | '(' expr ')'              { $$ =  $2; }


    ;

 asignacion : VAR ID '=' INT {
                              printf ("asignacion 1\n");
                              printf ("lista: %p\n",lista);
                               NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                               nuevo->hIzq=lista;
                               nuevo->nombre = $2;
                               nuevo->valor= $4;
                               nuevo->tipo=1;
                               lista= nuevo;
                               printf ("lista(luego deagregar): %p\n",lista);
                               printf ("nodo: direccion:%p nombre: %s tipo: %i valor: %i hIzq %p\n",nuevo,nuevo->nombre,nuevo->tipo,nuevo->valor,nuevo->hIzq);
                            }

	| asignacion ';' VAR ID '=' INT {
                                    printf ("asignacion 2");
                                    printf ("lista: %p \n",lista);
                                     NodoArbol *nuevo =malloc(sizeof(NodoArbol));
                                     nuevo->hIzq=lista;
                                     nuevo->nombre = $4;
                                     nuevo->valor= $6;
                                     nuevo->tipo=1;
                                     lista= nuevo;
                                     printf ("lista(luego deagregar): %p   \n",lista);
                                     printf ("nodo: direccion:%p nombre: %s tipo: %i valor: %i hIzq %p \n",nuevo,nuevo->nombre,nuevo->tipo,nuevo->valor,nuevo->hIzq);
                                }

	;


%%
