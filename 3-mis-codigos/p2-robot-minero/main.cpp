// Algoritmia LAB5 2022-1
// Pregunta de backtracking

#include <iostream>
#include <iomanip>
using namespace std;
#define MAXMOV 8
#define NCOORD 2
#define N 9
#define M 5
#define ANCHO 25

void completaterreno(int ter[N][M]) {
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) ter[i][j] = 0;
    // -1 representara una mina
    ter[0][4] = -1;
    ter[2][2] = -1;
    ter[4][1] = -1;
    ter[4][2] = -1;
    ter[4][4] = -1;
    ter[5][1] = -1;
    ter[5][2] = -1;
    ter[5][4] = -1;
    ter[6][1] = -1;
    ter[6][3] = -1;
    for (int i = 0; i < 4; i++) ter[7][i] = -1;
}

void completamov(int mov[MAXMOV][NCOORD]) {
    mov[0][0] = -1;
    mov[0][1] = 0;
    mov[1][0] = -1;
    mov[1][1] = 1;
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

void imprimeterreno(int ter[N][M], int nsol) {
    for (int i = 0; i < ANCHO; i++) cout << "=";
    cout << endl;
    cout << "SOLUCION " << nsol << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cout << right << setw(5) << ter[i][j];
        cout << endl;
    }
}

bool validapos(int x, int y, int terreno[N][M]) {
    return x >= 0 && x < N && y >= 0 && y < M && terreno[x][y] == 0;
}

bool buscaruta(int x, int y, int nmov, int mov[MAXMOV][NCOORD], int terreno[N][M]) {
    if (x == N - 1 and y == M - 1) {
        // caso base, aca llega al destino
        imprimeterreno(terreno, 1);
        return true;
    }
    int xfin, yfin;
    for (int i = 0; i < MAXMOV; i++) {
        xfin = x + mov[i][0];
        yfin = y + mov[i][1];
        if (validapos(xfin, yfin, terreno)) {
            terreno[xfin][yfin] = nmov;
            bool rutavalida = buscaruta(xfin, yfin, nmov + 1, mov, terreno);
            terreno[xfin][yfin] = 0;
            if (rutavalida) return true;
        }
    }
    return false;
}

void veinterutas(int x, int y, int nmov, int mov[MAXMOV][NCOORD], int terreno[N][M]) {
    static int nsol = 0;
    if (x == N - 1 and y == M - 1) {
        // caso base, aca llega al destino
        nsol++;
        imprimeterreno(terreno, nsol);
        return;
    }
    int xfin, yfin;
    for (int i = 0; i < MAXMOV; i++) {
        xfin = x + mov[i][0];
        yfin = y + mov[i][1];
        if (validapos(xfin, yfin, terreno)) {
            terreno[xfin][yfin] = nmov;
            veinterutas(xfin, yfin, nmov + 1, mov, terreno);
            terreno[xfin][yfin] = 0;
            if (nsol == 20) return;
        }
    }
}

int main() {
    int mov[MAXMOV][NCOORD];
    int terreno[N][M];
    completamov(mov);
    completaterreno(terreno);
    // imprimeterreno(terreno);
    veinterutas(-1, -1, 1, mov, terreno);
    return 0;
}
