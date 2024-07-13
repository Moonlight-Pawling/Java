#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include<time.h>
#define T 3
typedef struct {
    char simbolo;
    char nombre[20];  // Cambiado a un array de caracteres para almacenar nombres más largos
} Jugador;

void tablero(char matriz[T][T]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf(" %c ", matriz[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
}

/*int movimiento(char matriz[T][T], int col, int fila, char simbolo) {
    if (matriz[col][fila] == ' ') {
        matriz[col][fila] = simbolo;
        return 1;  // Movimiento válido
    } else {
        return 0;  // Movimiento inválido
    }
}*/

int movimiento(char matriz[T][T], int col, int fila, char simbolo) {
    if ((fila >= 0 && fila < T) && (col >= 0 && col < T) && matriz[col][fila] == ' ') {
        // El movimiento es válido
        matriz[col][fila] = simbolo;
        return 1;
    } else {
        // El movimiento es inválido
        return 0;
    }
}



int ganador(char matriz[T][T], char simbolo) {
    for (int i = 0; i < 3; ++i) {
        if (matriz[i][0] == simbolo && matriz[i][1] == simbolo && matriz[i][2] == simbolo) {
            return 1;  // Alguien ganó
        }
    }

    for (int j = 0; j < 3; ++j) {
        if (matriz[0][j] == simbolo && matriz[1][j] == simbolo && matriz[2][j] == simbolo) {
            return 1;  // Alguien ganó
        }
    }

    if ((matriz[0][0] == simbolo && matriz[1][1] == simbolo && matriz[2][2] == simbolo) ||
        (matriz[0][2] == simbolo && matriz[1][1] == simbolo && matriz[2][0] == simbolo)) {
        return 1;  // Alguien ganó
    }

    return 0;  // Nadie ha ganado aún
}

int main(int argc, char const *argv[]) {
    char matriz[T][T] = {{' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '}};
    Jugador jugador1, jugador2;
	srand(time(NULL));
    printf(" < Hola! Bienvenido al juego del gato >\n");
    printf("	< Jugador 1 obtiene (X) >\n");
    printf("	< Jugador 2 obtiene (O) >\n");

    int numJugadores;
    do {
        printf("<Ingrese 1 para jugar contra la maquina>\n");
		printf("<Ingresar 2 para jugar con otra persona>\n");
		printf("----> ");
        scanf("%d", &numJugadores);
    } while (numJugadores != 1 && numJugadores != 2);

    printf("Jugador 1, favor de ingresar tu nombre: ");
    scanf("%s", jugador1.nombre);
    jugador1.simbolo = 'X';

    if (numJugadores == 2) {
        printf("Jugador 2, favor de ingresar tu nombre: ");
        scanf("%s", jugador2.nombre);
        jugador2.simbolo = 'O';
    } else {
        strcpy(jugador2.nombre, "Computadora");
        jugador2.simbolo = 'O';
    }

    int jugadorActual = 1;
    int totalMovim = 0;
    int fin = 0;
	int filaauxiliar, columnaauxiliar;
	
    while (!fin && totalMovim < 9) {
        system("cls");
        printf("Tablero de Juego:\n");
        tablero(matriz);

        int fila, col;
        Jugador jugadorActualObj = (jugadorActual == 1) ? jugador1 : jugador2;
        printf("%s (%c), es tu turno. Ingresa columna (vertical 1-3) y fila (horizontal 1-3) separadas por espacio: ",jugadorActualObj.nombre, jugadorActualObj.simbolo);
        
        if (jugadorActual == 2 && numJugadores == 1) {
        	Sleep(1000);
		}
        
		if (jugadorActual == 1 || (jugadorActual == 2 && numJugadores == 2)) {
            scanf("%d %d", &columnaauxiliar, &filaauxiliar);
            fila=filaauxiliar-1;
            col=columnaauxiliar-1;
        } else {
                fila = rand() % 3;
                col = rand() % 3;
        }

        if (movimiento(matriz, fila, col, jugadorActualObj.simbolo)) {
            totalMovim++;
            fin = ganador(matriz, jugadorActualObj.simbolo);
            jugadorActual = (jugadorActual == 1) ? 2 : 1;
        } else {
        	if (jugadorActual == 1 || (jugadorActual == 2 && numJugadores == 2)) {
        		printf("Movimiento invalido. Intentalo de nuevo.\n");
                Sleep(2000);
			}
        }
    }

    system("cls");
    printf("Tablero de juego final:\n");
    tablero(matriz);

    if (fin) {
        Jugador ganador = (jugadorActual == 1) ? jugador2 : jugador1;
        printf("%s (%c) ha ganado!\n", ganador.nombre, ganador.simbolo);
    } else {
        printf("Empate! El juego ha terminado sin ganadores.\n");
    }
    
    return 0;
}