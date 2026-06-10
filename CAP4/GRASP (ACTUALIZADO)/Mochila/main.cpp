#include <algorithm>
#include <vector>
#include <iostream>
#define MAX_ITERACIONES 10000
#define alpha 0.25

using namespace std;

struct Objeto {
    double peso;
    double beneficio;
    double ratio=0;
};

void imprimir_mochila(vector<Objeto> &mochila, int mochila_peso) {
    int suma_total_beneficio=0, suma_total_peso=0;
    cout<<"Mochila:"<<endl;
    for (int i=0;i<mochila.size();i++) {
        cout<<"Peso:"<<mochila[i].peso<<" | Beneficio:"<<mochila[i].beneficio<<" | Ratio:"<<mochila[i].ratio<<endl;
        suma_total_beneficio+=mochila[i].beneficio;
        suma_total_peso+=mochila[i].peso;
    }
    cout<<"========== RESUMEN =========="<<endl;
    cout<<"Beneficio Obtenido:"<<suma_total_beneficio<<endl;
    cout<<"Peso restante:"<<mochila_peso<<endl;
}

double mejor_solucion(vector<Objeto>& mochila) {
    //la mejor solucion es quien tenga mayor ratio MAXIMIZAR
    double max=0;
    for (int i=0;i<mochila.size();i++) {
        if (mochila[i].ratio>max) {
            max=mochila[i].ratio;
        }
    }
    return max;
}

double peor_solucion(vector<Objeto>& mochila) {
    //la peor solucion es quien tenga menor ratio MAXIMIZAR
    double min=99999;
    for (int i=0;i<mochila.size();i++) {
        if (mochila[i].ratio<min) {
            min=mochila[i].ratio;
        }
    }
    return min;
}

void obtener_ratios(vector<Objeto>&mochila) {
    for (int i=0;i<mochila.size();i++) {
        mochila[i].ratio=mochila[i].beneficio/mochila[i].peso;
    }
}

bool cmp(Objeto &a, Objeto &b) {
    return a.ratio>b.ratio; //DESC (Mayor a menor)
}

void generar_RCL(vector<Objeto> &copia_mochila,double limite_inferior,vector<Objeto> &RCL){
    for(int i=0;i<copia_mochila.size();i++){
        if(copia_mochila[i].ratio >= limite_inferior){
            RCL.push_back(copia_mochila[i]);
        }
    }
}

int idx_usado(Objeto usado, vector<Objeto>&copia_mochila) {
    for (int i=0;i<copia_mochila.size();i++) {
        if(usado.peso == copia_mochila[i].peso &&
           usado.beneficio == copia_mochila[i].beneficio) {
            return i;
        }
    }
    return -1;
}

void grasp_mochila(vector<Objeto> &mochila, int peso_mochila) {
    //obtener ratios
    obtener_ratios(mochila);
    vector<Objeto> mejor_mochila;
    double mejor_beneficio=0, mejor_peso=99999;
    int i=0;
    while (i<MAX_ITERACIONES) {
        vector<Objeto> solucion_iteracion_mochila;
        vector<Objeto> copia_mochila=mochila;
        double copia_peso_mochila=peso_mochila;
        double beneficio_iteracion=0;
        while (copia_peso_mochila>0 and copia_mochila.size()!=0) {
            double beta=mejor_solucion(copia_mochila);
            double tau=peor_solucion(copia_mochila);
            //obtener limite como queremos MAXIMIZAR debemos cambiar el limite inferior
            double limite_inferior=beta-alpha*(beta-tau);
            //vamos a ordenar los valores por los ratios, como queremos maximizar entonces DESC
            sort(copia_mochila.begin(),copia_mochila.end(), cmp);
            vector<Objeto> RCL;
            generar_RCL(copia_mochila, limite_inferior, RCL);
            //elegir uno al azar
            if(RCL.empty()) break;
            int idx_azar=rand()%RCL.size();
            if (RCL[idx_azar].peso<=copia_peso_mochila) {
                solucion_iteracion_mochila.push_back(RCL[idx_azar]);
                copia_peso_mochila-=RCL[idx_azar].peso;
                beneficio_iteracion+=RCL[idx_azar].beneficio;
            }
            //borrar de mi copia
            copia_mochila.erase(copia_mochila.begin()+idx_usado(RCL[idx_azar], copia_mochila));
        }
        //cuando ya se tiene una solucion, entonces se ve si es la mejor
        if (mejor_beneficio<beneficio_iteracion or mejor_beneficio==beneficio_iteracion and mejor_peso>copia_peso_mochila) {
            mejor_mochila=solucion_iteracion_mochila;
            mejor_beneficio=beneficio_iteracion;
            mejor_peso=copia_peso_mochila;
        }
        i++;
    }
    imprimir_mochila(mejor_mochila, mejor_peso);
}

int main() {
    srand(time(nullptr));
    vector<Objeto>mochila={{3,90},{4,100},{5,110},{2,36},{6,10}};
    double peso_mochila=10;
    grasp_mochila(mochila, peso_mochila);
    return 0;
}