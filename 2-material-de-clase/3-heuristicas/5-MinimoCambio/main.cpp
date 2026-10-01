#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void buscaminicambio(int monto,int n,int *deno) {
    vector<int>vcambio;
    sort(deno,deno+n);
    for (int i=n-1;i>=0;i--) {
        while (monto>=deno[i]) {
            monto-=deno[i];
            vcambio.push_back(deno[i]);
        }
        if (monto==0) break;
    }
    for (int i=0;i<vcambio.size();i++)
        cout << vcambio[i] << " ";
}

int main() {
    int deno[]={1,2,5,10,20,50};
    int n=sizeof(deno)/sizeof(deno[0]);
    int monto=19;
    buscaminicambio(monto,n,deno);
    return 0;
}
