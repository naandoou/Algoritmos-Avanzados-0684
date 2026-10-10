#include <iostream>
using namespace std;
#define N 5
#define BUSCADO 29

bool buscaanilla(int aviario[N][N], int valor) {
    // empezamos de la esquina superior derecha
    // esto porque utilizaremos el artificio de que, iniciando de ahi,
    // cada vez que nos traslademos a la izquierda el numero disminuirá,
    // y cada vez que nos traslademos abajo, el numero aumentará
    int n = 0, m = N - 1; // -> posicion inicial
    while (true) {
        if (aviario[n][m] == valor) return true;
        // este algoritmo es greedy porque siempre elegimos el valor que se acerca más
        // al buscado, sin saber lo que hay despues. Somos golosos y ciegos
        if (aviario[n][m] > valor) {
            // si el valor actual es mayor al que buscamos, nos trasladamos a la izquierda
            // esto lo hacemos para obtener un numero menor y acercarnos al buscado
            if (m != 0) m -= 1; // si aun puede ir a la izquierda
            else return false;
            // si ya no puede ir mas a la izquierda, ya no existen numeros menores al actual,
            // y como el buscado es menor al actual, aseguramos que el buscado no está
        }
        else {
            // si el valor actual es menor al que buscamos, nos trasladamos hacia abajo
            // esto lo hacemos para obtener un numero mayor y acercarnos al buscado
            if (n != N - 1) n += 1; // si aun se puede ir hacia abajo
            else return false;
            // si ya no se puede ir hacia abajo, ya no existen numeros mayores al actual,
            // y como el buscado es mayor al actual, aseguramos que el buscado no está
        }
    }
}

int main() {
    int aviario[N][N] = {
        {1, 8, 17, 21, 36},
        {6, 14, 28, 33, 38},
        {9, 16, 29, 35, 41},
        {10, 20, 30, 37, 45},
        {13, 31, 32, 43, 50}
    };
    int valor = BUSCADO;
    int hayanilla = buscaanilla(aviario, valor);
    if (hayanilla == true) cout << "La anilla " << valor << " si se encuentra en el aviario.";
    else cout << "La anilla " << valor << " no se encuentra en el aviario.";
    return 0;
}
