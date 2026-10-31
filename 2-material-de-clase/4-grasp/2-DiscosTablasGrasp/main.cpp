#include <algorithm>
#include <iostream>
#include <vector>
#define ALFA        0.5
#define MAXITERA    1

using namespace std;

struct Tobjeto {
    int cod;
    int rendimiento;
};
struct Tsalida {
    int disco;
    int tabla;
};

bool compara(Tobjeto a, Tobjeto b) {
    return a.rendimiento>b.rendimiento;
}
int buscaind(vector<Tobjeto> vobj, int valor) {
    int cont=0;
    for(int i=0;i<vobj.size();i++)
        if (vobj[i].rendimiento>=valor)
            cont++;
    return cont;
}


int asignadiscos(Tobjeto *tabla,Tobjeto *disco,int n,int m) {
    int mejor=0;
    vector<Tsalida> vfinal;
    srand(time(NULL));
    for (int i=0;i<MAXITERA;i++) {
        int residual;
        vector<Tobjeto>vtablas;
        vector<Tobjeto>vdisco;
        vector<Tsalida>vresultado;
        vtablas.insert(vtablas.begin(),tabla,tabla+n);
        vdisco.insert(vdisco.begin(),disco,disco+m);
        sort(vtablas.begin(),vtablas.end(),compara);
        while (not vtablas.empty()) {
            // RCL de tablas
            int beta1=vtablas[0].rendimiento;
            int tau1=vtablas[vtablas.size()-1].rendimiento;
            int finrcl1=beta1-ALFA*(beta1-tau1);
            int indmin1=buscaind(vtablas,finrcl1);
            int indale1 = rand()%indmin1;
            // ordenando los discos
            sort(vdisco.begin(),vdisco.end(),compara);
            // RCL de discos
            int beta2=vdisco[0].rendimiento;
            int tau2=vdisco[vdisco.size()-1].rendimiento;
            int finrcl2=beta2-ALFA*(beta2-tau2);
            int indmin2=buscaind(vdisco,finrcl2);
            int indale2 = rand()%indmin2;

            if (vdisco[indale2].rendimiento>=vtablas[indale1].rendimiento) {
                vresultado.push_back({vdisco[indale2].cod,vtablas[indale1].cod});
                vdisco[indale2].rendimiento-=vtablas[indale1].rendimiento;
            }
            vtablas.erase(vtablas.begin()+indale1);
        }
        sort(vdisco.begin(),vdisco.end(),compara);
        // residual de la asignacion que representa al resultado
        residual=vdisco[vdisco.size()-1].rendimiento;
        if (residual>mejor) {
            mejor=residual;
            vfinal.clear();
            vfinal.insert(vfinal.begin(),vresultado.begin(),vresultado.end());
        }
    }
    for (int i=0;i<vfinal.size();i++)
        cout << vfinal[i].disco << " " << vfinal[i].tabla << endl;
    cout << endl;
    cout << mejor << endl;
    return mejor;
}



int main() {
    Tobjeto tabla[]={
        {1,150},{2,100},{3,80},
        {4,50},{5,120},{6,10}};

    Tobjeto disco[]={{1,250},{2,200},{3,200}};

    int n=sizeof(tabla)/sizeof(tabla[0]);
    int m=sizeof(disco)/sizeof(disco[0]);

    asignadiscos(tabla,disco,n,m);

    return 0;
}
