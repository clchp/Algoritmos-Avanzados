#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Grafos {
    char letra;
    int cant_vecinos;
    vector<char> vecinos;
    int color_asignado=-1;
};

void imprimir(vector<Grafos> mapa, int n) {
    for (int i = 0; i < n; i++) {
        cout<<"Grafo "<<mapa[i].letra<<": cantidad vecinos --> "<<mapa[i].cant_vecinos<<" | vecinos: ";
        for (int j = 0; j < mapa[i].cant_vecinos; j++) {
            cout<<mapa[i].vecinos[j];
            if (j+1!=mapa[i].cant_vecinos) cout<<"-";
        }
        cout<<" | color asignado: "<<mapa[i].color_asignado<<endl;
    }
}

int cmp (Grafos &a, Grafos &b) {
    return a.cant_vecinos > b.cant_vecinos;
}

int buscar_grafito(vector<Grafos>&mapa, char letra) {
    for (int i=0;i<mapa.size();i++) {
        if (mapa[i].letra == letra) {
            return mapa[i].color_asignado;
        }
    }
}

int asignar_color(vector<Grafos>& mapa, Grafos grafito) {
    vector<char> vecinos = grafito.vecinos;
    vector<int> colores_vecinos;
    // guardar colores de vecinos
    for (int i = 0; i < vecinos.size(); i++) {
        colores_vecinos.push_back(buscar_grafito(mapa, vecinos[i]));
    }
    // probar colores desde 0
    int color = 0;
    while (true) {
        bool encontrado = false;
        // ver si el color ya lo usa un vecino
        for (int i = 0; i < colores_vecinos.size(); i++) {
            if (colores_vecinos[i] == color) {
                encontrado = true;
                break;
            }
        }
        // si nadie lo usa, ese color sirve
        if (!encontrado) {
            return color;
        }
        color++;
    }
}

void calcular_min_numero_colores(vector<Grafos>&mapa) {
    //ordenar por cantidad de vecinos
    sort(mapa.begin(), mapa.end(), cmp);
    //imprimir(mapa, mapa.size());
    for (int i = 0; i < mapa.size(); i++) {
        mapa[i].color_asignado=asignar_color(mapa, mapa[i]);
    }
    imprimir(mapa,mapa.size());
}

int main() {
    vector<Grafos> mapa={
        {'A', 3, {'B','C','D'}},
        {'B', 3,{'A','C','E'}},
        {'C', 4,{'A','B','D','F'}},
        {'D',3,{'A','C','F'}},
        {'E',2,{'B','F'}},
        {'F',3,{'C','D','E'}}
    };
    calcular_min_numero_colores(mapa);
    return 0;
}