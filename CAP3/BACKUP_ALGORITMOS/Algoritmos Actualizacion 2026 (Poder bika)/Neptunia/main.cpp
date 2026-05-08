#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct objetos {
    double peso;
    double ganancia;
    double ratio=0;
};

void obtener_ratios(vector<objetos>&objetitos, int n){
    for (int i = 0; i < n; i++) {
        objetitos[i].ratio=objetitos[i].ganancia/objetitos[i].peso;
    }
    return;
}

bool cmp(objetos &a, objetos &b) { //es un bool cueck
    return a.ratio > b.ratio;
}

void solucionNeptunia(vector<objetos> & objetitos, int n, int capacidadMax) {
    //obtener ratios
    obtener_ratios(objetitos, n);
    //ordenar desc por ratios
    sort(objetitos.begin(), objetitos.end(), cmp);
    double gananciaTotal=0;
    for (int i = 0; i < n; i++) {
        if (capacidadMax==0)break;
        if (objetitos[i].peso <= capacidadMax) {
            capacidadMax-=objetitos[i].peso;
            gananciaTotal+=objetitos[i].ganancia;
        }
    }
    cout<<"La capacidad restante fue de "<<capacidadMax<<" Tn"<<endl;
    cout<<"La ganancia maxima fue de "<<gananciaTotal<<" Millones de dolares"<<endl;
    return;
}

int main(){
    vector<objetos> objetitos={
        {2,10},
        {3,15},
        {5,10},
        {12,14},
        {2,8},
        {5,5}
    };
    int capacidadMax=20;
    solucionNeptunia(objetitos, objetitos.size(), capacidadMax);

    return 0;
}