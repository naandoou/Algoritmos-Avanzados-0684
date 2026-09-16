#include <iostream>
#include <algorithm>

using namespace std;

bool compara(int a, int b) {
    return a<b;
}
void muestra(int *paq,int n) {
    for(int i=0;i<n;i++)
        cout<<paq[i]<<" ";
    cout<<endl;
}

int cargamochila(int peso,int n,int *paq) {
    sort(paq, paq+n,compara);
    muestra(paq,n);
    int residual=peso;
    for(int i=0;i<n;i++) {
        if (residual-paq[i]>=0)
            residual-=paq[i];
    }

    return residual;
}


int main() {
    int peso=15;
    int paq[]={2,1,2,4,12};
    int n=sizeof(paq)/sizeof(paq[0]);
    cout <<cargamochila(peso,n,paq);

    return 0;
}
