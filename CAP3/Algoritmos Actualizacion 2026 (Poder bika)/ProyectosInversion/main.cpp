#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct proyecto {
    double costo;
    double retorno;
    double ratio;
};

void obtener_ratios(vector<proyecto> &proyectos, int n) {
    for (int i = 0; i < n; i++) {
        proyectos[i].ratio = proyectos[i].retorno / proyectos[i].costo;
    }
    return;
}

void imprimir_proyectos(vector<proyecto> &proyectos, int n) {
    for (int i = 0; i < n; i++) {
        cout<<"Proyecto "<<i+1
            <<": costo -> "<<proyectos[i].costo
            <<" | retorno -> "<<proyectos[i].retorno
            <<" | ratio -> "<<proyectos[i].ratio
            <<endl;
    }
    return;
}

int cmp(proyecto &a, proyecto &b) {
    return a.ratio > b.ratio;
}

int retorno_total(vector<proyecto> solucion, int n) {
    int retorno_total = 0;

    for (int i = 0; i < n; i++) {
        retorno_total += solucion[i].retorno;
    }

    return retorno_total;
}

void calcular_mejor_inversion(vector<proyecto> proyectos,
                              int n,
                              int presupuesto) {

    // ordenar proyectos por ratio
    sort(proyectos.begin(), proyectos.end(), cmp);

    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"PROYECTOS ORDENADOS:"<<endl;

    imprimir_proyectos(proyectos, n);

    vector<proyecto> solucion;

    for (int i = 0; i < n; i++) {

        if (presupuesto == 0) break;

        if (proyectos[i].costo <= presupuesto) {
            solucion.push_back(proyectos[i]);
            presupuesto -= proyectos[i].costo;
        }
    }

    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"SOLUCION ENCONTRADA"<<endl;

    imprimir_proyectos(solucion, solucion.size());

    cout<<"Presupuesto restante: "<<presupuesto<<endl;

    cout<<"Retorno total obtenido: "
        <<retorno_total(solucion, solucion.size())
        <<endl;
}

int main() {

    // { costo , retorno , ratio }
    vector<proyecto> proyectos = {
        {700, 950, 0},
        {450, 620, 0},
        {900, 1300, 0},
        {300, 500, 0},
        {650, 870, 0}
    };

    int presupuesto = 1800;

    cout<<"Presupuesto original: "<<presupuesto<<endl;

    obtener_ratios(proyectos, proyectos.size());

    imprimir_proyectos(proyectos, proyectos.size());

    calcular_mejor_inversion(proyectos,
                             proyectos.size(),
                             presupuesto);

    return 0;
}