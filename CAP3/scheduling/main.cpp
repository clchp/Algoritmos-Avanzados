#include <iostream>
#include <algorithm>
#include <vector>

using namespace  std;

struct Maquina {
    int tiempo;
    int indice;
};

bool cmp(Maquina a, Maquina b) {
    return a.tiempo > b.tiempo; //DESC
}

int hallar_maquina_libre(int numero_maquinas, int tarea, vector<int>tiemposMaquina) {
    int minMaquina=9999;
    int indice;
    for (int j = 0; j < numero_maquinas; j++) { //hallar cual e s la que esta libre
        if (minMaquina>tiemposMaquina[j]+tarea) {
            minMaquina = tiemposMaquina[j]+tarea;
            indice=j;
        }
    }
    return indice;
}
void imprimirResultados(int numero_maquinas, vector<vector<Maquina>>maquinas, vector<int>tiemposMaquina) {
    cout << "Asignacion de tareas:" << endl;
    for (int i = 0; i < numero_maquinas; i++) {
        cout << "Maquina " << i+1 << " -> Tareas: ";
        for (Maquina t : maquinas[i]) cout << t.indice << " ";
        cout << "| Tiempo total: " << tiemposMaquina[i] << endl;
    }
}

void scheduling(vector<vector<Maquina>>&maquinas, int numero_maquinas, vector<Maquina>tareas, int numero_tareas,
    vector<int>&tiemposMaquina) {
    for (int i = 0; i < numero_tareas; i++) { //recorrer hasta que todas las tareas esten asignadas en alguna maquina
        int idx_maquina_libre=hallar_maquina_libre(numero_maquinas, tareas[i].tiempo, tiemposMaquina);
        tiemposMaquina[idx_maquina_libre]+=tareas[i].tiempo; //actualizo el tiempo
        Maquina maquinita{tareas[i].tiempo, tareas[i].indice};
        maquinas[idx_maquina_libre].push_back(maquinita);
    }
    imprimirResultados(numero_maquinas, maquinas, tiemposMaquina);
}

int main() {
    int numero_maquinas=3;
    vector<vector<Maquina>> maquinas(numero_maquinas); //guardo la data de las tareas que hara
    vector<Maquina> tareas={{14,1},{9,2},{10,3},{6,4},{11,5},{15,6},{13,7},{8,8}};
    int numero_tareas=tareas.size();
    vector<int>tiemposMaquina (numero_maquinas,0);
    sort(tareas.begin(),tareas.end(),cmp); //los ordena de forma DESC
    scheduling(maquinas, numero_maquinas, tareas, numero_tareas, tiemposMaquina);

    return 0;
}