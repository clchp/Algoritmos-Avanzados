#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <ctime>

#define ITERACIONES 10000
#define alfa 0.3


using namespace std;


struct objetos {
    int indice;
    double peso;
    double beneficio;
    double significancia; // beneficio/peso
};

void agregar_significancia_objetos(int n, vector<objetos> &arr_objetos) {
    for (int i = 0; i < n; i++) {
        arr_objetos[i].significancia = arr_objetos[i].beneficio / arr_objetos[i].peso;
    }
}

pair<double, double> mejor_y_peor_ratio(vector<objetos> &v) {
    double maxv = -1e9, minv = 1e9;
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i].significancia > maxv) maxv = v[i].significancia;
        if (v[i].significancia < minv) minv = v[i].significancia;
    }
    return {maxv, minv};
}

vector<int> construir_RCL(vector<objetos> &copia, double residuo) {
    vector<int> candidatos;
    for (int i = 0; i < copia.size(); i++) {
        if (copia[i].peso <= residuo) candidatos.push_back(i); //escoge solo los que entran en la mochila tdv. Guarda Index
    }
    if (candidatos.empty()) return {};

    double beta = INT_MIN, tau = INT_MAX;
    for (int idx : candidatos) {
        if (copia[idx].significancia > beta) beta = copia[idx].significancia; //mejor solucion
        if (copia[idx].significancia < tau) tau = copia[idx].significancia; //peor solucion
    }
    double limite = beta - alfa * (beta - tau);

    vector<int> RCL;
    for (int idx : candidatos) {
        if (copia[idx].significancia >= limite) RCL.push_back(idx); //guarda los INIDICES de los valores que estan dentro del rango
    }
    return RCL; //devuelve los indices de los valores
}

double ganancia(vector<objetos> &sol) {
    double s = 0;
    for (int i = 0; i < (int)sol.size(); i++) s += sol[i].beneficio;
    return s;
}

void graspmochila(vector<objetos> &arr_objetos, double peso_mochila, int n) {
    vector<objetos> mejor_solucion;
    double mejor_res = INT_MAX;  // se quiere el residuo minimo
    double mejor_gan = INT_MIN; // se quiere la ganancia maxima
    srand(time(NULL));

    for (int it = 0; it < ITERACIONES; it++) {
        vector<objetos> copia_objetos = arr_objetos; //se copia para cada iteracion y tener uns solucion
        vector<objetos> solucion; //aqui se guarda la solucion
        double residuo = peso_mochila; //aqui se guardara el residuo para restar

        while (residuo > 0 && !copia_objetos.empty()) { // si tdv hay objetos en la copia y el residup es mayor
            vector<int> RCL = construir_RCL(copia_objetos, residuo); // se construye las posible ssoluciones
            if (RCL.empty()) break; //no tiene sentido esa iteracion

            int indiceAleatorio = rand() % RCL.size(); //escogemos un indice random del RCL
            int idx = RCL[indiceAleatorio]; //indice aleatorio del RCL
            solucion.push_back(copia_objetos[idx]); //guarda la solucion porque para que haya entrado quiere decir que cumple con la condicion
            residuo -= copia_objetos[idx].peso; //quitamos el peso
            copia_objetos.erase(copia_objetos.begin() + idx); //borramos el valor
        }

        double gan = ganancia(solucion); //hallamos la ganancia de la solucion
        if (gan > mejor_gan || (gan == mejor_gan && residuo < mejor_res)) { //si la ganancia es mayor o la ganancia es igual y el residuo menor, se guarda mejor solucion
            mejor_gan = gan;
            mejor_res = residuo;
            mejor_solucion = solucion;
        }
    }

    cout << "==============================" << endl;
    cout << " Mejor solucion (GRASP Construccion)" << endl;
    cout << "==============================" << endl;
    for (int i = 0; i < mejor_solucion.size(); i++) {
        cout << " - Objeto " << mejor_solucion[i].indice
             << "  Peso: " << mejor_solucion[i].peso
             << "  Beneficio: " << mejor_solucion[i].beneficio
             << "  Ratio: " << mejor_solucion[i].significancia << endl;
    }
    cout << "Ganancia total: " << mejor_gan << endl;
    cout << "Residuo: " << mejor_res << endl;
    cout << "==============================" << endl;
}

int main() {
    vector<objetos> arr_objetos = {
        {1, 10, 60},
        {2, 20, 100},
        {3, 30, 120},
        {4, 5, 30},
        {5, 8, 40},
        {6, 12, 70},
        {7, 25, 90},
        {8, 15, 75},
        {9, 7, 20},
        {10, 18, 85}
    };

    int n = arr_objetos.size();
    double peso_mochila = 50;
    agregar_significancia_objetos(n, arr_objetos);
    graspmochila(arr_objetos, peso_mochila, n);

    return 0;
}