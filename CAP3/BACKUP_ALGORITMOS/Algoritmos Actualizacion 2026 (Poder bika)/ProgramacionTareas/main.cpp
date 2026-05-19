#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct telares {
    int tiempo_1_metro;
    int tiempo_actual;
    vector<int> telas_trabajadas={};
};

void imprimir(vector<int> telas, int n) {
    for (int i = 0; i < n; i++) {
        cout << telas[i] << " ";
    }
    cout << endl;
}

int cmp(telares &t1, telares &t2) {
    return t1.tiempo_1_metro < t2.tiempo_1_metro;
}

int buscar_mejor_maquina(vector<telares> maquinas, int tela) {
    int min = 999999;
    int idx = 0;

    for (int i = 0; i < maquinas.size(); i++) {
        int tiempo_final =maquinas[i].tiempo_actual +(tela * maquinas[i].tiempo_1_metro); //con esto sacamos cuanto se demoraria considerando que se toma esa maquina
        if (tiempo_final < min) {
            min = tiempo_final;
            idx = i;
        }
    }
    return idx;
}

void imprimir_solucion(vector<telares>maquinas, int n) {
    for (int i = 0; i < n; i++) {
        cout<<"Maquina "<<i+1<<": ";
        for (int j = 0; j < maquinas[i].telas_trabajadas.size(); j++) {
            cout<<maquinas[i].telas_trabajadas[j]<<" ";
        }
        cout<<"| Tiempo 1 metro: "<<maquinas[i].tiempo_1_metro<<" | Tiempo actual trabajado: "<<maquinas[i].tiempo_actual<<endl;
    }
    cout << endl;
}

void calcular_makespan(vector<int>telas, vector<telares> &maquinas) {
    //ordenar telares y ordenar maquinas
    sort(telas.begin(), telas.end(), greater<int>());
    sort(maquinas.begin(), maquinas.end(), cmp); //ya no es necesario, buscar_mejor_maquina lo busca
    //imprimir_solucion(maquinas, maquinas.size());
    //imprimir(telas, telas.size());
    for (int i = 0; i < telas.size(); i++) {
        int idx=buscar_mejor_maquina(maquinas, telas[i]);
        maquinas[idx].tiempo_actual+= telas[i]*maquinas[idx].tiempo_1_metro;
        maquinas[idx].telas_trabajadas.push_back(telas[i]);
    }
    //calculamos el makespan
    int makespan=0;
    for (int i = 0; i < maquinas.size(); i++) {
        if (makespan<maquinas[i].tiempo_actual) {
            makespan=maquinas[i].tiempo_actual; //nos quedamos con el mayor
        }
    }
    cout<<"El makespan es de: "<<makespan<<endl;
    imprimir_solucion(maquinas, maquinas.size());
    return;
}

int main() {
    vector<int> telas={10, 7, 9, 12, 6, 8}; // Telas a tejer
    vector<telares> maquinas={
        {5,0},
        {4,0},
        {6,0}
    };
    calcular_makespan(telas, maquinas);

    return 0;
}