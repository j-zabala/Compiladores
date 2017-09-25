
/*

   Pre-Proyecto de Compiladores 2017

   Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

 */

#include <stdio.h>
#include <stdlib.h>



/* estructura autoreferenciada */
typedef struct nodoArbol {
        int tipoNodo;

        struct nodoArbol *nextsentencia;
        struct nodoArbol *nextlista;

        struct nodoArbol *tcondicion;
        struct nodoArbol *tthen;
        struct nodoArbol *telse;

        struct NodoArbol* cuerpo;
        struct NodoArbol* param;
        char *tipo;
        char *nombre;
        int valor;
        int nrolinea;
} NodoArbol;

//struct nodoArbol NodoArbol; /* sinónimo de la estructura nodoArbol */
