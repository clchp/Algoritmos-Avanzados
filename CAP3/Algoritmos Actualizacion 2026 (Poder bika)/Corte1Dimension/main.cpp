#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cmp(int a, int b) {
    return a > b;
}

void imprimir(vector<int>barras, int n) {
    cout << endl;
    cout << "Cantidad de barras usadas: "<< n<< endl;
    cout << endl;
    cout << "Espacio sobrante por barra:" << endl;

    for (int i = 0; i < n; i++) {
        cout << "Barra "<< i + 1<< " -> sobra: "<< barras[i]<< endl;
    }
}

void solucion_cortar(int L, vector<int> piezas) {

    // ordenas descendente
    sort(piezas.begin(), piezas.end(), cmp);

    vector<int> barras; //guarda espacio de cada barra

    for (int pieza : piezas) {
        bool colocado = false;
        // Buscar la primera barra donde entre
        for (int i = 0; i < barras.size(); i++) {
            if (barras[i] >= pieza) { //si hay espacio
                barras[i] -= pieza;
                colocado = true;
                break;
            }
        }
        // Si no entra en ninguna barra, crear nueva
        if (!colocado) {
            barras.push_back(L - pieza);
        }
    }

    // imprimir resultados
    imprimir(barras, barras.size());
}

int main() {

    int L = 10; //longitud de cada barra
    vector<int> piezas = {4, 6, 3, 4, 4, 6, 3}; //piezas posibles

    solucion_cortar(L, piezas);

    return 0;
}