#include <iostream>
#include <vector>
using namespace std;

int num_combinaciones=0;
vector <int> sub_conjunto{};

void imprimir_bloque(vector<int> arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

void solucion_cmbinaciones(int n, int conjunto[], int index) {
    if (index == n) { // quiere decir que ya llego al final
        imprimir_bloque(sub_conjunto);
        num_combinaciones++;
        return; // ya termino el programa
    }
    //Lo tomo
    sub_conjunto.push_back(conjunto[index]);
    solucion_cmbinaciones(n, conjunto, index + 1);

    //No lo tomo
    sub_conjunto.pop_back();
    solucion_cmbinaciones(n, conjunto, index + 1);
}

int main() {
    int tamano=3;
    int conjunto[]={1,2,3};
    cout<<"Los numeros del arreglo son: {";
    for (int i=0;i<tamano;i++) {
        cout<<conjunto[i];
        if (tamano-1-i>0) cout<<",";
    }
    cout<<"}"<<endl;
    cout<<"Las posibles combinaciones son: "<<endl;
    solucion_cmbinaciones(tamano, conjunto, 0);
    cout<<"La cantidad de subconjuntos es: "<<num_combinaciones<<endl;
    return 0;

}