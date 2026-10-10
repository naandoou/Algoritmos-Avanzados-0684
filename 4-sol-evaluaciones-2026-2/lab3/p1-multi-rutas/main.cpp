#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
#define NNOD 7
#define NCAM 3
#define ESPACIO 32

struct Nodo {
    int id;
    int demanda;
    int distancia;
};

struct Cliente {
    int id;
    int demanda;
};

struct Camion {
    int id;
    int capacidad;
};

bool validarnovisitado(vector<int> yavisitados, int i) {
    for (int visitado: yavisitados) if (visitado == i) return false;
    return true;
}

int comparavec(Nodo a, Nodo b) {
    return a.distancia < b.distancia;
}

int buscarutas(int mapa[NNOD][NNOD], Camion *camiones, Cliente *clientes, int nnod, int ncam) {
    // queremos minimizar la distancia total, entonces siempre elegiremos ir
    // al nodo no visitado mas cercano (segun distancia) al que se puede ir
    // considerando la capacidad del camion
    vector<int> yavisitados; // en este no vamos a añadir al almacen
    int distanciaflota = 0;

    // cabecera
    cout << left << setw(12) << "Vehiculo";
    cout << left << setw(29) << "Ruta";
    cout << left << setw(25) << "Carga total (unidades)";
    cout << "Distancia de la ruta (km)" << endl;

    for (int i = 0; i < ncam; i++) {
        // vamos a hallar la ruta de cada camion uno por uno
        int pos = 0; // iniciamos en almacen
        vector<int> rutasol = {0}; // inicia en 0
        int demandaacum = 0;
        int distanciaacum = 0;
        while (true) {
            if (pos != 0) yavisitados.push_back(pos);
            // filtrado de vecinos validos
            vector<Nodo> vecinos;
            for (int j = 0; j < nnod; j++) {
                if (mapa[pos][j] > 0 and validarnovisitado(yavisitados, j)) {
                    // si existe ruta y no se visitó, se considera vecino
                    if (camiones[i].capacidad >= clientes[j].demanda) {
                        // ademas, verificamos que la capacidad sea suficiente
                        vecinos.push_back({j, clientes[j].demanda, mapa[pos][j]});
                    }
                }
            }

            // ordenamos a los vecinos por distancia
            sort(vecinos.begin(), vecinos.end(), comparavec);

            // escogemos al de menor distancia
            if (!vecinos.empty()) {
                // acumulamos
                rutasol.push_back(vecinos[0].id);
                demandaacum += vecinos[0].demanda;
                distanciaacum += vecinos[0].distancia;
                // actualizamos capacidad
                camiones[i].capacidad -= vecinos[0].demanda;
                if (vecinos[0].id == 0) break; // si el vecino al que iremos es el almacen, terminamos la ruta -> break
                pos = vecinos[0].id; // actualizamos posicion para la siguiente iteracion
            } else return false; // ni siquiera existe una ruta
        }

        // imprimos ruta de cada camion
        cout << left << setw(12) << i + 1;
        int espacios = ESPACIO;
        for (int r = 0; r < rutasol.size(); r++) {
            if (r != 0) cout << " - ";
            cout << rutasol[r];
            espacios -= 4;
        }
        cout << setw(espacios) << " ";
        cout << left << setw(25) << demandaacum;
        cout << distanciaacum << endl;

        // acumulamos distancia total
        distanciaflota += distanciaacum;
    }

    // imprimimos distancia total
    cout << "Distancia total recorrida por la flota: " << distanciaflota << " km" << endl;

    // validamos solucion voraz verificando si todos los clientes fueron atendidos exactamente una vez
    if (yavisitados.size() == nnod - 1) return 1;
    // ya se verificó que no hay repetidos con la funcion validarnovisitado
    return 0;
}

int main() {
    int mapa[NNOD][NNOD] = {
        {0, 12, 15, 9, 14, 10, 18},
        {12, 0, 10, 17, 20, 20, 14},
        {15, 10, 0, 11, 19, 22, 22},
        {9, 17, 11, 0, 8, 21, 16},
        {14, 20, 19, 8, 0, 13, 12},
        {10, 20, 22, 21, 13, 0, 16},
        {18, 14, 22, 16, 12, 16, 0}
    };
    int nnod = sizeof(mapa) / sizeof(mapa[0]);

    // Caso sin solucion: No es posible atender a todos los clientes
    // En este escenario, no existen conexiones entre ningun cliente
    // int mapa[NNOD][NNOD] = {
    //     {0, 10, 20, 30, 40, 50, 5},
    //     {10, 0, 0, 0, 0, 0, 0},
    //     {20, 0, 0, 0, 0, 0, 0},
    //     {30, 0, 0, 0, 0, 0, 0},
    //     {40, 0, 0, 0, 0, 0, 0},
    //     {50, 0, 0, 0, 0, 0, 0},
    //     {5, 0, 0, 0, 0, 0, 0}
    // };
    // int nnod = sizeof(mapa) / sizeof(mapa[0]);

    Camion camiones[] = {
        {0, 100},
        {1, 100},
        {2, 100}
    };
    int ncam = sizeof(camiones) / sizeof(camiones[0]);

    Cliente clientes[] = {
        {0, 0},
        {1, 30},
        {2, 40},
        {3, 25},
        {4, 50},
        {5, 20},
        {6, 35}
    };
    int ncli = sizeof(clientes) / sizeof(clientes[0]);

    int haysolucion = buscarutas(mapa, camiones, clientes, nnod, ncam);
    cout << endl << "CONCLUSION" << endl;
    if (haysolucion) cout << "Hay solucion -> Cada cliente se atendio exactamente una vez";
    else cout << "No hay solucion -> Hay clientes sin atender, la ruta mostrada no es valida o no existe ruta";
    return 0;
}
