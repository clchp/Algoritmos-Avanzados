#include <iostream>
#include <vector>

using namespace std;

int num_permutaciones=0;
vector<int>solucion={};
bool usado[3] = {false, false, false}; // con este vamos a saber si ya usamos el número o no

void imprimir_bloque(int n, vector<int> arr) {
    cout<<"[";
    for (int i = 0; i < n; i++) {
        cout<<arr[i];
        if (i != n - 1) {cout<<",";}
    }
    cout<<"]"<<endl;
}
void solucion_permutaciones(int n, vector<int> arr) {
    if (solucion.size() == n) { // si tiene el tamaño entocnes quiere decir que esta lleno
        imprimir_bloque(n, solucion);
        num_permutaciones++;
        return;
    }
    //sino tomamos la solucion, pero en este caso debe estra compelto y no usado
    for (int i = 0; i < n; i++) {
        if (!usado[i]) {
            solucion.push_back(arr[i]); //añadimos la solucion
            usado[i] = true; // y cambiamos su valor
            solucion_permutaciones(n, arr);

            solucion.pop_back();
            usado[i] = false;
        }
    }
}

int main() {
    int tamano=3;
    vector<int> conjunto={1,2,3};

    cout<<"Bloque inicial: "<<endl;
    imprimir_bloque(tamano, conjunto);
    cout<<"Las permutaciones son las siguientes: "<<endl;
    solucion_permutaciones(tamano, conjunto);
    cout<<"La cantidad de permutaciones para el conjunto es de "<<num_permutaciones<<endl;

    return 0;
}