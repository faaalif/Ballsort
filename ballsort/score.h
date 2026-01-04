#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoScore {
    char nombre[30];
    int movimientos;
    struct nodoScore *izq;
    struct nodoScore *der;
} nodoScore;


nodoScore *crearNodoScore(char nombre[], int mov);
nodoScore *insertarScore(nodoScore *raiz, char nombre[], int mov);
void guardarRec(nodoScore *raiz, FILE *f);
void guardarScores(nodoScore *raiz);
nodoScore *leerScores();
void imprimirTop10(nodoScore *raiz);
void mainPortadaScore();


int contadorRanking = 0;
int posY_Impresion = 0; 


nodoScore *crearNodoScore(char nombre[], int mov)
{
    nodoScore *nuevo = (nodoScore*)malloc(sizeof(nodoScore));
    strcpy(nuevo->nombre, nombre);
    nuevo->movimientos = mov;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

nodoScore *insertarScore(nodoScore *raiz, char nombre[], int mov)
{
    if (raiz == NULL)
        return crearNodoScore(nombre, mov);

    if (mov < raiz->movimientos)
        raiz->izq = insertarScore(raiz->izq, nombre, mov);
    else
        raiz->der = insertarScore(raiz->der, nombre, mov);

    return raiz;
}

void guardarRec(nodoScore *raiz, FILE *f)
{
    if (raiz == NULL) return;
    guardarRec(raiz->izq, f);
    fprintf(f, "%s %d\n", raiz->nombre, raiz->movimientos);
    guardarRec(raiz->der, f);
}

void guardarScores(nodoScore *raiz)
{
    FILE *f = fopen("score.txt", "w");
    if (!f) return;
    guardarRec(raiz, f);
    fclose(f);
}

nodoScore *leerScores()
{
    FILE *f = fopen("score.txt", "r");
    nodoScore *raiz = NULL;
    char nombre[30];
    int mov;

    if (!f) return NULL;

    while (fscanf(f, "%s %d", nombre, &mov) == 2)
    {
        raiz = insertarScore(raiz, nombre, mov);
    }
    fclose(f);
    return raiz;
}


void imprimirTop10(nodoScore *raiz)
{
    if (raiz == NULL || contadorRanking >= 10)
        return;

    
    imprimirTop10(raiz->izq);

    
    if (contadorRanking < 10)
    {
        
        gotoxy(38, posY_Impresion); 
        printf("%02d", contadorRanking + 1); 
        
        
        gotoxy(48, posY_Impresion); 
        printf("%-15s", raiz->nombre); 
        
        
        gotoxy(70, posY_Impresion); 
        printf("%d", raiz->movimientos);

        posY_Impresion += 2; 
        contadorRanking++;
    }

    
    imprimirTop10(raiz->der);
}

void mainPortadaScore()
{
    system("cls");
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    
    int boxX = 35;
    int boxY = 5;
    int ancho = 45;
    int alto = 25;

    
    cuadro(boxX, boxY, ancho, alto, 15);

    
    gotoxy(boxX + 15, boxY + 2);
    printf("MEJORES JUGADORES");
    
    
    for(int i=boxX+1; i<boxX+ancho; i++) { gotoxy(i, boxY+3); printf("%c", 196); }


    gotoxy(37, boxY + 5); printf("RANGO");
    gotoxy(48, boxY + 5); printf("JUGADOR");
    gotoxy(68, boxY + 5); printf("MOVIMIENTOS");

    
    for(int i=boxX+1; i<boxX+ancho; i++) { gotoxy(i, boxY+6); printf("%c", 196); }


    
    nodoScore *ranking = leerScores();

    if (ranking == NULL)
    {
        gotoxy(boxX + 12, boxY + 10);
        printf("No hay registros aun.");
    }
    else
    {
        contadorRanking = 0;
        posY_Impresion = boxY + 8; 
        imprimirTop10(ranking);
    }

    gotoxy(boxX + 5, boxY + alto + 2);
    printf("Presiona cualquier tecla para volver...");
    getch();
}

#endif
