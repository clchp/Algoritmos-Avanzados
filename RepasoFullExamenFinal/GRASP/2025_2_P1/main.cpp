#include <algorithm>
#include <vector>
#include <iostream>

#define x 0.6
#define y 0.4
#define alpha 0.25

using namespace std;

struct Proyecto {
    int nombre;
    double beneficio;
    double costo;
    string categoria;
    double riesgo;
    double greedy=-1;
};

struct Portafolio {
    vector<Proyecto> proyectos={};
    double costoTotal=0;
    double presupuesto;
    vector<string> categoriasAsignadas={};
};

void greedy(Proyecto &proyecto) {
    /* Se define de tal manera porque el beneficio/costo nos da el ratio o sea el peso que tiene
     * el proyecto. X simboliza eel peso del ratio en la decision y y el peso por el riesgo. Será más
     * conveniente escoger un proyecto que su riesgo sea menor (10-r).
     */
    proyecto.greedy=x*(proyecto.beneficio/proyecto.costo)+y*(10-proyecto.riesgo);
}

bool cmp(Proyecto &p1, Proyecto &p2) {
    return p1.greedy>p2.greedy; //DESC
}

void construirRCL(vector<Proyecto> &RCL, double limite_inferior, vector<Proyecto> &proyectos) {
    for (int i=0;i<proyectos.size(); i++) {
        if (proyectos[i].greedy>=limite_inferior) {
            RCL.push_back(proyectos[i]);
        }
    }
}

void imprimir(vector<Proyecto> &proyectos) {
    for (int i = 0; i < proyectos.size(); i++) {
        cout<<"P"<<proyectos[i].nombre<<" - greedy: "<<proyectos[i].greedy<<endl;
    }
}

bool proyectoEsValido(Proyecto &aleatorio, Portafolio &portafolio, vector<Proyecto> &proyectos) {
    //CONDICIONES, NO PASARSE DEL PRESUPUESTO Y QUE NO ESTE ESA CATEGORIA YA TOMADA
    bool cumplePresupuesto=false, categoriasValido=true;
    if (portafolio.proyectos.empty()) {
        categoriasValido=true;
    }else {
        for (int i=0;i<portafolio.categoriasAsignadas.size();i++) {
            if (portafolio.categoriasAsignadas[i]==aleatorio.categoria) {
                categoriasValido=false;
                break;
            }
        }
    }
    if (aleatorio.costo+portafolio.costoTotal<=portafolio.presupuesto) {
        cumplePresupuesto=true;
    }
    cout<<endl<<"CRITERIOS PARA EL PROYECTOS P"<<aleatorio.nombre<<endl;
    cout<<"¿Cumple con el criterio de las categorias: ?"<<categoriasValido<<endl;
    cout<<"¿Cumple con el criterio del presupuesto: ?"<<cumplePresupuesto<<endl;
    if (categoriasValido and cumplePresupuesto) {
        cout<<"DECISION FINAL: SE TOMA EL PROYECTO"<<endl;
    }else {
        cout<<"DECISION FINAL: NO SE TOMA EL PROYECTO"<<endl;
    }
    return categoriasValido and cumplePresupuesto;
}

int hallarIdx(int nombre, vector<Proyecto> &proyectos) {
    for (int i=0;i<proyectos.size();i++) {
        if (proyectos[i].nombre==nombre) {
            return i;
        }
    }
    return -1;
}

void imprimirPortafolio(Portafolio &portafolio, double presupuesto) {
    cout<<endl<<"==================="<<endl;
    cout<<"Portfolio 2026"<<endl;
    cout<<"==================="<<endl;
    cout<<"Proyectos seleccionados: "<<endl;
    for (int i=0;i<portafolio.proyectos.size();i++) {
        cout<<"P"<<portafolio.proyectos[i].nombre<<" - costo: "<<portafolio.proyectos[i].costo<<" - beneficio: "<<portafolio.proyectos[i].beneficio<<" - riesgo: "<<portafolio.proyectos[i].riesgo
        <<" - categoria: "<<portafolio.proyectos[i].categoria<<endl;
    }
    cout<<"Presupuesto: "<<presupuesto<<endl;
    cout<<"Costo Total: "<<portafolio.costoTotal<<endl;
    cout<<"Ahorro: "<<portafolio.presupuesto<<endl;
    cout<<"Categorias cubiertas: ";
    for (int i=0;i<portafolio.categoriasAsignadas.size();i++) {
        cout<<portafolio.categoriasAsignadas[i]<<" ";
    }
}

void grasp(vector<Proyecto> &proyectos, double presupuesto) {
    Portafolio portafolio={{},0,presupuesto, {}};

    while (portafolio.proyectos.size()!=2) {
        for (int i = 0; i < proyectos.size(); i++) {
            greedy(proyectos[i]);
        }
        sort(proyectos.begin(), proyectos.end(), cmp);
        for (int i = 0; i < proyectos.size(); i++) {
            cout<<"P"<<proyectos[i].nombre<<" - greedy: "<<proyectos[i].greedy<<endl;
        }
        double beta=proyectos.front().greedy;
        double tau=proyectos.back().greedy;
        double limite_inferior=beta-alpha*(beta-tau);
        vector<Proyecto> RCL;
        construirRCL(RCL, limite_inferior, proyectos);
        cout<<endl<<"RCL"<<endl;
        Proyecto aleatorio;
        imprimir(RCL);
        for (int i = 0; i < RCL.size(); i++) {
            if (RCL[i].nombre%2==0) {
                aleatorio=RCL[i];
                break;
            }
        }
        if (aleatorio.greedy==-1) {
            aleatorio=RCL.front();
        }
        cout<<endl<<"Seleccionado: "<<endl;
        cout<<"P"<<aleatorio.nombre<<" - greedy: "<<aleatorio.greedy<<endl;
        //analizamos si entra
        bool esValido=proyectoEsValido(aleatorio, portafolio, proyectos);
        if (esValido) {
            portafolio.proyectos.push_back(aleatorio);
            portafolio.categoriasAsignadas.push_back(aleatorio.categoria);
            portafolio.presupuesto-=aleatorio.costo;
            portafolio.costoTotal+=aleatorio.costo;
        }
        //lo eliminamos igual porque ya se examino
        proyectos.erase(proyectos.begin()+hallarIdx(aleatorio.nombre, proyectos));
    }
    imprimirPortafolio(portafolio, presupuesto);
}

int main(){
    vector<Proyecto> proyectos = {
        {0, 80, 40, "Marketing", 8},
        {1, 120, 90, "TI", 5},
        {2, 60, 20, "Produccion", 3},
        {3, 30, 10, "Logistica", 9},
        {4, 200, 150, "RRHH", 2},
        {5, 55, 25, "Marketing", 7},
        {6, 110, 70, "TI", 10},
        {7, 45, 30, "Produccion", 4},
        {8, 75, 50, "Logistica", 6},
        {9, 90, 60, "RRHH", 1}
    };
    double presupuesto=150;
    grasp(proyectos, presupuesto);
    return 0;
}