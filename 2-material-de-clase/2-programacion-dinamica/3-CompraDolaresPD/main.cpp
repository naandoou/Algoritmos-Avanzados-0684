#include <iostream>
#include <climits>

using namespace std;

int ganancia(int k,int n,int *precios) {
    int dp[k+1][n];
    for (int i=0;i<=k;i++) dp[i][0]=0;
    for (int i=1;i<n;i++)  dp[0][i]=0;

    for (int i=1;i<=k;i++) {
        for (int j=1;j<n;j++) {
            int maximo=INT_MIN;
            for (int m=0;m<j;m++)
                maximo=max(maximo,precios[j]-precios[m]+dp[i-1][m]);
            dp[i][j]=max(maximo,dp[i][j-1]);
        }
    }
    for (int i=0;i<=k;i++) {
        for (int j=0;j<n;j++)
            cout<<dp[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    return dp[k][n-1];
}

int main() {
    int k=3;
    int precios[]={300,320,350,330,360,380};
    int n=sizeof(precios)/sizeof(precios[0]);

    cout<<"La ganancia es:"<<endl<<ganancia(k,n,precios)<<endl;

    return 0;
}
