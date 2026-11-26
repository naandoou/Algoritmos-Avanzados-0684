#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>

#define ITERACIONES 1000
#define NUMIND 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.5
#define TMUTACION 0.3
#define TAMRULETA 100

using namespace std;

int calculafitness(vector<int> cromo,int *peso) {
    int pesoTotal=0;

    for(int i=0;i<cromo.size();i++)
        if(cromo[i]!=0)
            pesoTotal+=peso[i];

    return pesoTotal;
}

bool aberracion(vector<int> ind,int *peso,int *capacidad, int n,int m) {

    vector<int> carga(m+1,0);
    for(int i=0;i<n;i++) {
        int mochila=ind[i];
        if(mochila!=0)
            carga[mochila]+=peso[i];
    }

    for(int j=1;j<=m;j++)
        if(carga[j]>capacidad[j-1])
            return true;

    return false;
}

void muestrapoblacion(vector<vector<int>> poblacion, int *peso) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++)
            cout<<poblacion[i][j]<<" ";

        cout<<" fitness="<<calculafitness(poblacion[i],peso)<<endl;
    }
}


void mataclon(vector<vector<int>> &poblacion) {
    map<vector<int>,vector<int>> unicos;
    for(int i=0;i<poblacion.size();i++)
        unicos[poblacion[i]]=poblacion[i];

    poblacion.clear();
    for(auto &ind:unicos)
        poblacion.push_back(ind.second);
}


void generapoblacion(vector<vector<int>> &poblacion,
                     int *peso,int *capacidad,int n,int m) {
    int cont=0;
    while(cont<NUMIND) {
        vector<int> individuo;
        for(int i=0;i<n;i++)
            individuo.push_back(rand()%(m+1));

        if(!aberracion(individuo,peso,capacidad,n,m)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

bool calculasupervivencia(vector<vector<int>> poblacion, vector<int> &supervivencia,
                          int *peso) {

    long long sumaFitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumaFitness+=calculafitness(poblacion[i],peso);
    // No se puede aplicar ruleta si todos tienen fitness cero

    if(sumaFitness==0)return false;

    int acumulado=0;

    for(int i=0;i<poblacion.size();i++) {
        acumulado+=calculafitness(poblacion[i],peso);
        int limite=round(100.0*acumulado/sumaFitness);
        supervivencia.push_back(limite);
    }
    supervivencia.back()=100;

    return true;
}

void cargaruleta(vector<int> supervivencia,int *ruleta) {
    int inicio=0;
    for(int i=0;i<supervivencia.size();i++) {
        int fin=supervivencia[i];
        for(int j=inicio;j<fin;j++)
            ruleta[j]=i;
        inicio=fin;
    }
}

bool seleccion(vector<vector<int>> poblacion,vector<vector<int>> &padres, int *peso) {

    int ruleta[TAMRULETA];
    vector<int> supervivencia;
    if(!calculasupervivencia(poblacion,supervivencia,peso))
        return false;
    cargaruleta(supervivencia,ruleta);
    int npadres=round(poblacion.size()*TSELECCION);
    for(int i=0;i<npadres;i++) {
        int ticket=rand()%100;
        int ind=ruleta[ticket];
        if(ind!=-1)
            padres.push_back(poblacion[ind]);
    }
    return !padres.empty();
}

void creahijo(vector<int> padre,vector<int> madre, vector<int> &hijo) {
    int pos=round(padre.size()*PCASAMIENTO);
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>> &poblacion,vector<vector<int>> padres,
    int *peso,int *capacidad,int n,int m) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j) {
                vector<int> hijo;
                creahijo(padres[i],padres[j],hijo);
                if(!aberracion(hijo,peso,capacidad,n,m))
                    poblacion.push_back(hijo);
            }
}

// MUTACION

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>> padres,
              int *peso,int *capacidad,int n,int m) {

    int nmut=round(n*TMUTACION);
    for(int i=0;i<padres.size();i++) {
        int cont=0;
        while(cont<nmut) {

            int gen=rand()%n;
            padres[i][gen]=rand()%(m+1);
            cont++;
        }
        if(!aberracion(padres[i],peso,capacidad,n,m))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int>> &poblacion,
               vector<vector<int>> padres,
               int *peso,int *capacidad,int n,int m) {

    for(int i=0;i<padres.size();i++) {
        for(int j=0;j<n;j++)
            padres[i][j]=m-padres[i][j];

        if(!aberracion(padres[i],peso,capacidad,n,m))
            poblacion.push_back(padres[i]);
    }
}

void regenerapoblacion(vector<vector<int>> &poblacion,
                       int *peso) {
    mataclon(poblacion);
    sort(poblacion.begin(),poblacion.end(),
         [peso](const vector<int>& a,
                const vector<int>& b) {

            return calculafitness(a,peso)>
                   calculafitness(b,peso);
         });
    if(poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,
                        poblacion.end());
}

void muestramejor(vector<vector<int>> poblacion,
                  int *peso,int *capacidad,int m) {
    int mejor=0;
    cout<<endl<<"Mejor fitness = "<<calculafitness(poblacion[0],peso)<<endl;

    for(int ind:poblacion[0])
        cout<<ind<<" ";

    cout<<endl;
    int sumaCap=0;
    for(int i=0;i<m;i++)
        sumaCap+=capacidad[i];

    cout<<"Desperdicio = " <<sumaCap-calculafitness(poblacion[0],peso)<<endl;
}


void multimochilaAG(int *peso,int n,int *capacidad,int m) {
    vector<vector<int>> poblacion;
    srand(time(NULL));
    generapoblacion(poblacion,peso,capacidad,n,m);
    for(int it=0;it<ITERACIONES;it++) {
        vector<vector<int>> padres;
        casamiento(poblacion,padres,peso,capacidad,n,m);
        mutacion(poblacion,padres,peso,capacidad,n,m);
        inversion(poblacion,padres,peso,capacidad,n,m);
        regenerapoblacion(poblacion,peso);
        cout<<endl<<"ITERACION "<<it+1<<endl;
        muestramejor(poblacion,peso,capacidad,m);
    }
}

int main() {

    int peso[]={4,7,5,8,13,6,12};
    int capa[]={15,15,10,20};
    int n=sizeof(peso)/sizeof(peso[0]);
    int m=sizeof(capa)/sizeof(capa[0]);

    multimochilaAG(peso,n,capa,m);

    return 0;
}
