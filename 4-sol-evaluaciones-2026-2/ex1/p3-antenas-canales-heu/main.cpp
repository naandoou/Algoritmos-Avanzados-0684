#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define N 7
#define CANAL_DEFECTO 1

/* A -> 0
 * B -> 1
 * C -> 2
 * D -> 3
 * E -> 4
 * F -> 5
 * G -> 6
 */

struct Antena {
    int id;
    int canal;
    int ninterf;
};

int comparaporinterf(Antena a, Antena b) {
    return a.ninterf > b.ninterf;
}

int comparaporid(Antena a, Antena b) {
    return a.id < b.id;
}

int contarinterf(int antena, int mapa[N][N]) {
    int cont = 0;
    for (int i = 0; i < N; i++) if (mapa[antena][i] == 1) cont++;
    return cont;
}

bool validarprohibido(int canal, vector<int> canalesprohibidos) {
    for (int i = 0; i < canalesprohibidos.size(); i++) {
        if (canal == canalesprohibidos[i]) return true;
    }
    return false;
}

int asignacanal(vector<int> canalesprohibidos) {
    // nuestra logica de asignacion será asignar el canal
    // con el menor valor entre 1 y 7 que no esté en la
    // lista de canales prohibidos.
    // Canales mayores a 7 son imposibles, porque el caso extremo
    // seria asignar un canal distinto a cada antena
    // A -> 1 | B -> 2 | ... | G -> 7
    for (int canal = 1; canal <= N; canal++) {
        // al encontrar el primero que no es prohibido, lo devolvemos
        if (!validarprohibido(canal, canalesprohibidos)) return canal;
    }
    return -1; // esto, aunque se quiera, es imposible por el caso extremo que se explicó
}

void minimizarcanales(int mapa[N][N]) {
    // creamos un arreglo de antenas, con informacion de id, canal asignado y numero de interferencias
    // canal 0 significa que aun no se asigno un canal -> todos inicializan en 0
    Antena antenas[N];
    for (int i = 0; i < N; i++) antenas[i] = {i, 0, contarinterf(i, mapa)};

    // ordenamos descendentemente por cantidad de interferencias -> criterio voraz
    sort(antenas, antenas + N, comparaporinterf);

    // creamos un vector de canales asignados, cada posicion corresponde a una antena
    int canalesasignados[N]{};

    // vamos recorriendo las antenas con el criterio voraz que asignamos
    for (int i = 0; i < N; i++) {
        vector<int> canalesprohibidos;
        int idantena = antenas[i].id;
        // guardamos en un vector los canales prohibidos para la antena actual
        for (int j = 0; j < N; j++)
            if (mapa[idantena][j] == 1 and canalesasignados[j] != 0)
                canalesprohibidos.push_back(canalesasignados[j]);

        if (!canalesprohibidos.empty()) {
            // si ya hay canales asignados
            antenas[idantena].canal = asignacanal(canalesprohibidos);
            canalesasignados[idantena] = antenas[idantena].canal;
        }
        else {
            // si no hay ningun canal prohibido, asignaremos el valor por defecto
            // esto ocurre cuando recien empezamos a asignar
            antenas[idantena].canal = CANAL_DEFECTO; // asignamos el canal 1 por defecto
            canalesasignados[idantena] = CANAL_DEFECTO;
        }
    }

    // imprimimos los canales
    // ordenamos por id
    sort(antenas, antenas + N, comparaporid);
    for (int i = 0; i < N; i++) cout << "Antena " << (char)('A' + i) << " -> Canal " << antenas[i].canal << endl;
}

int main() {
    int mapa[N][N] = {
        {0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };
    // el criterio voraz a seguir será escoger a la antena con mayor cantidad
    // de interferencias primero, el ordenamiento será descendente segun
    // numero de interferencias -> A, B, C, D, E, F, G
    minimizarcanales(mapa);
    return 0;
}
