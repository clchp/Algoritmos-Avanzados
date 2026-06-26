#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define ALPHA 0.3
#define MAX_ITERACIONES 5000


struct informacion {
    int nombre_antena;
    vector<int> zonas;
    int beneficio_antena=0; //zonas no cubiertas tdv
};

struct solucion {
    vector<informacion> info;
    vector<int> zonas_con_cobertura={};
};

void imprimir_solucion(solucion& data) {
    cout<<"SOLUCION"<<endl;
    for (int i = 0; i < data.info.size(); i++) {
        cout<<"A"<<data.info[i].nombre_antena<<" --> ";
        for (int j = 0; j < data.info[i].zonas.size(); j++) {
            cout<<"Z"<<data.info[i].zonas[j];
            if (j+1!=data.info[i].zonas.size()) {
                cout<<", ";
            }
        }
        cout<<endl;
    }
    cout<<"La cantidad minima es "<<data.info.size()<<endl;
    cout<<"Las zonas cubiertas son: ";
    for (int i=0;i<data.zonas_con_cobertura.size();i++) {
        cout<<"Z"<<data.zonas_con_cobertura[i];
        if (i+1!=data.zonas_con_cobertura.size()) {
            cout<<", ";
        }
    }
}

bool cmp(informacion &a, informacion &b) {
    return a.beneficio_antena>b.beneficio_antena; //DESC
}



void construir_RCL(vector<informacion>&RCL, double limite_inferior, vector<informacion>&data) {
    for (int i = 0; i < data.size(); i++) {
        if (limite_inferior<=data[i].beneficio_antena) {
            RCL.push_back(data[i]);
        }
    }
}

void añadir_zonas_cubiertas_por_antena(int &zona, solucion &solucion_iteracion) {
    bool esta_cubierto=false;
    for (int i = 0; i < solucion_iteracion.zonas_con_cobertura.size(); i++) {
        if (zona==solucion_iteracion.zonas_con_cobertura[i]) { //si ya está en zona cubierta
            esta_cubierto=true;
            break;
        }
    }
    if (!esta_cubierto) {
        solucion_iteracion.zonas_con_cobertura.push_back(zona); //se añade la nueva zona
    }
    return;
}

void obtener_zonas_cubiertas(solucion &solucion_iteracion) {
    if (solucion_iteracion.info.size()==0) {
        solucion_iteracion.zonas_con_cobertura={}; //no hay nada
        return;
    }
    for (int i = 0; i < solucion_iteracion.info.size(); i++) { //analizamos cada antena
        for (int j = 0; j < solucion_iteracion.info[i].zonas.size(); j++) { //analizamos cada zona cubierta por la antena
            añadir_zonas_cubiertas_por_antena(solucion_iteracion.info[i].zonas[j], solucion_iteracion);
        }
    }
    //ordenarlo para que quede bonito :)
    sort(solucion_iteracion.zonas_con_cobertura.begin(), solucion_iteracion.zonas_con_cobertura.end()); //ASC
}

void obtener_beneficios_por_antena(vector<informacion> &data, solucion &solucion_iteracion) {
    //ahora vamos a ver la lista de zonas ya cubiertas
    for (int i=0;i<data.size();i++) { //por cada antena
        int zona_coberturada=0;
        for (int j=0;j<data[i].zonas.size();j++) {
            int zona_a_evaluar=data[i].zonas[j];
            //ahora a ver si esa zona esta ya con cobertura
            for (int k=0;k<solucion_iteracion.zonas_con_cobertura.size();k++) {
                if (zona_a_evaluar==solucion_iteracion.zonas_con_cobertura[k]) {
                    zona_coberturada++;
                    break;
                }
            }
        }
        data[i].beneficio_antena=data[i].zonas.size()-zona_coberturada;
    }
}

int hallar_antena(int antena, vector<informacion> &data) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i].nombre_antena==antena) {
            return i;
        }
    }
    return -1;
}

void hallar_solucion_iteracion(solucion &solucion_iteracion, vector <informacion> data) {
    while (solucion_iteracion.zonas_con_cobertura.size()<8) {
        //obtener beneficios
        obtener_beneficios_por_antena(data, solucion_iteracion);
        //ordenar beneficios
        sort(data.begin(),data.end(),cmp);
        //imprimir_solucion(data);
        double beta=data[0].beneficio_antena; //mejor solucion
        double tau=data[data.size()-1].beneficio_antena; //peor solucion
        double limite_inferior = beta-ALPHA*(beta-tau);
        vector<informacion> RCL;
        construir_RCL(RCL, limite_inferior, data);
        int idx_aleatorio=rand()%RCL.size();
        informacion aleatorio=RCL[idx_aleatorio];
        //vemos si es que el elegido tiene zonas ya cubiertas
        if (aleatorio.beneficio_antena!=0) {
            solucion_iteracion.info.push_back(aleatorio);
            obtener_zonas_cubiertas(solucion_iteracion);
        }
        //eliminar
        data.erase(data.begin()+hallar_antena(aleatorio.nombre_antena, data));
    }
}

void algoritmo_grasp(vector<informacion> &data) {
    solucion mejor_solucion;
    int menor_cantidad=999999;
    int i=0;
    while (i<MAX_ITERACIONES) {
        solucion solucion_iteracion;
        hallar_solucion_iteracion(solucion_iteracion, data);
        if (menor_cantidad>solucion_iteracion.info.size()) {
            menor_cantidad=solucion_iteracion.info.size();
            mejor_solucion=solucion_iteracion;
        }
        i++;
    }
    imprimir_solucion(mejor_solucion);
}

int main(){
    srand(time(NULL));
    vector<informacion> data={
        {1,{1,2,3}},
        {2, {2,4,5}},
        {3, {3,5,6}},
        {4, {6,7}},
        {5,{7,8}},
        {6, {1,4,8}}
    };
    algoritmo_grasp(data);
    return 0;
}