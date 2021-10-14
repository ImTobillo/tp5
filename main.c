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
                rta = buscarDatoArbol(arbol->der, dato);

            return rta;
        }

    }
    else
        return 0;
}

int buscarDatoArbol2 (nodoA* arbol, int dato)
{
    int rta = 0;

    if (arbol)
    {
        if (arbol->dato == dato) // condicion de corte
            return 1; // solucion trivial
        else
        {
            rta = buscarDatoArbol2(arbol->izq, dato); // caso recursivo 1
            if (rta == 0)
                rta = buscarDatoArbol2(arbol->der, dato); // caso recursivo 2
        }
    }
    return rta;
}

void mostrarPreorden (nodoA* arbol)
{
    if (arbol)
    {
        printf("%i\t", arbol->dato);
        mostrarPreorden(arbol->izq);
        mostrarPreorden(arbol->der);
    }
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

    printf("CANTIDAD NODOS HOJA: %i\n", contarNodosHoja(arbol));
    printf("EXISTE %i?: %i\n\n", 4, buscarDatoArbol2(arbol, 4));

    printf("ARBOL PREORDEN:\t");
    mostrarPreorden(arbol);


    return 0;
}
