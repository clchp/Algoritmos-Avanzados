#include <iostream>
#include <vector>

using namespace std;

#define alfa 0.4
#define ITERACIONES 10000

struct Nodo {
    char Nombre;
    int ganancia;
    vector<int> lugares_conocidos;
};

vector<int> construir_RCL(int actual, vector<Nodo>& nodos, vector<bool>& visitado) {
    vector<int> candidatos;

    // Guardamos solo los vecinos del nodo actual que no estén visitados
    for (int idx : nodos[actual].lugares_conocidos) { //recorremos los vecinos del actual
        if (!visitado[idx]) // si no ha sido visitado se guarda
            candidatos.push_back(idx); //indice de no visitado guardado
    }

    if (candidatos.empty()) return {};

    // hallar beta (mejor ganancia) y tau (peor ganancia)
    int beta = INT_MIN, tau = INT_MAX;
    for (int idx : candidatos) {
        if (nodos[idx].ganancia > beta) beta = nodos[idx].ganancia;
        if (nodos[idx].ganancia < tau) tau = nodos[idx].ganancia;
    }

    // umbral para formar la RCL
    double limite = beta - alfa * (beta - tau);
    vector<int> RCL;
    for (int idx : candidatos)
        if (nodos[idx].ganancia >= limite)
            RCL.push_back(idx);

    return RCL;
}

void grasp_nodos(vector<Nodo>& nodos, int n) {
    srand(time(NULL)); //random
    int mejor_ganancia = INT_MIN;
    vector<int> mejor_camino;
    for (int it = 0; it < ITERACIONES; it++) {
        vector<bool> visitado(n, false); //se marcan los lugares que ya se ha visitado
        vector<int> camino; //la solucion para la iteracion
        int actual = 0; // empezamos desde A
        visitado[actual] = true; //lo marcamos como que ya lo visitamos
        camino.push_back(actual); //lo agregamos a la solucion de la iteracion
        int ganancia_total = 0; //la ganancia de esta iteracion seria 0, porque comienza en A, lugar de partida

        while (true) {
            vector<int> RCL = construir_RCL(actual, nodos, visitado); // aqui se coloca solo los que cumplen
            if (RCL.empty()) break;

            int idxAle = rand() % RCL.size(); //escogemos uno random
            int siguiente = RCL[idxAle]; //la siguiente ciudad que visitara será la que s eescoja en el random

            ganancia_total += nodos[siguiente].ganancia; //se le suma la ganancia total
            camino.push_back(siguiente); // se agrega a la solucion
            visitado[siguiente] = true; //se marca como visitado
            actual = siguiente; //se vuelve ahora el actual
        }

        if (ganancia_total > mejor_ganancia) { //se actualza valores
            mejor_ganancia = ganancia_total;
            mejor_camino = camino;
        }
    }

    cout << "==============================" << endl;
    cout << " Mejor camino GRASP " << endl;
    cout << "==============================" << endl;
    cout << "Ruta: ";
    for (int i : mejor_camino) cout << nodos[i].Nombre << " ";
    cout << endl << "Ganancia total: " << mejor_ganancia << endl;
    cout << "==============================" << endl;
}

int main() {
    vector<Nodo> nodos = {
        {'A', 0, {1, 2, 3, 4, 7}}, // A -> B,C,D,E,H
        {'B', 20, {2, 3, 5, 7}}, // B -> C,D,F,H
        {'C', 30, {5}}, // C -> F
        {'D', 40, {}}, // D -> -
        {'E', 40, {2, 5, 6}}, // E -> C,F,G
        {'F', 40, {}}, // F -> -
        {'G', 10, {}}, // G -> -
        {'H', 50, {}} // H -> -
    };
    int n=nodos.size();
    grasp_nodos(nodos, n);
    return 0;
}
