#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Falta completar

int mochivenganza(int *paq, int n, int peso) {
    int F[n + 1][peso + 1];
    F[0][0] = 1;
    for (int i = 1; i <= peso; i++) F[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= peso; j++) {
            F[i][j] = (paq[i] == peso) or (F[i-1][peso - paq[i]] == 1);
        }
    }

}

int main() {
    int paq[] = {1, 2, 5};
    int n = sizeof(paq) / sizeof(paq[0]);
    int peso = 8;
    int valido = mochivenganza(paq, n, peso);
    return 0;
}
