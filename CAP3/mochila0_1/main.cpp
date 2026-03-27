#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Objeto {
    int valor;
    double tiempo;
    double espacio;
    double energia;
    double ratio;
};
struct Camion {
    double tiempo;
    double espacio;
    double energia;
};

bool cmp(Objeto a, Objeto b) {
    return a.ratio > b.ratio; //Descendente
}
void calcularRatio(vector<Objeto> &objetos, int n, Camion camion) {
    double tiempoNormalizado[n], espacioNormalizado[n], energiaNormalizado[n];
    for (int i=0; i<n; i++) { //normalizamos
        tiempoNormalizado[i]=objetos[i].tiempo/camion.tiempo;
        energiaNormalizado[i]=objetos[i].energia/camion.energia;
        espacioNormalizado[i]=objetos[i].espacio/camion.espacio;
    }
    for (int i=0; i<n; i++) {//hallar ratio
        objetos[i].ratio=((1.0/3)*tiempoNormalizado[i])+((1.0/3)*espacioNormalizado[i])+((1.0/3)*energiaNormalizado[i]);
    }
}

int obtenerDatosMochila(Camion &camion, vector<Objeto> objetos, int n) {
    int valorMaximo=0;
    for (int i=0; i<n;i++) {//recorremos todos los elementos
        if (objetos[i].tiempo<=camion.tiempo and objetos[i].espacio<=camion.espacio and objetos[i].energia<=camion.energia) { //si es menor igual entra ENTERO
            valorMaximo+=objetos[i].valor;
            camion.tiempo-=objetos[i].tiempo; //se reduce la capacidad
            camion.espacio-=objetos[i].espacio; //se reduce la capacidad
            camion.energia-=objetos[i].energia; //se reduce la capacidad
        }else {
            //se haya la fraccion
            double fraccion=min(min(camion.tiempo/objetos[i].tiempo, camion.espacio/objetos[i].espacio), camion.energia/objetos[i].energia);
            valorMaximo+=objetos[i].valor*fraccion;
            camion.tiempo-=objetos[i].tiempo*fraccion; //se reduce la capacidad
            camion.espacio-=objetos[i].espacio*fraccion; //se reduce la capacidad
            camion.energia-=objetos[i].energia*fraccion; //se reduce la capacidad
            return valorMaximo; //es el ultimo
        }
    }
    return valorMaximo; //si todo entro
}
// Función para mostrar un objeto
void mostrarObjeto(const Objeto &obj) {
    cout << "Valor: " << obj.valor
         << ", Tiempo: " << obj.tiempo
         << ", Espacio: " << obj.espacio
         << ", Energia: " << obj.energia
         << ", Ratio: " << obj.ratio << endl;
}

// Función para mostrar el camion
void mostrarCamion(const Camion &cam) {
    cout << "Camion -> Tiempo disponible: " << cam.tiempo
         << ", Espacio disponible: " << cam.espacio
         << ", Energia disponible: " << cam.energia << endl;
}
int main() {
    vector<Objeto> objetos = {
        {120,6,5,4},
        {100,4,3,2},
        {80,5,4,3},
        {60,3,2,2}
    };
    int n = objetos.size();
    Camion camion={12,10,8};
    calcularRatio(objetos, n, camion);
    sort(objetos.begin(), objetos.end(), cmp);
    cout << "=== Estado inicial del camion ===" << endl;
    mostrarCamion(camion);
    cout << "\n=== Objetos disponibles ===" << endl;
    for (const auto &obj : objetos) {
        mostrarObjeto(obj);
    }
    cout << "\nSe puede obtener como valor max: " << obtenerDatosMochila(camion, objetos, n)<<endl;
    cout << "\n=== Estado final del camion ===" << endl;
    mostrarCamion(camion);
    return 0;
}
