#include <iostream>
using namespace std;

int verificapeso(int *paq,int peso,int n) {
    int dp[n+1][peso+1];
    for (int i=0;i<=peso;i++)
        dp[0][i]=0;
    for (int i=0;i<=n;i++)
        dp[i][0]=1;

    for (int i=1;i<=n;i++) {
        for (int j=1;j<=peso;j++) {
            dp[i][j]=dp[i-1][j];
            if (dp[i][j]==0 and j-paq[i-1]>=0)
                dp[i][j]=dp[i-1][j-paq[i-1]];
        }
    }
    for (int i=0;i<=n;i++) {
        for (int j=0;j<=peso;j++)
            cout << dp[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    return dp[n][peso];
}

int main() {
    int paq[]={2,3,4};
    int peso=7;
    int n=sizeof(paq)/sizeof(paq[0]);

    cout<<verificapeso(paq,peso,n);
    return 0;
}
