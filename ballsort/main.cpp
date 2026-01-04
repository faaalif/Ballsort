
 
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#define COLOR_TABLERO 15
#define COLOR_CUADRO 9
#define ESP 3
#define ESPY 6
#define RIGHT 77 // M
#define LEFT 75 // K
#define UP 72 // H
#define DOWN 80 // P
#define ESC 27
#define ENTER 13 
  
#include "funciones.h"
#include "score.h"
#include "listaS.h"
#include "ayuda.h"
#include "menu.h"
#include "portada.h"

 
int main()
{
	
	system("MODE 116, 44");
	mainPortada();
	srand(time(NULL));
	mainMenu();
	
	getch();
	return 0;
}
