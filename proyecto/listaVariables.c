
/*

   Pre-Proyecto de Compiladores 2017

   Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

 */

#include <stdio.h>
#include <stdlib.h>



/* estructura autoreferenciada */
typedef struct nodoListaVariables {
        struct nodoListaVariables *next;
        char *tipo;
        char *nombre;
        int valor;

} NodoListaVariables;
