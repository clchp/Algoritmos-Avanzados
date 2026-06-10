#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_ITERACIONES 10000
#define ALPHA 0.3

#define TIEMPO_ORDEN 6 //minutos

struct Orden {
    int nombre;
    int cantidad_botellas;
    int prioridad;
    int tiempo_orden; //cantidad_botellas * TIEMPO_ORDEN
};

struct Linea {
    int nombre;
    vector<Orden> ordenes={};
    int tiempo_linea=0; //todos tienen 0 al inicio (están vacías)
};

void imprimir_solucion(vector<Linea> &lineas, int makespan) {
    cout<<"Solucion"<<endl;
    for(int i=0;i<lineas.size();i++) {
        cout<<"Linea "<<lineas[i].nombre<<": ";
        for(int j=0;j<lineas[i].ordenes.size();j++) {
            cout<<lineas[i].ordenes[j].nombre<<"("<<lineas[i].ordenes[j].cantidad_botellas<<" botellas)";
            if (j+1!=lineas[i].ordenes.size()) {
                cout<<", ";
            }
        }
        cout<<endl;
    }
    cout<<"El makespan es de: "<<makespan<<endl;
}

bool cmp(Orden& a, Orden& b) {
    return a.cantidad_botellas>b.cantidad_botellas; //DESC
}

void crear_RCL(vector<Orden> &RCL, double limite_inferior, vector<Orden> &ordenes) {
    for (int i=0;i<ordenes.size();i++) {
        if (ordenes[i].cantidad_botellas>=limite_inferior) {
            RCL.push_back(ordenes[i]);
        }
    }
    return;
}

void hallar_maquina_libre(vector<Linea> &lineas_iteracion, Orden aleatorio) {
    int tiempo_minimo=99999;
    int maquina_libre=-1;
    for (int i=0;i<lineas_iteracion.size();i++) {
        if (tiempo_minimo>lineas_iteracion[i].tiempo_linea+aleatorio.tiempo_orden) {
            tiempo_minimo=lineas_iteracion[i].tiempo_linea+aleatorio.tiempo_orden;
            maquina_libre=i; //el id de la maquina más libre con esa orden
        }
    }
    //una vez que se tiene el id de la maquina elegida procede a añadirse
    lineas_iteracion[maquina_libre].tiempo_linea += aleatorio.tiempo_orden;
    lineas_iteracion[maquina_libre].ordenes.push_back(aleatorio);
    return;
}

int hallar_orden(int nombre, vector<Orden> &ordenes) {
    for (int i=0;i<ordenes.size();i++) {
        if (ordenes[i].nombre==nombre) {
            return i;
        }
    }
    return -1;
}

void calcular_makespan(int &makespan_iteracion, vector<Linea> &lineas_iteracion) {
    for (int i=0;i<lineas_iteracion.size();i++) {
        if (makespan_iteracion<lineas_iteracion[i].tiempo_linea) {
            makespan_iteracion=lineas_iteracion[i].tiempo_linea;
        }
    }
}

void hallar_solucion(vector<Linea> &lineas_iteracion, vector<Orden> ordenes, int &makespan_iteracion) {
    while (!ordenes.empty()) {
        //ordenamos de forma DESC
        sort(ordenes.begin(), ordenes.end(), cmp);
        double beta=ordenes[0].cantidad_botellas; //mejor solucion
        double tau=ordenes[ordenes.size()-1].cantidad_botellas; //peor solucion
        double limite_inferior=beta-ALPHA*(beta-tau);
        vector<Orden> RCL;
        crear_RCL(RCL, limite_inferior, ordenes);
        int idx_aleatorio=rand()%RCL.size();
        Orden aleatorio=RCL[idx_aleatorio];
        //el elegido se metera en la linea que este mas libre en ese momento
        hallar_maquina_libre(lineas_iteracion, aleatorio); //aqui actualizamos el tiempo en cada linea
        //ahora lo eliminamos
        ordenes.erase(ordenes.begin()+hallar_orden(aleatorio.nombre, ordenes));
    }
    //calcular makespan
    calcular_makespan(makespan_iteracion, lineas_iteracion);
}

void inicializar_lineas(vector<Linea> &lineas_iteracion) {
    for (int i=0;i<lineas_iteracion.size();i++) {
        lineas_iteracion[i].nombre=i+1;
    }
}

void algoritmo_grasp(vector<Linea>&lineas_solucion, vector<Orden> &ordenes) {
    int i=0;
    int mejor_makespan=99999;
    while (i<MAX_ITERACIONES) {
        int makespan_iteracion=0;
        vector<Linea> lineas_iteracion(5);
        //iniciañozar lineas_iteracion
        inicializar_lineas(lineas_iteracion);
        hallar_solucion(lineas_iteracion, ordenes, makespan_iteracion);
        if (mejor_makespan>makespan_iteracion) {
            mejor_makespan=makespan_iteracion;
            lineas_solucion=lineas_iteracion;
        }
        i++;
    }
    imprimir_solucion(lineas_solucion, mejor_makespan);
}

int main() {
    srand(time(NULL));
    vector<Orden> ordenes={
        {1,103,2,103*TIEMPO_ORDEN},
        {2,58,1,58*TIEMPO_ORDEN},
        {3,88,3,88*TIEMPO_ORDEN},
        {4,126,1,126*TIEMPO_ORDEN},
        {5,195,2,195*TIEMPO_ORDEN},
        {6,90,2,90*TIEMPO_ORDEN},
        {7,54,3,54*TIEMPO_ORDEN},
        {8,195,1,195*TIEMPO_ORDEN},
        {9,124,2,124*TIEMPO_ORDEN},
        {10,113,3,113*TIEMPO_ORDEN},
        {11,193,2,193*TIEMPO_ORDEN},
        {12,55,1,55*TIEMPO_ORDEN},
        {13,97,1,97*TIEMPO_ORDEN},
        {14,97,2,97*TIEMPO_ORDEN},
        {15,169,2,169*TIEMPO_ORDEN},
        {16,50,2,50*TIEMPO_ORDEN},
        {17,167,3,167*TIEMPO_ORDEN},
        {18,74,1,74*TIEMPO_ORDEN},
        {19,79,2,79*TIEMPO_ORDEN},
        {20,109,1,109*TIEMPO_ORDEN}
    };
    vector<Linea> lineas(5);
    inicializar_lineas(lineas);
    algoritmo_grasp(lineas, ordenes);
    return 0;
}
