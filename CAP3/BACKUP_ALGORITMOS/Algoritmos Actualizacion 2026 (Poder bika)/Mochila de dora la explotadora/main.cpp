#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct objetos {
    double peso;
    double beneficio;
    double ratio;
};

void obtener_ratios(vector<objetos> &objetos_mochila, int n) {
    for (int i = 0; i < n; i++) {
       objetos_mochila[i].ratio=objetos_mochila[i].beneficio / objetos_mochila[i].peso;
    }
    return;
}

void imprimir_mochila(vector<objetos> &objetos_mochila, int n) {
    for (int i = 0; i < n; i++) {
        cout<<"Objeto "<<i+1<<": peso -> "<<objetos_mochila[i].peso<<" | beneficio -> "<<objetos_mochila[i].beneficio<<" | ratio -> "<<objetos_mochila[i].ratio<<endl;
    }
    return;
}

int cmp(objetos &a, objetos &b) {
    return a.ratio > b.ratio;
}

int beneficio_total(vector<objetos> solucion, int n) {
    int beneficio_total=0;
    for (int i = 0; i < n; i++) {
        beneficio_total+=solucion[i].beneficio;
    }
    return beneficio_total;
}

void calcular_mejor_sol(vector<objetos>objetos_mochila, int n, int peso_mochila) {
    //ordenamos
    sort(objetos_mochila.begin(), objetos_mochila.end(), cmp);
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"ORDENADOS: "<<endl;
    imprimir_mochila(objetos_mochila, n);
    vector<objetos> solucion;
    for (int i = 0; i < n; i++) {
        if (peso_mochila==0) break;
        if (objetos_mochila[i].peso<=peso_mochila) {
            solucion.push_back(objetos_mochila[i]);
            peso_mochila-=objetos_mochila[i].peso;
        }
    }
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"SOLUCION ENCONTRADA MOCHILA 0/1"<<endl;
    imprimir_mochila(solucion, solucion.size());
    cout<<"Capacidad de la mochila restante: "<<peso_mochila<<endl;
    cout<<"Beneficio total de la solucion: "<<beneficio_total(solucion, solucion.size())<<endl;
}

int main() {
    vector<objetos> objetos_mochila = {
        {2,12,0},
        {1,10,0},
        {3,20,0},
        {2,15,0},
        {4,25,0}
    };
    int peso_mochila=7;
    cout<<"Capacidad de la mochila original: "<<peso_mochila<<endl;
    obtener_ratios(objetos_mochila, objetos_mochila.size());
    imprimir_mochila(objetos_mochila, objetos_mochila.size());
    calcular_mejor_sol(objetos_mochila, objetos_mochila.size(), peso_mochila);
    return 0;
}