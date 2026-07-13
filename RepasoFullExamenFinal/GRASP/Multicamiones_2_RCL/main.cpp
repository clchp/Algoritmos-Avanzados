#include <algorithm>
#include <vector>
#include <iostream>
#define MAX_ITERACIONES 1000
#define alpha 0.3

using namespace std;

struct Paquete {
    char nombre;
    double peso;
};

struct Camion {
    int nombre;
    double capacidad;
    double capacidadActual;
    vector<Paquete> paquetes = {};
};

bool cmpPaquetes(Paquete &p1, Paquete &p2) {
    return p1.peso>p2.peso;
}

bool cmpCamiones(Camion &c1, Camion &c2) {
    return c1.capacidadActual>c2.capacidadActual;
}

void crearRCLCamiones(double limite_inferior, vector<Camion>&RCLCamiones,vector<Camion> &camiones) {
    for (int i = 0; i < camiones.size(); i++) {
        if (camiones[i].capacidadActual>=limite_inferior) {
            RCLCamiones.push_back(camiones[i]);
        }
    }
    return;
}

void crearRCLPaquetes(double limite_inferior, vector<Paquete> &RCLPaquetes,vector<Paquete> &paquetes) {
    for (int i = 0; i < paquetes.size(); i++) {
        if (paquetes[i].peso>=limite_inferior) {
            RCLPaquetes.push_back(paquetes[i]);
        }
    }
    return;
}

int hallarIdxC(vector<Camion> &camiones, int nombre) {
    for (int i=0; i<camiones.size(); i++) {
        if (camiones[i].nombre==nombre) {
            return i;
        }
    }
    return -1;
}
int hallarIdxP(vector<Paquete> &paquetes, char nombre) {
    for (int i=0; i<paquetes.size(); i++) {
        if (paquetes[i].nombre==nombre) {
            return i;
        }
    }
    return -1;
}

void hallarSolucionIteracion(vector<Camion> &camiones, vector<Paquete> paquetes) {
    while (!paquetes.empty()) {
        //ordenamos DESC los paquetes
        sort(paquetes.begin(), paquetes.end(), cmpPaquetes);
        double betaP=paquetes.front().peso;
        double tauP=paquetes.back().peso;
        double limite_inferiorP=betaP-alpha*(betaP-tauP);
        vector<Paquete> RCLPaquetes;
        crearRCLPaquetes(limite_inferiorP, RCLPaquetes, paquetes);
        int idx_aleatorioP=rand()%RCLPaquetes.size();
        Paquete aleatorioP=RCLPaquetes[idx_aleatorioP];

        //ahora construimos para camiones
        //ordenamos por el que que tenga mayor espacio libre en ese momento DESC
        sort(camiones.begin(), camiones.end(), cmpCamiones);
        double betaC=camiones.front().capacidadActual;
        double tauC=camiones.back().capacidadActual;
        double limite_inferiorC=betaC-alpha*(betaC-tauC);
        vector<Camion> RCLCamiones;
        crearRCLCamiones(limite_inferiorC, RCLCamiones, camiones);
        int idx_aleatorioC=rand()%RCLCamiones.size();
        Camion aleatorioC=RCLCamiones[idx_aleatorioC];

        //ahora vamos a ver si entra
        if (aleatorioC.capacidadActual>=aleatorioP.peso) { //entra ahi
            int idxCamionUsado=hallarIdxC(camiones, aleatorioC.nombre);
            camiones[idxCamionUsado].paquetes.push_back(aleatorioP);
            camiones[idxCamionUsado].capacidadActual-=aleatorioP.peso;
        }
        paquetes.erase(paquetes.begin()+hallarIdxP(paquetes, aleatorioP.nombre));
    }
    return;
}

void imprimirMejorSolucion(vector<Camion> &bestSolucion, double desperdicioTotal) {
    for (int i = 0; i < bestSolucion.size(); i++) {
        cout<<"C"<<bestSolucion[i].nombre<<" - ("<<bestSolucion[i].capacidadActual<<"/"<<bestSolucion[i].capacidad<<") :";
        for (int j = 0; j < bestSolucion[i].paquetes.size(); j++) {
            cout<<bestSolucion[i].paquetes[j].nombre<<" ["<<bestSolucion[i].paquetes[j].peso<<"]";
            if (j+1!=bestSolucion[i].paquetes.size()) {
                cout<<", ";
            }
        }
        cout<<endl;
    }
    cout<<"Desperdicio total: "<<desperdicioTotal<<endl;
}

void grasp(vector<Camion> camiones, vector<Paquete> paquetes) {
    int i=0;
    vector<Camion> bestSolucion;
    double minEspacioLibre = 99999; //minimizar el desperdicio
    int maxCantidadPaquetesTransportados=0;
    vector<Camion> camionesOriginal=camiones;
    while(i<MAX_ITERACIONES) {
        camiones=camionesOriginal;
        hallarSolucionIteracion(camiones, paquetes);
        double espacioLibre=0, cantPaquetesTransportados=0;
        for (int j=0; j<camiones.size(); j++) {
            espacioLibre+=camiones[j].capacidadActual;
            cantPaquetesTransportados += camiones[j].paquetes.size();
        }
        if (maxCantidadPaquetesTransportados==cantPaquetesTransportados) {
            if (minEspacioLibre>espacioLibre) {
                minEspacioLibre=espacioLibre;
                maxCantidadPaquetesTransportados=cantPaquetesTransportados;
                bestSolucion = camiones;
            }
        }
        else if (maxCantidadPaquetesTransportados<cantPaquetesTransportados) {
            maxCantidadPaquetesTransportados=cantPaquetesTransportados;
            minEspacioLibre = espacioLibre;
            bestSolucion = camiones;
        }
        i++;
    }
    imprimirMejorSolucion(bestSolucion, minEspacioLibre);
}

int main() {
    srand(time(NULL));
    //EN ESTE CASO DE PRUEBA, NO ENTRAN TODOS PESOTOTAL>CAPACIDADTOTAL
    // vector<Paquete> paquetes = {
    //     {'A',30},
    //     {'B',25},
    //     {'C',20},
    //     {'D',35},
    //     {'E',15},
    //     {'F',10},
    //     {'G',40},
    //     {'H',18}
    // };
    // vector<Camion> camiones = {
    //     {1,60,60},
    //     {2,70,70},
    //     {3,50,50}
    // };
    vector<Paquete> paquetes = {
        {'A',30},
        {'B',25},
        {'C',20},
        {'D',15},
        {'E',5},
        {'F',5}
    };
    vector<Camion> camiones = {
        {1,50,50},
        {2,50,50},
    };

    //Esto por si piden que DEBEN estar de por si todos los pedidos deben ser transportados.
    // double pesoTotal=0, capacidadTotal=0;
    // for (int i=0; i<paquetes.size(); i++) {
    //     pesoTotal+=paquetes[i].peso;
    // }
    // for (int i=0; i<camiones.size(); i++) {
    //     capacidadTotal+=camiones[i].capacidad;
    // }
    // if (pesoTotal>capacidadTotal) {
    //     cout<<"No es posible transportar todos los paquetes porque la capacidad total de los camiones es insuficiente."<<endl;
    // }
    // else {
    //     grasp(camiones, paquetes);
    // }

    //SINO SIEMPRE SE HACE GRASP
    grasp(camiones, paquetes);
    return 0;
}
