#include "ustd.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void cls(){
    system("cls");
}

void pausa(){
    system("pause");
}

int contar_caracteres(const char* cadena, char caracter){
    int contador = 0;
    int indice = 0;
    while(cadena[indice] != '\0'){
        if(cadena[indice] == caracter){
            contador++;
        }

        indice++;
    }

    return contador;
}
