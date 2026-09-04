#include <iostream>
#include <iomanip>
using namespace std;
#define N 6

void inicializa(int *arreglo, int n) {
    for (int i = 0; i < n; i++) arreglo[i] = 0;
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int coinrecurivo(int *monedas, int *F, int n, int i) {
    if (i == n) return F[N];
    if (i == 0) F[i + 1] = monedas[i];
    else F[i + 1] = max(F[i], monedas[i] + F[i - 1]);
    return coinrecurivo(monedas, F, n, i + 1);
}

int coiniterativo(int *monedas, int n) {
    int F[n + 1];
    F[0] = 0;
    F[1] = monedas[0];
    for (int i = 2; i <= n; i++) {
        int max1 = F[i - 2] + monedas[i - 1];
        int max2 = F[i - 1];
        F[i] = max(max1, max2);
    }
    for (int i = 0; i <= n; i++) cout << right << setw(3) << F[i];
    cout << endl;
    return F[n];
}

int main() {
    int monedas[N] = {5, 1, 2, 10, 6, 2};
    int n = sizeof(monedas) / sizeof(monedas[0]);
    int F[n + 1];
    inicializa(F, n + 1);
    int maximo = coinrecurivo(monedas, F, n, 0);
    cout << maximo << endl;
    cout << "=======================" << endl;
    cout << coiniterativo(monedas, n) << endl;
    return 0;
}
