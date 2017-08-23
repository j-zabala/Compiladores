%{

#include <stdlib.h>
#include <stdio.h>

%}
 
%union { int i; char *s; char c;}
 
%token<i> INT
%token<s> ID
%token VAR


%type<i> expr
 
 
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
                       
                        
    | expr '+' expr     { $$ = $1 + $3; 
                           printf("%s,%d,%d,%d\n","Operador Suma\n",$1,$3,$1+$3);
                        }
    | expr '*' expr     { $$ = $1 * $3; 
                           printf("%s,%d,%d,%d\n","Operador Producto\n",$1,$3,$1*$3);  
                        }
    | '(' expr ')'              { $$ =  $2; }
    
    
    ;
 
 asignacion : VAR ID '=' INT {printf ("asignacion");} 
	
	| asignacion ';' VAR ID '=' INT {printf ("asignacion");} 
	
	;
	
	
%%


