#include <iostream>
#include <iomanip>
using namespace std;
#define MAXMOV 8
#define NCOORD 2
#define N 9
#define M 5

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

void completaterreno(char ter[N][M]) {
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) ter[i][j] = ' ';
    // completando escombros
    ter[0][3] = '*';
    ter[0][4] = '*';
    ter[1][3] = '*';
    ter[2][2] = '*';
    ter[4][1] = '*';
    ter[4][2] = '*';
    ter[4][4] = '*';
    ter[5][1] = '*';
    ter[5][2] = '*';
    ter[5][4] = '*';
    ter[6][1] = '*';
    ter[7][0] = '*';
    ter[7][1] = '*';
    ter[7][3] = '*';
    // completando supervivientes
    ter[1][2] = '+';
    ter[1][4] = '+';
    ter[3][1] = '+';
    ter[3][2] = '+';
    ter[5][3] = '+';
    ter[6][0] = '+';
    ter[6][4] = '+';
    ter[8][2] = '+';
}

bool validaposicion(int x, int y, char ter[N][M]) {
    return x >= 0 && x < N && y >= 0 && y < M && (ter[x][y] == ' ' or ter[x][y] == '+');
}

bool validasondeo(int x, int y, char ter[N][M]) {
    // verifica si hay un superviviente
    return x >= 0 && x < N && y >= 0 && y < M && ter[x][y] == '+';
}

void imprimeterreno(char ter[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cout << right << setw(5) << ter[i][j];
        cout << endl;
    }
}

bool robotrescatador(int x, int y, char nmov, int mov[MAXMOV][NCOORD], char terreno[N][M]) {
    static int nsupervivientes = 0;
    if (x == N - 1 && y == M - 1) {
        cout << "Se encontraron " << nsupervivientes << " supervivientes" << endl;
        imprimeterreno(terreno);
        return true;
    }
    int xfin, yfin, xsondeo, ysondeo;
    for (int i = 0; i < MAXMOV; i++) {
        xfin = x + mov[i][0];
        yfin = y + mov[i][1];
        if (validaposicion(xfin, yfin, terreno)) {
            // aca sondeamos la zona para buscar supervivientes
            if (terreno[xfin][yfin] == '+') {
                nsupervivientes++;
                terreno[xfin][yfin] = ' ';
            }
            for (int j = 0; j < MAXMOV; j++) {
                xsondeo = xfin + mov[j][0];
                ysondeo = yfin + mov[j][1];
                if (validasondeo(xsondeo, ysondeo, terreno)) {
                    nsupervivientes++;
                    terreno[xsondeo][ysondeo] = ' ';
                }
            }
            terreno[xfin][yfin] = nmov;
            if (robotrescatador(xfin, yfin, nmov + 1, mov, terreno)) return true;
            terreno[xfin][yfin] = ' ';
        }
    }
    return false;
}

int main() {
    int mov[MAXMOV][NCOORD];
    char terreno[N][M];
    completamov(mov);
    completaterreno(terreno);
    if (robotrescatador(-1, -1, 'A', mov, terreno));
    else cout << "No se encontro una ruta de escape";
    return 0;
}
