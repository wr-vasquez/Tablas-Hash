#ifndef CARGAS_ARCHIVOS_H_INCLUDED
#define CARGAS_ARCHIVOS_H_INCLUDED

// Determina la cantidad de caracteres que puede leer en cada linea
#define MAX_LECTURA_LINEA_ARCHIVO 256

// Está función busca un archivo en la ruta especificada
// Retorna -1 si la ruta del archivo está vacía
char* cargar_archivo_csv(const char* ruta_archivo);

char* concatenar_lineas(const char* linea, const char* total);

#endif // CARGAS_ARCHIVOS_H_INCLUDED
