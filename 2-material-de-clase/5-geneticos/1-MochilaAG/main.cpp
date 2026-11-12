#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#define NUMIND 20
#define NUMGENERACIONES 1
#define TASASELECCION 0.25
using namespace std;

bool esaberracion(vector<int>cromosoma,int *paq,
    int peso) {
    int suma=0;
    for (int i=0;i<cromosoma.size();i++)
        suma+=cromosoma[i]*paq[i];
    if (suma>peso)
        return true;
    return false;
}

int calculafitness(vector<int>cromosoma,int *paq) {
    int suma=0;
    for (int i=0;i<cromosoma.size();i++)
        suma+=cromosoma[i]*paq[i];
    return suma;
}

void generapoblacion(vector<vector<int>>&poblacion,
    int *paq,int n,int peso) {
    int cont=0;
    srand(time(NULL));
    while (cont<NUMIND) {
        vector<int>cromosoma;
        for (int i=0;i<n;i++)
            cromosoma.push_back(rand()%2);
        if (not esaberracion(cromosoma,paq,peso)) {
            poblacion.push_back(cromosoma);
            cont++;
        }
    }


}

void muestrapoblacion(vector<vector<int>>&poblacion,int *paq) {
    for (int i=0;i<poblacion.size();i++) {
        cout <<setw(4)<<i+1<<" ";
        for (int j=0;j<poblacion[i].size();j++)
            cout << poblacion[i][j] << " ";
        cout << "fo=" <<calculafitness(poblacion[i], paq)<<endl;
    }
}
void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int>&supervivencia,int *paq,int n,int peso) {
    int sumafitness=0;

    for (int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i], paq);
    int acumulado=0;
    for (int i=0;i<poblacion.size();i++) {
        acumulado+=calculafitness(poblacion[i], paq);
        int limite =round(100*acumulado/sumafitness);
        supervivencia.push_back(limite);
    }
}
void cargaruleta(vector<int>&supervivencia,int *ruleta) {
    int ini=0;
    for (int i=0;i<supervivencia.size();i++) {
        int fin=supervivencia[i];
        for (int j=ini;j<fin;j++)
            ruleta[j]=i;
        ini=fin;
    }
}

void seleccion(vector<vector<int>>poblacion,
    vector<vector<int>>&mejores,int *paq,int n,int peso ) {
    int ruleta[100];
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,paq,n,peso);
    int numpadres=round(poblacion.size()*TASASELECCION);
    cargaruleta(supervivencia,ruleta);
    for (int i=0;i<numpadres;i++) {
        int ticket=rand()%100;
        int ind=ruleta[ticket];
        mejores.push_back(poblacion[ind]);
    }
}
void mochila(int *paq,int n,int peso) {
    vector<vector<int>>poblacion;
    int cont=0;
    generapoblacion(poblacion,paq,n,peso);
    muestrapoblacion(poblacion,paq);
    for (int i=0;i<NUMGENERACIONES;i++) {
        vector<vector<int>>mejores;
        seleccion(poblacion,mejores,paq,n,peso);
        cout <<"Seleccion:"<<endl;
        muestrapoblacion(mejores,paq);
    }

}



int main() {
    int paq[]={10,21,4,5,9,18,2,17,14};
    int peso=30;
    int n=sizeof(paq)/sizeof(paq[0]);

    mochila(paq,n,peso);

    return 0;
}
