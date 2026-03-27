#include <iostream>
#include <algorithm>

using namespace std;
int coin_row(int coin[], int n) {
    if (n==0) return 0; //no hay monedas
    if (n==1) return coin[0]; // solo hay una moneda, por lo que se entrega esa
    int dp[n+1];
    dp[0]=0;
    dp[1]=coin[0];

    for (int i = 2; i <=n; i++) {
        dp[i]=max(dp[i-1], dp[i-2]+coin[i-1]);
    }
    return dp[n];
}

int main() {
    int coins[]={5,1,2,10,6,2};
    int n=6;

    cout<<"La maxima cantidad que se puede obtener con no adyacentes es: "<<coin_row(coins,n)<<endl;
    return 0;
}