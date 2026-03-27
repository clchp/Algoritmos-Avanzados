#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> dp;

int mochila(int n, int w, vector<int>tareas) {
    if (n==0 or w==0)return 0;
    if (dp[n][w]!=-1) return dp[n][w];
    if (tareas[n-1]>w) dp[n][w]=mochila(n-1,w,tareas);
    else dp[n][w]=max(mochila(n-1,w,tareas), tareas[n-1]+mochila(n-1,w-tareas[n-1],tareas));
    return dp[n][w];
}

int main() {
    vector<int> pesos={7,2,5,5,10};// horas que se tiene por cada tarea
    int n=pesos.size();
    int w=25;

    dp.assign(n+1,vector<int>(w+1,-1));
    int peso=mochila(n, w, pesos);
    if (peso<w)
        cout<<"No es posible llegar al peso factible "<<w<<" El peso maximo factible es: "<<peso<<endl;
    else
        cout<<"Si fue posible llegar al peso factible "<<w<<endl;
    return 0;
}
