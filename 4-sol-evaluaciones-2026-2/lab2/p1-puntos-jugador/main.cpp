#include <iostream>
#include <iomanip>
using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

int calcularpuntosmax(int *camino, int n) {
    int dp[n + 2];
    // pasos anteriores imaginarios -> ganancia 0
    dp[0] = 0;
    dp[1] = 0;
    // programacion dinamica
    for (int i = 2; i <= n + 1; i++) {
        // sumamos los puntos de la posicion actual mas el maximo acumulado
        // entre la posicion anterior o posicion dos veces anterior
        dp[i] = camino[i - 2] + max(dp[i - 1], dp[i - 2]);
    }
    // impresion matriz soluciones
    cout << "Arreglo de soluciones:" << endl;
    for (int i = 0; i <= n + 1; i++) cout << right << setw(5) << dp[i];
    cout << endl;
    return dp[n + 1];
}

int main() {
    int camino[] = {5, 8, -4, 10, -3, 7};
    int n = sizeof(camino) / sizeof(camino[0]);
    int maxpuntos = calcularpuntosmax(camino, n);
    cout << "Por tanto, la maxima cantidad de puntos es = " << maxpuntos << endl;
    return 0;
}
