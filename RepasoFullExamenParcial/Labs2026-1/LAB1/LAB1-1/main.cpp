#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void imprimir(vector<int> numeros) {
    for (int i = 0; i < numeros.size(); i++) {
        cout << numeros[i];
        if (i + 1 != numeros.size()) {
            cout << ", ";
        }
    }
}

void backtracking(vector<int> numeros,vector<int>& actual,vector<int>& mejor,int suma_actual,
    int suma_total,int objetivo,int pos,int& mejor_diferencia) {
    // CASO BASE
    if (pos == numeros.size()) {
        int diferencia = abs(2 * suma_actual-suma_total);
        if (diferencia < mejor_diferencia) {
            mejor_diferencia = diferencia;
            mejor = actual;
        }
        return;
    }
    // Si la suma actual supera el objetivo, volvemos para no desperdiciar recursos
    if (suma_actual > objetivo) {
        return;
    }

    // OPCION 1 -> meter elemento
    actual.push_back(numeros[pos]);
    backtracking(numeros,actual,mejor,suma_actual + numeros[pos],suma_total,objetivo,pos + 1,mejor_diferencia);
    actual.pop_back(); //si es que vuelve deshacemos el cambio
    // OPCION 2 -> no meter elemento
    backtracking(numeros,actual,mejor,suma_actual,suma_total,objetivo,pos + 1,mejor_diferencia);
}

int main() {
    vector<int> numeros = {3,1,4,2,5,1};
    sort(numeros.begin(),numeros.end(),greater<int>());
    cout << "NUMEROS ORDENADOS:" << endl;
    imprimir(numeros);

    int suma_total = 0;
    for (int i = 0; i < numeros.size(); i++) {
        suma_total += numeros[i];
    }

    int objetivo = suma_total / 2;
    vector<int> actual; //aqui se guarda el subconjunto actual
    vector<int> mejor; //aqui la mejor solucion

    int mejor_diferencia = 999999;

    backtracking(numeros,actual,mejor,0,suma_total,objetivo,0,mejor_diferencia);

    // ARMAR SEGUNDO SUBCONJUNTO
    vector<int> segundo = numeros;
    for (int i = 0; i < mejor.size(); i++) {
        auto it = find(segundo.begin(),segundo.end(),mejor[i]);

        if (it != segundo.end()) {
            segundo.erase(it);
        }
    }

    cout << endl << endl;

    cout << "SUBCONJUNTO 1:" << endl;
    imprimir(mejor);

    cout << endl;

    cout << "SUBCONJUNTO 2:" << endl;
    imprimir(segundo);

    cout << endl;

    cout << "DIFERENCIA MINIMA: "
         << mejor_diferencia << endl;

    return 0;
}