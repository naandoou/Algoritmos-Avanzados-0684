#include <algorithm>
#include <iostream>
#include <vector>
#define N 8
struct Nodo {
    int ciudad;
    int distancia;
};

using namespace std;

bool compara(Nodo a, Nodo b) {
    return a.distancia < b.distancia;
}

int calcularuta(int ini,int fin, int mapa[][N]) {
    int totalmin=0;
    int ciudad=ini;
    cout << ini;
    while (true) {
        vector<Nodo> vecinos;
        for (int i=0;i<N;i++)
            if (mapa[ciudad][i]>0) {
                Nodo aux;
                aux.ciudad=i;
                aux.distancia=mapa[ciudad][i];
                vecinos.push_back(aux);
            }
        if (not vecinos.empty()) {
            sort(vecinos.begin(),vecinos.end(),compara);
            ciudad=vecinos[0].ciudad;
            cout << " - " << ciudad;
            totalmin+=vecinos[0].distancia;
        }
        if (fin==ciudad)break;
        if (vecinos.empty()) {
            cout << "No hay solucion"<< endl;
            totalmin=0;
            break;
        }
    }
    cout <<endl;
    return totalmin;
}

int main() {
    int mapa[][N]={
                {0,4,5,6,0,0,0,0},
                {0,0,0,0,2,0,0,0},
                {0,0,0,0,0,0,0,3},
                {0,0,0,0,0,3,0,0},
                {0,0,0,0,0,0,10,0},
                {0,0,0,0,0,0,2,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0}};

    cout << calcularuta(0,6,mapa) << endl;

    return 0;
}
