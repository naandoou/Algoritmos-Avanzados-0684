#include <algorithm>
#include <iostream>
#include <vector>
struct Tobjeto {
    int id;
    int cant;
};

struct Tresultado {
    int idcamion;
    int idpaquete;
};

using namespace std;

bool comparapaq(Tobjeto a, Tobjeto b) {
    return a.cant > b.cant;
}

bool comparacam(Tobjeto a, Tobjeto b) {
    return a.cant < b.cant;
}


void cargacamion(Tobjeto*paq,Tobjeto*cam,int n,int m) {
    vector<Tobjeto>vpaq;
    vector<Tobjeto>vcam;
    vector<Tresultado>vsolucion;
    vpaq.insert(vpaq.begin(),paq,paq+n);
    vcam.insert(vcam.begin(),cam,cam+m);
    sort(vpaq.begin(),vpaq.end(),comparapaq);
    for (int i=0;i<vpaq.size();i++)
        cout << vpaq[i].id<<" ";
    cout << endl;
    while (not vpaq.empty()) {
        sort(vcam.begin(),vcam.end(),comparacam);
        for (int i=0;i<vcam.size();i++) {
            if (vcam[i].cant>=vpaq[0].cant) {
                vcam[i].cant -= vpaq[0].cant;
                vsolucion.push_back({vcam[i].id,vpaq[0].id});
                break;
            }
        }
        vpaq.erase(vpaq.begin());
    }
    for (int i=0;i<vsolucion.size();i++)
        cout << vsolucion[i].idcamion<<" - "<<vsolucion[i].idpaquete<<endl;


}

int main() {
    Tobjeto paq[]={
        {1,150},{2,100},{3,180},{4,50},
           {5,120},{6,10}};
    Tobjeto cam[]={
        {1,250},{2,200},{3,200},
        {4,100},{5,300}};

    int n=sizeof(paq)/sizeof(paq[0]);
    int m=sizeof(cam)/sizeof(cam[0]);

    cargacamion(paq,cam,n,m);

    return 0;
}
