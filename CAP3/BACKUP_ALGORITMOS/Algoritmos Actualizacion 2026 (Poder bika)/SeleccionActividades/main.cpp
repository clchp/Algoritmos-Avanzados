#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Actividad {
    char letra;
    int inicio;
    int final;
    bool estado=false;
};

int cmp(Actividad &a, Actividad &b) {
    return a.final < b.final;
}

void imprimir_tabla(vector<Actividad> actividades, int n) {
    for (int i = 0; i < actividades.size(); i++) {
        cout << actividades[i].letra<< " [" << actividades[i].inicio<< "-" << actividades[i].final << "] ";
        if (actividades[i].estado) {
            cout << "SELECCIONADO";
        } else {
            cout << "NO SELECCIONADO";
        }
        cout << endl;
    }
}

void ordenar_actividades(vector<Actividad>&actividades) {
    //ordenamos las actividades
    sort(actividades.begin(), actividades.end(), cmp);
    vector<char> soluciones;
    //tomamos el primero como tal, porque ya esta ordenado
    actividades[0].estado = true;
    soluciones.push_back(actividades[0].letra);
    int ultimoFin = actividades[0].final;
    // revisar restantes
    for (int i = 1; i < actividades.size(); i++) {
        // si no se solapa
        if (actividades[i].inicio >= ultimoFin) {
            actividades[i].estado = true;
            soluciones.push_back(actividades[i].letra);
            ultimoFin = actividades[i].final;
        }
    }
    // imprimir resultado
    cout << "Actividades seleccionadas: ";
    for (int i = 0; i < soluciones.size(); i++) {
        cout << soluciones[i] << " ";
    }
    cout << endl << endl;

    // imprimir tabla
    imprimir_tabla(actividades, actividades.size());
}

int main() {
    vector<Actividad> actividades={
        {'A', 1,4},
        {'B', 3,5},
        {'C',0,6},
        {'D',5,7},
        {'E',3,9},
        {'F',5,9},
        {'G',6,10},
        {'H',8,11}
    };
    ordenar_actividades(actividades);

    return 0;
}