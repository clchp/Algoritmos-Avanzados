#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Tarea {
    char nombre;
    double tiempo;
    double peso;
    double ratio=0;
    double completion_time=0;
    double costo_ponderado=0;
};

void imprimir(vector<Tarea> tareas) {
    for (int i = 0; i < tareas.size(); i++) {
        cout<<"Tarea: "<<tareas[i].nombre<<endl;
        cout<<"Tiempo de procesamiento: "<<tareas[i].tiempo<<endl;
        cout<<"Peso: "<<tareas[i].peso<<endl;
        cout<<"Ratio w/p: "<<tareas[i].ratio<<endl;
        cout<<"Completion time: "<<tareas[i].completion_time<<endl;
        cout<<"Costo ponderado: "<<tareas[i].costo_ponderado<<endl;
        cout<<"-----------------------------------------------------"<<endl;
    }
}

void obtener_ratio(vector<Tarea>&tareas) {
    for (int i = 0; i < tareas.size(); i++) {
        tareas[i].ratio = tareas[i].peso / tareas[i].tiempo;
    }
    return;
}

bool cmp(Tarea t1, Tarea t2) {
    if (t1.ratio == t2.ratio) {
        return t1.tiempo<t2.tiempo;
    }else {
        return t1.ratio > t2.ratio;
    }
}

void ordenamiento_segun_regla_de_smith(vector<Tarea>&tareas) {
    //obtener el ratio
    obtener_ratio(tareas);
    //ordenamos
    sort(tareas.begin(), tareas.end(), cmp);
    //completamos en base a lo demas
    int tiempo_acumulado=0;
    double costo_total=0;
    for (int i = 0; i < tareas.size(); i++) {
        tareas[i].completion_time +=tiempo_acumulado+tareas[i].tiempo;
        tiempo_acumulado=tareas[i].completion_time;
        tareas[i].costo_ponderado=tareas[i].peso*tareas[i].completion_time;
        costo_total+=tareas[i].costo_ponderado;
    }
    imprimir(tareas);
    cout<<"COSTO PONDERADO TOTAL: "<<costo_total<<endl;
}

int main() {
    vector<Tarea> tareas={
        {'A', 4,20},
        {'B', 2,10},
        {'C',5,15},
        {'D', 3,18}
    };

    ordenamiento_segun_regla_de_smith(tareas);
    return 0;
}
