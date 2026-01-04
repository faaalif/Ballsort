#define ALTO_N 2
#define ANCHO_N 3
#define COLOR_N 15 //BLANCO

int coldisp[8] = {0};

typedef struct {
    int num;
    int x, y;
} info;

struct reg {
    info dato;
    reg *sig;
};
typedef reg nodo;


nodo *crea_nodoLS(info dato);
void inserta_inicioLS(nodo **cab, info dato);
int pop_inicioLS(nodo **cab, info *out);
void recorreLS(nodo *cab, int x, int y);
void imprime_Nodo(info dato, int x, int y);
void borra_Nodo(info dato, int x, int y);
void crea_lista(nodo **cab, int nodos);
int cuenta_nodos(nodo *cab);

void tablero(int posX, int posY, int ancho, int alto, int rens, int cols, nodo *listas[2][5]);
void moverCuadro(int posX, int posY, int ancho, int alto, int ren, int col, int numnodos, nodo *listas[2][5]);
int win_condition(nodo *listas[2][5], int numnodos);
int torre_completa(nodo *cab, int numnodos);




nodo *crea_nodoLS(info dato)
{
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    if (!nuevo) {
        printf("ERROR\n");
        exit(1);
    }
    nuevo->dato = dato;
    nuevo->dato.x = -1;
    nuevo->dato.y = -1;
    nuevo->sig = NULL;
    return nuevo;
}


void inserta_inicioLS(nodo **cab, info dato)
{
    nodo *nuevo = crea_nodoLS(dato);
    nuevo->sig = *cab;
    *cab = nuevo;
}


int pop_inicioLS(nodo **cab, info *out)
{
    if (*cab == NULL) return 0;

    nodo *aux = *cab;
    *out = aux->dato;
    *cab = aux->sig;
    free(aux);
    return 1;
}


void recorreLS(nodo *cab, int x, int y)
{
    nodo *aux = NULL;
    int cantidad = cuenta_nodos(cab);
    int start_y = y + (ALTO_N + 1) * (5 - cantidad);

    for(aux = cab; aux != NULL; aux = aux->sig, start_y += 3){
        aux->dato.x = x;
        aux->dato.y = start_y;
        imprime_Nodo(aux->dato, x, start_y);
    }
}

void imprime_Nodo(info dato, int x, int y)
{
    cuadro(x, y, ANCHO_N, ALTO_N, COLOR_N);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dato.num);
    gotoxy(x + 1, y + 1);
    printf("%c%c", 219, 219);
}

void borra_Nodo(info dato, int x, int y)
{
    cuadro(x, y, ANCHO_N, ALTO_N, 0);
    gotoxy(x + 1, y + 1);
    printf("  ");
}

void crea_lista(nodo **cab, int nodos)
{
    int colores[8] = {1, 2, 4, 5, 6, 3, 11, 12};
    info dato;

    // nodos = cu√°ntos bloques va a tener esta torre

    for (int k = 0; k < nodos; k++)
    {
        // Paso 1: Encontrar el MINIMO de uso actual
        int minUso = coldisp[0];
        for (int i = 1; i < 8; i++)
            if (coldisp[i] < minUso)
                minUso = coldisp[i];

        // Paso 2: Crear una lista de colores candidatos (los menos usados)
        int candidatos[8];
        int c = 0;

        for (int i = 0; i < 8; i++)
            if (coldisp[i] == minUso)
                candidatos[c++] = i;

        // Paso 3: Elegir 1 color al azar entre los candidatos
        int elegido = candidatos[rand() % c];

        // Paso 4: Crear el bloque con ese color
        dato.num = colores[elegido];
        coldisp[elegido]++;

        // Insertar el bloque en la torre
        inserta_inicioLS(cab, dato);
    }
}


int cuenta_nodos(nodo *cab)
{
    int cont = 0;
    while (cab) {
        cont++;
        cab = cab->sig;
    }
    return cont;
}


void tablero(int posX, int posY, int ancho, int alto, int rens, int cols, nodo *listas[2][5])
{
    int i, j;
    int x, y;
    int nodoX, nodoY;

    int limpiezaInicioY = posY - ESPY - 3;
    int limpiezaFinY = posY + (alto + ESPY) * rens + 3;

    for (int yy = limpiezaInicioY; yy < limpiezaFinY; yy++) {
        for (int xx = posX - 2; xx < posX + (ancho + ESP) * cols + 4; xx++) {
            gotoxy(xx, yy);
            printf(" ");
        }
    }

    for (i = 0, y = posY, nodoY = posY + 1; i < rens; i++, y += alto + ESPY, nodoY = y + 1) {
        for (j = 0, x = posX, nodoX = posX + 2; j < cols; j++, x += ancho + ESP, nodoX += 10) {
            cuadro(x, y, ancho, alto, COLOR_TABLERO);
            recorreLS(listas[i][j], nodoX, nodoY);
        }
    }
}



void moverCuadro(int posX, int posY, int ancho, int alto, int ren, int col,
                 int numnodos, nodo *listas[2][5])
{
    char tecla = 0;
    info bloque_recogido;
    int movimientos = 0;

    int x = posX, y = posY;
    int i = 0, j = 0;

    int colorTorre = 5;
    int borrarTorre = 15;

    int torres[2][2] = { {-1,-1}, {-1,-1} };
    int cont_torre = -1;

    nodo *aux;

    cuadro(x, y, ancho, alto, colorTorre);

    do {
        tecla = getch();
        cuadro(x, y, ancho, alto, borrarTorre);

        switch(tecla)
        {
        case RIGHT:
            if (j < col - 1) { x += ancho + ESP; j++; }
            break;

        case LEFT:
            if (j > 0) { x -= ancho + ESP; j--; }
            break;

        case UP:
            if (i > 0) { y -= alto + ESPY; i--; }
            break;

        case DOWN:
            if (i < ren - 1) { y += alto + ESPY; i++; }
            break;

        case ENTER:
            if (cont_torre != -1)
            {
                // 1. Validar si est· llena
                if (cuenta_nodos(listas[i][j]) == numnodos)
                {
                    gotoxy(60,4);
                    printf("Intenta otra torre esta esta llena");
                    break;
                }

                // 2. Validar color 
                int es_origen = (i == torres[0][0] && j == torres[0][1]);

                if (listas[i][j] != NULL && !es_origen)
                {
                    if (listas[i][j]->dato.num != bloque_recogido.num)
                    {
                        gotoxy(60,4);
                        printf("Diferente color, busca un color igual o regresa de donde lo tomaste"); 
                        
                        // --- CAMBIO: ELIMINAMOS EL imprime_Nodo AQUÕ ---
                        // Al no dibujarlo aquÌ, visualmente el bloque sigue estando 
                        // ˙nicamente encima de la torre de donde lo sacaste.
                        
                        break; 
                    }
                }


                inserta_inicioLS(&listas[i][j], bloque_recogido);

                tablero(posX, posY, ancho, alto, ren, col, listas);

				if (win_condition(listas, numnodos))
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					gotoxy(75, 10);
					printf("Felicidades has completado el Ball Sort");
				
					char nombre[30];
					gotoxy(75, 12);
					printf("Nombre del ganador: ");
					scanf("%s", nombre);

					nodoScore *ranking = leerScores();
					ranking = insertarScore(ranking, nombre, movimientos);
					guardarScores(ranking);

					gotoxy(75, 14);
					printf("Partida acutalizada en nuestro tablero de ganadores");

					getch();
					return;
				}


                cont_torre = -1;

                movimientos++;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                gotoxy(75, 5);
                printf("Has realizado %d movimientos", movimientos);

                break;
            }


            // Cuando se selecciona un bloque

            else
            {
                if (!pop_inicioLS(&listas[i][j], &bloque_recogido))
                {
                    gotoxy(60,4);
                    printf("Torre vacia");
                    break;
                }

                tablero(posX, posY, ancho, alto, ren, col, listas);

                imprime_Nodo(bloque_recogido, x + 2, y - ESP - 1);

                cont_torre = 0;
                torres[0][0] = i;
                torres[0][1] = j;

                break;
            }

            break;
        }

        cuadro(x, y, ancho, alto, colorTorre);

    } while(tecla != ESC);
}

int torre_completa(nodo *cab, int numnodos)
{
    // 1. Debe tener todos los nodos
    if (cuenta_nodos(cab) != numnodos)
        return 0;

    // 2. Todos deben tener el MISMO color
    int colorBase = cab->dato.num;
    nodo *aux = cab;

    while (aux != NULL)
    {
        if (aux->dato.num != colorBase)
            return 0;

        aux = aux->sig;
    }

    return 1; // Torre completa y homog√©nea
}

int win_condition(nodo *listas[2][5], int numnodos)
{
    int torresOK = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            // Torres completamente vac√≠as (auxiliares)
            if (listas[i][j] == NULL)
                continue;

            if (torre_completa(listas[i][j], numnodos))
                torresOK++;
        }
    }

    // Sale si se tienen las 8 torres llenas
    return (torresOK == 8);
}
