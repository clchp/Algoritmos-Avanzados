#include <iostream>
#include <vector>

#define alfa 0.3
#define ITERACIONES 10000

using namespace std;

struct Moneda {
    int valor; //el valor de la moneda
    int cantidad; //monedas usadas
};
vector<int> escoger_RSL(int monto, vector<Moneda>&copia) { //aqui se tendra los indices que funcionan para la soluciob
    vector<int>candidatos;
    for (int i = 0; i < copia.size(); i++) {
        if (monto>=copia[i].valor) {candidatos.push_back(i);} //se guarda el indice de una posible solucion
    }
    if (candidatos.empty())return{}; //sin nada

    //escogemos tau y beta
    int beta=INT_MIN, tau=INT_MAX; //la mejor solucion será la mas grande y la solucion menor será la mas chica
    for (int idx:candidatos) {
        if (copia[idx].valor>beta) beta=copia[idx].valor;
        if (copia[idx].valor<tau) tau=copia[idx].valor;
    }
    vector<int> RCL; //donde se guardan las posibles soluciones
    int limiteInferior= beta-(alfa*(beta-tau));
    for (int idx:candidatos) {
        if (copia[idx].valor>=limiteInferior) RCL.push_back(idx);
    }
    return RCL;
}
int cantidad_monedas(vector<Moneda>solucion) {
    int cont=0;
    for (int i = 0; i < solucion.size(); i++) {
        cont+=solucion[i].cantidad;
    }
    return cont;
}


void grasp_monedas(int valor_llegar, vector<Moneda>arr_monedas, int n) {
    vector<Moneda> mejor_solucion;
    int menor_residuo=INT_MAX;
    int menor_monedas=INT_MAX;
    srand(time(NULL));
    for (int i = 0; i < ITERACIONES; i++) {
        int monto=valor_llegar;
        vector<Moneda> copia=arr_monedas;
        vector<Moneda> solucion;
        while (monto>0 and !copia.empty()) {
            vector<int> RCL=escoger_RSL(monto, copia);
            if (RCL.empty())break; //no vale la pena escogerlo
            //escogemos un valor aleatorio
            int indxAle=rand()%RCL.size(); //el indice aleatorio
            int idx=RCL[indxAle];
            int cantidad = monto / copia[idx].valor;   // cuántas de esa moneda puedo usar
            if (cantidad > 0) { // si se emplea la moneda para algo
                solucion.push_back({copia[idx].valor, cantidad}); //el valor + la cantidad
                monto -= cantidad * copia[idx].valor; // se resta el valor
            }
            copia.erase(copia.begin()+idx); // se borra el valor
        }
        if (cantidad_monedas(solucion)<menor_monedas || (cantidad_monedas(solucion)==menor_monedas and monto<menor_residuo)) {
            menor_monedas=cantidad_monedas(solucion);
            mejor_solucion=solucion;
            menor_residuo=monto;
        }
    }
    cout<<"La mejor solucion es de: "<<endl;
    for (Moneda idx: mejor_solucion) {
        cout<<idx.valor<<" con "<<idx.cantidad<<endl;
    }
    cout<<"El residuo fue de: "<<menor_residuo<<" con la cantidad de monedas minima: "<<menor_monedas<<" para llegar a "<<
        valor_llegar<<endl;
}

int main() {
    vector<Moneda> arr_monedas={
        {100,0},{80,0},{1,0},{2,0},{30,0}
    };
    int n=arr_monedas.size();
    int valor_llegar=624;
    grasp_monedas(valor_llegar, arr_monedas, n);
    return 0;
}