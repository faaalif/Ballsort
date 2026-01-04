#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// === MEDIDAS NUEVAS (16x25) ===
#define FILAS_MENU 16
#define COLS_MENU 25

// Prototipos
void mainMenu();
void presenta_menu(int posX, int posY, int **img);
int scroll_menu(int posX, int posY, int cantOpc);
void leerMenuArt(char nomArch[30], int **img, int f, int c);
void mostrarMenuArt(int **img, int f, int c, int posX, int posY);

void mainMenu(){
    int numnodos = 5; 
    int ren = 2, col = 5, ancho = 7, alto = (numnodos * 3) + 1; 
    int op = 0;
    
    // === COORDENADAS DEL JUEGO (LAS ORIGINALES) ===
    // Esto asegura que tu Ball Sort NO se mueva de su lugar
    int gameX = 10; 
    int gameY = 5;
    
    // === COORDENADAS VISUALES DEL MENU ===
    // Esto es solo para donde aparecen las letras "1. APLICACION", etc.
    int menuX = 50; 
    int menuY = 22; // Lo bajamos para que quepa la imagen arriba

    int cont=0;
    nodo *listas[2][5] = {NULL};    

    // Carga de la imagen
    char nomArch[30] = "menu.txt";
    int **imgMenu;
    int i;

    imgMenu = (int **)malloc(FILAS_MENU * sizeof(int *));
    for (i = 0; i < FILAS_MENU; i++) {
        imgMenu[i] = (int *)malloc(COLS_MENU * sizeof(int));
    }
    leerMenuArt(nomArch, imgMenu, FILAS_MENU, COLS_MENU);

    // Inicializacion
    for (int c = 0; c < 8; c++) coldisp[c] = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4 ; j++) crea_lista(&listas[i][j], numnodos);
    }

    do{
          // Dibujamos el menú usando las coordenadas del MENÚ
          presenta_menu(menuX, menuY, imgMenu);
          
          op = scroll_menu(menuX, menuY, 4);
          system("cls");
          
          switch(op)
          {
                case 1:
                    // AQUÍ USAMOS gameX y gameY PARA QUE EL JUEGO SE VEA BIEN
                    tablero(gameX, gameY, ancho, alto, ren, col, listas);
                    moverCuadro(gameX, gameY, ancho, alto, ren, col, numnodos, listas); 
                break;
                case 2:
                    mainAyuda(); 
                break;
                case 3:
                    mainPortadaScore();
                    getch();
                break;
                case 4:
                    // Salir
                break;
          }
          if(op != 1 && op != 4) getch(); 

    }while(op != 4);

    // Liberar memoria
    for (i = 0; i < FILAS_MENU; i++) free(imgMenu[i]);
    free(imgMenu);
}

void presenta_menu(int posX, int posY, int **img)
{
       system("cls");
       
       // === DIBUJAR IMAGEN ===
       // La dibujamos ARRIBA del texto.
       // Calculamos: PosicionTexto - AlturaImagen - un margen
       int imgX = posX - 12; // Centramos la imagen respecto al texto (ajusta este 12 si lo ves chueco)
       int imgY = posY - FILAS_MENU - 2; 
       
       if(img != NULL){
           mostrarMenuArt(img, FILAS_MENU, COLS_MENU, imgX, imgY); 
       }

       // === DIBUJAR TEXTO ===
       SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);
       
       gotoxy(posX, posY);     printf("1. JUGAR");
       gotoxy(posX, posY + 1); printf("2. AYUDA");
       gotoxy(posX, posY + 2); printf("3. SCORE");
       gotoxy(posX, posY + 3); printf("4. SALIR");  
}
 
int scroll_menu(int posX, int posY, int cantOpc)
{
    char tecla = '\0';
    int op = 1, y = posY;
    posX = posX - 3; 
    
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11); 
    gotoxy(posX, y);
    printf("->");
    
    do{
        tecla = getch();
        SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),0);
        gotoxy(posX, y);
        printf("->");
        
        if(tecla == 80 && op < cantOpc) { y++; op++; }
        if(tecla == 72 && op > 1)       { y--; op--; }
        
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 11);
        gotoxy(posX, y);
        printf("->");
        
    }while(tecla != 27 && tecla != 13);
    
    return (op);
}

void leerMenuArt(char nomArch[30], int **img, int f, int c) {
    FILE *arch = fopen(nomArch, "r");
    if (arch) {
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < c; j++) {
                fscanf(arch, "%d", &img[i][j]);
            }
        }
        fclose(arch);
    }
}

void mostrarMenuArt(int **img, int f, int c, int posX, int posY) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < f; i++) {
        gotoxy(posX, posY + i); 
        for (int j = 0; j < c; j++) {
            int color = img[i][j];
            
            // Mapeo de colores por si acaso
            // 0 = Negro (fondo)
            // 15 = Blanco
            // 4 = Rojo
            // 6 = Amarillo Oscuro / Ocre (Windows Console default)
            
            SetConsoleTextAttribute(h, color);
            printf("%c%c", 219, 219);
        }
    }
    SetConsoleTextAttribute(h, 15); 
}

#endif
