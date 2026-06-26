#include <algorithm>
#include <vector>
#include <iostream>
#define MAX_ITERACCIONES 1000
#define ALPHA 0.3

using namespace std;

struct reunion {
    int nombre;
    int inicio;
    int final;
};

struct sala {
    vector<reunion> reuniones;
    int cantidad=0;
};

bool cmp(reunion &a, reunion &b) {
    return a.final<b.final; //ASC
}

void imprimir_solucion(sala &solucion) {
    sort(solucion.reuniones.begin(), solucion.reuniones.end(),cmp);
    cout<<"La solucion contiene lo siguientes datos:"<<endl;
    for (int i = 0; i < solucion.reuniones.size(); i++) {
        cout<<"Renion N"<<solucion.reuniones[i].nombre<<": Rango de tiempo: "<<solucion.reuniones[i].inicio<<"-"<<solucion.reuniones[i].final<<" Duracion: "<<
            solucion.reuniones[i].final-solucion.reuniones[i].inicio<<endl;
    }
    cout<<"La cantidad total de reuniones es de: "<<solucion.cantidad<<endl;
}

void construir_RCL(vector<reunion>&RCL, vector<reunion>&reuniones, double limite_superior) {
    for (int i = 0; i < reuniones.size(); i++) {
        if (limite_superior >= reuniones[i].final) {
            RCL.push_back(reuniones[i]);
        }
    }
    return;
}

int hallar_idx(reunion &aleatorio, vector<reunion> &reuniones) {
    for (int i = 0; i < reuniones.size(); i++) {
        if (aleatorio.nombre==reuniones[i].nombre) {
            return i;
        }
    }
    return -1;
}

//es valido si no se solapa con lo que ya se tiene (ESTE VALIDO VE TODOS, NO ASUME QUE SOLUCION EN ORDEN)
bool es_valido(sala &solucion_iteracion,reunion &aleatorio){
    for (auto &reu : solucion_iteracion.reuniones) {
        bool se_solapan =!(aleatorio.final <= reu.inicio || aleatorio.inicio >= reu.final);
        if (se_solapan) {
            return false;
        }
    }
    return true;
}


void hallar_solucion_iteraccion(sala &solucion_iteracion, vector<reunion>reuniones) {
    while (!reuniones.empty()) {
        //vamos a ordenar por finalizacion de reuniones MENOR A MAYOR (ASC)
        sort(reuniones.begin(), reuniones.end(), cmp);
        //mejor solucion es la que tiene un menor final
        double beta=reuniones[0].final;
        //peor solucion es la que tiene un mayor final
        double tau=reuniones[reuniones.size()-1].final;
        //se quiere MAXIMIZAR la cantidad de reuniones
        double limite_superior=beta+ALPHA*(tau-beta);
        vector<reunion> RCL;
        construir_RCL(RCL, reuniones, limite_superior);
        int idx_aleatorio=rand()%RCL.size();
        reunion aleatorio=RCL[idx_aleatorio];
        //vemos si es que es valido
        if (es_valido(solucion_iteracion, aleatorio)) {
            solucion_iteracion.cantidad++;
            solucion_iteracion.reuniones.push_back(aleatorio);
        }
        //eliminamos
        reuniones.erase(reuniones.begin()+hallar_idx(aleatorio, reuniones));
    }
}

void algoritmo_grasp(vector<reunion>&reuniones) {
    sala mejor_solucion;
    int i=0;
    while (i<MAX_ITERACCIONES) {
        sala solucion_iteracion;
        hallar_solucion_iteraccion(solucion_iteracion, reuniones);
        if (solucion_iteracion.cantidad>mejor_solucion.cantidad) {
            mejor_solucion=solucion_iteracion;
        }
        i++;
    }
    imprimir_solucion(mejor_solucion);
}

int main() {
    srand(time(NULL));
    vector<reunion> reuniones={
        {1,1,4},
        {2,3,5},
        {3,0,6},
        {4,5,7},
        {5,8,9},
        {6,5,9},
        {7,6,10},
        {8,8,11},
        {9,2,13},
        {10,12,14}
    };
    algoritmo_grasp(reuniones);
    return 0;
}