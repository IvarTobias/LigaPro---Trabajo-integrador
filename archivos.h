#include <stdio.h>
#include <stdbool.h>

bool guardarPartidos(tCola cola, char nombreArchivo[]) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return false;
    }
    
    tNodoPartido* auxiliar = cola.primero;
    
    while (auxiliar != NULL) {
        fwrite(&(auxiliar->info), sizeof(tPartido), 1, archivo);
        auxiliar = auxiliar->siguiente;
    }
    
    fclose(archivo);
    printf("Partidos guardados correctamente en '%s'.\n", nombreArchivo);
    return true;
}

bool cargarPartidos(tCola* cola, char nombreArchivo[]) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo. No se encontro '%s'.\n", nombreArchivo);
        return false;
    }
    
    tPartido partido;
    int contador = 0;
    
    fread(&partido, sizeof(tPartido), 1, archivo);
    while (!feof(archivo)) {
        agregarPartido(cola, partido);
        contador++;
        fread(&partido, sizeof(tPartido), 1, archivo);
    }
    
    fclose(archivo);
    printf("Se cargaron %d partidos desde '%s'.\n", contador, nombreArchivo);
    return true;
}
