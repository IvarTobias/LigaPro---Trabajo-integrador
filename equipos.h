#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CAD 30
#define LINEA "--------------------------------------------------"


   // ESTRUCTURAS
typedef char tString30[MAX_CAD];

typedef struct {
    tString30 nombre;
    int puntos;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int golesAFavor;
    int golesEnContra;
} tEquipo;

typedef struct nodoEquipo {
    tEquipo info;
    struct nodoEquipo* siguiente;
} tNodoEquipo;

typedef tNodoEquipo* tLista;


   // IMPLEMENTACIÓN DE FUNCIONES
void inicializarLista(tLista* lista) {
    *lista = NULL;
}

bool listaVacia(tLista lista) {
    return lista == NULL;
}

void insertarEquipo(tLista* lista, tEquipo equipo) {
    tNodoEquipo* nuevo = (tNodoEquipo*) malloc(sizeof(tNodoEquipo));
    nuevo->info = equipo;
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

tEquipo* buscarEquipo(tLista lista, char nombre[]) {
    while (lista != NULL) {
        if (strcmp(lista->info.nombre, nombre) == 0)
            return &(lista->info);
        lista = lista->siguiente;
    }
    return NULL;
}

void mostrarLista(tLista lista) {
    printf("%s\nEQUIPOS REGISTRADOS\n%s\n", LINEA, LINEA);
    while (lista != NULL) {
        printf("%s (Pts: %d)\n", lista->info.nombre, lista->info.puntos);
        lista = lista->siguiente;
    }
    printf("%s\n", LINEA);
}


    // ACTUALIZACIONES DE ESTADÍSTICAS 
void actualizarGoles(tEquipo* equipo, int golesFavor, int golesContra) {
    equipo->golesAFavor += golesFavor;
    equipo->golesEnContra += golesContra;
}

void equipoGano(tEquipo* equipo) {
    equipo->partidosGanados++;
    equipo->puntos += 3;
}

void equipoEmpato(tEquipo* equipo) {
    equipo->partidosEmpatados++;
    equipo->puntos += 1;
}

void equipoPerdio(tEquipo* equipo) {
    equipo->partidosPerdidos++;
}


   // TABLA ORDENADA
void mostrarTablaOrdenada(tLista lista) {
    int i, j;
    
    if (listaVacia(lista)) {
        printf("No hay equipos cargados.\n");
        return;
    }

    int cantidad = 0;
    tNodoEquipo* auxiliar = lista;
    while (auxiliar) { 
        cantidad++; 
        auxiliar = auxiliar->siguiente; 
    }

    tEquipo* equipos = (tEquipo*) malloc(sizeof(tEquipo) * cantidad);
    auxiliar = lista;
    for (i = 0; i < cantidad; i++) {
        equipos[i] = auxiliar->info;
        auxiliar = auxiliar->siguiente;
    }

    /* Ordenamiento por puntos / diferencia / nombre */
    for (i = 0; i < cantidad - 1; i++) {
        for (j = i + 1; j < cantidad; j++) {
            int diferenciaI = equipos[i].golesAFavor - equipos[i].golesEnContra;
            int diferenciaJ = equipos[j].golesAFavor - equipos[j].golesEnContra;

            bool intercambiar = false;

            if (equipos[i].puntos < equipos[j].puntos) {
                intercambiar = true;
            }
            if (equipos[i].puntos == equipos[j].puntos && diferenciaI < diferenciaJ) {
                intercambiar = true;
            }
            if (equipos[i].puntos == equipos[j].puntos && diferenciaI == diferenciaJ &&
                     strcmp(equipos[i].nombre, equipos[j].nombre) > 0) {
                intercambiar = true;
            }

            if (intercambiar) {
                tEquipo temp = equipos[i];
                equipos[i] = equipos[j];
                equipos[j] = temp;
            }
        }
    }

    printf("\n%s\nTABLA DE POSICIONES\n%s\n", LINEA, LINEA);
    printf("%-3s %-20s %3s %3s %4s %4s\n", "Pos", "Equipo", "Pts", "PJ", "GF", "GC");

    for (i = 0; i < cantidad; i++)
        printf("%-3d %-20s %3d %3d %4d %4d\n",
               i + 1, equipos[i].nombre, equipos[i].puntos, equipos[i].partidosJugados,
               equipos[i].golesAFavor, equipos[i].golesEnContra);

    free(equipos);
    printf("%s\n", LINEA);
}
