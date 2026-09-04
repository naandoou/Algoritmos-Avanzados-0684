#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

bool verificar_arreglo(vector<int> solu, int n) {
    for (int i = 0; i < solu.size(); i++) if (n == solu[i]) return false;
    return true;
}

void imprimir_solu(vector<int> solu) {
    for (int s: solu) cout << right << setw(3) << s;
    cout << endl;
}

void generarPermutaciones(int arr[3], int n, vector<int> solu) {
    if (solu.size() >= n) {
        imprimir_solu(solu);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (verificar_arreglo(solu, arr[i])) {
            // el numero arr[i] no esta repetido en solu
            solu.push_back(arr[i]);
            generarPermutaciones(arr, n, solu);
            solu.pop_back();
        }
    }
}

int main() {
    int arr[3] = {1,2,3};
    int n = sizeof(arr)/sizeof(arr[0]);
    vector<int> solu;
    generarPermutaciones(arr,n,solu);


    return 0;
}
