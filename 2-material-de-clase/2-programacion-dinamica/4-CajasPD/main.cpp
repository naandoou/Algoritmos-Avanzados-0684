#include <algorithm>
#include <iostream>
#define MAX 10
using namespace std;

struct Caja {
    int largo;
    int ancho;
    int alto;
    int peso;
};

bool compara(Caja a, Caja b) {
    return a.largo*a.ancho > b.largo*b.ancho;
}


void maxaltura(int *largo,int *ancho,int *alto,
    int *peso, int n) {
    Caja cajas[MAX];
    int cont=0;
    for (int i=0;i<n;i++) {
        cajas[cont].largo=max(ancho[i],largo[i]);
        cajas[cont].ancho=min(ancho[i],largo[i]);
        cajas[cont].alto=alto[i];
        cajas[cont].peso=peso[i];
        cont++;
        cajas[cont].largo=max(alto[i],largo[i]);
        cajas[cont].ancho=min(alto[i],largo[i]);
        cajas[cont].alto=ancho[i];
        cajas[cont].peso=peso[i];
        cont++;
        cajas[cont].largo=max(ancho[i],alto[i]);
        cajas[cont].ancho=min(ancho[i],alto[i]);
        cajas[cont].alto=largo[i];
        cajas[cont].peso=peso[i];
        cont++;
    }
    sort(cajas,cajas+cont,compara);
    int dp[MAX]{};
    for (int i=0;i<cont;i++) {
        dp[i]=cajas[i].alto;
        for (int j=0;j<i;j++) {
            if (cajas[i].peso<=cajas[j].peso
                and cajas[i].largo<cajas[j].largo
                and cajas[i].ancho<cajas[j].ancho) {
                int naltura=cajas[i].alto+dp[j];
                if (naltura>dp[i])
                    dp[i]=naltura;
            }
        }
    }
    cout << endl;
    for (int i=0;i<cont;i++) {
        cout<<dp[i]<<" ";
    }
}



int main() {
    int altura[]={1,2};
    int ancho[]={3,15};
    int largo[]={4,6};
    int peso[]={2,10};
    int n=sizeof(altura)/sizeof(altura[0]);

    maxaltura(altura,ancho,largo,peso,n);

    return 0;
}
