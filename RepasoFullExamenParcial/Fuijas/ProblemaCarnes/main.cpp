#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool es_Valido(int peso,vector <int >listaPesos,int k) {
    if (listaPesos.empty()) {
        return true;
    }
    for (int i=0;i<listaPesos.size();i++) {
        if (abs(peso-listaPesos[i])<=k) {
            return true;
        }
    }
    return false;
}
bool hacer_combinacion(int indice,int P,int k,vector<int>t,vector<int >&indices,vector <int>&listaPesos) {
    if (P==0) {
        return true; // se logro llegar al peso de 15
    }
    if ( indice>=t.size()) {
        return false;
    }
    int peso=t[indice];
    if (peso>P) { //aqui devuelvo false si es que ya sobrepase el P actualizado
        return hacer_combinacion(indice+1,P,k,t,indices,listaPesos); //tomo el siguiebtem este no
    }
    if (es_Valido(peso,listaPesos,k)) {
        listaPesos.push_back(peso);
        indices.push_back(indice);
        if (hacer_combinacion(indice+1,P-peso,k,t,indices,listaPesos)) {
            return true;
        }
        listaPesos.pop_back();
        indices.pop_back();
    }
    if (hacer_combinacion(indice+1,P,k,t,indices,listaPesos)) {
        return true;
    }
    return false;
}

int main() {

    int P=15;
    int k=3;
    vector<int> t={2, 8, 9, 6, 7, 6};
    vector<vector<int>> listaCombinaciones;

    while (true) {
        vector<int> indices;
        vector <int> lista;
        if (hacer_combinacion(0,P,k,t,indices,lista)) {
            listaCombinaciones.push_back(lista);
            for (int i=indices.size()-1;i>=0;i--) {
                t.erase(t.begin()+indices[i]);
            }
        }
        else {
            break;
        }

    }

    int total=listaCombinaciones.size();
    cout << "TOTAL: "<<total<<endl;
    for (vector orden : listaCombinaciones) {

        for (int i=0;i<orden.size();i++) {
            cout << orden[i]<<" ";
        }
        cout << endl;
    }

}