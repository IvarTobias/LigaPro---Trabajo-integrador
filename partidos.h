#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    tString30 equipoLocal;
    tString30 equipoVisitante;
    tString30 fecha;
    int golesLocal;
    int golesVisitante;
} tPartido;

typedef struct nodoPartido {
    tPartido info;
    struct nodoPartido* siguiente;
} tNodoPartido;

typedef struct {
    tNodoPartido* primero;
    tNodoPartido* ultimo;
} tCola;


// IMPLEMENTACIÓN DE FUNCIONES
  

void inicializarCola(tCola* cola) {
    cola->primero = cola->ultimo = NULL;
}

bool colaVacia(tCola cola) {
    return cola.primero == NULL;
}

void agregarPartido(tCola* cola, tPartido partido) {
    tNodoPartido* nuevo = (tNodoPartido*) malloc(sizeof(tNodoPartido));
    nuevo->info = partido;
    nuevo->siguiente = NULL;

    if (cola->primero == NULL)
        cola->primero = nuevo;
    else
        cola->ultimo->siguiente = nuevo;

    cola->ultimo = nuevo;
}

bool quitarPartido(tCola* cola, tPartido* partido) {
    if (colaVacia(*cola)) {
        printf("No se puede eliminar ningun partido.\n");
        return false;
    }

    tNodoPartido* nodo = cola->primero;
    *partido = nodo->info;

    cola->primero = nodo->siguiente;
    if (cola->primero == NULL) 
        cola->ultimo = NULL;

    free(nodo);
    return true;
}
