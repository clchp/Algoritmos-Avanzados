#include <iostream>
#include <vector>

using namespace std;

struct Tablas {
    int indice;
    int velocidad;
};

void mySwap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void mySwapTablas(Tablas &a, Tablas &b) {
    Tablas temp = a;
    a = b;
    b = temp;
}

void ordenarTablas(vector<Tablas> &v, int n) {
    // Ordenamiento burbuja
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (v[j].velocidad < v[j + 1].velocidad) {
                //descendente
                mySwapTablas(v[j], v[j + 1]);
            }
        }
    }
}

void ordenarNumeros(vector<int> &v, int n) {
    // Ordenamiento burbuja
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (v[j] < v[j + 1]) {
                //descendente
                mySwap(v[j], v[j + 1]);
            }
        }
    }
}

void imprimirSolucion(vector<vector<int>> solucion, int n) {
    for (int i = 0; i < n; i++) {
        cout<<"Para el disco "<<i+1<<" se tiene ";
        for (int sol:solucion[i]) {
            cout<<sol<<" - ";
        }
        cout<<endl;
    }
}
int hallarMasLibre(int velocidad, vector<int>discos,int cant_discos) {
    int idx, minValor=99999;
    for(int i=0;  i<cant_discos; i++) {
        if (minValor>velocidad-discos[i]) {
            minValor=velocidad-discos[i];
            idx=i;
        }
    }
    return idx;
}

void obetenerOptimizacion(vector<Tablas> tablas, vector<int> discos, int cant_tablas, int cant_discos) {
    vector<vector<int> > solucion(cant_discos); //aqui se guarda la solucion
    for (int i = 0; i < cant_tablas; i++) {
        //recorre la cantidad de tablas
        //hallar el que esta libre en ese momento
        int mas_libre=hallarMasLibre(tablas[i].velocidad, discos, cant_discos);
        //el que este mas libre, es el que lleno primero
        discos[mas_libre]-= tablas[i].velocidad;
        solucion[mas_libre].push_back(tablas[i].indice);
    }
    //solucion
    imprimirSolucion(solucion, cant_discos);
}

int main() {
    vector<Tablas> tablas = {{1, 150}, {2, 100}, {3, 180}, {4, 50}, {5, 120}, {6, 10}};
    int cant_tablas = tablas.size();
    vector<int> discos = {250, 200, 200, 100};
    int cant_discos = discos.size();
    //ordenar ambos
    ordenarTablas(tablas, cant_tablas);
    ordenarNumeros(discos, cant_discos);
    obetenerOptimizacion(tablas, discos, cant_tablas, cant_discos);

    return 0;
}
