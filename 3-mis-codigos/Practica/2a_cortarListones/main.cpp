#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define N 5
#define M 5
#define C 3
#define X (-1)
#define Y (-1)
#define MAX_MOV 8
#define MAX_DIR 4

void generamovimientos(int mov[8][2]) {
    // para atacar todas las direcciones con un while
    // el ante ciclo pasado, un problema salia mas rapido en sentido antihorario
    mov[0][0] = -1;
    mov[0][1] = 0;
    mov[1][0] = -1;
    mov[1][1] = +1;
    mov[2][0] = 0;
    mov[2][1] = 1;
    mov[3][0] = 1;
    mov[3][1] = 1;
    mov[4][0] = 1;
    mov[4][1] = 0;
    mov[5][0] = 1;
    mov[5][1] = -1;
    mov[6][0] = 0;
    mov[6][1] = -1;
    mov[7][0] = -1;
    mov[7][1] = -1;
}

// movimiento del largo del liston
void generadirecciones(int dir[4][2], int largo) {
    largo--;
    dir[0][0] = -1 * largo;
    dir[0][1] = 0;
    dir[1][0] = 0;
    dir[1][1] = largo;
    dir[2][0] = largo;
    dir[2][1] = 0;
    dir[3][0] = 0;
    dir[3][1] = -1 * largo;
}

void inicializatablero(int tablero[N][M]) {
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) tablero[i][j] = 0;
}

void imprime(int tablero[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cout << right << setw(5) << tablero[i][j];
        cout << endl;
    }
}

int validaposicion(int x, int y, int tablero[N][M], int n, int m) {
    // aqui valido una posicion
    return x >= 0 && x < N && y >= 0 && y < M;
}

int validarecorrido(int xini, int yini, int xfin, int yfin, int tablero[N][M], int n, int m) {
    // aqui valido el recorrido
    if (xini == xfin) {
        // si la fila no cambia
        if (yini < yfin) for (int i = yini; i <= yfin; i++) if (tablero[xini][i] != 0 or i >= M) return 0;
        if (yini > yfin) for (int i = yini; i >= yfin; i--) if (tablero[xini][i] != 0 or i < 0) return 0;
    }
    if (yini == yfin) {
        // si la columna no cambia
        if (xini < xfin) for (int i = xini; i <= xfin; i++) if (tablero[i][yini] != 0 or i >= M) return 0;
        if (xini > xfin) for (int i = xini; i >= xfin; i--) if (tablero[i][yini] != 0 or i < 0) return 0;
    }
    return 1;
}

void marca(int xini, int yini, int xfin, int yfin, int nmov, int tablero[N][M]) {
    if (xini > xfin) for (int i = xini; i >= xfin; i--) tablero[i][yini] = nmov;
    if (yini < yfin) for (int i = yini; i <= yfin; i++) tablero[xini][i] = nmov;
    if (xini < xfin) for (int i = xini; i <= xfin; i++) tablero[i][yini] = nmov;
    if (yini > yfin) for (int i = yini; i >= yfin; i--) tablero[xini][i] = nmov;
}

void generacortes(int x, int y, int n, int m, int nmov, int tablero[N][M], int mov[8][2], int dir[4][2],
                  int solu[N][M]) {
    // falta ver el escenario en el que no cumple las pintadas
    int ninix, niniy;
    static int maxcorte = 0;
    for (int i = 0; i < MAX_MOV; i++) {
        ninix = x + mov[i][0];
        niniy = y + mov[i][1];
        if (validaposicion(ninix, niniy, tablero, n, m)) {
            int nfinx, nfiny;
            for (int j = 0; j < MAX_DIR; j++) {
                nfinx = ninix + dir[j][0];
                nfiny = niniy + dir[j][1];
                if (validarecorrido(ninix, niniy, nfinx, nfiny, tablero, n, m)) {
                    // en este escenario, se puede colocar el liston. Entonces pintamos la matriz
                    marca(ninix, niniy, nfinx, nfiny, nmov, tablero);
                    if (maxcorte < nmov) {
                        for (int k = 0; k < N; k++) for (int l = 0; l < M; l++) solu[k][l] = tablero[k][l];
                        maxcorte = nmov;
                        cout << maxcorte << endl;
                    }
                    generacortes(nfinx, nfiny, n, m, nmov + 1, tablero, mov, dir, solu);
                    // cuando es correcto, devuelve 1
                    marca(ninix, niniy, nfinx, nfiny, 0, tablero); // lo despintamos
                }
            }
        }
    }
}

int main() {
    // valores iniciales
    int mov[8][2], dir[4][2], tablero[N][M];
    int solu[N][M];
    generamovimientos(mov);
    generadirecciones(dir, C);

    // inicializar con 0s
    inicializatablero(solu);
    inicializatablero(tablero);
    imprime(tablero);
    cout << "-------------------------------" << endl;
    // backtracking cortes
    int x = -1, y = -1;
    generacortes(X, Y, N, M, 1, tablero, mov, dir, solu); // funcion recursiva
    imprime(tablero);

    return 0;
}
