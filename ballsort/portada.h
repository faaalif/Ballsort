#include <stdio.h>    
#include <stdlib.h>   
#include <conio.h>    
#include <windows.h>

void mainPortada();
void portada();
void leerImagen(char nomArch[30], int **img, int f, int c); // leer archivo
void mostrarImagen(int **img, int f, int c); // imprimir archivo

void mainPortada(){
	portada();
}

void portada(){
	char nomArch[30] = "portada.txt"; // archivo de texto con datos
    int f = 43, c = 58; // resoluci�n del pixel art
    int **img = NULL;
    int i;

    // Reserva din�mica de memoria para matriz
    img = (int **)malloc(f * sizeof(int *));
    for (i = 0; i < f; i++) {
        img[i] = (int *)malloc(c * sizeof(int));
    }

    leerImagen(nomArch, img, f, c);
    mostrarImagen(img, f, c);
	getch();

    for (i = 0; i < f; i++) {
        free(img[i]);
    }
    free(img);
    img = NULL;
    
}

void leerImagen(char nomArch[30], int **img, int f, int c) {
    FILE *arch = NULL;
    int i, j;
    arch = fopen(nomArch, "r"); // abrir archivo en modo lectura

    if (arch) {
        for (i = 0; i < f; i++) {
            for (j = 0; j < c; j++) {
                fscanf(arch, "%d", &img[i][j]); // leer cada entero
            }
        }
        fclose(arch);
    } else {
        printf("No se pudo abrir el archivo.\n");
    }
}

void mostrarImagen(int **img, int f, int c) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j;

    for (i = 0; i < f; i++) {
        for (j = 0; j < c; j++) {
            SetConsoleTextAttribute(h, img[i][j]); // color del p�xel
            printf("%c%c", 219, 219); // imprime dos cuadros por p�xel
             // delay para efecto visual
        }
        printf("\n"); // salto de l�nea al terminar la fila
    }
}
