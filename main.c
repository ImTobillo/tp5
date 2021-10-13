#include <stdio.h>
#include <stdlib.h>

/// estructuras

typedef struct nodoA
{
    int dato;
    struct nodoA* izq;
    struct nodoA* der;
}nodoA;

/// funciones

void inicArbol (nodoA** arbol)
{
    *arbol = NULL;
}

nodoA* crearNodoA (int dato)
{
    nodoA* aux = (nodoA*)malloc(sizeof(nodoA));
    aux->dato = dato;
    aux->der = NULL;
    aux->izq = NULL;
    return aux;
}




/// main

int main()
{
    nodoA* arbol;

    inicArbol(&arbol);




    return 0;
}
