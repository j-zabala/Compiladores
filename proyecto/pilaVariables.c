
/*

   Pre-Proyecto de Compiladores 2017

   Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

 */

#include <stdio.h>
#include <stdlib.h>



/* estructura autoreferenciada */
typedef struct nodoPila {
        struct nodoListaVariables *lista;
        struct nodoPila *nodoInferior;
        int nivelScope;

} NodoPila;
