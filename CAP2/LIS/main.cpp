#include <iostream>
#include <iomanip>
#include <vector>

#define N 8

using namespace std;
struct Nodo {
    int longitud;
    int padre;
};
vector<Nodo> dp;
void resolver_LIS(int secuencia[N]) {
    dp.resize(N);
    for (int i = 0; i < N; i++) {
        dp[i].padre = -1; //todavia no tiene
        dp[i].longitud = 1; //como minimo puede una subsecuencia de 1
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <i; j++) {
            if (secuencia[j] < secuencia[i] and dp[j].longitud+1>dp[i].longitud) {
                dp[i].longitud = dp[j].longitud+1;
                dp[i].padre = j;
            }
        }
    }
    int maximo=0;
    int idx;
    for (int i = 0; i < N; i++) {
        if (maximo < dp[i].longitud) {
            maximo = dp[i].longitud; //awui hallamos el maximo maximo=5
            idx=i;
        }
    }
    cout<<maximo<<endl;
    //reconstruir
    vector<int>lis;

    while (idx != -1) {
        lis.push_back(secuencia[idx]);
        idx = dp[idx].padre;
    }

    for (int i = maximo-1; i >= 0; i--) {
        cout<<lis[i];
        if (i!=0){cout<<" ";}
    }
    return;
}

int main() {
    int secuencia[N] = {-7, 1, 9, 8, 3, 8, 10, 1};
    resolver_LIS(secuencia);
    return 0;
}