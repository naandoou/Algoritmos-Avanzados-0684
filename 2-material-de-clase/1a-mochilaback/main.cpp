#include <iostream>
using namespace std;
#define N 5

int mochila_back(int pos, int n, int peso, int *paq) {
    if (pos == n || peso < 0) return 0; // si se sale del arreglo (pos == n) o el peso es superado (peso < 0)
    if (paq[pos] == peso) return 1; // encontramos la solucion
    if (mochila_back(pos + 1, n, peso - paq[pos], paq)) return 1;
    return mochila_back(pos + 1, n, peso, paq); // cuando devuelve 0, no consideras ese paquete -> este es el backtracking
}

int main() {
    int paq[] = {2, 1, 4, 1, 12};
    int peso = 15;
    cout << mochila_back(0, N, peso, paq) << endl;
    return 0;
}