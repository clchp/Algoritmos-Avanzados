#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> nemo;

int mochila(int n, int w, vector<int> pesos, vector<int> valores) {
    if (n==0||w==0) return 0;
    if (nemo[n][w]!=-1) return nemo[n][w];
    if (pesos[n-1]>w) nemo[n][w]=mochila(n-1, w, pesos, valores);
    else nemo[n][w]=max(mochila(n-1, w, pesos, valores), valores[n-1]+mochila(n-1, w-pesos[n-1], pesos, valores));
    return nemo[n][w];
}


int main() {
    int n=4;
    int w=5;
    vector<int> pesos={2,1,3,2};
    vector<int> valores={12,10,20,15};
    nemo.assign(n+1, vector<int>(w+1, -1));

    cout<<"Mayor capacidad de mochila: "<<mochila(n,w,pesos,valores);

    return 0;
}