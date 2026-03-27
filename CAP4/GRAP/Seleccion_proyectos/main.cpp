#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

#define alfa 0.3
#define ITERACIONES 10000

struct Proyecto {
    int id;
    double costo;
    double beneficio;
    double ratio; // beneficio / costo
};

void calcular_ratios(vector<Proyecto> &proyectos) {
    for (int i = 0; i < proyectos.size(); i++)
        proyectos[i].ratio = proyectos[i].beneficio / proyectos[i].costo;
}

double calcular_beneficio(vector<Proyecto> &sel) {
    double suma = 0;
    for (auto &p : sel) suma += p.beneficio;
    return suma;
}

vector<int> construir_RCL(vector<Proyecto> &proyectos, double presupuesto_restante) {
    vector<int> candidatos;
    for (int i = 0; i < proyectos.size(); i++) {
        if (proyectos[i].costo <= presupuesto_restante) //solo entran los cuales su costo es menor
            candidatos.push_back(i);
    }
    if (candidatos.empty()) return {};

    double beta = INT_MIN, tau = INT_MAX;
    for (int idx : candidatos) {
        if (proyectos[idx].ratio > beta) beta = proyectos[idx].ratio;
        if (proyectos[idx].ratio < tau) tau = proyectos[idx].ratio;
    }

    double limite = beta - alfa * (beta - tau);
    vector<int> RCL;
    for (int idx : candidatos)
        if (proyectos[idx].ratio >= limite)
            RCL.push_back(idx);

    return RCL;
}

void grasp_proyectos(vector<Proyecto> &proyectos, double presupuesto) {
    srand(time(NULL)); //random
    calcular_ratios(proyectos); //por caaa proyecto, este sera criterio

    vector<Proyecto> mejor_sol;
    double mejor_beneficio = INT_MIN;
    double mejor_gasto = 0;

    for (int it = 0; it < ITERACIONES; it++) {
        vector<Proyecto> copia = proyectos; // se genera una copia
        vector<Proyecto> solucion; //se guarda la mejor solucion parcial
        double presupuesto_restante = presupuesto; //como el "residuo"

        while (presupuesto_restante > 0 && !copia.empty()) { //mientras haya espacio y haya valores de la copia
            vector<int> RCL = construir_RCL(copia, presupuesto_restante); //construimos los indices
            if (RCL.empty()) break; //rompe no hay valores que cumplan condicion

            int idxAle = rand() % RCL.size(); //valor aletarorio
            int idx = RCL[idxAle]; //indice aleatorio

            //if (copia[idx].costo <= presupuesto_restante) { //si el costo es menor que el presupuesto que me queda entra
                solucion.push_back(copia[idx]); //agrega a la solucion
                presupuesto_restante -= copia[idx].costo; //se resta
            //}

            copia.erase(copia.begin() + idx); //se borr valor en todos los casos
        }

        double beneficio_total = calcular_beneficio(solucion); //se calcula el beneficio d ela solucion de la iteracion
        if (beneficio_total > mejor_beneficio) { //se ve si cumple lo del beneficio
            mejor_beneficio = beneficio_total; //se actualiza
            mejor_sol = solucion; //se guarda la solucion
            mejor_gasto = presupuesto - presupuesto_restante; //se calcula lo que gasto por los proyectos
        }
    }

    cout << "==============================" << endl;
    cout << " Mejor conjunto de proyectos (GRASP)" << endl;
    cout << "==============================" << endl;
    for (auto &p : mejor_sol)
        cout << "Proyecto " << p.id << "  Costo: " << p.costo << "  Beneficio: " << p.beneficio << endl;
    cout << "Beneficio total: " << mejor_beneficio << endl;
    cout << "Presupuesto usado: " << mejor_gasto << endl;
    cout << "==============================" << endl;
}

int main() {
    vector<Proyecto> proyectos = {
        {1, 10, 20},
        {2, 15, 25},
        {3, 30, 50},
        {4, 20, 40},
        {5, 25, 45}
    };
    double presupuesto = 60;
    grasp_proyectos(proyectos, presupuesto);
    return 0;
}