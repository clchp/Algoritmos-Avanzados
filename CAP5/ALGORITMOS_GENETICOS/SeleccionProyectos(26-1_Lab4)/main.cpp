#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>
#define ITERACIONES 50
#define NUMIND 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.5
#define TMUTACION 0.3

using namespace std;

int calculafitness(vector<int> cromo, int *beneficio) {
    int sumap = 0;
    for (int i = 0; i < cromo.size(); i++) {
        sumap += cromo[i] * beneficio[i];
    }
    return sumap;
}

int calculacosto(vector<int> cromo, int *costo) {
    int sumap = 0;
    for (int i = 0; i < cromo.size(); i++) {
        sumap += cromo[i] * costo[i];
    }
    return sumap;
}

//lo que debe cumplir es con el presupuesto, que no exceda y los predecesores
/* PROYECTOS --> PREDECESORES
 * 2 --> 1
 * 3 --> 1
 * 5 --> 4
 * 6 --> 2,4
 */
bool aberracion(vector<int> ind, int presupuesto, int *costo, vector<vector<int> > predecesores) {
    if (calculacosto(ind, costo) > presupuesto) {
        return true;
    }
    for (int i = 0; i < ind.size(); i++) {
        // está seleccionado este proyecto?
        if (ind[i] == 1) {
            // reviso todos sus predecesores
            for (int j = 0; j < predecesores[i].size(); j++) {
                int pred = predecesores[i][j]-1;
                // si algun predecesor no está seleccionado
                if (ind[pred] == 0)
                    return true;
            }
        }
    }
    return false;
}

void muestrapoblacion(vector<vector<int> > poblacion, int *beneficio) {
    for (int i = 0; i < poblacion.size(); i++) {
        for (int j = 0; j < poblacion[i].size(); j++) {
            cout << poblacion[i][j] << " ";
        }
        cout << " fo=" << calculafitness(poblacion[i], beneficio) << endl;
    }
}

int decimal(vector<int> ind) {
    int num = 0;
    for (int i = 0; i < ind.size(); i++)
        num += ind[i] * pow(2, i);
    return num;
}

void mataclon(vector<vector<int> > &poblacion) {
    map<int, vector<int> > indunicos;

    for (int i = 0; i < poblacion.size(); i++) {
        int dec = decimal(poblacion[i]);
        indunicos[dec] = poblacion[i];
    }
    poblacion.clear();
    for (map<int, vector<int> >::iterator it = indunicos.begin();
         it != indunicos.end(); it++) {
        poblacion.push_back(it->second);
    }
}


void generapoblacion(vector<vector<int> > &poblacion,
                     int *costo, int n, int presupuesto, vector<vector<int> > predecesores) {
    int cont = 0;
    srand(time(NULL));
    while (cont < NUMIND) {
        vector<int> individuo;
        // aqui también cambiar
        for (int i = 0; i < n; i++)
            individuo.push_back(rand() % 2);
        if (!aberracion(individuo, presupuesto, costo, predecesores)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int> > poblacion,
                          vector<int> &supervivencia, int *beneficio, int n, int presupuesto) {
    int sumafitness = 0;

    for (int i = 0; i < poblacion.size(); i++)
        sumafitness += calculafitness(poblacion[i], beneficio);
    for (int i = 0; i < poblacion.size(); i++) {
        int superfit;
        superfit = round(100 * (double) calculafitness(poblacion[i], beneficio) / sumafitness);
        supervivencia.push_back(superfit);
    }
}

void cargaruleta(vector<int> supervivencia, int *ruleta) {
    int cont = 0;
    for (int i = 0; i < supervivencia.size(); i++)
        for (int j = 0; j < supervivencia[i]; j++) {
            ruleta[cont++] = i;
        }
}


void seleccion(vector<vector<int> > poblacion, vector<vector<int> > &padres,
               int *beneficio, int n, int presupuesto) {
    int ruleta[100]{-1};
    vector<int> supervivencia;
    calculasupervivencia(poblacion, supervivencia, beneficio, n, presupuesto);
    cargaruleta(supervivencia, ruleta);
    int npadres = round(poblacion.size() * TSELECCION);

    for (int i = 0; i < npadres; i++) {
        int ticket = rand() % 100;
        if (ruleta[ticket] != -1)
            padres.push_back(poblacion[ruleta[ticket]]);
    }
    //muestrapoblacion(padres,paq);
}

void creahijo(vector<int> padre, vector<int> madre,
              vector<int> &hijo) {
    int posi = round(padre.size() * PCASAMIENTO);

    for (int i = 0; i < posi; i++)
        hijo.push_back(padre[i]);
    for (int i = posi; i < madre.size(); i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int> > &poblacion, vector<vector<int> > padres,
                int *costo, int presupuesto, vector<vector<int> > predecesores) {
    for (int i = 0; i < padres.size(); i++)
        for (int j = 0; j < padres.size(); j++) {
            if (i != j) {
                vector<int> hijo;
                creahijo(padres[i], padres[j], hijo);
                if (!aberracion(hijo, presupuesto, costo, predecesores))
                    poblacion.push_back(hijo);
            }
        }
}


void regenerapoblacion(vector<vector<int> > &poblacion,
                       int *beneficio, int presupuesto) {
    mataclon(poblacion);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [beneficio](const vector<int> &a, const vector<int> &b) {
             int suma = 0, sumb = 0;
             for (int i = 0; i < a.size(); i++)
                 suma += calculafitness(a, beneficio);
             for (int i = 0; i < b.size(); i++)
                 sumb += calculafitness(b, beneficio);

             return suma > sumb;
         });
    if (poblacion.size() > NUMIND)
        poblacion.erase(poblacion.begin() + NUMIND, poblacion.end());
}

void mutacion(vector<vector<int> > &poblacion, vector<vector<int> > padres,
              int *costo, int presupuesto, vector<vector<int> > predecesores) {
    int nmutaciones = round(padres[0].size() * TMUTACION);
    for (int i = 0; i < padres.size(); i++) {
        int cont = 0;
        while (cont < nmutaciones) {
            int gen = rand() % padres[i].size();
            //aqui hay que cambiar si son numeros enteros
            if (padres[i][gen] == 0) padres[i][gen] = 1;
            else padres[i][gen] = 0;
            cont++;
        }
        if (!aberracion(padres[i], presupuesto, costo, predecesores))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int> > &poblacion, vector<vector<int> > padres,
               int *costo, int presupuesto, vector<vector<int> > predecesores) {
    for (int i = 0; i < padres.size(); i++) {
        for (int j = 0; j < padres[i].size(); j++) {
            //cambiar para numeros enteros
            if (padres[i][j] == 0) padres[i][j] = 1;
            else padres[i][j] = 0;
        }
        if (!aberracion(padres[i], presupuesto, costo, predecesores))
            poblacion.push_back(padres[i]);
    }
}

int muestramejor(vector<vector<int> > poblacion,
                 int *costo, int *beneficio, int presupuesto) {
    int mejor = 0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for (int i = 0; i < poblacion.size(); i++)
        if (calculafitness(poblacion[mejor], beneficio) < calculafitness(poblacion[i], beneficio))
            mejor = i;

    cout << endl << "La mejor solucion es (beneficio-costo):" << calculafitness(poblacion[mejor], beneficio)
            << "-" << calculacosto(poblacion[mejor], costo) << endl;
    for (int i = 0; i < poblacion[mejor].size(); i++)
        cout << poblacion[mejor][i] << "  ";
    cout << endl;
    return presupuesto - calculacosto(poblacion[mejor], costo);
}

void mochilaAG(int *beneficio, int n, int presupuesto, int *costo, vector<vector<int> > predecesores) {
    vector<vector<int> > poblacion;
    generapoblacion(poblacion, costo, n, presupuesto, predecesores);

    for (int i = 0; i < ITERACIONES; i++) {
        vector<vector<int> > padres;
        muestrapoblacion(poblacion, beneficio);
        cout << endl;
        seleccion(poblacion, padres, beneficio, n, presupuesto);
        casamiento(poblacion, padres, costo, presupuesto, predecesores);
        mataclon(poblacion);
        mutacion((poblacion), padres, costo, presupuesto, predecesores);
        inversion(poblacion, padres, costo, presupuesto, predecesores);

        regenerapoblacion(poblacion, beneficio, presupuesto);
        muestrapoblacion(poblacion, beneficio);
        muestramejor(poblacion, costo, beneficio, presupuesto);
    }
}

int main() {
    int costo[] = {100, 50, 150, 50, 50, 150, 100};
    int beneficio[] = {200, 300, 300, 400, 200, 800, 250};
    int n = sizeof(costo) / sizeof(costo[0]);
    int presupuesto = 400;
    vector<vector<int> > predecesores = {{},{1},{1},{},{4},{2, 4},{}
    };

    mochilaAG(beneficio, n, presupuesto, costo, predecesores);

    return 0;
}
