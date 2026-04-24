#include <iostream>
#include <vector>

using namespace std;
#define N 7

vector<int> dp={0}; //todo en 0

void resolver_coin_row(int coins[N]) {
    dp.resize(N+1,0); //un espacio mas para que el i coincida
    dp[0]=coins[0]; //porque se espera que para una moneda no haya nada
    dp[1]=coins[1]; //como primer valor ya tomara la primera moneda
    for (int i = 2; i <= N; i++) {
        dp[i]=max(dp[i-1],coins[i]+dp[i-2]); //lo mejor que tiene hasta un espacio antes o lo mejor que etendra contando esta moneda y lo de 2 espacios antes
    }
    cout<<dp[N]<<endl;
    return;
}

int main() {
    int coins[N]={0, 5, 1, 2, 10, 6, 2};
    resolver_coin_row(coins);
    return 0;
}