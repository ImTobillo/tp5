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

int contarNodosHoja (nodoA* arbol)
{
    if (arbol)
    {
        if (arbol->izq == NULL && arbol->der == NULL)
            return 1;
        else
            return contarNodosHoja(arbol->izq) + contarNodosHoja(arbol->der);
    }
    else
        return 0;
}

int buscarDatoArbol (nodoA* arbol, int dato)
{
    int rta;

    if (arbol)
    {
        if (arbol->dato == dato)
            return 1;
        else
        {
            rta = buscarDatoArbol(arbol->izq, dato);
            if (rta == 0)
            {
                rta =
            }
        }

    }
    else
        return 0;


}



/// main

int main()
{
    nodoA* arbol;

    inicArbol(&arbol);

    arbol = crearNodoA(3);
    arbol->izq = crearNodoA(7);
    arbol->izq->izq = crearNodoA(2);
    arbol->der = crearNodoA(10);
    arbol->der->izq = crearNodoA(1);
    arbol->der->der = crearNodoA(12);
    arbol->der->der->izq = crearNodoA(15);
    arbol->der->der->der = crearNodoA(6);

    //printf("%i", arbol->der->izq->dato);

    printf("%i", contarNodosHoja(arbol));




    return 0;
}
