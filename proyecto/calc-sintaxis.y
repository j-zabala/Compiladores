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
      cantidadenter=(((nodo->metodoOriginal)->maxoffSet)*-1);
    }else{
      cantidadenter=(((nodo->metodoOriginal)->maxoffSet)*-1)+16;
    }
    //printf("enter %i\n",cantidadenter );
    fprintf(arch, "  enter $%i,$0\n",cantidadenter);

    recuperarParametros((nodo->metodoOriginal)->param,1,arch);



    pasarACodAssembler(arch,nodo->next,metodonro);
    printf("nodo intermedio operacion: metodo\n");
  }

  if (strcmp(nodo->operacion,"ENDMETODO")==0){
    fprintf(arch, "  leave\n");
    fprintf(arch, ".LFE%i:\n",metodonro);
    fprintf(arch, "  .size	%s, .-%s\n",nodo->nombre,nodo->nombre );
    fprintf(arch, ".LC%i:\n",metodonro);
    char* aux= "\%i";
    fprintf(arch, "  .string	\"la funcion %s devuelve: %s \"  \n",(nodo->metodoOriginal)->nombre,aux);
    pasarACodAssembler(arch,nodo->next,metodonro+1);

  }


  if (strcmp(nodo->operacion,"MOV")==0){
    printf("mov en un mov p\n");
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
    printf("salio en un mov p\n");
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
       fprintf(arch, "  movq	$0, \%rax \n",(varAAssembler(nodo->op1)));
       fprintf(arch, "  call printf\n");
     }


     if(nodo->op1!=NULL){
       fprintf(arch, "  movq	%s, \%rax \n",(varAAssembler(nodo->op1)));
     }

       fprintf(arch, "  ret \n");
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
       fprintf(arch, "  cmp %s,1  \n",varAAssembler(nodo->op1));
       fprintf(arch, "  jne %s \n",nodo->nombre);
       pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"JMP")==0){
       fprintf(arch, "  jmp %s \n",nodo->nombre);
       pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"LABEL")==0){
       fprintf(arch, ".%s: \n",nodo->nombre);
       pasarACodAssembler(arch,nodo->next,metodonro);
     }

   if (strcmp(nodo->operacion,"SUM")==0){
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
      fprintf(arch, "  add	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }

   if (strcmp(nodo->operacion,"MULT")==0){
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
      fprintf(arch, "  imul	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"DIV")==0){
      fprintf(arch, "  movq	0, \%rdx \n");
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
      fprintf(arch, "  idiv %s \n",varAAssembler(nodo->op2));
      fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"MOD")==0){
      fprintf(arch, "  movq	0, \%rdx \n");
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
      fprintf(arch, "  idiv %s \n",varAAssembler(nodo->op2));
      fprintf(arch, "  movq	 \%rdx,%s \n",varAAssembler(nodo->op3));
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"MAYORQUE")==0){
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  cmpg	\%rax, \%rdx\n",varAAssembler(nodo->op2));
      fprintf(arch, "  jle	 %s \n",labelaux);
      fprintf(arch, "  movq	 1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"MENORQUE")==0){
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  cmpl	\%rax, \%rdx\n",varAAssembler(nodo->op2));
      fprintf(arch, "  jge	 %s \n",labelaux);
      fprintf(arch, "  movq	 1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"IGUAL")==0){
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op2));
      fprintf(arch, "  cmp	\%rax, \%rdx\n",varAAssembler(nodo->op2));
      fprintf(arch, "  jne	 %s \n",labelaux);
      fprintf(arch, "  movq	 1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
   if (strcmp(nodo->operacion,"NEGBOOL")==0){
      char* labelaux=nuevoLabel(".L");
      fprintf(arch, "  movq	 0,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "  movq	%s, \%rdx \n",varAAssembler(nodo->op1));
      fprintf(arch, "  cmp	1, \%rdx\n");
      fprintf(arch, "  je	 %s \n",labelaux);
      fprintf(arch, "  movq	 1,%s \n",varAAssembler(nodo->op3));
      fprintf(arch, "%s: \n",labelaux);
      pasarACodAssembler(arch,nodo->next,metodonro);
     }
     if (strcmp(nodo->operacion,"NEGINT")==0){
        fprintf(arch, "  movq	%s, \%rax \n",varAAssembler(nodo->op1));
        fprintf(arch, "  imul	-1, \%rax \n");
        fprintf(arch, "  movq	 \%rax,%s \n",varAAssembler(nodo->op3));
        pasarACodAssembler(arch,nodo->next,metodonro);
       }




       return;

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

    program: {
      inicializar();} clases {
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

clases: CLASS  LLAVEABRE LLAVECIERRA          {
  // printf("TERMINO1\n");
}

	| CLASS  LLAVEABRE  listavar_decl   LLAVECIERRA  {
    // printf("\nTERMINO2");
}

  | CLASS  LLAVEABRE listamethod_decl  LLAVECIERRA  {
    // printf("\nTERMINO3");
  }

  | CLASS  LLAVEABRE listavar_decl  listamethod_decl  LLAVECIERRA  {
    // printf("\nTERMINO4");
  }

;

var_decl: type  listaID PUNTOYCOMA   {
  // printf("\ndeclaracion de var finalizada");
};
;

listaID : ID  {
				if(variableGlobalPila->nodoInferior==NULL){
					if((buscarVariableSC($1->info)==NULL)&&(unicaVariable($1->info)==1)){
                      // printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable($1->info,aux,$1->linea);
                    }else{
                      printf("ERROR linea %i: id %s ya esta declarado \n",$1->linea,$1->info);
                      //printf("ERROR linea %i; la variable %s ya esta declarada \n",$1->linea,$1->info);
                      exit(0);
                      }

				}else{
					if(buscarVariableSC($1->info)==NULL){
                      // printf("%s\n","la variable no esta en el scope!!" );
                      nuevaVariable($1->info,aux,$1->linea);
                    }else{
                      printf("ERROR linea %i: id %s ya esta declarado \n",$1->linea,$1->info);
                      //printf("ERROR linea %i; la variable %s ya esta declarada \n",$1->linea,$1->info);
                      exit(0);
                      }
                }
              }


| listaID COMA ID {
				if(variableGlobalPila->nodoInferior==NULL){
	                  if((buscarVariableSC($3->info)==NULL)&&(unicaVariable($3->info)==1)){
	                  //  printf("%s\n","la variable no esta en el scope!!" );
	                    nuevaVariable($3->info,aux,$3->linea);
	                  }else{
	                   printf("ERROR linea %i: id %s ya esta declarado \n",$3->linea,$3->info);
	                   // printf("ERROR linea %i; la variable %s ya esta declarada \n",$3->linea,$3->info);
	                    exit(0);
	                  }
	            }else{
	            	if(buscarVariableSC($3->info)==NULL){
	                  //  printf("%s\n","la variable no esta en el scope!!" );
	                    nuevaVariable($3->info,aux,$3->linea);
	                  }else{
	                   printf("ERROR linea %i: id %s ya esta declarado \n",$3->linea,$3->info);
	                   // printf("ERROR linea %i; la variable %s ya esta declarada \n",$3->linea,$3->info);
	                    exit(0);
	                  }
	            }
  }
;


listamethod_decl : method_decl {$1->nextlista=listametodos;listametodos=$1;}
| listamethod_decl method_decl {$2->nextlista=listametodos;listametodos=$2;}


method_decl: type ID PARENTESISABRE param_decl PARENTESISCIERRA block {

  // printf("declaracion de metodo2\n");
  NodoArbol *aux= malloc(sizeof(NodoArbol));

  aux->tipo=$1;
  aux->tipoNodo=2;
  aux->nombre= $2->info;
  aux->cuerpo = $6;
  aux->nrolinea =$2->linea;
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
  $$ = aux;
}

|type ID PARENTESISABRE PARENTESISCIERRA {currentOffSet=-8;} block {
								                // printf("declaracion de metodo1\n");
								                NodoArbol *aux= malloc(sizeof(NodoArbol));

								                aux->tipo=$1;
								                aux->tipoNodo=2;
								                aux->nombre= $2->info;
								                aux->cuerpo = $6;
								                aux->nrolinea =$2->linea;
                                aux->maxoffSet = currentOffSet;
                                aux->param=NULL;
                                corregirOffSetParametro(aux->param,1);
                                if(verificarMetodoDeclarado(aux->nombre)==1||(unicoMetodo(aux->nombre)==0)){
								                  printf("ERROR en linea %i : id %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
								                  //printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
								                  exit(0);
								                };
								                $$ = aux;
								                }


  |VOID ID PARENTESISABRE param_decl PARENTESISCIERRA block {
                                                    // printf("declaracion de metodo4\n");

                                                    NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                    aux->tipo="void";
                                                    aux->tipoNodo=2;
                                                    aux->nombre= $2->info;
                                                    aux->cuerpo = $6;
                                                    aux->nrolinea =$2->linea;
                                                    aux->param = variableGlobalPila->lista;
                                                    corregirOffSetParametro(aux->param,1);
                                                    aux->maxoffSet = currentOffSet;
                                                    if(verificarMetodoDeclarado(aux->nombre)==1||(unicoMetodo(aux->nombre)==0)){
                                                      printf("ERROR en linea %i : id %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                      //printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                      exit(0);
                                                    };
                                                    eliminarNivelPila();

                                                    if(strcmp($2->info,"main")==0){

                                                      argumentosMain(aux);
                                                    }


                                                    $$ = aux;

                                                  }
  |VOID ID PARENTESISABRE PARENTESISCIERRA {currentOffSet=-8;} block {
                                                  // printf("declaracion de metodo3\n");

                                                  NodoArbol *aux= malloc(sizeof(NodoArbol));

                                                  aux->tipo="void";
                                                  aux->tipoNodo=2;
                                                  aux->nombre= $2->info;
                                                  aux->cuerpo = $6;
                                                  aux->nrolinea =$2->linea;
                                                  aux->maxoffSet = currentOffSet;
                                                  aux->param=NULL;
                                                  corregirOffSetParametro(aux->param,1);
                                                  if(verificarMetodoDeclarado(aux->nombre)==1||(unicoMetodo(aux->nombre)==0)){
                                                  	//cambiar mensaje por id ya declarado
                                                    //printf("ERROR en linea %i : metodo %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                    printf("ERROR en linea %i : id %s ya declarado  anteriormente  \n",aux->nrolinea,aux->nombre);
                                                    exit(0);
                                                  };
                                                  $$ = aux;
                                                  }


;



param_decl : {currentOffSet=-8;nuevoNivelPila();} Nparam_decl

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

                                                              if(strcmp($3->tipo,"bool")!=0){
                                                                printf("ERROR linea %i : la sentecia 'if' requiere una expresion booleana.\n",$1);
                                                                exit(0);
                                                              }

                                                              nuevo->tipoNodo=3;
                                                              nuevo->tcondicion = $3;
                                                              nuevo->tthen = $6;
                                                              nuevo->nrolinea =$1;
                                                              $$=nuevo;
                                                            }
          | IF PARENTESISABRE expr PARENTESISCIERRA THEN block ELSE block  {
                                                                        NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                                                        if(strcmp($3->tipo,"bool")!=0){
                                                                          printf("ERROR linea %i : la sentecia 'if' requiere una expresion booleana.\n",$1);
                                                                          exit(0);
                                                                        }

                                                                        nuevo->tipoNodo=4;
                                                                        nuevo->tcondicion = $3;
                                                                        nuevo->tthen = $6;
                                                                        nuevo->telse = $8;
                                                                        nuevo->nrolinea =$1;
                                                                        $$=nuevo;
                                                                      }

          | WHILE PARENTESISABRE expr PARENTESISCIERRA block {
                                        NodoArbol *nuevo= malloc(sizeof(NodoArbol));

                                        if(strcmp($3->tipo,"bool")!=0){
                                          printf("ERROR linea %i : la sentecia 'while' requiere una expresion booleana.\n",$1);
                                          exit(0);
                                        }

                                        nuevo->tipoNodo=5;
                                        nuevo->tcondicion = $3;
                                        nuevo->cuerpo = $5;
                                        nuevo->nrolinea =$1;
                                        $$=nuevo;
                                      }

          | RETURN expr PUNTOYCOMA {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=6;
                                        nuevo->tipo=$2->tipo;
                                        nuevo->expresion = $2;
                                        nuevo->nrolinea =$1;
                                        $$=nuevo;
                                      }
          | RETURN PUNTOYCOMA {    NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=7;
                                        nuevo->nrolinea =$1;
                                        nuevo->tipo="void";
                                        $$=nuevo;
                                      }
          | ID ASIG expr PUNTOYCOMA {   NodoArbol *nuevo= malloc(sizeof(NodoArbol));
                                        nuevo->tipoNodo=8;
                                        nuevo->nombre=$1->info;
                                        //printf("asignacion, nombre variable %s \n",$1->info);
                                        nuevo->op1=buscarVariable($1->info);
                                        //printf("volvio de buscar la variable");
                                        if(nuevo->op1==NULL){
                                          printf("ERROR linea %i : variable %s no declarada\n",$2->linea,$1->info);
                                          exit(0);
                                        }
                                        nuevo->expresion = $3;
                                        if(strcmp((nuevo->op1)->tipo,(nuevo->expresion)->tipo)!=0){
                                          printf("ERROR linea %i : se esta asignando una expr %s a una variable %s \n",$2->linea,(nuevo->op1)->tipo,(nuevo->expresion)->tipo);
                                          exit(0);
                                        }
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
                                                verificarTipoParametros(nuevo);
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
                                                verificarTipoParametros(nuevo);
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
                                    nuevo->tipo = (nuevo->op1)->tipo;
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
