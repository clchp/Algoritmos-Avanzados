#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_CAR 50
using namespace std;

void imprimir(vector<int> arr, int n){
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

}

int cmp(int a, int b) {
    return a > b;
}

void imprimir_linea(const char*caracter) {
    for (int i=0; i<MAX_CAR; i++) {
        cout<<caracter;
    }
    cout<<endl;
}

void encontrar_solucion(vector<int> denom, int cambio) {
    vector<int> solucion;
    //primero ordenmamos de forma descendente
    sort(denom.begin(), denom.end(), cmp);
    //reverse(denom.begin(), denom.end());
    //imprimimos paraver si esta
    cout<<"Ordenado: ";
    imprimir(denom, denom.size());
    cout<<endl;
    imprimir_linea("=");
    int i=0;
    while (cambio>0 and i<denom.size()) {
        if (denom[i]<=cambio) {
            cambio -= denom[i]; //le quitamos
            solucion.push_back(denom[i]);
        }
        else {
            i++;
        }
    }
    cout<<"El cambio que quedo fue de: "<<cambio<<endl;
    cout<<"Solucion encontrada: ";
    imprimir(solucion, solucion.size());
    return;
}

int main() {
    vector<int> denom = {1, 5, 10, 25, 50};
    int cambio=27;
    cout<<"Cambio principal: "<<cambio<<endl;
    //CASO MONEDAS INFINITAS
    encontrar_solucion(denom, cambio);

    return 0;
}