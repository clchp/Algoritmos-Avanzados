#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mochila(int n, int w, vector<int> pesos, vector<int> valores, vector<vector<int>> &dp){
    if(n==0 or w==0) return 0; // no hay espacio suficiente
    if(dp[n][w]!=-1) return dp[n][w];
    if(pesos[n-1]>w) dp[n][w]=mochila(n-1, w, pesos, valores, dp);
    else dp[n][w]=max(mochila(n-1, w, pesos, valores, dp), valores[n-1]+mochila(n-1, w-pesos[n-1],pesos, valores, dp));
    return dp[n][w];
}


int main(){
    vector<int> pesos={2,1,3,2};
    vector<int> valores={12,10,20,15};
    int n=4;
    int w=5;

    vector<vector<int>> dp(n+1, vector<int>(w+1, -1));
    cout<<"Mayor solucion: "<<mochila(n,w, pesos, valores, dp);

    return 0;
}