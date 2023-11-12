#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ustd.h"

#define MAX_REGISTROS 300

struct Registros{
    char dpi[14];
    char primer_nombre[26];
    char segundo_nombre[26];
    char primer_apellido[26];
    char segundo_apellido[26];
    char direccion[51];
    char correo_electronico[51];
    char telefono[51];
};

struct Registros regs[300];

unsigned int funcionHash(const char *llave) {
    unsigned int hash = 0;
    int i;

    for (i = 0; i < strlen(llave); i++) {  //Se devuelve el valor del numero de bytes
        hash = (hash * 31) + llave[i];
    }

    return hash % MAX_REGISTROS;
}

void reiniciar_tabla_hash(){
    for(int i = 0; i < MAX_REGISTROS; i++){
        strcpy(regs[i].dpi, "");
    }
}

void volcar_archivo(){
    char ruta_archivo[1024];

    cls();
    gotoxy(5, 10);
    printf("Escriba la dirección del archivo para leer: ");
    gotoxy(5, 11);
    printf("Ejemplo: C:/Windows/archivo.txt");
    gotoxy(5, 12);
    printf("No se permite contra barra");
    gotoxy(6, 14);
    printf("->| ");
    scanf("%s", &ruta_archivo);

    char* datos_archivo = "";
    datos_archivo = cargar_archivo_csv(ruta_archivo);

    if(datos_archivo == NULL){
        cls();
        gotoxy(5, 10);
        printf("Error: ruta invalida.");
        gotoxy(5, 11);
        pausa();
        return;
    }

    cls();
    gotoxy(5, 10);
    printf("Leyendo archivo.");

    gotoxy(5, 11);
    printf("Generando hash table.");


    char* datos_archivo_copia = strdup(datos_archivo);
    char* datos = "";

    // Contar el número de registros en el archivo
    int num_registros = 0;
    const char* cursor = datos_archivo_copia;
    while ((cursor = strchr(cursor, '\n'))) {
        num_registros++;
        cursor++;
    }

    // Leer los valores de cada campo en la estructura
    cursor = datos_archivo_copia;
    for (int i = 0; i < num_registros; i++) {
        // Saltar la primera línea del encabezado
        if (i == 0) {
            cursor = strchr(cursor, '\n') + 1;
        }

        struct Registros registro_nuevo;

        // Leer los valores de cada campo
        sscanf(cursor, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;\n]",
               registro_nuevo.dpi,
               registro_nuevo.primer_nombre,
               registro_nuevo.segundo_nombre,
               registro_nuevo.primer_apellido,
               registro_nuevo.segundo_apellido,
               registro_nuevo.direccion,
               registro_nuevo.correo_electronico,
               registro_nuevo.telefono);


        unsigned int valor_hash = funcionHash(registro_nuevo.dpi);
        //Se reliza la comparacion por medio de strcmp
        while (strcmp(regs[valor_hash].dpi, "") != 0) {
            valor_hash = (valor_hash + 1) % MAX_REGISTROS;
        }

        regs[valor_hash] = registro_nuevo;

        cursor = strchr(cursor, '\n') + 1;
    }

    gotoxy(5, 12);
    printf("Hash table cargado exitosamente.");
    gotoxy(5, 13);
    pausa();
}

void BuscarRegistro(){
    char dpi[14];
    cls();
    gotoxy(5, 10);
    printf("Ingrese un DPI para buscar: ");
    scanf("%s", &dpi);
    gotoxy(5, 11);
    printf("Buscando...");
    unsigned int posicion = funcionHash(dpi);
    while (strcmp(regs[posicion].dpi, "") != 0) {
        if (strcmp(regs[posicion].dpi, dpi) == 0) {
            gotoxy(7, 12);
            printf("Registro encontrado: ");
            gotoxy(7, 13);
            printf("DPI: %s\n", regs[posicion].dpi);
            gotoxy(7, 14);
            printf("Primer nombre: %s", regs[posicion].primer_nombre);
            gotoxy(7, 15);
            printf("Segundo nombre: %s", regs[posicion].segundo_nombre);
            gotoxy(7, 16);
            printf("Primer apellido: %s", regs[posicion].primer_apellido);
            gotoxy(7, 17);
            printf("Segundo apellido: %s", regs[posicion].segundo_apellido);
            gotoxy(7, 18);
            printf("Direccion: %s", regs[posicion].direccion);
            gotoxy(7, 19);
            printf("Correo electronico: %s", regs[posicion].correo_electronico);
            gotoxy(7, 20);
            printf("Telefono: %s", regs[posicion].telefono);
            gotoxy(7, 23);
            pausa();
            return;
        }

        posicion = (posicion + 1) % MAX_REGISTROS;
    }
    gotoxy(5, 12);
    printf("Registro no encontrado.");
    gotoxy(5, 14);
    pausa();
}


// Está función encuentra la posición de la tabla
void Ubicacion(){
    char dpi[14];
    cls();
    gotoxy(5, 10);
    printf("Ingrese un DPI para buscar: ");
    scanf("%s", &dpi);
    gotoxy(5, 11);
    printf("Buscando...");
    unsigned int posicion = funcionHash(dpi);
    while (strcmp(regs[posicion].dpi, "") != 0) {
        if (strcmp(regs[posicion].dpi, dpi) == 0) {
            gotoxy(7, 12);
            printf("Registro encontrado en la posición: %d",posicion);
            gotoxy(7, 13);
            pausa();
            return;
        }

        posicion = (posicion + 1) % MAX_REGISTROS;
    }
    gotoxy(5, 12);
    printf("Registro no encontrado.");
    gotoxy(5, 14);
    pausa();
}

void VerHashTable() {
    cls();
    // system("clear"); // Descomenta esta línea si estás en Linux o macOS

    int registros_vistos = 0;

    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("|   No.   |         DPI        |    Primer Nombre    |    Segundo Nombre    |   Primer Apellido   |   Segundo Apellido   |\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < MAX_REGISTROS; i++) {
        if (strcmp(regs[i].dpi, "") != 0) {
            printf("|  %5d  |  %-15s  |  %-19s  |  %-19s  |  %-19s  |  %-20s  |\n",
                   registros_vistos + 1,
                   regs[i].dpi,
                   regs[i].primer_nombre,
                   regs[i].segundo_nombre,
                   regs[i].primer_apellido,
                   regs[i].segundo_apellido);
            registros_vistos++;
        }
    }

    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nTotal de registros encontrados: %d\n", registros_vistos);
    pausa();
}

int main()
{
    // Cambiar idioma de consola para reconocer caracteres especiales
    setlocale(LC_ALL, "spanish");
    int opcion = 0;
    do{
        cls();
        gotoxy(5, 5);
        printf("****************** PROYECTO PROGRAMACIÓN III UMG ******************");
        gotoxy(15, 7);
        printf("1. Carga Archivos");
        gotoxy(15, 8);
        printf("2. Búsqueda");
        gotoxy(15, 9);
        printf("3. Ubicación");
        gotoxy(15, 10);
        printf("4. Eliminación");
        gotoxy(15, 11);
        printf("5. Ver hash table");
        gotoxy(15, 12);
        printf("6. Salir");

        gotoxy(20, 14);
        printf("Seleccione una opción: ");
        scanf("%i", &opcion);

        switch (opcion) {
            case 1:{
                reiniciar_tabla_hash();
                volcar_archivo();
                break;
            }
            case 2:{
                BuscarRegistro();
                break;
            }
            case 3:{
                Ubicacion();
                break;
            }
            case 4:{
                cls();
                gotoxy(5, 10);
                printf("Eliminando tabla...");
                reiniciar_tabla_hash();
                gotoxy(5, 11);
                printf("Tabla eliminada...");
                gotoxy(5, 13);
                pausa();
                break;
            }
            case 5:{
                VerHashTable();
                break;
            }
        }
    } while (opcion != 6);

    cls();
    printf("Programa terminado.");
    return 0;
}
