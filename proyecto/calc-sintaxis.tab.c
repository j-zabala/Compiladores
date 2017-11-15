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

int currentOffSet;


void imprimirNodo(NodoArbol *nodo);//como el forward de pascal

NodoArbol* pasarACodIntermedio(NodoArbol* nodo);


void agregarCodIntermedio(NodoInt* nuevo);

char* nuevoLabel(char* info);

void codAssembler (){
  FILE * archivo=fopen ("assembler.s", "w+");

  CAglobales(archivo);
  printf("termino con las globales");
  pasarACodAssembler(archivo,codigoIntermedio,0);


  fclose(archivo);
}

char* varAAssembler (NodoArbol* nodo){

  char* aux=(char*)malloc(sizeof(char)*20);
  if(nodo->isGlobal){
  sprintf(aux,"%s(\%rip)",nodo->nombre);

}else{
  sprintf(aux,"%i(\%rbp)",nodo->offSet);
}
  return aux;

}



void CAglobales(FILE* archivo){
  printf("comienza el agregado de las var globales\n");
  if(variableGlobalPila==NULL){printf("nullll\n");}
  NodoArbol* recorrido=variableGlobalPila->lista;
  printf("ahhhhh\n");
  while(recorrido!=NULL){
    printf("entro en el while\n");
    if(recorrido->isGlobal==1){
      printf("\n es glob");
      fprintf(archivo, "  .comm %s,8 \n",recorrido->nombre );

      printf("se agrega la variable %s a las globals",recorrido->nombre);
    }
    recorrido=recorrido->nextlista;
  }
  printf("termino el while\n");
  fprintf(archivo, "  .text\n");

}

void recuperarParametros(NodoArbol* nodo,int nro,FILE* arch){
    if(nodo==NULL){return;}
    if(nro <=6){
      char* reg =(char*)malloc(sizeof(char)*10);
      switch (nro) {
        case 1: fprintf(arch, "  movq  \%rdi");break;
        case 2: fprintf(arch, "  movq  \%rsi");break;
        case 3: fprintf(arch, "  movq  \%rdx");break;
        case 4: fprintf(arch, "  movq  \%rcx");break;
        case 5: fprintf(arch, "  movq  \%r8d");break;
        case 6: fprintf(arch, "  movq  \%r9d");break;

      }
      fprintf(arch, ",%s \n",varAAssembler(nodo));
    }
    recuperarParametros(nodo->nextlista,nro+1,arch);

}




void pasarACodAssembler(FILE* arch,NodoInt* nodo,int metodonro){
  if  (nodo == NULL){return;}


  if (strcmp(nodo->operacion,"METODO")==0){
    printf("nodo intermedio operacion: metodo\n");
    //printf("el nodo op es un METODO\n");
    fprintf(arch, "  .globl	%s\n",nodo->nombre );
    fprintf(arch, "  .type	%s, @function\n",nodo->nombre );
    fprintf(arch, "%s:\n",nodo->nombre );
    fprintf(arch, ".LFB%i:\n",metodonro);
    int cantidadenter;
    //printf("escribio el encabezado del metodo\n");
    if(nodo->metodoOriginal==NULL){
      printf("el metodooriginal es null\n");
    }
    if(((nodo->metodoOriginal)->maxoffSet%16)==0){
      printf("el maxoffSet del metodo  %s  es %i\n",(nodo->metodoOriginal)->nombre,(nodo->metodoOriginal)->maxoffSet);
      cantidadenter=(((nodo->metodoOriginal)->maxoffSet)*-1);
    }else{
      printf("no mod 0 el maxoffSet del metodo  %s  es %i\n",(nodo->metodoOriginal)->nombre,(nodo->metodoOriginal)->maxoffSet);
      cantidadenter=(((nodo->metodoOriginal)->maxoffSet)*-1)+8;
    }
    //printf("enter %i\n",cantidadenter );
    fprintf(arch, "  enter $%i,$0\n",cantidadenter);

    recuperarParametros((nodo->metodoOriginal)->param,1,arch);



    pasarACodAssembler(arch,nodo->next,metodonro);
    printf("nodo intermedio operacion: metodo\n");
  }

  if (strcmp(nodo->operacion,"ENDMETODO")==0){
    fprintf(arch,"  endmetodo%i:\n",metodonro);
    fprintf(arch, "  leave\n");
    fprintf(arch, "  ret \n");
    fprintf(arch, ".LFE%i:\n",metodonro);
    fprintf(arch, "  .size	%s, .-%s\n",nodo->nombre,nodo->nombre );
    fprintf(arch, ".LC%i:\n",metodonro);
    char* aux= "\%i";
    fprintf(arch, "  .string	\"la funcion %s devuelve: %s \"  \n",(nodo->metodoOriginal)->nombre,aux);
    pasarACodAssembler(arch,nodo->next,metodonro+1);

  }


  if (strcmp(nodo->operacion,"MOV")==0){
    printf("inicia mov de %s a %s\n",(nodo->op1)->nombre,(nodo->op2)->nombre );
    printf("el tipo del nodo es %i , corresponde a la variable %s\n",(nodo->op2)->tipoNodo,(nodo->op2)->nombre);
    if((nodo->op2)->tipoNodo==1){
      printf("hacemos un movq de una variable a una variable\n");
      fprintf(arch, "  movq %s, \%rax \n",varAAssembler(nodo->op2));

      fprintf(arch, "  movq \%rax, %s \n",varAAssembler(nodo->op1));
      printf( "  movq %s, \%rax \n",varAAssembler(nodo->op2));

      printf( "  movq \%rax, %s \n",varAAssembler(nodo->op1));
    }
    if((nodo->op2)->tipoNodo==12||(nodo->op2)->tipoNodo==13){
      printf("hacemos un movq de un literal a una variable\n");
        fprintf(arch, "  movq $%i,%s \n",(nodo->op2)->valor,varAAssembler(nodo->op1));
        printf("  movq $%i,%s \n",(nodo->op2)->valor,varAAssembler(nodo->op1));

    }
    printf("fin mov \n");
    pasarACodAssembler(arch,nodo->next,metodonro);
  }

   if (strcmp(nodo->operacion,"LOADP")==0){
     printf("entro en un load p\n");
     if(nodo->nroparametro >6){
       fprintf(arch, "  movq \%rdi, \%rax \n");
       fprintf(arch, "  movq	%s, \%rdi \n",varAAssembler(nodo->op1));
       fprintf(arch, "  pushq	\%rdi \n");
       fprintf(arch, "  movq  \%rax,\%rdi \n");
     }

     if(nodo->nroparametro <=6){
       char* reg ;
       fprintf(arch, "  movq	%s,",varAAssembler(nodo->op1));

       switch (nodo->nroparametro) {
         case 1: fprintf(arch, "\%rdi \n");break;
         case 2: fprintf(arch, "\%rsi \n");break;
         case 3: fprintf(arch, "\%rdx \n");break;
         case 4: fprintf(arch, "\%rcx \n");break;
         case 5: fprintf(arch, "\%r8d \n");break;
         case 6: fprintf(arch, "\%r9d \n");break;

       }

     }

     printf("end en un load p\n");
     pasarACodAssembler(arch,nodo->next,metodonro);
   }

   if (strcmp(nodo->operacion,"RETURN")==0){
    if(nodo->op1!=NULL){
       fprintf(arch, "  movq	%s, \%rsi \n",(varAAssembler(nodo->op1)));
       fprintf(arch, "  movq $.LC%i,\%rdi\n",metodonro);
       fprintf(arch, "  movq	$0, \%rax \n");
       fprintf(arch, "  call printf\n");
     }
     if(nodo->op1==NULL){
       fprintf(arch, "  movq	$0, \%rsi \n");
       fprintf(arch, "  movq $.LC%i,\%rdi\n",metodonro);
       fprintf(arch, "  movq	$0, \%rax \n");
       fprintf(arch, "  call printf\n");

     }



     if(nodo->op1!=NULL){
       fprintf(arch, "  movq	%s, \%rax \n",(varAAssembler(nodo->op1)));
       fprintf(arch, "  jmp endmetodo%i\n",metodonro);
     }


    pasarACodAssembler(arch,nodo->next,metodonro);
     }

   if (strcmp(nodo->operacion,"CALL")==0){
       fprintf(arch, "  call %s \n",nodo->nombre);
       if(nodo->op1!=NULL){
         fprintf(arch, "  movq	\%rax, %s  \n",varAAssembler(nodo->op1));
       }
         pasarACodAssembler(arch,nodo->next,metodonro);
     }

   if (strcmp(nodo->operacion,"JMPFalso")==0){
       fprintf(arch, "  cmp $1,%s  \n",varAAssembler(nodo->op1));
       fprintf(arch, "  jne %s \n",nodo->nombre);
       pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"JMP")==0){
       fprintf(arch, "  jmp %s \n",nodo->nombre);
       pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"LABEL")==0){
       fprintf(arch, "%s: \n",nodo->nombre);
       pasarACodAssembler(arch,nodo->next,metodonro);
     }

   if (strcmp(nodo->operacion,"SUM")==0){
     printf("entro en un nodo sum\n");
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
      fprintf(arch, "  add	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
     if (strcmp(nodo->operacion,"RES")==0){
       printf("entro en un nodo res\n");
        fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
        fprintf(arch, "  sub	%s, \%rax \n",varAAssembler(nodo->op2));
        fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
        pasarACodAssembler(arch,nodo->next,metodonro);
       }
   if (strcmp(nodo->operacion,"MULT")==0){
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
      fprintf(arch, "  imul	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
    if (strcmp(nodo->operacion,"AND")==0){
        fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
        fprintf(arch, "  testq	\%rax, \%rax \n");
        char * label1=nuevoLabel("lAND");
        char * label2=nuevoLabel("lAND");
        fprintf(arch, "  je	%s \n",label1);
        fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
        fprintf(arch, "  testq	\%rax, \%rax \n");
        fprintf(arch, "  je	%s \n",label1);
        fprintf(arch, "  movq	 $1,%s \n",varAAssembler(nodo->op3));
        fprintf(arch, "  jmp	%s \n",label2);
        fprintf(arch, "  %s: \n",label1);
        fprintf(arch, "  movq	 $0,%s \n",varAAssembler(nodo->op3));
        fprintf(arch, "  %s: \n",label2);

        pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"OR")==0){
     char * label2=nuevoLabel("lOR");
     char * label3=nuevoLabel("lOR");
     char * label4=nuevoLabel("lOR");
       fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
       fprintf(arch, "  testq	\%rax, \%rax \n");
       fprintf(arch, "  jne	%s \n",label2);
       fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
       fprintf(arch, "  testq	\%rax, \%rax \n");
       fprintf(arch, "  je	%s \n",label3);
       fprintf(arch, "  %s: \n",label2);

       fprintf(arch, "  movq	 $1,%s \n",varAAssembler(nodo->op3));
       fprintf(arch, "  jmp	%s \n",label4);
       fprintf(arch, "  %s: \n",label3);
       fprintf(arch, "  movq	 $0,%s \n",varAAssembler(nodo->op3));
       fprintf(arch, "  %s: \n",label4);

       pasarACodAssembler(arch,nodo->next,metodonro);
    }
   if (strcmp(nodo->operacion,"DIV")==0){
      fprintf(arch, "  movq	$0, \%rdx \n");
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
      fprintf(arch, "  movq %s,\%rbx \n",varAAssembler(nodo->op2));
      fprintf(arch, "  cqo\n");
      fprintf(arch, "  idiv \%rbx \n");
      fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"MOD")==0){
     fprintf(arch, "  movq	$0, \%rdx \n");
     fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
     fprintf(arch, "  movq %s,\%rbx \n",varAAssembler(nodo->op2));
     fprintf(arch, "  cqo\n");
     fprintf(arch, "  idiv \%rbx \n");
      fprintf(arch, "  movq	 \%rdx,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"MAYORQUE")==0){
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 $0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  cmp	\%rax, \%rdx\n",varAAssembler(nodo->op2));
      fprintf(arch, "  jle	 %s \n",labelaux);
      fprintf(arch, "  movq	 $1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"MENORQUE")==0){
     printf("entra a MENORQUE\n" );
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 $0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  cmp	\%rax, \%rdx\n",varAAssembler(nodo->op2));
      fprintf(arch, "  jge	 %s \n",labelaux);
      fprintf(arch, "  movq	 $1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      printf("SALE DE  MENORQUE\n" );
      pasarACodAssembler(arch,nodo->next,metodonro);

     }
   if (strcmp(nodo->operacion,"IGUAL")==0){
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 $0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  cmp	\%rax, \%rdx\n",varAAssembler(nodo->op2));
      fprintf(arch, "  jne	 %s \n",labelaux);
      fprintf(arch, "  movq	 $1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"NEGBOOL")==0){
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 $0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  cmp	$1, \%rdx\n");
      fprintf(arch, "  je	 %s \n",labelaux);
      fprintf(arch, "  movq	 $1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
     if (strcmp(nodo->operacion,"NEGINT")==0){
        fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
        fprintf(arch, "  imul	$-1, \%rax \n");
        fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
        pasarACodAssembler(arch,nodo->next,metodonro);
       }




       return;

}


NodoArbol* nuevoLiteralbin(char* operacion, int valor1, int valor2){
  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
  if(strcmp(operacion,"+")==0){
    nuevo->tipo="int";
    nuevo->tipoNodo=12;
    nuevo->valor= valor1+valor2;
  }
  if(strcmp(operacion,"*")==0){
    nuevo->tipo="int";
    nuevo->tipoNodo=12;
    nuevo->valor= valor1*valor2;
  }
  if(strcmp(operacion,"-")==0){
    nuevo->tipo="int";
    nuevo->tipoNodo=12;
    nuevo->valor= valor1-valor2;
  }
  if(strcmp(operacion,"/")==0){
    nuevo->tipo="int";
    nuevo->tipoNodo=12;
    nuevo->valor= valor1/valor2;
  }
  if(strcmp(operacion,"%")==0){
    nuevo->tipo="int";
    nuevo->tipoNodo=12;
    nuevo->valor= valor1%valor2;
  }
  if(strcmp(operacion,"==")==0){
    nuevo->tipo="bool";
    nuevo->tipoNodo=13;
    nuevo->valor= valor1==valor2;
  }
  if(strcmp(operacion,"<")==0){
    nuevo->tipo="bool";
    nuevo->tipoNodo=13;
    nuevo->valor= valor1<valor2;
  }
  if(strcmp(operacion,">")==0){
    nuevo->tipo="bool";
    nuevo->tipoNodo=13;
    nuevo->valor= valor1>valor2;
  }
  if(strcmp(operacion,"&&")==0){
    nuevo->tipo="bool";
    nuevo->tipoNodo=13;
    nuevo->valor= valor1&&valor2;
  }
  if(strcmp(operacion,"||")==0){
    nuevo->tipo="bool";
    nuevo->tipoNodo=13;
    nuevo->valor= valor1||valor2;
  }
  return nuevo;
}

NodoArbol* nuevoLiteralun(char* operacion, int valor1){
  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
  if(strcmp(operacion,"-")==0){
    nuevo->tipo="int";
    nuevo->tipoNodo=12;
    nuevo->valor= valor1*-1;
  }
  if(strcmp(operacion,"!")==0){
    nuevo->tipo="bool";
    nuevo->tipoNodo=13;
    nuevo->valor= !valor1;
  }
  return nuevo;
}

NodoArbol* optimizarExpresion(NodoArbol* nodoexp){
  printf("entro al optimizar\n");
  if(nodoexp==NULL){return NULL;}
  if(nodoexp->tipoNodo==14||nodoexp->tipoNodo==15){
    printf("OPTIMIZAR EXPRESION DE %s\n",nodoexp->nombre);
    nodoexp->op1 = optimizarExpresion(nodoexp->op1);

  }

  if(nodoexp->tipoNodo==14){
    nodoexp->op2 = optimizarExpresion(nodoexp->op2);
  }


  if (  nodoexp->tipoNodo==14&&   ((nodoexp->op1)->tipoNodo==12||(nodoexp->op1)->tipoNodo==13)    &&(nodoexp->op1)->tipoNodo==(nodoexp->op2)->tipoNodo){
    printf("eloperando 1 es %i\n",(nodoexp->op1)->valor);
    printf("eloperando 2 es %i\n",(nodoexp->op2)->valor);
    return nuevoLiteralbin(nodoexp->nombre,(nodoexp->op1)->valor,(nodoexp->op2)->valor);

  }
if(nodoexp->tipoNodo==15){

  if(nodoexp->op1!=NULL&& ((nodoexp->op1)->tipoNodo==12)||  (nodoexp->op1)->tipoNodo==13){
    printf("entro al ifloco rompedor\n");
    return nuevoLiteralun(nodoexp->nombre,(nodoexp->op1)->valor);
  }
}

  printf("no optimizo\n");
  return nodoexp;
}


void loadParametros(NodoArbol* parameters,int posicion){
  if(parameters==NULL){ return; }
  NodoInt* aux=malloc(sizeof(NodoInt));
  aux->operacion="LOADP";
  aux->nombre=parameters->nombre;
  aux->op1=pasarACodIntermedio(parameters);
  aux->nroparametro=posicion;
  loadParametros(parameters->next,posicion+1);
  agregarCodIntermedio(aux);
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
  currentOffSet=nodo->maxoffSet;
  nuevo->metodoOriginal=nodo;
  agregarCodIntermedio(nuevo);

  pasarACodIntermedio(nodo->cuerpo);

  nuevo = malloc(sizeof(NodoInt));
  nuevo->nombre = nodo->nombre;
  nuevo->operacion = "ENDMETODO";
  agregarCodIntermedio(nuevo);

  nodo->maxoffSet=currentOffSet;
  nuevo->metodoOriginal=nodo;
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
  nuevo->tipoNodo=1;
  nuevo->offSet = currentOffSet;
  currentOffSet =currentOffSet -8;

  printf("SE CREO LA VARIABLE %s tipo %s\n",nuevo->nombre,nuevo->tipo );
  return nuevo;
}


NodoArbol* pasarACodIntermedio(NodoArbol* nodo){
  if(nodo == NULL){
    printf("null pasarACodIntermedio\n");
    return NULL;}
  //printf("despues del null en pasarACodIntermedio\n");
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
    printf("\nhacemos el nodo call: el nombre del nodo es :%s\n",(nodo->call_metodo)->nombre);
    nuevo->nombre= (nodo->call_metodo)->nombre;
    if(strcmp((nodo->call_metodo)->tipo,"void")!=0){
      nuevo->op1=nuevaVariableTemporal((nodo->call_metodo)->tipo);
    }


    //ver si apuntamos al metodo
    loadParametros(nodo->call_params,1);
    agregarCodIntermedio(nuevo);
    return nuevo->op1;
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
    if(strcmp("-",nodo->nombre)==0){
      nuevo->operacion="RES";
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
    if(strcmp("&&",nodo->nombre)==0){
      printf("ENCONTRO EL ANDDDDDDDDD\n");
      nuevo->operacion="AND";
    }
    if(strcmp("||",nodo->nombre)==0){
      nuevo->operacion="OR";
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
  aux->offSet= currentOffSet;
  currentOffSet=currentOffSet-8;
  if(variableGlobalPila->nodoInferior==NULL){
    aux->isGlobal = 1;
  }else{
    aux->isGlobal = 0;
  }

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
  currentOffSet=-8;
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
  	//printf("funcion: %s\n", recorrido->nombre);;

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
      if (strcmp(recorrido->tipo,param_tipo)!=0){
        printf("ERROR linea %i: en la funcion %s se quiere retornar una expresion de distinto tipo que el tipo de retorno del metodo\n",recorrido->nrolinea, nombre_metodo);exit(0);}
      cant_ret_correctos=cant_ret_correctos+verifTiposRet(param_tipo,nombre_metodo,recorrido);
    }
    recorrido=recorrido->next;
  }

  //if (cant_ret_correctos==0){
  //  printf("ERROR: la funcion %s posee flujos de ejecucion sin return\n", nombre_metodo);
  //  exit(0);
  // }
  return cant_ret_correctos;
}


void controlTiposMetod(){
  NodoArbol* metodo = listametodos;
  while(metodo!=NULL){
    verifTipos(metodo->tipo,metodo->nombre,metodo->cuerpo);
    metodo=metodo->nextlista;

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

int unicoMetodo(char* nombre){
	NodoArbol* nuevo = malloc(sizeof(NodoArbol));
	nuevo = buscarVariableSC(nombre);
	if(nuevo==NULL){
		return 1;
	}
	return 0;
}

int unicaVariable(char* nombre){
	NodoArbol* nuevo = malloc(sizeof(NodoArbol));
	//printf("nombre variable : %s\n", nombre);
	nuevo = buscarMetodo(nombre);
	if(nuevo==NULL){
		return 1;
	}
	return 0;
}

void argumentosMain(NodoArbol* main){
  NodoArbol* parametros=main->param;
  if(parametros!=NULL){
    printf("ERROR linea %i: el metodo main no debe tener ningun parametro.\n", main->nrolinea);
    exit(0);
  }
}

void verificarMain(NodoArbol* listMeth){
  NodoArbol* recorrido=listMeth;
  int cantMain=0;
  while (recorrido!=NULL) {
    if(strcmp(recorrido->nombre,"main")==0){
      cantMain++;
    //  argumentosMain(recorrido);
    }
    recorrido=recorrido->nextlista;
  }
  if(cantMain==0){
    printf("ERROR: el programa no tiene definido un metodo 'main'(y debe tener unicamente uno).\n");
    exit(0);
  }
}


void corregirOffSetParametro(NodoArbol* param,int pos){
  if (param==NULL){return;}
  if(param!=NULL){
    param->posicionParametro=pos;
    if(pos>6){
        param->offSet=16+(pos-7)*8;  //para que el 7mo lo dje en 16, el 8vo en 24
    }

  }
  corregirOffSetParametro(param->nextlista,pos+1);
}






char *aux;

NodoArbol *nodoauxiliar ; //este puntero apunta al primer statement cuando se arma la lista de los statements
NodoArbol *nodoauxiliarAnt ; // lo usamos para guardar el nodo anterior al nodoauxiliar

#line 1252 "calc-sintaxis.tab.c" /* yacc.c:339  */

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
#line 1187 "calc-sintaxis.y" /* yacc.c:355  */
 int i; char *s; char c; struct nodoArbol *p; struct infoString *infos; struct infoInt *infoi  ;

#line 1331 "calc-sintaxis.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 1348 "calc-sintaxis.tab.c" /* yacc.c:358  */

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
#define YYLAST   295

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

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
       0,  1262,  1262,  1262,  1277,  1281,  1285,  1289,  1295,  1300,
    1324,  1348,  1349,  1352,  1377,  1377,  1398,  1427,  1427,  1454,
    1454,  1456,  1457,  1462,  1462,  1464,  1466,  1468,  1470,  1474,
    1475,  1478,  1479,  1495,  1500,  1514,  1528,  1544,  1559,  1566,
    1572,  1590,  1592,  1597,  1599,  1614,  1632,  1637,  1638,  1642,
    1658,  1674,  1690,  1706,  1722,  1738,  1754,  1770,  1787,  1804,
    1820,  1836,  1837,  1850,  1851,  1856,  1865,  1867,  1876
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
  "listamethod_decl", "method_decl", "$@2", "$@3", "param_decl", "$@4",
  "Nparam_decl", "block", "$@5", "Nblock", "listavar_decl",
  "listastatement", "type", "statement", "method_call", "param_call",
  "ultparam_call", "expr", "literal", "bool_literal", YY_NULLPTR
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

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -53,     7,     4,   -53,   -18,   -53,    28,    15,   -53,   -53,
     -53,   -53,    64,   -53,   122,    33,    19,   -53,   -53,    44,
     -53,   -53,   129,    38,     1,    40,    38,   -53,    42,    65,
     -53,   -53,    45,    18,   -53,    47,   -53,   -53,   -53,    57,
      66,   -53,   -53,   -53,    48,   -53,    18,   -53,   -53,   -53,
      60,   -53,    78,    20,    62,   107,    71,   -53,   -53,   -53,
      85,    22,    81,   -53,    80,   -53,   104,   130,   130,   -53,
      77,   -53,   -53,   130,   130,   -53,   130,   -53,   140,   -53,
     -53,   130,   -53,    79,   -53,   -53,   -53,   -53,   -53,    86,
      82,   220,   156,   172,   -53,   -53,   188,   130,   130,   130,
     130,   130,   -53,   130,   130,   130,   130,   130,   204,   -53,
     -53,   130,   -53,    98,   -53,    -8,    -8,   -53,   -53,   -53,
     265,   271,   271,   251,   236,   -53,   220,   -53,   -53,   111,
     -53,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     0,    33,    34,
       4,    29,     0,    11,     0,     0,     0,     6,    12,     0,
       5,    30,     0,     9,     0,    19,     0,     7,    19,     0,
       8,    17,     0,     0,    14,     0,    10,    23,    23,    20,
       0,    23,    23,    18,     0,    16,     0,    21,    15,    13,
      23,    24,     0,     0,     0,     0,     0,    42,    28,    43,
      23,    23,     0,    31,     0,    22,     0,     0,     0,    65,
      62,    67,    68,     0,     0,    39,     0,    63,     0,    64,
      66,     0,    26,    23,    27,    32,     9,    41,    44,     0,
      46,    47,     0,     0,    59,    60,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,     0,     0,     0,    25,
      45,     0,    40,     0,    61,    49,    50,    51,    52,    53,
      56,    54,    55,    57,    58,    23,    48,    23,    37,    35,
      23,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,   -53,   -53,   -11,   -53,   102,    -4,   -53,   -53,
      93,   -53,   -53,   -37,   -53,   -53,    73,    68,   -10,   -52,
     -44,   -53,   -53,   -46,   -53,   -53
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,    11,    24,    12,    13,    41,    37,
      32,    33,    39,    59,    44,    51,    14,    61,    15,    63,
      77,    89,    90,    78,    79,    80
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      43,    45,    19,    21,    48,    49,    64,     3,    18,    85,
       4,    99,    19,   100,   101,     6,    64,    64,    18,    16,
      91,    92,    93,    40,    29,    30,    53,    94,    95,    54,
      96,    85,     8,     9,    55,   108,    52,    23,    56,    64,
      62,     7,     8,     9,    25,    66,    57,    67,    26,    21,
      62,   115,   116,   117,   118,   119,    84,   120,   121,   122,
     123,   124,    10,    28,    53,   126,    31,    54,    34,    36,
      47,    38,    55,    42,     8,     9,    56,     7,     8,     9,
      46,    50,    65,    53,    57,    86,    54,    68,   128,    53,
     129,    55,    54,   131,    58,    56,    81,    55,    17,     8,
       9,    56,    66,    57,    87,   111,   127,    69,    70,    57,
      69,    70,   110,   109,    71,    72,    22,    71,    72,    82,
     130,    35,    73,    60,    74,    73,     0,    74,    83,    76,
      88,    75,    76,    69,    70,     7,     8,     9,     0,     0,
      71,    72,     7,     8,     9,     0,     0,     0,    73,     0,
      74,     0,     0,     0,     0,    76,    20,    97,    98,    99,
       0,   100,   101,    27,   102,     0,     0,     0,   103,   104,
     105,   106,   107,    97,    98,    99,     0,   100,   101,     0,
     112,     0,     0,     0,   103,   104,   105,   106,   107,    97,
      98,    99,     0,   100,   101,     0,     0,     0,   113,     0,
     103,   104,   105,   106,   107,    97,    98,    99,     0,   100,
     101,     0,     0,     0,   114,     0,   103,   104,   105,   106,
     107,    97,    98,    99,     0,   100,   101,     0,     0,     0,
     125,     0,   103,   104,   105,   106,   107,    97,    98,    99,
       0,   100,   101,     0,     0,     0,     0,     0,   103,   104,
     105,   106,   107,    97,    98,    99,     0,   100,   101,     0,
       0,     0,     0,     0,   103,   104,   105,   106,    97,    98,
      99,     0,   100,   101,     0,     0,     0,     0,     0,   103,
     104,   105,    97,    98,    99,     0,   100,   101,    97,    98,
      99,     0,   100,   101,   104,   105
};

static const yytype_int16 yycheck[] =
{
      37,    38,    12,    14,    41,    42,    50,     0,    12,    61,
       6,    19,    22,    21,    22,    33,    60,    61,    22,     4,
      66,    67,    68,    33,    23,    24,     4,    73,    74,     7,
      76,    83,    14,    15,    12,    81,    46,     4,    16,    83,
      50,    13,    14,    15,    25,    25,    24,    27,     4,    60,
      60,    97,    98,    99,   100,   101,    34,   103,   104,   105,
     106,   107,    34,    25,     4,   111,    26,     7,    26,     4,
       4,    26,    12,    26,    14,    15,    16,    13,    14,    15,
      23,    33,     4,     4,    24,     4,     7,    25,   125,     4,
     127,    12,     7,   130,    34,    16,    25,    12,    34,    14,
      15,    16,    25,    24,    24,    23,     8,     3,     4,    24,
       3,     4,    26,    34,    10,    11,    14,    10,    11,    34,
       9,    28,    18,    50,    20,    18,    -1,    20,    60,    25,
      26,    24,    25,     3,     4,    13,    14,    15,    -1,    -1,
      10,    11,    13,    14,    15,    -1,    -1,    -1,    18,    -1,
      20,    -1,    -1,    -1,    -1,    25,    34,    17,    18,    19,
      -1,    21,    22,    34,    24,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    17,    18,    19,    -1,    21,    22,    -1,
      24,    -1,    -1,    -1,    28,    29,    30,    31,    32,    17,
      18,    19,    -1,    21,    22,    -1,    -1,    -1,    26,    -1,
      28,    29,    30,    31,    32,    17,    18,    19,    -1,    21,
      22,    -1,    -1,    -1,    26,    -1,    28,    29,    30,    31,
      32,    17,    18,    19,    -1,    21,    22,    -1,    -1,    -1,
      26,    -1,    28,    29,    30,    31,    32,    17,    18,    19,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    17,    18,    19,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    17,    18,
      19,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    17,    18,    19,    -1,    21,    22,    17,    18,
      19,    -1,    21,    22,    29,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,     0,     6,    39,    33,    13,    14,    15,
      34,    40,    42,    43,    52,    54,     4,    34,    43,    54,
      34,    40,    42,     4,    41,    25,     4,    34,    25,    23,
      24,    26,    46,    47,    26,    46,     4,    45,    26,    48,
      54,    44,    26,    49,    50,    49,    23,     4,    49,    49,
      33,    51,    54,     4,     7,    12,    16,    24,    34,    49,
      52,    53,    54,    55,    56,     4,    25,    27,    25,     3,
       4,    10,    11,    18,    20,    24,    25,    56,    59,    60,
      61,    25,    34,    53,    34,    55,     4,    24,    26,    57,
      58,    59,    59,    59,    59,    59,    59,    17,    18,    19,
      21,    22,    24,    28,    29,    30,    31,    32,    59,    34,
      26,    23,    24,    26,    26,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    26,    59,     8,    49,    49,
       9,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    38,    37,    39,    39,    39,    39,    40,    41,
      41,    42,    42,    43,    44,    43,    43,    45,    43,    47,
      46,    48,    48,    50,    49,    51,    51,    51,    51,    52,
      52,    53,    53,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    57,    58,    58,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    61,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     3,     4,     4,     5,     3,     1,
       3,     1,     2,     6,     0,     6,     6,     0,     6,     0,
       2,     2,     4,     0,     2,     4,     3,     3,     2,     1,
       2,     1,     2,     1,     1,     6,     8,     5,     3,     2,
       4,     2,     1,     1,     3,     4,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     1,     1,     1,     1,     1,     1,     1
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
#line 1262 "calc-sintaxis.y" /* yacc.c:1646  */
    {
      inicializar();}
#line 2548 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 1263 "calc-sintaxis.y" /* yacc.c:1646  */
    {
        //eliminarNivelPila();
        controlTiposMetod();
        verificarMain(listametodos);
        printf("ANTES DE CODIGO intermedio\n");
        if(listametodos==NULL){
          printf("listametodos es NULL\n");
        }
        codIntermedio(listametodos);
        printf("DESPUES DE CODIGO intermedio\n");
        imprimirLista(codigoIntermedio);
        codAssembler();
    }
#line 2566 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 1277 "calc-sintaxis.y" /* yacc.c:1646  */
    {
  // printf("TERMINO1\n");
}
#line 2574 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 1281 "calc-sintaxis.y" /* yacc.c:1646  */
    {
    // printf("\nTERMINO2");
}
#line 2582 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 1285 "calc-sintaxis.y" /* yacc.c:1646  */
    {
    // printf("\nTERMINO3");
  }
#line 2590 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 1289 "calc-sintaxis.y" /* yacc.c:1646  */
    {
    // printf("\nTERMINO4");
  }
#line 2598 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 1295 "calc-sintaxis.y" /* yacc.c:1646  */
    {
  // printf("\ndeclaracion de var finalizada");
}
#line 2606 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 1300 "calc-sintaxis.y" /* yacc.c:1646  */
    {
				if(variableGlobalPila->nodoInferior==NULL){
					if((buscarVariableSC((yyvsp[0].infos)->info)==NULL)&&(unicaVariable((yyvsp[0].infos)->info)==1)){
                      // printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
                    }else{
                      printf("ERROR linea %i: id %s ya esta declarado \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info);
                      //printf("ERROR linea %i; la variable %s ya esta declarada \n",$1->linea,$1->info);
                      exit(0);
                      }

				}else{
					if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
                      // printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
                    }else{
                      printf("ERROR linea %i: id %s ya esta declarado \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info);
                      //printf("ERROR linea %i; la variable %s ya esta declarada \n",$1->linea,$1->info);
                      exit(0);
                      }
                }
              }
#line 2633 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 1324 "calc-sintaxis.y" /* yacc.c:1646  */
    {
				if(variableGlobalPila->nodoInferior==NULL){
	                  if((buscarVariableSC((yyvsp[0].infos)->info)==NULL)&&(unicaVariable((yyvsp[0].infos)->info)==1)){
	                  //  printf("%s\n","la variable no esta en el scope!!" );
	                    nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
	                  }else{
	                   printf("ERROR linea %i: id %s ya esta declarado \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info);
	                   // printf("ERROR linea %i; la variable %s ya esta declarada \n",$3->linea,$3->info);
	                    exit(0);
	                  }
	            }else{
	            	if(buscarVariableSC((yyvsp[0].infos)->info)==NULL){
	                  //  printf("%s\n","la variable no esta en el scope!!" );
	                    nuevaVariable((yyvsp[0].infos)->info,aux,(yyvsp[0].infos)->linea);
	                  }else{
	                   printf("ERROR linea %i: id %s ya esta declarado \n",(yyvsp[0].infos)->linea,(yyvsp[0].infos)->info);
	                   // printf("ERROR linea %i; la variable %s ya esta declarada \n",$3->linea,$3->info);
	                    exit(0);
	                  }
	            }
  }
#line 2659 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 1348 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->nextlista=listametodos;listametodos=(yyvsp[0].p);}
#line 2665 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 1349 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->nextlista=listametodos;listametodos=(yyvsp[0].p);}
#line 2671 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 1352 "calc-sintaxis.y" /* yacc.c:1646  */
    {

  // printf("declaracion de metodo2\n");
  NodoArbol *aux= malloc(sizeof(NodoArbol));

  aux->tipo=(yyvsp[-5].s);
  aux->tipoNodo=2;
  aux->nombre= (yyvsp[-4].infos)->info;
  aux->cuerpo = (yyvsp[0].p);
  aux->nrolinea =(yyvsp[-4].infos)->linea;
  aux->param = variableGlobalPila->lista;
  corregirOffSetParametro(aux->param,1);
  aux->maxoffSet = currentOffSet;
  eliminarNivelPila();
  if((verificarMetodoDeclarado(aux->nombre)==1)||(unicoMetodo(aux->nombre)==0)){
														    printf("ERROR en linea %i : id %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
														    //printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
    exit(0);
  };
  if(strcmp(aux->nombre,"main")==0){
    argumentosMain(aux);
  }
  (yyval.p) = aux;
}
#line 2700 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 1377 "calc-sintaxis.y" /* yacc.c:1646  */
    {currentOffSet=-8;}
#line 2706 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 1377 "calc-sintaxis.y" /* yacc.c:1646  */
    {
								                // printf("declaracion de metodo1\n");
								                NodoArbol *aux= malloc(sizeof(NodoArbol));

								                aux->tipo=(yyvsp[-5].s);
								                aux->tipoNodo=2;
								                aux->nombre= (yyvsp[-4].infos)->info;
								                aux->cuerpo = (yyvsp[0].p);
								                aux->nrolinea =(yyvsp[-4].infos)->linea;
                                aux->maxoffSet = currentOffSet;
                                aux->param=NULL;
                                corregirOffSetParametro(aux->param,1);
                                if(verificarMetodoDeclarado(aux->nombre)==1||(unicoMetodo(aux->nombre)==0)){
								                  printf("ERROR en linea %i : id %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
								                  //printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
								                  exit(0);
								                };
								                (yyval.p) = aux;
								                }
#line 2730 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 1398 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                    // printf("declaracion de metodo4\n");

                                                    NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                    aux->tipo="void";
                                                    aux->tipoNodo=2;
                                                    aux->nombre= (yyvsp[-4].infos)->info;
                                                    aux->cuerpo = (yyvsp[0].p);
                                                    aux->nrolinea =(yyvsp[-4].infos)->linea;
                                                    aux->param = variableGlobalPila->lista;
                                                    corregirOffSetParametro(aux->param,1);
                                                    aux->maxoffSet = currentOffSet;
                                                    if(verificarMetodoDeclarado(aux->nombre)==1||(unicoMetodo(aux->nombre)==0)){
                                                      printf("ERROR en linea %i : id %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                      //printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                      exit(0);
                                                    };
                                                    eliminarNivelPila();

                                                    if(strcmp((yyvsp[-4].infos)->info,"main")==0){

                                                      argumentosMain(aux);
                                                    }


                                                    (yyval.p) = aux;

                                                  }
#line 2764 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 1427 "calc-sintaxis.y" /* yacc.c:1646  */
    {currentOffSet=-8;}
#line 2770 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 1427 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                  // printf("declaracion de metodo3\n");

                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo="void";
                                                  aux->tipoNodo=2;
                                                  aux->nombre= (yyvsp[-4].infos)->info;
                                                  aux->cuerpo = (yyvsp[0].p);
                                                  aux->nrolinea =(yyvsp[-4].infos)->linea;
                                                  aux->maxoffSet = currentOffSet;
                                                  aux->param=NULL;
                                                  corregirOffSetParametro(aux->param,1);
                                                  if(verificarMetodoDeclarado(aux->nombre)==1||(unicoMetodo(aux->nombre)==0)){
                                                  	//cambiar mensaje por id ya declarado
                                                    //printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                    printf("ERROR en linea %i : id %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                    exit(0);
                                                  };
                                                  (yyval.p) = aux;
                                                  }
#line 2796 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 1454 "calc-sintaxis.y" /* yacc.c:1646  */
    {currentOffSet=-8;nuevoNivelPila();}
#line 2802 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 1456 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevaVariable((yyvsp[0].infos)->info,(yyvsp[-1].s),(yyvsp[0].infos)->linea);}
#line 2808 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 1457 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevaVariable((yyvsp[0].infos)->info,(yyvsp[-1].s),(yyvsp[-2].infos)->linea);}
#line 2814 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 1462 "calc-sintaxis.y" /* yacc.c:1646  */
    {nuevoNivelPila();}
#line 2820 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 1462 "calc-sintaxis.y" /* yacc.c:1646  */
    {eliminarNivelPila(); (yyval.p)=(yyvsp[0].p);}
#line 2826 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 1464 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p)->first;}
#line 2832 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 1466 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2838 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 1468 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p)->first;}
#line 2844 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 1470 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2850 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 1474 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2856 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 1475 "calc-sintaxis.y" /* yacc.c:1646  */
    {}
#line 2862 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 1478 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->first=(yyvsp[0].p);(yyval.p)=(yyvsp[0].p);}
#line 2868 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 1479 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 2886 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 1495 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                aux="int";
                (yyval.s)=aux;
                }
#line 2895 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 1500 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  aux="bool";
                  (yyval.s)=aux;
                  }
#line 2904 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 1514 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                              NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                                              if(strcmp((yyvsp[-3].p)->tipo,"bool")!=0){
                                                                printf("ERROR linea %i : la sentecia 'if' requiere una expresion booleana.\n",(yyvsp[-5].i));
                                                                exit(0);
                                                              }

                                                              nuevo->tipoNodo=3;
                                                              nuevo->tcondicion = (yyvsp[-3].p);
                                                              nuevo->tthen = (yyvsp[0].p);
                                                              nuevo->nrolinea =(yyvsp[-5].i);
                                                              (yyval.p)=nuevo;
                                                            }
#line 2923 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 1528 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                                                        NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                                                        if(strcmp((yyvsp[-5].p)->tipo,"bool")!=0){
                                                                          printf("ERROR linea %i : la sentecia 'if' requiere una expresion booleana.\n",(yyvsp[-7].i));
                                                                          exit(0);
                                                                        }

                                                                        nuevo->tipoNodo=4;
                                                                        nuevo->tcondicion = (yyvsp[-5].p);
                                                                        nuevo->tthen = (yyvsp[-2].p);
                                                                        nuevo->telse = (yyvsp[0].p);
                                                                        nuevo->nrolinea =(yyvsp[-7].i);
                                                                        (yyval.p)=nuevo;
                                                                      }
#line 2943 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1544 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                                        NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                        if(strcmp((yyvsp[-2].p)->tipo,"bool")!=0){
                                          printf("ERROR linea %i : la sentecia 'while' requiere una expresion booleana.\n",(yyvsp[-4].i));
                                          exit(0);
                                        }

                                        nuevo->tipoNodo=5;
                                        nuevo->tcondicion = (yyvsp[-2].p);
                                        nuevo->cuerpo = (yyvsp[0].p);
                                        nuevo->nrolinea =(yyvsp[-4].i);
                                        (yyval.p)=nuevo;
                                      }
#line 2962 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1559 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=6;
                                        nuevo->tipo=(yyvsp[-1].p)->tipo;
                                        nuevo->expresion = (yyvsp[-1].p);
                                        nuevo->nrolinea =(yyvsp[-2].i);
                                        (yyval.p)=nuevo;
                                      }
#line 2974 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1566 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=7;
                                        nuevo->nrolinea =(yyvsp[-1].i);
                                        nuevo->tipo="void";
                                        (yyval.p)=nuevo;
                                      }
#line 2985 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1572 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3008 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1590 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p);}
#line 3014 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1592 "calc-sintaxis.y" /* yacc.c:1646  */
    {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=10;
                                        nuevo->nrolinea =(yyvsp[0].infos)->linea;
                                        (yyval.p)=nuevo;
                                      }
#line 3024 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1597 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 3030 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1599 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3050 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1614 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3070 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1632 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p)->first;}
#line 3076 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1637 "calc-sintaxis.y" /* yacc.c:1646  */
    { (yyvsp[0].p)->first=(yyvsp[0].p); (yyval.p)=(yyvsp[0].p);  }
#line 3082 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1638 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyvsp[0].p)->first=(yyvsp[-2].p)->first; (yyvsp[-2].p)->next = (yyvsp[0].p); (yyval.p)=(yyvsp[0].p);  }
#line 3088 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1642 "calc-sintaxis.y" /* yacc.c:1646  */
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
                      (yyval.p)=optimizarExpresion(nuevo);
                      }
#line 3109 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1658 "calc-sintaxis.y" /* yacc.c:1646  */
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
                          (yyval.p)=optimizarExpresion(nuevo);
                          }
#line 3130 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1674 "calc-sintaxis.y" /* yacc.c:1646  */
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
                          (yyval.p)=optimizarExpresion(nuevo);
                          }
#line 3151 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1690 "calc-sintaxis.y" /* yacc.c:1646  */
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
                          (yyval.p)=optimizarExpresion(nuevo);
                          }
#line 3172 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1706 "calc-sintaxis.y" /* yacc.c:1646  */
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
                          (yyval.p)=optimizarExpresion(nuevo);
                          }
#line 3193 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1722 "calc-sintaxis.y" /* yacc.c:1646  */
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
                          (yyval.p)=optimizarExpresion(nuevo);
                          }
#line 3214 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1738 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3235 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1754 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3256 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1770 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3278 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1787 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3299 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1804 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3320 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1820 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3341 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1836 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[-1].p);}
#line 3347 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1837 "calc-sintaxis.y" /* yacc.c:1646  */
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
#line 3365 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1850 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 3371 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1851 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 3377 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1856 "calc-sintaxis.y" /* yacc.c:1646  */
    {
              NodoArbol *nuevo= malloc(sizeof(NodoArbol));
              nuevo->tipo="int";
              nuevo->tipoNodo=12;
              nuevo->valor= (yyvsp[0].infoi)->info;
              nuevo->nrolinea =(yyvsp[0].infoi)->linea;
              (yyval.p)=nuevo;
              }
#line 3390 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1865 "calc-sintaxis.y" /* yacc.c:1646  */
    {(yyval.p)=(yyvsp[0].p);}
#line 3396 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1867 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                    nuevo->tipo="bool";
                    nuevo->tipoNodo=13;
                    nuevo->valor= 1;
                    nuevo->nrolinea =(yyvsp[0].i);
                    (yyval.p)=nuevo;
                  }
#line 3409 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1876 "calc-sintaxis.y" /* yacc.c:1646  */
    {
                  NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                  nuevo->tipo="bool";
                  nuevo->tipoNodo=13;
                  nuevo->valor=0;
                  nuevo->nrolinea =(yyvsp[0].i);
                  (yyval.p)=nuevo;
                }
#line 3422 "calc-sintaxis.tab.c" /* yacc.c:1646  */
    break;


#line 3426 "calc-sintaxis.tab.c" /* yacc.c:1646  */
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
#line 1887 "calc-sintaxis.y" /* yacc.c:1906  */

