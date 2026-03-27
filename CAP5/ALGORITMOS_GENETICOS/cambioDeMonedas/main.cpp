#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==============================
// Parámetros del AG
// ==============================
#define NUM_IND      20    // tamaño de población
#define NUM_ITER     40    // número de generaciones
#define T_SELECCION  0.5   // porcentaje de padres
#define P_CRUCE      0.7   // probabilidad de cruce
#define P_MUTACION   0.2   // probabilidad de mutar un job

// ==============================
// Estructura de Individuo
// genes[m][j] = 0/1
//   m: máquina
//   j: job
// ==============================
struct Individuo {
    vector< vector<int> > genes; // matriz binaria máquina x job
    int makespan;                // tiempo total (fin del último job)
    int fitness;                 // mayor fitness = mejor (menor makespan)

    Individuo() {
        makespan = 0;
        fitness  = 0;
    }
};

// ==============================
// Ayudas: genes <-> asignación
// asign[j] = máquina donde va el job j
// ==============================

// Inicializar genes con ceros
void inicializarGenes(Individuo &ind, int numMaquinas, int numJobs) {
    ind.genes.clear();
    ind.genes.resize(numMaquinas, vector<int>(numJobs, 0));
}

// Desde asignación → matriz binaria
void asignarAsignacionAGenes(Individuo &ind,
                             const vector<int> &asign,
                             int numMaquinas,
                             int numJobs) {
    inicializarGenes(ind, numMaquinas, numJobs);

    for (int j = 0; j < numJobs; j++) {
        int m = asign[j];
        if (m < 0 || m >= numMaquinas) m = 0; // seguridad
        ind.genes[m][j] = 1;
    }
}

// Desde matriz binaria → asignación
void obtenerAsignacion(const Individuo &ind,
                       vector<int> &asign,
                       int numMaquinas,
                       int numJobs) {
    asign.clear();
    asign.resize(numJobs, 0);

    for (int j = 0; j < numJobs; j++) {
        int maq = 0;
        for (int m = 0; m < numMaquinas; m++) {
            if (ind.genes[m][j] == 1) {
                maq = m;
                break;
            }
        }
        asign[j] = maq;
    }
}

// ==============================
// Evaluación: calcular makespan
// tiempos[m][j]   = duración de job j en máquina m
// preds[j]        = lista de jobs que deben terminar antes de j
// maxTotal        = cota superior para fitness (suma de peores tiempos)
// ==============================
void actualizarMetricas(Individuo &ind,
                        const vector< vector<int> > &tiempos,
                        const vector< vector<int> > &preds,
                        int numMaquinas,
                        int numJobs,
                        int maxTotal) {

    vector<int> asign;
    obtenerAsignacion(ind, asign, numMaquinas, numJobs);

    vector<int> jobEnd(numJobs, 0);      // fin de cada job
    vector<int> machineEnd(numMaquinas, 0); // fin de cada máquina
    vector<bool> hecho(numJobs, false);  // ya programado
    int hechos = 0;

    // Programamos trabajos respetando dependencias:
    // mientras queden jobs sin programar, buscamos alguno
    // cuyas dependencias ya estén hechos.
    while (hechos < numJobs) {
        bool avanzo = false;

        for (int j = 0; j < numJobs; j++) {
            if (hecho[j]) continue;

            // ¿todas sus dependencias están hechas?
            bool listo = true;
            int finPredMax = 0;
            for (int k = 0; k < (int)preds[j].size(); k++) {
                int p = preds[j][k];
                if (!hecho[p]) {
                    listo = false;
                    break;
                }
                if (jobEnd[p] > finPredMax)
                    finPredMax = jobEnd[p];
            }
            if (!listo) continue;

            int m = asign[j];
            int dur = tiempos[m][j];

            // puede empezar cuando:
            //  - su máquina esté libre (machineEnd[m])
            //  - todas sus dependencias hayan terminado (finPredMax)
            int start = machineEnd[m];
            if (finPredMax > start) start = finPredMax;

            int finish = start + dur;

            jobEnd[j]     = finish;
            machineEnd[m] = finish;
            hecho[j]      = true;
            hechos++;
            avanzo = true;
        }

        // Si no pudimos programar ningún job → hay ciclo de dependencias
        if (!avanzo) {
            ind.makespan = maxTotal;
            ind.fitness  = 1;
            return;
        }
    }

    // Makespan = máximo tiempo de fin de todos los trabajos
    int mk = 0;
    for (int j = 0; j < numJobs; j++) {
        if (jobEnd[j] > mk)
            mk = jobEnd[j];
    }
    ind.makespan = mk;

    // Fitness: mientras menor makespan, mayor fitness.
    ind.fitness = (maxTotal - ind.makespan) + 1;
    if (ind.fitness < 1) ind.fitness = 1;
}

// ==============================
// Generar asignación aleatoria
// ==============================
void generarAsignacionAleatoria(vector<int> &asign,
                                int numMaquinas,
                                int numJobs) {
    asign.clear();
    asign.resize(numJobs);

    for (int j = 0; j < numJobs; j++) {
        asign[j] = rand() % numMaquinas;
    }
}

// Generar individuo aleatorio
void generarIndividuoAleatorio(Individuo &ind,
                               const vector< vector<int> > &tiempos,
                               const vector< vector<int> > &preds,
                               int numMaquinas,
                               int numJobs,
                               int maxTotal) {
    vector<int> asign;
    generarAsignacionAleatoria(asign, numMaquinas, numJobs);
    asignarAsignacionAGenes(ind, asign, numMaquinas, numJobs);
    actualizarMetricas(ind, tiempos, preds, numMaquinas, numJobs, maxTotal);
}

// ==============================
// Población inicial P0
// ==============================
void generarPoblacionInicial(vector<Individuo> &poblacion,
                             const vector< vector<int> > &tiempos,
                             const vector< vector<int> > &preds,
                             int numMaquinas,
                             int numJobs,
                             int maxTotal) {
    poblacion.clear();
    for (int i = 0; i < NUM_IND; i++) {
        Individuo ind;
        generarIndividuoAleatorio(ind, tiempos, preds,
                                  numMaquinas, numJobs, maxTotal);
        poblacion.push_back(ind);
    }
}

// ==============================
// Matar clones (misma asignación)
// ==============================
string codificar(const Individuo &ind,
                 int numMaquinas,
                 int numJobs) {
    vector<int> asign;
    obtenerAsignacion(ind, asign, numMaquinas, numJobs);

    string clave = "";
    for (int j = 0; j < numJobs; j++) {
        // codificamos máquina como letra
        clave += char('A' + asign[j]);
    }
    return clave;
}

void matarClones(vector<Individuo> &poblacion,
                 int numMaquinas,
                 int numJobs) {
    map<string, Individuo> unicos;

    for (int i = 0; i < (int)poblacion.size(); i++) {
        string clave = codificar(poblacion[i], numMaquinas, numJobs);
        unicos[clave] = poblacion[i];
    }

    poblacion.clear();
    map<string, Individuo>::iterator it;
    for (it = unicos.begin(); it != unicos.end(); it++) {
        poblacion.push_back(it->second);
    }
}

// ==============================
// Supervivencia y ruleta
// ==============================
void calcularSupervivencia(const vector<Individuo> &poblacion,
                           vector<int> &supervivencia) {
    supervivencia.clear();
    int sumaFit = 0;

    for (int i = 0; i < (int)poblacion.size(); i++) {
        sumaFit += poblacion[i].fitness;
    }

    if (sumaFit == 0) {
        supervivencia.assign(poblacion.size(), 1);
        return;
    }

    for (int i = 0; i < (int)poblacion.size(); i++) {
        double propor = (double)poblacion[i].fitness / (double)sumaFit;
        int porcentaje = (int)(100.0 * propor + 0.5);
        supervivencia.push_back(porcentaje);
    }
}

void cargarRuleta(const vector<int> &supervivencia,
                  int ruleta[100]) {
    int cont = 0;
    for (int i = 0; i < (int)supervivencia.size() && cont < 100; i++) {
        for (int j = 0; j < supervivencia[i] && cont < 100; j++) {
            ruleta[cont] = i;
            cont++;
        }
    }
    while (cont < 100) {
        ruleta[cont] = -1;
        cont++;
    }
}

void seleccion(const vector<Individuo> &poblacion,
               vector<Individuo> &padres) {
    padres.clear();

    int ruleta[100];
    for (int i = 0; i < 100; i++) ruleta[i] = -1;

    vector<int> supervivencia;
    calcularSupervivencia(poblacion, supervivencia);
    cargarRuleta(supervivencia, ruleta);

    int nPadres = (int)(poblacion.size() * T_SELECCION + 0.5);
    if (nPadres < 2) nPadres = 2;

    for (int i = 0; i < nPadres; i++) {
        int ticket = rand() % 100;
        if (ruleta[ticket] != -1) {
            padres.push_back(poblacion[ruleta[ticket]]);
        }
    }
}

// ==============================
// Cruce sobre asignación (vector<int> asign)
// ==============================
Individuo cruzar(const Individuo &p1,
                 const Individuo &p2,
                 const vector< vector<int> > &tiempos,
                 const vector< vector<int> > &preds,
                 int numMaquinas,
                 int numJobs,
                 int maxTotal) {
    vector<int> a1, a2;
    obtenerAsignacion(p1, a1, numMaquinas, numJobs);
    obtenerAsignacion(p2, a2, numMaquinas, numJobs);

    vector<int> hijoAsign(numJobs);

    int punto = rand() % numJobs; // corte simple

    for (int j = 0; j < numJobs; j++) {
        if (j < punto) hijoAsign[j] = a1[j];
        else           hijoAsign[j] = a2[j];
    }

    Individuo hijo;
    asignarAsignacionAGenes(hijo, hijoAsign, numMaquinas, numJobs);
    actualizarMetricas(hijo, tiempos, preds, numMaquinas, numJobs, maxTotal);
    return hijo;
}

void aplicarCruce(const vector<Individuo> &padres,
                  vector<Individuo> &poblacion,
                  const vector< vector<int> > &tiempos,
                  const vector< vector<int> > &preds,
                  int numMaquinas,
                  int numJobs,
                  int maxTotal) {
    int n = (int)padres.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double r = (double)rand() / RAND_MAX;
            if (r <= P_CRUCE) {
                Individuo hijo = cruzar(padres[i], padres[j],
                                        tiempos, preds,
                                        numMaquinas, numJobs, maxTotal);
                poblacion.push_back(hijo);
            }
        }
    }
}

// ==============================
// Mutación: mover algunos jobs a otra máquina
// ==============================
void mutar(Individuo &ind,
           const vector< vector<int> > &tiempos,
           const vector< vector<int> > &preds,
           int numMaquinas,
           int numJobs,
           int maxTotal) {
    double r = (double)rand() / RAND_MAX;
    if (r > P_MUTACION) return;

    vector<int> asign;
    obtenerAsignacion(ind, asign, numMaquinas, numJobs);

    // cambiamos la máquina de un job al azar
    int j = rand() % numJobs;
    int maqActual = asign[j];
    int nuevaMaq = rand() % numMaquinas;
    if (nuevaMaq == maqActual) {
        nuevaMaq = (nuevaMaq + 1) % numMaquinas;
    }
    asign[j] = nuevaMaq;

    asignarAsignacionAGenes(ind, asign, numMaquinas, numJobs);
    actualizarMetricas(ind, tiempos, preds, numMaquinas, numJobs, maxTotal);
}

void aplicarMutacion(vector<Individuo> &poblacion,
                     const vector< vector<int> > &tiempos,
                     const vector< vector<int> > &preds,
                     int numMaquinas,
                     int numJobs,
                     int maxTotal) {
    for (int i = 0; i < (int)poblacion.size(); i++) {
        mutar(poblacion[i], tiempos, preds,
              numMaquinas, numJobs, maxTotal);
    }
}

// ==============================
// Regenerar población (matar clones, ordenar, recortar)
// ==============================
bool compararPorFitness(const Individuo &a, const Individuo &b) {
    return a.fitness > b.fitness;
}

void regenerarPoblacion(vector<Individuo> &poblacion,
                        int numMaquinas,
                        int numJobs) {
    matarClones(poblacion, numMaquinas, numJobs);
    sort(poblacion.begin(), poblacion.end(), compararPorFitness);

    if ((int)poblacion.size() > NUM_IND) {
        poblacion.erase(poblacion.begin() + NUM_IND, poblacion.end());
    }
}

// ==============================
// Mejor individuo
// ==============================
Individuo obtenerMejor(const vector<Individuo> &poblacion) {
    int mejor = 0;
    for (int i = 1; i < (int)poblacion.size(); i++) {
        if (poblacion[i].fitness > poblacion[mejor].fitness) {
            mejor = i;
        }
    }
    return poblacion[mejor];
}

// ==============================
// GA principal para scheduling con dependencias
// ==============================
Individuo schedulingAG(const vector< vector<int> > &tiempos,
                       const vector< vector<int> > &preds,
                       int numMaquinas,
                       int numJobs) {

    // maxTotal = suma de “peores” tiempos por job (cota para fitness)
    int maxTotal = 0;
    for (int j = 0; j < numJobs; j++) {
        int peor = 0;
        for (int m = 0; m < numMaquinas; m++) {
            if (tiempos[m][j] > peor)
                peor = tiempos[m][j];
        }
        maxTotal += peor;
    }

    vector<Individuo> poblacion;
    generarPoblacionInicial(poblacion, tiempos, preds,
                            numMaquinas, numJobs, maxTotal);

    for (int it = 0; it < NUM_ITER; it++) {
        vector<Individuo> padres;
        seleccion(poblacion, padres);
        aplicarCruce(padres, poblacion, tiempos, preds,
                     numMaquinas, numJobs, maxTotal);
        aplicarMutacion(poblacion, tiempos, preds,
                        numMaquinas, numJobs, maxTotal);
        regenerarPoblacion(poblacion, numMaquinas, numJobs);
    }

    return obtenerMejor(poblacion);
}

// ==============================
// main: ejemplo de uso
// ==============================
int main() {
    srand((unsigned)time(NULL));

    // Ejemplo: 4 jobs, 2 máquinas
    // tiempos[m][j] = tiempo del job j en la máquina m
    vector< vector<int> > tiempos(2, vector<int>(4));
    // Máquina 0
    tiempos[0][0] = 5;  // job0 en maq0
    tiempos[0][1] = 7;  // job1 en maq0
    tiempos[0][2] = 4;  // job2 en maq0
    tiempos[0][3] = 6;  // job3 en maq0
    // Máquina 1
    tiempos[1][0] = 3;  // job0 en maq1
    tiempos[1][1] = 8;  // job1 en maq1
    tiempos[1][2] = 6;  // job2 en maq1
    tiempos[1][3] = 5;  // job3 en maq1

    int numMaquinas = 2;
    int numJobs     = 4;

    // Dependencias: preds[j] = lista de jobs que deben ir antes
    vector< vector<int> > preds(numJobs);
    // job1 depende de job0
    preds[1].push_back(0);
    // job2 depende de job0
    preds[2].push_back(0);
    // job3 depende de job1 y job2
    preds[3].push_back(1);
    preds[3].push_back(2);

    Individuo mejor = schedulingAG(tiempos, preds, numMaquinas, numJobs);

    cout << "\n===== MEJOR SOLUCION (SCHEDULING CON DEPENDENCIAS) =====\n";
    cout << "Makespan = " << mejor.makespan
         << "  (fitness = " << mejor.fitness << ")\n";

    vector<int> asign;
    obtenerAsignacion(mejor, asign, numMaquinas, numJobs);

    cout << "Asignacion job -> maquina:\n";
    for (int j = 0; j < numJobs; j++) {
        cout << "  Job " << j << " -> Maquina " << asign[j] << "\n";
    }

    cout << "\nMatriz binaria genes[m][j] del mejor individuo:\n";
    for (int m = 0; m < numMaquinas; m++) {
        cout << "Maq " << m << ": ";
        for (int j = 0; j < numJobs; j++) {
            cout << mejor.genes[m][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
