
/*

   Pre-Proyecto de Compiladores 2017

   Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

 */

#include <stdio.h>
#include <stdlib.h>



/* estructura autoreferenciada */
typedef struct nodoArbol {

        struct nodoArbol *next;
        // 
        struct nodoArbol *condicion;
        struct nodoArbol *then;
        struct nodoArbol *else;



        int tipo;
        char *nombre;
        int valor;
} NodoArbol;

//struct nodoArbol NodoArbol; /* sinónimo de la estructura nodoArbol */
