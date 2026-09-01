#include <iostream>
using namespace std;
int mochilaback(int pos,int n,int peso,int *paq) {
    if (pos==n or peso<0)
        return 0;
    if (paq[pos]==peso)
        return 1; // 1 es true si no sabias
    if (mochilaback(pos+1,n,peso-paq[pos],paq))
        return 1;
    else
        return(mochilaback(pos+1,n,peso,paq));//yo soy el back
}


int main() {
    int paq[]={2,1,4,1,12};
    int peso=15;
    int n=sizeof(paq)/sizeof(paq[0]);
    cout << mochilaback(0,n,peso,paq);
    return 0;
}