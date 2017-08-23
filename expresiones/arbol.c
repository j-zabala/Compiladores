/**
 * Crea un arbol binario y lo recorre en
 * preorden, inorden, y en postOrden
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
