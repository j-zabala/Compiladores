
/*

   Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

 */

#include <stdio.h>
#include <stdlib.h>



/* estructura autoreferenciada */
// ESTRUCTURA DE LA LISTA DE OPERACIONES DE CODIGO INTERMEDIO
typedef struct nodoInt {
        int tipoNodo;
        struct nodoInt *next;//proxima sentnecia
        char *tipo;
        char *operacion;
        char * nombre;
        struct nodoArbol* op1;
        struct nodoArbol* op2;
        struct nodoArbol* op3;
        struct nodoArbol* metodoOriginal;
        int nroparametro;
} NodoInt;
