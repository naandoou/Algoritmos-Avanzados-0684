#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#define ALFA 0.5
#define MAXITERACIONES 1000

using namespace std;

int buscaind(vector<int>paq,int valor) {
    int cont=0;
    for (int i=0;i<paq.size();i++) {
        if (valor>=paq[i])
            cont++;
    }
    return cont;
}

void cargapaquetes(int *paq,int peso,int n) {
    vector<int>vpaq;
    int mejor=INT_MAX;
    vector<int>vmejor;
    srand(time(NULL));
    for (int i=0;i<MAXITERACIONES;i++) {
        vector<int>vsolucion;
        vpaq.insert(vpaq.begin(),paq,paq+n);
        sort(vpaq.begin(),vpaq.end());
        int residual=peso;
        while (not vpaq.empty()) {
            int beta=vpaq[0];
            int tau=vpaq[vpaq.size()-1];
            int finrcl=beta+ALFA*(tau-beta);
            int indrcl=buscaind(vpaq,finrcl);
            int indale=rand()%indrcl;
            if (residual-vpaq[indale]>=0) {
                residual-=vpaq[indale];
                vsolucion.push_back(vpaq[indale]);
            }
            vpaq.erase(vpaq.begin()+indale);
        }
        if (residual<mejor) {
            mejor=residual;
            vmejor.clear();
            vmejor.insert(vmejor.begin(),vsolucion.begin(),vsolucion.end());
        }
    }
    for (int i=0;i<vmejor.size();i++)
        cout << vmejor[i] << " ";
    cout << endl;
    cout << "Residual:"<< mejor << endl;
}

int main() {
    int paq[]={2,2,3,4,3,10,5,11,20,15};
    int peso=25;
    int n=sizeof(paq)/sizeof(paq[0]);
    cargapaquetes(paq,peso,n);
    return 0;
}
