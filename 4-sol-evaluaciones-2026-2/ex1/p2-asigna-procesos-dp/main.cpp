#include <iomanip>
#include <iostream>
using namespace std;
#define M 3
#define N 8

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int asignar(int costo[][M], int compatible[][M]) {
    int dp[N + 1][M + 1];
    for (int i = 0; i <= N; i++) dp[i][0] = -1;
    for (int i = 0; i <= M; i++) dp[0][i] = -1;
    dp[0][0] = 0;
    for (int j = 1; j <= M; j++) {
        for (int i = 1; i <= N; i++) {
            if (compatible[i - 1][j - 1] == 1) {
                // si es compatible
                if (dp[i - 1][j - 1] == -1 and dp[i - 1][j] == -1) dp[i][j] = -1;
                else if (dp[i - 1][j - 1] == -1 and dp[i - 1][j] != -1) dp[i][j] = costo[i - 1][j - 1] + dp[i - 1][j];
                else if (dp[i - 1][j - 1] != -1 and dp[i - 1][j] == -1) dp[i][j] = costo[i - 1][j - 1] + dp[i - 1][j - 1];
                else dp[i][j] = costo[i - 1][j - 1] + min(dp[i - 1][j - 1], dp[i - 1][j]);
            }
            else dp[i][j] = -1;
        }
    }

    // impresion
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) cout << right << setw(4) << dp[i][j];
        cout << endl;
    }
  
    return dp[N][M];
}

int main() {
    int costo[][M] = {
        {6, 5, 4},
        {5, 4, 8},
        {8, 6, 3},
        {6, 8, 5},
        {7, 2, 6},
        {3, 6, 4},
        {4, 2, 3},
        {3, 8, 5},
    };

    int compatible[][M] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 0},
        {1, 1, 1},
        {0, 1, 1}
    };

    int minimocosto = asignar(costo, compatible);
    cout << "El minimo costo es: " << minimocosto << endl;
    return 0;
}
