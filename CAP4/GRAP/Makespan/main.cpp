#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

#define alfa 0.3
#define ITERACIONES 5000

int calcular_makespan(const vector<int>& carga) {
    int max_load = 0;
    for (int c : carga)
        if (c > max_load) max_load = c;
    return max_load;
}

void grasp_tareas_general(vector<vector<int>>& tiempos) {
    srand(time(NULL));
    int maquinas = tiempos.size();
    int tareas = tiempos[0].size();

    int mejor_makespan = INT_MAX;
    vector<int> mejor_asignacion(tareas, -1);
    vector<int> mejor_carga(maquinas, 0);

    for (int it = 0; it < ITERACIONES; it++) {
        vector<int> carga(maquinas, 0);
        vector<int> asignacion(tareas, -1);

        for (int j = 0; j < tareas; j++) {
            // Calcular incremento si se asigna la tarea j a cada máquina
            vector<int> incremento(maquinas);
            for (int i = 0; i < maquinas; i++)
                incremento[i] = carga[i] + tiempos[i][j];

            int beta = INT_MAX, tau = INT_MIN;
            for (int i = 0; i < maquinas; i++) {
                if (incremento[i] < beta) beta = incremento[i];
                if (incremento[i] > tau) tau = incremento[i];
            }

            double limite = beta + alfa * (tau - beta);
            vector<int> RCL;
            for (int i = 0; i < maquinas; i++)
                if (incremento[i] <= limite)
                    RCL.push_back(i);

            int idx = RCL[rand() % RCL.size()];
            asignacion[j] = idx;
            carga[idx] += tiempos[idx][j];
        }

        int makespan = calcular_makespan(carga);
        if (makespan < mejor_makespan) {
            mejor_makespan = makespan;
            mejor_asignacion = asignacion;
            mejor_carga = carga;
        }
    }

    cout << "==============================" << endl;
    cout << " Mejor asignacion (GRASP generalizado)" << endl;
    cout << "==============================" << endl;

    // Imprimir cada tarea con su tiempo y máquina asignada
    for (int j = 0; j < tiempos[0].size(); j++) {
        int maquina = mejor_asignacion[j];
        cout << "Tarea " << j + 1
             << " -> Maquina " << maquina + 1
             << "  (tiempo: " << tiempos[maquina][j] << ")\n";
    }

    cout << "\n--- Carga final por máquina ---\n";
    for (int i = 0; i < tiempos.size(); i++) {
        cout << "Maquina " << i + 1 << ": " << mejor_carga[i] << " unidades de tiempo\n";
    }

    cout << "\nMakespan total: " << mejor_makespan << endl;
    cout << "==============================" << endl;
}

int main() {
    // Matriz de tiempos [máquina][tarea]
    vector<vector<int>> tiempos = {
        {5, 7, 6, 8},   // Máquina 1
        {8, 4, 9, 5},   // Máquina 2
        {6, 5, 7, 6}    // Máquina 3
    };

    grasp_tareas_general(tiempos);
    return 0;
}