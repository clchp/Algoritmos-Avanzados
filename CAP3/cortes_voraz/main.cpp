#include <iostream>
#include <algorithm>
#include <vector>

struct Cortes {
    int tipo;
    int cantidad;
};

using namespace std;

bool cmp(Cortes a, Cortes b) {
    return a.tipo > b.tipo;
}
int obtenerCantTablas(int longitud, vector<int> barras) {
    int cant=0;
    for (int i = 0; i < barras.size(); i++) {
        if (barras[i]==longitud)break; // si es igual a Longitud, quiere decir que no se ha usado, por lo cual hasta aqhi termina
        cant++; //se cuenta
    }
    return cant;
}
int obtenerDespercio(vector<int> barras, int cantidad_tablas) {
    int desperdicio=0;
    for (int i = 0; i < cantidad_tablas; i++) {
        desperdicio+=barras[i];
    }
    return desperdicio;
}
int obtenerRecortesTotales(vector<Cortes> cortes) {
    int suma=0;
    for (int i = 0; i < cortes.size(); i++) {
        suma+=cortes[i].cantidad;
    }
    return suma;
}


void cortes_voraz(vector<Cortes> cortes, int &desperdicio, int &cantidad_tablas, int longitud, int n, int numero_cortes) {
    vector<int> barras(numero_cortes, longitud);
    for (int i = 0; i < n; i++) {
        //para los n tipos diferentes de madera
        for (int j = 0; j < cortes[i].cantidad; j++) {
            //para las cantidades
            int k = 0;
            while (barras[k] < cortes[i].tipo) k = k + 1; //la siguiente, hasta que haya espacio
            barras[k] -= cortes[i].tipo;
        }
    }
    cantidad_tablas=obtenerCantTablas(longitud, barras);
    desperdicio=obtenerDespercio(barras, cantidad_tablas);
}


int main() {
    vector<Cortes> cortes = {{6, 7}, {5, 3}, {3, 4}, {2, 7}, {1, 3}};
    int desperdicio = 0, cantidad_tablas = 0;
    int longitud = 10;
    int numero_cortes=obtenerRecortesTotales(cortes);
    sort(cortes.begin(), cortes.end(), cmp); //ordenar por tipo
    cortes_voraz(cortes, desperdicio, cantidad_tablas, longitud, cortes.size(), numero_cortes);
    cout << "Se tiene un desperdicio de " << desperdicio << " y una cantidad de " << cantidad_tablas << " tablas" <<
            endl;
    return 0;
}
