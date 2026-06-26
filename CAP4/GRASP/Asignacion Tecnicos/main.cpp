#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define ALPHA 0.3
#define MAX_ITERACIONES 1000

struct Incidencia {
    int nombre;
    int tiempo;
};

struct Tecnico {
    int nombre;
    vector<Incidencia> incidencias_x_tecnico = {};
};

struct Candidato {
    int tecnico;
    int incidencia;
    int tiempo;
};

struct solucion_productividad {
    vector<int> tec;
    vector<Incidencia> inc;
    double menor_tiempo = 99999;
};

void imprimir_solucion(solucion_productividad sol) {
    cout << "SOLUCION" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "Tecnico: " << sol.tec[i]
             << " Atiende incidencia(n" << sol.inc[i].nombre
             << ") en " << sol.inc[i].tiempo
             << " minutos" << endl;
    }

    cout << "Tiempo total: " << sol.menor_tiempo << endl;
    return;
}

bool cmp(Incidencia &a, Incidencia &b) {
    return a.tiempo < b.tiempo; // ASC: minimizar
}


int mejor_solucion(vector<Tecnico> &productividad) {
    int tiempo_menor = 9999;

    for (int i = 0; i < productividad.size(); i++) {
        for (int j = 0;j < productividad[i].incidencias_x_tecnico.size();j++) {
            if (tiempo_menor >productividad[i].incidencias_x_tecnico[j].tiempo) {
                tiempo_menor =productividad[i].incidencias_x_tecnico[j].tiempo;
            }
        }
    }
    return tiempo_menor;
}

int peor_solucion(vector<Tecnico> productividad) {
    int tiempo_mayor = 0;

    for (int i = 0; i < productividad.size(); i++) {
        for (int j = 0;j < productividad[i].incidencias_x_tecnico.size();j++) {
            if (tiempo_mayor <productividad[i].incidencias_x_tecnico[j].tiempo) {
                tiempo_mayor =productividad[i].incidencias_x_tecnico[j].tiempo;
            }
        }
    }
    return tiempo_mayor;
}

void construir_rcl(vector<Candidato> &RCL,vector<Tecnico> &productividad,double limite_superior) {
    for (int i = 0; i < productividad.size(); i++) {
        for (int j = 0;j < productividad[i].incidencias_x_tecnico.size();j++) {
            if (limite_superior>=productividad[i].incidencias_x_tecnico[j].tiempo) {
                RCL.push_back({productividad[i].nombre,
                    productividad[i].incidencias_x_tecnico[j].nombre,
                    productividad[i].incidencias_x_tecnico[j].tiempo});
            }
        }
    }
    return;
}

void eliminar_candidato(int incidencia, int tecnico, vector<Tecnico> &productividad) {
    //Eliminar tecnico
    for (int i=0; i<productividad.size(); i++) {
        if (productividad[i].nombre==tecnico) {
            productividad.erase(productividad.begin()+i);
            break;
        }
    }
    //Eliminar incidencia de cada uno de los tecnicos
    for (int i=0; i<productividad.size(); i++) {
        for (int j=0;j<productividad[i].incidencias_x_tecnico.size();j++) {
            if (productividad[i].incidencias_x_tecnico[j].nombre==incidencia) {
                productividad[i].incidencias_x_tecnico.erase(productividad[i].incidencias_x_tecnico.begin()+j);
                break;
            }
        }
    }
    return;
}

void hallar_solucion_iterativa(solucion_productividad &solucion_iteracion,vector<Tecnico> productividad) {
    int tiempo_total=0;
    while (!productividad.empty()) {
        // En este caso NO sirve, cueck, perdi tiempo 🥲
        // ordenar_filas_tecnicos(productividad);
        int beta = mejor_solucion(productividad);
        int tau = peor_solucion(productividad);
        double limite_superior = beta + ALPHA * (tau - beta);
        vector<Candidato> RCL;
        construir_rcl(RCL,productividad,limite_superior);
        int idx_aleatorio=rand()%RCL.size();
        Candidato aleatorio=RCL[idx_aleatorio];
        // No es necesario porque se saca de una lista donde todos son candidatos validos
        //if (candidado_valido(aleatorio.incidencia, aleatorio.tecnico, productividad)) {
            tiempo_total+=aleatorio.tiempo;
            solucion_iteracion.inc.push_back({aleatorio.incidencia, aleatorio.tiempo});
            solucion_iteracion.tec.push_back(aleatorio.tecnico);
            solucion_iteracion.menor_tiempo=tiempo_total;
        //}
        //eliminamos
        eliminar_candidato(aleatorio.incidencia, aleatorio.tecnico, productividad);
    }
}

void algoritmo_grasp(vector<Tecnico> &productividad) {
    int i = 0;
    solucion_productividad mejor_solucion_productividad;
    while (i < MAX_ITERACIONES) {
        solucion_productividad solucion_iteracion;
        hallar_solucion_iterativa(solucion_iteracion,productividad);
        // se analiza si es la mejor solucion
        if (mejor_solucion_productividad.menor_tiempo >solucion_iteracion.menor_tiempo) {
            mejor_solucion_productividad =solucion_iteracion;
        }
        i++;
    }
    imprimir_solucion(mejor_solucion_productividad);
}

int main() {
    srand(time(NULL));
    vector<Tecnico> productividad = {
        {1, {{1,12},{2,8},{3,15},{4,10},{5,9}}},
        {2, {{1,7},{2,14},{3,11},{4,13},{5,12}}},
        {3, {{1,10},{2,9},{3,16},{4,8},{5,14}}},
        {4, {{1,15},{2,11},{3,7},{4,12},{5,10}}},
        {5, {{1,9},{2,13},{3,10},{4,14},{5,11}}}
    };
    algoritmo_grasp(productividad);
    return 0;
}