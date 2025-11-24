#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipos.h"
#include "partidos.h"
#include "torneo.h"
#include "archivos.h"

   
void mostrarMenu() {
    printf("\n-------------------------------\n");
    printf("LIGA PRO - Sistema de Gestion de Torneos\n");
    printf("-------------------------------\n");
    printf("1) Registrar equipo\n");
    printf("2) Mostrar equipos\n");
    printf("3) Programar partido\n");
    printf("4) Mostrar partidos programados\n");
    printf("5) Procesar siguiente partido\n");
    printf("6) Mostrar tabla de posiciones\n");
    printf("7) Buscar equipo por nombre\n");
    printf("8) Guardar partidos en archivo\n");
    printf("9) Cargar partidos desde archivo\n");
    printf("0) Salir\n");
    printf("Opcion: ");
}

   // MAIN DEL PROGRAMA
int main() {

    tLista listaEquipos;
    tCola colaPartidos;

    inicializarLista(&listaEquipos);
    inicializarCola(&colaPartidos);

    int opcion;
    char nombre[MAX_CAD];

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
        	
           // 1) Registrar equipo
        case 1: {
            tEquipo equipo;
            
            strcpy(equipo.nombre, "");

            printf("Ingrese nombre del equipo: ");
            scanf("%s", equipo.nombre);

            equipo.puntos = 0;
            equipo.partidosJugados = 0;
            equipo.partidosGanados = 0;
            equipo.partidosEmpatados = 0;
            equipo.partidosPerdidos = 0;
            equipo.golesAFavor = 0;
            equipo.golesEnContra = 0;

            insertarEquipo(&listaEquipos, equipo);

            printf("Equipo '%s' registrado correctamente.\n", equipo.nombre);
            break;
        }
        
            // 2) Mostrar equipos
        case 2:
            mostrarLista(listaEquipos);
            break;
            
           //  3) Programar partido
        case 3: {
            tPartido partido = {"", "", "", -1, -1};

            printf("Equipo local: ");
            scanf("%s", partido.equipoLocal);

            printf("Equipo visitante: ");
            scanf("%s", partido.equipoVisitante);

            printf("Fecha (DD/MM/AAAA): ");
            scanf("%s", partido.fecha);

            agregarPartido(&colaPartidos, partido);

            printf("Partido programado correctamente.\n");
            break;
            
        }
           // 4) Mostrar partidos programados
        case 4: {
            printf("\nPARTIDOS PROGRAMADOS:\n");
            printf("%s\n", LINEA);

            tCola temporal = colaPartidos;
            tNodoPartido* auxiliar = temporal.primero;

            if (!auxiliar)
                printf("No hay partidos cargados.\n");

            while (auxiliar != NULL) {
                printf("%s vs %s (%s)\n",
                       auxiliar->info.equipoLocal,
                       auxiliar->info.equipoVisitante,
                       auxiliar->info.fecha);
                auxiliar = auxiliar->siguiente;
            }
            printf("%s\n", LINEA);
            break;
            
        }
           // 5) Procesar siguiente partido
        case 5:
            procesarSiguientePartido(&listaEquipos, &colaPartidos);
            break;
            
            // 6) Mostrar tabla
        case 6:
            mostrarTablaOrdenada(listaEquipos);
            break;
            
            // 7) Buscar equipo por nombre
        case 7:
            printf("Ingrese nombre del equipo: ");
            scanf("%s", nombre);

            {
                tEquipo* resultado = buscarEquipo(listaEquipos, nombre);

                if (resultado == NULL)
                    printf("No se encontro el equipo '%s'.\n", nombre);
                else {
                    printf("\nEquipo encontrado:\n");
                    printf("%s\n", LINEA);
                    printf("Nombre: %s\n", resultado->nombre);
                    printf("PJ: %d | PG: %d | PE: %d | PP: %d\n",
                           resultado->partidosJugados, resultado->partidosGanados, 
                           resultado->partidosEmpatados, resultado->partidosPerdidos);
                    printf("Puntos: %d\n", resultado->puntos);
                    printf("GF: %d | GC: %d\n",
                           resultado->golesAFavor, resultado->golesEnContra);
                    printf("%s\n", LINEA);
                }
            }
            break;
            
            // 8) Guardar partidos en archivo
        case 8:
            guardarPartidos(colaPartidos, "partidos.dat");
            break;
            
           // 9) Cargar partidos desde archivo
        case 9:
            cargarPartidos(&colaPartidos, "partidos.dat");
            break;
            
          // 0) SALIR
        case 0:
            printf("Saliendo del sistema...\n");
            break;
        }

        if (opcion < 0 || opcion > 9) {
            printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
