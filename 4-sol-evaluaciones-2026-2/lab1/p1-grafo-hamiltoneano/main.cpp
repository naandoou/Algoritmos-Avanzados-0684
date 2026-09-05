#include <iostream>
#include <vector>
using namespace std;
#define N 5

// 0: A
// 1: B
// 2: C
// 3: D
// 4: E

bool verificaprimeravisita(int nodo, vector<int> sol) {
    for (int i = 0; i < sol.size(); i++) if (sol[i] == nodo) return false;
    return true;
}

void imprimirciclo(vector<int> sol) {
    for (int i = 0; i < sol.size() - 1; i++) {
        char letrauno, letrados;
        letrauno = 'A' + sol[i];
        letrados = 'A' + sol[i + 1];
        cout << letrauno << " -> " << letrados << endl;
    }
}

bool hamiltoneano(int nodoactual, int grafo[N][N], vector<int> sol, int nodoinicio) {
    if (sol.size() == N) {
        // aca, verificamos la conexion directa entre el ultimo nodo y el nodo de inicio
        if (grafo[nodoactual][nodoinicio] == 0) return false;
        // en caso haya conexion, imprimimos el ciclo y retornamos true
        sol.push_back(nodoinicio);
        imprimirciclo(sol);
        return true;
    }
    // cuando iniciamos el recorrido, pusheamos directamente el primer nodo
    if (sol.size() == 0) sol.push_back(0);
    // recorremos las opciones de recorrido
    for (int i = 0; i < N; i++) {
        // verificamos que la opcion de recorrido sea correcta
        if (grafo[nodoactual][i] == 1 and verificaprimeravisita(i, sol)) {
            sol.push_back(i);
            if (hamiltoneano(i, grafo, sol, nodoinicio)) return true;
            sol.pop_back();
        }
    }
    return false;
}

int main() {
    int grafo[N][N] = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0}
    };
    // int grafo[N][N] = {
    //     {0, 1, 1, 0, 0},
    //     {1, 0, 1, 0, 0},
    //     {1, 1, 0, 1, 1},
    //     {0, 0, 1, 0, 1},
    //     {0, 0, 1, 1, 0}
    // };

    vector<int> sol;
    if (hamiltoneano(0, grafo, sol, 0)) cout << "Por tanto, el ciclo es hamiltoneano" << endl; // iniciamos en nodo A (0)
    else cout << "El ciclo no es hamiltoneano";
    return 0;
}
