#include <iomanip>
#include <iostream>
using namespace std;
#define N 9
#define M 5

int robotminero(int campo[N][M], int n, int m) {
    int dp[n + 1][m + 1];
    // estado de inicializacion
    // nuestros primeros estados (que se ubicarian afuera del campo),
    // se inicializan en uno los que colindan con la esquina superior izquierda del campo,
    // para que el robot pueda empezar a navegar desde ahi, y se rellena con 0 lo demas
    // para evitar llenar posiciones que no son el inicio
    dp[0][0] = 1;
    dp[0][1] = 1;
    dp[1][0] = 1;
    for (int i = 2; i <= m; i++) dp[0][i] = 0;
    for (int i = 2; i <= n; i++) dp[i][0] = 0;
    // programacion dinamica
    // si es que dp arriba o de la izquierda es 1, osea que el robot pudo llegar ahi,
    // verificamos si no hay un escombro, en caso no lo haya, este seria el unico escenario
    // en el que el robot podria llegar ahi, asi que completamos dp con 1
    // en cualquier otro caso, colocaremos 0
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // condicion de que podemos llegar a la posicion desde arriba o desde abajo
            if (dp[i - 1][j] == 1 or dp[i][j - 1] == 1) {
                // condicion de que no hay escombro
                if (campo[i - 1][j - 1] == 1) dp[i][j] = 1;
                else dp[i][j] = 0;
            } else dp[i][j] = 0;
        }
    }
    // impresion de la matriz solucion
    cout << "Matriz de solucion:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) cout << right << setw(4) << dp[i][j];
        cout << endl;
    }
    return dp[n][m];
}

int main() {
    int campo[N][M] = {
        {1, 1, 1, 0, 0},
        {1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    // int campo[N][M] = {
    //     {1, 1, 1, 0, 0},
    //     {1, 1, 1, 0, 1},
    //     {1, 1, 0, 1, 1},
    //     {1, 1, 1, 1, 1},
    //     {1, 0, 0, 1, 0},
    //     {1, 0, 0, 1, 0},
    //     {1, 0, 1, 0, 1},
    //     {0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1}
    // };

    int n = sizeof(campo) / sizeof(campo[0]);
    int m = sizeof(campo[0]) / sizeof(campo[0][0]);
    int encontrosalida = robotminero(campo, n, m);
    if (encontrosalida) cout << "Encontro salida" << endl;
    else cout << "No encontro salida" << endl;
    return 0;
}
