%{

#include <stdlib.h>
#include <stdio.h>
#include "arbol.c"
#include <time.h>

NodoArbol *lista =NULL;




%}

%union { int i; char *s; char c; struct NodoArbol *p;}

%token<i> INT
%token<s> ID
%token VAR


%type<p> expr


%left '+'
%left '*'

%%

prog: expr ';'          { printf("%s%d\n", "Resultado: ",$1); }
	| asignacion ';' expr ';' {printf("este programa tiene asignaciones");}
    ;

expr: INT               { $$ = $1;
                           printf("%s%d\n","Constante entera:",$1);
                        }

     | ID                 {
							$$ =0 ;
							printf("la gramatica detecto un id dentro de la expresion");
							}


    | expr '+' expr     { //$$ = $1 + $3;
                           //printf("%s,%d,%d,%d\n","Operador Suma\n",$1,$3,$1+$3);
                        }
    | expr '*' expr     { //$$ = $1 * $3;
                           //printf("%s,%d,%d,%d\n","Operador Producto\n",$1,$3,$1*$3);
                        }
    | '(' expr ')'              { $$ =  $2; }


    ;

 asignacion : VAR ID '=' INT {
                              printf ("asignacion 1\n");
                              printf ("lista: %p\n",lista);
                               NodoArbol *nuevo =malloc(sizeof(NodoArbol)); ;
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
