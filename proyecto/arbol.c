
/*
   Pre-Proyecto de Compiladores 2017
   Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

 */

#include <stdio.h>
#include <stdlib.h>



/* estructura autoreferenciada */
typedef struct nodoArbol {
        int tipoNodo;
        struct nodoArbol *nextlista;

        struct nodoArbol *next;//proxima sentnecia

        struct nodoArbol *tcondicion;
        struct nodoArbol *tthen;
        struct nodoArbol *telse;

        struct nodoArbol *expresion;


        struct nodoArbol* cuerpo;
        struct nodoArbol* param; //se usa en la definicion de las funciones

        // atibutos de llamada a metodo
        struct nodoArbol* call_params;
        struct nodoArbol* call_metodo;

        struct nodoArbol* first;
        char *tipo;
        char *nombre;
        struct nodoArbol* valorExpresion;

        struct nodoArbol* op1;
        struct nodoArbol* op2;

        int offSet;
        int maxoffSet;
        int posicionParametro;
        int isGlobal;

        int valor;  //para los literales
        int nrolinea;
} NodoArbol;

//struct nodoArbol NodoArbol; /* sinónimo de la estructura nodoArbol */
