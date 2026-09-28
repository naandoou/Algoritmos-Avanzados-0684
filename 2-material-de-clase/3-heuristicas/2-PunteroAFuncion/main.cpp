#include <iostream>

using namespace std;

int suma(int a, int b) {
    return a + b;
}
int resta(int a, int b) {
    return a - b;
}
int compara(const void* a, const void* b) {
    int *ai,*bi;
    ai = (int*)a;
    bi = (int*)b;
    return *ai - *bi;
}

int main() {
    int (*puntf)(int,int);
    puntf = suma;
    cout << puntf(4,4) << endl;
    puntf = resta;
    cout << puntf(7,4) << endl;
    int notas[]={12,10,15,16,20};
    int n=sizeof(notas)/sizeof(notas[0]);
    qsort(notas,n,sizeof(int),compara);
    for(int i=0;i<n;i++) {
        cout << notas[i] << " ";
    }

    return 0;
}
