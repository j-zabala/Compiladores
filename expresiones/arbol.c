
/*

Pre-Proyecto de Compiladores 2017 

Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi 

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/* estructura autoreferenciada */
typedef struct nodoArbol {
  struct nodoArbol *hIzq;
  struct nodoArbol *hDer;

  int tipo;
  char *nombre;
  int valor;
} NodoArbol;

 //struct nodoArbol NodoArbol; /* sinónimo de la estructura nodoArbol */
