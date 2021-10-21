#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
#include "string.h"

/// estructuras

typedef struct nodoA
{
    int dato;
    struct nodoA* izq;
    struct nodoA* der;
} nodoA;

typedef struct
{
    int legajo;
    char nombre[20];
    int edad;
}Persona;

typedef struct nodoABB
{
    Persona dato;
    struct nodoABB* izq;
    struct nodoABB* der;
}nodoABB;

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

/// funciones ABB

int buscarABB_int (nodoA* arbol, int dato)
{
    if (arbol)
    {
        if (arbol->dato == dato)
            return 1;
        else
        {
            if (arbol->dato < dato)
                return buscarABB_int(arbol->der, dato);
            else
                return buscarABB_int(arbol->izq, dato);
        }
    }
    else
        return 0;
}

int buscarABB_intRep (nodoA* arbol, int dato)
{
    while (arbol && arbol->dato != dato)
    {
        if (arbol->dato > dato)
            arbol = arbol->izq;
        else
            arbol = arbol->der;
    }

    if (arbol)
        return 1;
    else
        return 0;
}

void insertarABB_Int (nodoA** arbolABB, int dato)
{
    if (*arbolABB)
    {
        if ((*arbolABB)->dato < dato)
            insertarABB_Int(&(*arbolABB)->der, dato);
        else if ((*arbolABB)->dato > dato)
            insertarABB_Int(&(*arbolABB)->izq, dato);
    }
    else
        *arbolABB = crearNodoA(dato);
}

void insertarABB_IntRep (nodoA** arbolABB, int dato)
{
    if (*arbolABB)
    {
        nodoA* aux = *arbolABB;

        while ((aux->izq && aux->dato > dato) || (aux->der && aux->dato < dato))
        {
            if (aux->dato > dato)
                aux = aux->izq;
            else
                aux = aux->der;
        }

        if (aux->izq == NULL && aux->dato > dato)
            aux->izq = crearNodoA(dato);
        else
            aux->der = crearNodoA(dato);
    }
    else
        *arbolABB = crearNodoA(dato);
}

void mostrarOrdenadoArbolABB (nodoA* arABB)
{
    if (arABB)
    {
        mostrarOrdenadoArbolABB(arABB->izq);
        printf("%i\t", arABB->dato);
        mostrarOrdenadoArbolABB(arABB->der);
    }
}

/// funciones ABB personas

typedef struct nodo
{
    Persona dato;
    struct nodo* sig;
}nodo;

nodo* crearNodo (Persona dato)
{
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    return nuevo;
}

void insertarAlFinalLista (nodo** lista, Persona dato)
{
    if (*lista)
    {
        nodo* aux = *lista;

        while (aux->sig)
            aux = aux->sig;

        aux->sig = crearNodo(dato);
    }
    else
        *lista = crearNodo(dato);
}

nodoABB* crearNodoABB (Persona dato)
{
    nodoABB* nuevo = (nodoABB*)malloc(sizeof(nodoABB));
    nuevo->dato = dato;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    return nuevo;
}

Persona cargarPersona()
{
    Persona per;
    printf("INGRESE EDAD: ");
    scanf("%i", &per.edad);
    printf("INGRESE NOMBRE: ");
    fflush(stdin);
    gets(per.nombre);
    printf("INGRESE LEGAJO: ");
    scanf("%i", &per.legajo);
    return per;
}

void insertarABB (nodoABB** arbol, Persona dato)
{
    if (*arbol)
    {
        if ((*arbol)->dato.legajo > dato.legajo)
            insertarABB(&(*arbol)->izq, dato);
        else
            insertarABB(&(*arbol)->der, dato);
    }
    else
        *arbol = crearNodoABB(dato);
}

void mostrarPersona (Persona dato)
{
    printf("LEGAJO: %i\n", dato.legajo);
    printf("NOMBRE: %s\n", dato.nombre);
    printf("EDAD: %i\n", dato.edad);
}

void mostrarABB_enOrden (nodoABB* arbol)
{
    if (arbol)
    {
        mostrarABB_enOrden(arbol->izq);
        mostrarPersona(arbol->dato);
        mostrarABB_enOrden(arbol->der);
    }
}

void copiarArbolEnLista (nodoABB* arbol, nodo** lista)
{
    if (arbol)
    {
        copiarArbolEnLista(arbol->izq, lista);
        insertarAlFinalLista(lista, arbol->dato);
        copiarArbolEnLista(arbol->der, lista);
    }
}

void mostrarLista (nodo* lista)
{
    while (lista)
    {
        mostrarPersona(lista->dato);
        lista = lista->sig;
    }
}

Persona buscarPorLegajoABB (nodoABB* arbol, int legajo)
{
    if (arbol)
    {
        if (arbol->dato.legajo == legajo)
            return arbol->dato;
        else
        {
            if (arbol->dato.legajo > legajo)
                return buscarPorLegajoABB(arbol->izq, legajo);
            else
                return buscarPorLegajoABB(arbol->der, legajo);
        }
    }
    else
    {
        Persona ret;
        ret.legajo = -1;
        return ret;
    }
}

nodoABB* buscarPorLegajoABB_retSubArb (nodoABB* arbol, int legajo)
{
    if (arbol)
    {
        if (arbol->dato.legajo == legajo)
            return arbol;
        else
        {
            if (arbol->dato.legajo > legajo)
                return buscarPorLegajoABB_retSubArb(arbol->izq, legajo);
            else
                return buscarPorLegajoABB_retSubArb(arbol->der, legajo);
        }
    }
    else
        return NULL;
}

int buscarPorNombreABB (nodoABB* arbol, char* nombre)
{
    int rta;

    if (arbol)
    {
        if (strcmpi(nombre, arbol->dato.nombre) == 0)
            return 1;
        else
        {
            rta = buscarPorNombreABB(arbol->izq, nombre);

            if (rta == 0)
                rta = buscarPorNombreABB(arbol->der, nombre);

            return rta;
        }
    }
    else
        return 0;
}

int alturaArbol (nodoABB* arbol)
{
    int altIzq, altDer;

    if (arbol)
    {
        altIzq = 1 + alturaArbol(arbol->izq);
        altDer = 1 + alturaArbol(arbol->der);

        if (altIzq > altDer)
            return altIzq;
        else
            return altDer;
    }
    else
        return 0;
}

int cantNodosArbol (nodoABB* arbol)
{
    if (arbol)
        return 1 + cantNodosArbol(arbol->izq) + cantNodosArbol(arbol->der);
    else
        return 0;
}

int cantHojasArbol (nodoABB* arbol)
{
    if (arbol)
    {
        if (arbol->izq == NULL && arbol->der == NULL)
            return 1;
        else
            return cantHojasArbol(arbol->izq) + cantHojasArbol(arbol->der);
    }
    else
        return 0;
}

int nivelNodo (nodoABB* arbol, int leg)
{
    if (arbol)
    {
        if (leg == arbol->dato.legajo)
            return 0;
        else
        {
            if (leg < arbol->dato.legajo)
                return 1 + nivelNodo(arbol->izq, leg);
            else
                return 1 + nivelNodo(arbol->der, leg);
        }
    }
    else
        return 0;
}

void eliminarSucesor (nodoABB** subArbol, nodoABB* raiz)
{
    if ((*subArbol)->izq)
        eliminarSucesor(&(*subArbol)->izq, raiz);
    else
    {
        nodoABB* aux = *subArbol;
        raiz->dato = (*subArbol)->dato;
        *subArbol = (*subArbol)->der;
        free(aux);
    }
}

void eliminarAntecesor (nodoABB** subArbol, nodoABB* raiz)
{
    if ((*subArbol)->der)
        eliminarAntecesor(&(*subArbol)->der, raiz);
    else
    {
        nodoABB* aux = *subArbol;
        raiz->dato = (*subArbol)->dato;
        *subArbol = (*subArbol)->izq;
        free(aux);
    }
}

void borrarNodoArbol (nodoABB** arbol, int legajo)
{
    if (*arbol)
    {
        if ((*arbol)->dato.legajo == legajo)
        {
            nodoABB* aux = *arbol;
            if ((*arbol)->izq && (*arbol)->der)
            {
                eliminarSucesor(&(*arbol)->der, aux);
                //eliminarAntecesor(&(*arbol)->izq, aux);
            }
            else
            {
                if ((*arbol)->izq)
                    *arbol = (*arbol)->izq;
                else
                    *arbol = (*arbol)->der;
                free(aux);
            }

        }
        else
        {
            if (legajo < (*arbol)->dato.legajo)
                borrarNodoArbol(&(*arbol)->izq, legajo);
            else
                borrarNodoArbol(&(*arbol)->der, legajo);
        }
    }
}

void graficarArbol (nodoA* arbol, int x, int y)
{
    if (arbol)
    {
        gotoxy(x,y);
        printf("%i", arbol->dato);
        graficarArbol(arbol->izq, x-8, y+4);
        graficarArbol(arbol->der, x+8, y+4);
    }
}

/// main

int main()
{
    /*nodoA* arbol;

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

    printf("\n\n");*/


    nodoA* arbolABB = NULL;

    insertarABB_Int(&arbolABB, 10);
    insertarABB_IntRep(&arbolABB, 4);
    insertarABB_Int(&arbolABB, 2);
    insertarABB_IntRep(&arbolABB, 3);
    insertarABB_IntRep(&arbolABB, 12);

    graficarArbol(arbolABB, 38, 0);

    /*printf("ARBOL PREORDEN:\t");
    mostrarPreorden(arbolABB);

    printf("\n\n");

    printf("12? %i\n", buscarABB_int(arbolABB, 12));
    printf("6? %i\n\n", buscarABB_intRep(arbolABB, 6));

    printf("ARBOL ABB ORDENADO (inorder):\t");
    mostrarOrdenadoArbolABB(arbolABB);

    nodoABB* arbolABB = NULL;

    insertarABB(&arbolABB, cargarPersona());
    insertarABB(&arbolABB, cargarPersona());
    insertarABB(&arbolABB, cargarPersona());
*/

///
    /*mostrarABB_enOrden(arbolABB);

    printf("\n\n");

    nodo* lista = NULL;

    copiarArbolEnLista(arbolABB, &lista);

    mostrarLista(lista);

    printf("\n\n");

    printf("tobias? %i\n\n", buscarPorNombreABB(arbolABB, "tobias"));

    printf("ALTURA DEL ARBOL: %i\n\n", alturaArbol(arbolABB));

    printf("CANT NODOS ARBOL: %i\n\n", cantNodosArbol(arbolABB));

    printf("CANT HOJAS ARBOL: %i\n\n", cantHojasArbol(arbolABB));

    printf("NIVEL NODO LEG 6: %i\n\n", nivelNodo(arbolABB, 6));
*/
    //borrarNodoArbol(&arbolABB, 7);
    //borrarNodoArbol(&arbolABB, 5);
  //  borrarNodoArbol(&arbolABB, 11);

    //mostrarABB_enOrden(arbolABB);



    return 0;
}
