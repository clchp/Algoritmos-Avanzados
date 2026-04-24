#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    // leer n desde la entrada estándar
    cout<<"Ingrese el numero n (1<=n<4=5): ";
    cin>>n;

    // Casos base
    if (n == 1 || n == 2) {
        cout << 2 << endl;
        return 0;
    }

    // Utilizamos long long porque para n=45 el resultado supera el límite de un int
    vector<long long> dp(n + 1, 0); //solo llenamos max por columnas

    dp[1] = 2; // Formas posibles: R, W
    dp[2] = 2; // Formas posibles: RW, WR (B no puede ir en los extremos)

    // Llenamos la tabla de Programación Dinámica
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2]; //los que terminan en ese mismo color y el mimso color pero dos anteriores para que el azul este en el medio
    }

    // Imprimir el resultado para N
    cout << dp[n] << endl;

    return 0;
}