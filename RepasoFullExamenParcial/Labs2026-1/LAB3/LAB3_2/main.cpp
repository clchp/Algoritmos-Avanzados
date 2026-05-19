#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct NodoVecinos {
    int nombreVecino;
    int distancias;
};

struct NodoCiudad {
    int num;
    vector<NodoVecinos> vecinitos;
    bool es_gasolinera=false;
};

int buscarIdx(vector<NodoCiudad>& mapita, int numeroBuscar) {
    for (int i = 0; i < mapita.size(); ++i) {
        if (mapita[i].num == numeroBuscar) {
            return i;
        }
    }
    return -1; //naca la pirinica
}

bool cmp(NodoVecinos v1, NodoVecinos v2) {
    return v1.distancias>v2.distancias; //de forma descendente quiero el que tenga mayor distancia primero
}

bool ya_lo_he_visitado(int numeroVecino, vector<int> caminito) {
    for (int i = 0; i < caminito.size(); ++i) {
        if (numeroVecino == caminito[i]) {
            return true;
        }
    }
    return false;
}

void buscar_info_destino(int nombreCiudadActual, vector<NodoCiudad> mapa, int nombreCiudadDestino,int &distancia) {
    vector<NodoVecinos> v=mapa[buscarIdx(mapa, nombreCiudadActual)].vecinitos;
    for (int i = 0; i < v.size(); ++i) {
        if (nombreCiudadDestino==v[i].nombreVecino) {
            distancia= v[i].distancias;
        }
    }

    return;
}

void imprimir_resultados(vector<int>caminito, int capacidad_actual, int destino, int origen, vector<NodoCiudad> mapa, int capMax) {
    cout<<"--------------------------"<<endl;
    cout<<"Camino de "<<origen<<" a "<<destino<<endl;
    int distancia=-1;
    for (int i = 0; i < caminito.size(); ++i) {
        cout<<"Tramo N"<<i+1<<": Ciudad --> "<<caminito[i];
        if (i+1!=caminito.size()) {
            buscar_info_destino(caminito[i], mapa, caminito[i+1], distancia);
            cout<<"("<<distancia<<")";
        }else {
            cout<<"(-)";
        }
        if (mapa[buscarIdx(mapa, caminito[i])].es_gasolinera) {
            cout<<" (Recarga de: "<<capMax<<")"<<endl;
        }
        else {
            cout<<endl;
        }
    }
    cout<<"--------------------------"<<endl<<"Termino la carrera con: "<<capacidad_actual<<endl;
}

bool esta_destino(vector<NodoVecinos>mis_vecinitos, int numero_destino, int &idxDestino) {
    for (int i = 0; i < mis_vecinitos.size(); ++i) {
        if (mis_vecinitos[i].nombreVecino==numero_destino) {
            idxDestino = i;
            return true;
        }
    }
    return false;
}

bool existe_otras_rutas(vector<NodoVecinos>mis_vecinitos, int capacidad_actual, vector<NodoCiudad> mapa) {
    for (int i = 0; i < mis_vecinitos.size(); ++i) {
        if (mis_vecinitos[i].distancias<=capacidad_actual and mapa[buscarIdx(mapa,mis_vecinitos[i].nombreVecino)].es_gasolinera) {
            return true; //tdv se puede
        }
    }
    return false;
}

void resolver(vector<NodoCiudad> mapa, int numero_Origen, int numero_destino, int capacidadMaxima) {
    vector<int> caminito{};
    int capacidad_actual=capacidadMaxima;
    //hacemos que sea escalable :ppppp
    int idx=buscarIdx(mapa, numero_Origen);
    caminito.push_back(mapa[idx].num); //aqui marcamos que estamos en ese
    while (true) {
        bool se_movio=false;
        vector<NodoVecinos> mis_vecinitos=mapa[idx].vecinitos;
        //ordenar a los vecinitos por el mas lejos
        sort(mis_vecinitos.begin(), mis_vecinitos.end(), cmp);
        //siempre priorizar ir hacia el destino
        int idxDestino=-1;
        if (esta_destino(mis_vecinitos, numero_destino, idxDestino)) {
            if (capacidad_actual >= mis_vecinitos[idxDestino].distancias) {
                capacidad_actual-=mis_vecinitos[idxDestino].distancias;
                caminito.push_back(mis_vecinitos[idxDestino].nombreVecino);
                imprimir_resultados(caminito, capacidad_actual, numero_destino, numero_Origen,mapa, capacidadMaxima); //ya termino
                return;
            }
            //solo terminamos si es que ya no puedo ir a otro lado
            if (!existe_otras_rutas(mis_vecinitos, capacidad_actual, mapa)) {
                //imprimimos hasta donde se acabo
                cout << "NO HAY SOLUCION"<<endl;
                imprimir_resultados(caminito, capacidad_actual, numero_destino, numero_Origen,mapa, capacidadMaxima); //a ver que imprime
                return;
            }

        }
        for (int i=0;i<mis_vecinitos.size();i++) {
            if (!ya_lo_he_visitado(mis_vecinitos[i].nombreVecino, caminito) and capacidad_actual>=mis_vecinitos[i].distancias) {
                bool es_gasolineria=mapa[buscarIdx(mapa, mis_vecinitos[i].nombreVecino)].es_gasolinera;
                capacidad_actual-=mis_vecinitos[i].distancias;
                if (es_gasolineria) {
                    capacidad_actual=capacidadMaxima;
                }
                caminito.push_back(mis_vecinitos[i].nombreVecino);
                se_movio=true;
                idx=buscarIdx(mapa, mis_vecinitos[i].nombreVecino); //movemos ahora a buscar donde terminamos
                break; //ya no sigue buscando
            }
        }
        if (!se_movio) {
            cout << "NO HAY SOLUCION";
            imprimir_resultados(caminito, capacidad_actual, numero_destino, numero_Origen,mapa,capacidadMaxima); //a ver que imprime
            return;
        }
    }
}

//DISCLAIMER: Estaba aburrida y creo que hice más de lo que el lab pedia :p pero es bueno pensar más alla de lo que te piden, a veces...


int main() {
    vector<NodoCiudad> mapa = {

        {0, {{1,4},{2,8},{3,5}}, true},
        {1, {{0,4},{2,3},{4,6}}, false},
        {2, {{0,8},{1,3},{3,4},{4,7}}, true},
        {3, {{0,5},{2,4},{4,3},{5,4}}, false},
        {4, {{1,6},{2,7},{3,3},{5,9}}, false},

        {5, {{3,4},{4,9}}, false}
    };
    int numero_Origen=0;
    int numero_destino=5;
    int capacidadMaxima=10;

    resolver(mapa, numero_Origen, numero_destino, capacidadMaxima);
    return 0;
}