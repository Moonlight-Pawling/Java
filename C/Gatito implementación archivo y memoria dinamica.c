#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define T 3

typedef struct {
    char simbolo;
    char* nombre;
} Jugador;

void tablero(char** matriz) {
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < T; ++j) {
            printf(" %c ", matriz[i][j]);
            if (j < T - 1) printf("|");
        }
        printf("\n");
        if (i < T - 1) printf("-----------\n");
    }
}

int movimiento(char** matriz, int col, int fila, char simbolo) {
    if ((fila >= 0 && fila < T) && (col >= 0 && col < T) && matriz[col][fila] == ' ') {
        matriz[col][fila] = simbolo;
        return 1;
    } else {
        return 0;
    }
}

int ganador(char** matriz, char simbolo) {
    for (int i = 0; i < T; ++i) {
        if (matriz[i][0] == simbolo && matriz[i][1] == simbolo && matriz[i][2] == simbolo) {
            return 1;
        }
    }

    for (int j = 0; j < T; ++j) {
        if (matriz[0][j] == simbolo && matriz[1][j] == simbolo && matriz[2][j] == simbolo) {
            return 1;
        }
    }

    if ((matriz[0][0] == simbolo && matriz[1][1] == simbolo && matriz[2][2] == simbolo) ||
        (matriz[0][2] == simbolo && matriz[1][1] == simbolo && matriz[2][0] == simbolo)) {
        return 1;
    }

    return 0;
}

int main(int argc, char const* argv[]) {
    FILE* archivo;
    archivo = fopen("Registro de partidas.txt", "a+");

    if (archivo == NULL) {
        printf("Error al abrir el archivo. Verifique si está corrompido o si tiene permisos de escritura en el directorio donde se ejecuta el programa.\n");
        return 1;
    }

    time_t tiempo;
    struct tm* fecha;
    time(&tiempo);
    fecha = localtime(&tiempo);

    fprintf(archivo, "Fecha de inicio: %s", asctime(fecha));

    char** matriz = (char**)malloc(T * sizeof(char*));
    for (int i = 0; i < T; ++i) {
        matriz[i] = (char*)malloc(T * sizeof(char));
        for (int j = 0; j < T; ++j) {
            matriz[i][j] = ' ';
        }
    }

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
    jugador1.nombre = (char*)malloc(20 * sizeof(char)); // Supongamos una longitud máxima de 20 caracteres
    scanf("%s", jugador1.nombre);
    jugador1.simbolo = 'X';

    if (numJugadores == 2) {
        printf("Jugador 2, favor de ingresar tu nombre: ");
        jugador2.nombre = (char*)malloc(20 * sizeof(char)); // Supongamos una longitud máxima de 20 caracteres
        scanf("%s", jugador2.nombre);
        jugador2.simbolo = 'O';
    } else {
        jugador2.nombre = (char*)malloc(20 * sizeof(char));
        strcpy(jugador2.nombre, "Computadora");
        jugador2.simbolo = 'O';
    }

    fprintf(archivo, "Jugador 1: %s (%c)\n", jugador1.nombre, jugador1.simbolo);
    fprintf(archivo, "Jugador 2: %s (%c)\n\n", jugador2.nombre, jugador2.simbolo);

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
        printf("%s (%c), es tu turno. Ingresa columna (vertical 1-3) y fila (horizontal 1-3) separadas por espacio: ", jugadorActualObj.nombre, jugadorActualObj.simbolo);

        if (jugadorActual == 2 && numJugadores == 1) {
            Sleep(1000);
        }

        if (jugadorActual == 1 || (jugadorActual == 2 && numJugadores == 2)) {
            scanf("%d %d", &columnaauxiliar, &filaauxiliar);
            fila = filaauxiliar - 1;
            col = columnaauxiliar - 1;
        } else {
            fila = rand() % 3;
            col = rand() % 3;
        }

        if (movimiento(matriz, fila, col, jugadorActualObj.simbolo)) {
            totalMovim++;
            fprintf(archivo, "Movimiento de %s (%c): Fila %d, Columna %d\n", jugadorActualObj.nombre, jugadorActualObj.simbolo, fila + 1, col + 1);
            fprintf(archivo, "| %c | %c | %c |\n", matriz[0][0], matriz[0][1], matriz[0][2]);
            fprintf(archivo, "-------------\n");
            fprintf(archivo, "| %c | %c | %c |\n", matriz[1][0], matriz[1][1], matriz[1][2]);
            fprintf(archivo, "-------------\n");
            fprintf(archivo, "| %c | %c | %c |\n", matriz[2][0], matriz[2][1], matriz[2][2]);
            fprintf(archivo, "\n");
            fin = ganador(matriz, jugadorActualObj.simbolo);
            jugadorActual = (jugadorActual == 1) ? 2 : 1;
        } else {
            if (jugadorActual == 1 || (jugadorActual == 2 && numJugadores == 2)) {
                printf("Movimiento invalido. Inténtalo de nuevo.\n");
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
        fprintf(archivo, "%s (%c) ha ganado!\n\n\n", ganador.nombre, ganador.simbolo);
    } else {
        printf("Empate! El juego ha terminado sin ganadores.\n");
        fprintf(archivo, "Empate! El juego ha terminado sin ganadores.\n\n\n");
    }

    // Liberar la memoria asignada dinámicamente
    for (int i = 0; i < T; ++i) {
        free(matriz[i]);
    }
    free(matriz);
    
    free(jugador1.nombre);
    free(jugador2.nombre);

    fclose(archivo);

    return 0;
}
