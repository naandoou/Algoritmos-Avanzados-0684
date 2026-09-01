#include <iostream>

using namespace std;

int cont = 0;
int soluciones[100][3];  // Solo se necesitan 3 columnas para x, y, z

bool esValido(int x, int y, int z, int total) {
    if (x == 0 || y == 0 || z == 0 || x > 9 || y > 9 || z > 9 || x + y + z > total)
        return false;

    if (x + y + z == total) {
        for (int i = 0; i < cont; ++i) {
            if (soluciones[i][0] == x && soluciones[i][1] == y && soluciones[i][2] == z)
                return false;
        }
    }

    return true;
}

bool busca(int x, int y, int z, int total) {
    if (!esValido(x, y, z, total))
        return false;

    if (x != y && x != z && y != z && x + y + z == total) {
        soluciones[cont][0] = x;
        soluciones[cont][1] = y;
        soluciones[cont][2] = z;
        cont++;
        cout << x << " " << y << " " << z << endl;
    }
    // backtracking recursivo
    if (busca(x, y, z + 1, total)) return true;
    if (busca(x, y + 1, z, total)) return true;
    if (busca(x + 1, y, z, total)) return true;

    return false;
}

int main() {
    int total = 8;
    busca(1, 1, 1, total);

    return 0;
}
