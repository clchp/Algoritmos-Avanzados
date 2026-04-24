#include <iostream>
#include <vector>

#define STATES 3
#define N 2 //2 columnas
using namespace std;

void resolver_estados() {
    int dp[STATES+1][N+1];
    //AQUI LLENO DE 0's
    for (int state = 0; state <= STATES; state++) {
        for (int n = 0; n <= N; n++) {
            dp[state][n] = 0;
        }
    }
    //inicializamos
    dp[0][1] = 1; //este es C/C
    dp[1][1] = 1; //este es C/A
    dp[2][1] = 1; //este es A/C

    for (int i = 2; i <= N; i++) {
        dp[0][i]=dp[0][i-1]+dp[1][i-1]+dp[2][i-1];
        dp[1][i]=dp[0][i-1]+dp[2][i-1];
        dp[2][i]=dp[0][i-1]+dp[1][i-1];
    }
    int resultado=dp[0][N]+dp[1][N]+dp[2][N];
    cout<<"El resultado es: "<<resultado<<endl;
    return;

}

int main() {
    resolver_estados();
    return 0;
}