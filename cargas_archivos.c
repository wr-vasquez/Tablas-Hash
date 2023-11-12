#include "cargas_archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

char* cargar_archivo_csv(const char* ruta_archivo){
    FILE* archi;

    // Si la ruta del archivo viene vacia retornar null
    if(strlen(ruta_archivo) == 0){
        return NULL;
    }

    archi = fopen(ruta_archivo, "rb");

    if(archi == NULL){
        printf("\nError desde cargar_archivo_csv: fopen devolvio NULL");
        return NULL;
    }

    char linea[MAX_LECTURA_LINEA_ARCHIVO];
    char* res = "";
    // Posicionar el puntero al inicio del archivo
    fseek(archi, 0, SEEK_SET);
    while(fgets(linea, MAX_LECTURA_LINEA_ARCHIVO, archi)){
        res = concatenar_lineas(res, linea);
    }

    fclose(archi);
    return res;
}



char* concatenar_lineas(const char* linea, const char* total) {
    // Obtener la longitud de las cadenas
    size_t longitudLinea = strlen(linea);
    size_t longitudTotal = strlen(total);

    // Calcular la longitud total del resultado
    size_t longitudResultado = longitudLinea + longitudTotal;

    // Asignar memoria para el resultado
    char* resultado = (char*)malloc((longitudResultado + 1) * sizeof(char));
    if (resultado == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        return NULL;
    }

    // Copiar la cadena 'linea' al resultado
    strcpy(resultado, linea);

    // Concatenar la cadena 'total' al resultado
    strcat(resultado, total);

    return resultado;
}
