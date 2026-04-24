#include <iostream>
#include <vector>

using namespace std;

vector<int>dp;
#define N 4
#define W 5

void mochilita_resolver(int pesos[N], int beneficios[N]) {
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0)); //N+1 filas y W+1 columnas
    for (int elementos=1; elementos<=N; elementos++) {
        for (int capacidad=1;capacidad<=W;capacidad++) {
            int peso=pesos[elementos-1];
            int beneficio=beneficios[elementos-1];
            if (peso<=capacidad) { //eso quiere decir que todavia hay espacio y se puede meter
                dp[elementos][capacidad]=max(dp[elementos-1][capacidad], beneficio+dp[elementos-1][capacidad-peso]);
            }else {
                dp[elementos][capacidad]=dp[elementos-1][capacidad]; //se queda con el anterior
            }
        }
    }
    cout<<"Mochilita resolver: "<<dp[N][W]<<endl;
}

int main() {
    int pesos[N]={2, 1, 3, 2};
    int beneficios[N]={12, 10, 20, 15};
    mochilita_resolver(pesos, beneficios);
    return 0;
}

