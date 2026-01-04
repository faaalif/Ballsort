#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// TAMAÑO DE TU DIBUJO (17 filas x 40 columnas)
#define FILAS_AYUDA 17 
#define COLS_AYUDA 40 

// Prototipos
void mainAyuda();
void leerAyuda(char nomArch[30], int **img, int f, int c);
void mostrarAyuda(int **img, int f, int c, int posX, int posY);

// Función principal de Ayuda
void mainAyuda(){
    system("cls");
    
    char nomArch[30] = "ayuda.txt"; 
    int **img;
    int i;

    // 1. Crear espacio en memoria
    img = (int **)malloc(FILAS_AYUDA * sizeof(int *));
    for (i = 0; i < FILAS_AYUDA; i++) {
        img[i] = (int *)malloc(COLS_AYUDA * sizeof(int));
    }

    // 2. Leer el archivo de texto
    leerAyuda(nomArch, img, FILAS_AYUDA, COLS_AYUDA);
    
    // 3. Dibujar en pantalla (Centrado en X=18, Y=3)
    mostrarAyuda(img, FILAS_AYUDA, COLS_AYUDA, 18, 3); 

    // 4. Escribir las instrucciones debajo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int textoY = 3 + FILAS_AYUDA + 2; 
    
    gotoxy(40, textoY);     printf("=== INSTRUCCIONES ===");
    gotoxy(35, textoY + 2); printf("- Flechas: Mover el selector");
    gotoxy(35, textoY + 3); printf("- ENTER:   Agarrar o Soltar bloque");
    gotoxy(35, textoY + 4); printf("- ESC:     Salir al menu");
    gotoxy(35, textoY + 5); printf("- Objetivo: Agrupa los colores");
    
    gotoxy(35, textoY + 8); printf("Presiona cualquier tecla para volver...");
    getch();

    // 5. Limpiar memoria
    for (i = 0; i < FILAS_AYUDA; i++) {
        free(img[i]);
    }
    free(img);
}

// Función para leer los 0 y 15 del txt
void leerAyuda(char nomArch[30], int **img, int f, int c) {
    FILE *arch = fopen(nomArch, "r");
    if (arch) {
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < c; j++) {
                fscanf(arch, "%d", &img[i][j]);
            }
        }
        fclose(arch);
    } else {
        gotoxy(10, 10); printf("ERROR: No se encontro ayuda.txt");
        getch();
    }
}

// Función para pintar los cuadritos
void mostrarAyuda(int **img, int f, int c, int posX, int posY) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i = 0; i < f; i++) {
        gotoxy(posX, posY + i); 
        
        for (int j = 0; j < c; j++) {
            int color = img[i][j]; // Toma el 0 o 15 directo del archivo
            SetConsoleTextAttribute(h, color); 
            printf("%c%c", 219, 219); 
        }
    }
    SetConsoleTextAttribute(h, 15); // Regresar a blanco al terminar
}
