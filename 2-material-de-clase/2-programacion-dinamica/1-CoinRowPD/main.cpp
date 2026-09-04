#include <iostream>
using namespace std;

int calculacoin(int *mon,int n) {
    int F[n+1];
    F[0]=0;
    F[1]=mon[0];
    for (int i=2;i<=n;i++) {
        int max1=F[i-2]+mon[i-1];
        int max2=F[i-1];
        if (max1>max2)F[i]=max1;
        else
            F[i]=max2;
    }
    for (int i=0;i<=n;i++)
        cout<<F[i]<<" ";
    cout<<endl;
    return F[n];
}


int main() {
    int mon[]={5,1,2,10,6,2};
    int n=sizeof(mon)/sizeof(mon[0]);

    cout << calculacoin(mon,n);

    return 0;
}
