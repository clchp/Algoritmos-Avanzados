#include <iostream>
#include <vector>

using namespace std;

struct Grafo {
    char letra;
    vector<char> vecinos;
    vector<int> distancias;
};

int buscarMapa(char punto, vector<Grafo> &mapa) {
    for (int i = 0; i < mapa.size(); i++) {
        if (mapa[i].letra == punto) {
            return i;
        }
    }
    return -1;
}

int menor_distancia_mapa(vector<int>distancias, vector<char>vecinos, char &sgte_vecino) {
    int min=99999;
    for (int i = 0; i < distancias.size(); i++) {
        if (min>distancias[i]) {
            min = distancias[i];
            sgte_vecino = vecinos[i];
        }
    }
    return min;
}

bool rutaRappi(char puntoDestino, char puntoInicio, vector <Grafo>&mapa, int &tiempoViaje) {
    //situarme donde estoy
    int idxPuntoInicio=buscarMapa(puntoInicio, mapa);
    char sgte_vecino;
    while (true) {
        vector<int> distancias=mapa[idxPuntoInicio].distancias;
        vector<char> vecinos=mapa[idxPuntoInicio].vecinos;
        if (vecinos.empty()) return false; //quiere decir que no hay solucion
        //buscar el menor
        int menor_distancia=menor_distancia_mapa(distancias, vecinos, sgte_vecino);
        tiempoViaje+=menor_distancia;
        idxPuntoInicio=buscarMapa(sgte_vecino, mapa);
        if (sgte_vecino==puntoDestino) break;
    }
    return true;
}

int main() {
    vector<Grafo> mapa={
        {'A', {'B','C','D'},{4,5,6}},
        {'B',{'E'},{2}},
        {'C',{'H'},{3}},
        {'D',{'F'},{3}},
        {'E',{'G'},{10}},
        {'F',{'G'},{2}},
        {'G',{},{}},
        {'H',{},{}}
    };
    char puntoInicio='A';
    char puntoDestino='G';
    int tiempoViaje=0;
    if (rutaRappi(puntoDestino, puntoInicio, mapa, tiempoViaje)) {
        cout<<"El tiempo de llegada de "<<puntoInicio<<" a "<<puntoDestino<<" es de: "<<tiempoViaje<<" min"<<endl;
    }else {
        cout<<"No se encontro una solucion"<<endl;
    }

    return 0;
}