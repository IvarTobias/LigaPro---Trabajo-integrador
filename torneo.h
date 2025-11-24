
#include <stdio.h>


   // PROCESAR PARTIDOS
 

bool procesarSiguientePartido(tLista* lista, tCola* cola) {
    if (colaVacia(*cola)) {
        printf("No hay partidos para procesar.\n");
        return false;
    }

    tPartido partido;
    quitarPartido(cola, &partido);

    printf("\nProcesando partido: %s vs %s (%s)\n",
           partido.equipoLocal, partido.equipoVisitante, partido.fecha);

    printf("Goles %s: ", partido.equipoLocal);
    scanf("%d", &partido.golesLocal);

    printf("Goles %s: ", partido.equipoVisitante);
    scanf("%d", &partido.golesVisitante);

    tEquipo* local = buscarEquipo(*lista, partido.equipoLocal);
    tEquipo* visita = buscarEquipo(*lista, partido.equipoVisitante);

    if (!local || !visita) {
        printf("ERROR: Alguno de los equipos no existe en la lista.\n");
        return false;
    }

    local->partidosJugados++; 
    visita->partidosJugados++;

    actualizarGoles(local, partido.golesLocal, partido.golesVisitante);
    actualizarGoles(visita, partido.golesVisitante, partido.golesLocal);

    if (partido.golesLocal > partido.golesVisitante) {
        equipoGano(local);
        equipoPerdio(visita);
    }
    if (partido.golesLocal < partido.golesVisitante) {
        equipoGano(visita);
        equipoPerdio(local);
    }
    if (partido.golesLocal == partido.golesVisitante) {
        equipoEmpato(local);
        equipoEmpato(visita);
    }

    printf("Partido procesado correctamente.\n");
    return true;
}
