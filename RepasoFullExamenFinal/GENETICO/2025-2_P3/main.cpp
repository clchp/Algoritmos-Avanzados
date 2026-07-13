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

using namespace  std;

int calculafitness(vector<int>cromo,int matriz[][5]) {
    int sumap=0;
    for(int i=0;i<cromo.size();i++) {
        if (cromo[i]!=0) {
            sumap+=matriz[i][cromo[i]-1];
        }
    }
    return sumap;
}

bool aberracion(vector<int>ind,int *maquinas_num_max,int matriz[][5]) {
    //vamosa verificar que el individuo cumpla con no pasarse de operarios por maquina y que haya al menos un operario por cada maquina
    vector<int> operarios_x_maquina={0,0,0,0,0};
    for (int i=0;i<ind.size();i++) {
        if (ind[i]!=0) {
            operarios_x_maquina[ind[i]-1]++;
        }
    }
    //Condicion de operadores por maquina
    for (int i=0;i<operarios_x_maquina.size();i++) {
        if (maquinas_num_max[i]<operarios_x_maquina[i]) {
            return true;
        }
    }
    //condicion de que al menos haya uno
    for (int i=0;i<operarios_x_maquina.size();i++) {
        if (operarios_x_maquina[i]==0) {
            return true;
        }
    }
    return false;
}

void muestrapoblacion(vector<vector<int>>poblacion,int matriz[][5]) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<" fo="<< calculafitness(poblacion[i],matriz)<<endl;
    }

}

int decimal(vector<int>ind, int base) {
    int num=0;
    for (int i=0;i<ind.size();i++)
        num+=ind[i]*pow(base,i);
    return num;
}

void mataclon(vector<vector<int>> &poblacion, int base) {
    map<int,vector<int>> indunicos;

    for(int i=0;i<poblacion.size();i++) {
        int dec=decimal(poblacion[i], base);
        indunicos[dec]=poblacion[i];
    }
    poblacion.clear();
    for(map<int,vector<int>>::iterator it=indunicos.begin();
        it!=indunicos.end();it++) {
        poblacion.push_back(it->second);
    }
}

void generapoblacion(vector<vector<int>> &poblacion,
    int matriz[][5],int *maquinas_num_max,int num_maquinas, int num_operadores) {
    int cont=0;
    srand(time(NULL));
    while (cont<NUMIND) {
        vector<int> individuo;
        for (int i=0; i<num_operadores; i++)
            individuo.push_back(rand()%num_maquinas+1);
        if (!aberracion(individuo,maquinas_num_max,matriz)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,int matriz[][5]) {
    int sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],matriz);
    for (int i=0;i<poblacion.size();i++) {
        int superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],matriz)/sumafitness);
        supervivencia.push_back(superfit);
    }
}
void cargaruleta(vector<int >supervivencia,int *ruleta) {
    int cont=0;
    for (int i=0;i<supervivencia.size();i++)
        for (int j=0;j<supervivencia[i];j++) {
            ruleta[cont++]=i;
        }
}

void seleccion(vector<vector<int>>poblacion,vector<vector<int>> &padres,
   int matriz[][5]) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,matriz);
    cargaruleta(supervivencia,ruleta);
    int npadres=round(poblacion.size()*TSELECCION);

    for (int i=0;i<npadres;i++) {
        int ticket=rand()%100;
        if (ruleta[ticket]!=-1)
            padres.push_back(poblacion[ruleta[ticket]]);
    }
    //muestrapoblacion(padres,paq);
}

void creahijo(vector<int>padre,vector<int>madre,
    vector<int>&hijo) {
    int posi=round(padre.size()*PCASAMIENTO);

    for (int i=0;i<posi;i++)
        hijo.push_back(padre[i]);
    for (int i=posi;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[][5], int *maquinas_num_max) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,maquinas_num_max,matriz))
                    poblacion.push_back(hijo);
            }


        }
}


void regenerapoblacion(vector<vector<int>> &poblacion,
        int matriz[][5], int base){
    mataclon(poblacion, base);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [matriz](const vector<int>& a, const vector<int>& b) {
            int suma=0, sumb=0;
            for(int i=0;i<a.size();i++)
                suma += calculafitness(a, matriz);
            for(int i=0;i<b.size();i++)
                sumb += calculafitness(b, matriz);

            return suma > sumb;
         });
    if (poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,poblacion.end());

}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[][5], int *maquinas_num_max, int base) {
    int nmutaciones=round(padres[0].size()*TMUTACION);
    for (int i=0;i<padres.size();i++) {
        int cont=0;
        while (cont<nmutaciones) {
            int gen=rand()%padres[i].size();
            //aqui hay que cambiar si son numeros enteros
            int nuevo;
            do {
                nuevo=rand()%base;
            }while (nuevo==padres[i][gen]);
            padres[i][gen]=nuevo;
            cont++;
        }
        if (!aberracion(padres[i],maquinas_num_max,matriz))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[][5], int *maquinas_num_max) {

    for (int i=0;i<padres.size();i++) {
        int fin =rand()%padres[i].size();
        int inicio= rand()%padres[i].size();

        if (inicio>fin) {
            swap(inicio, fin);
        }

        while (inicio<fin) {
            swap(padres[i][inicio],padres[i][fin]);
            inicio++;
            fin--;
        }

        if (!aberracion(padres[i],maquinas_num_max,matriz))
            poblacion.push_back(padres[i]);
    }
}

int muestramejor(vector<vector<int>> poblacion,
        int matriz[][5]){
    int mejor=0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],matriz)<calculafitness(poblacion[i],matriz))
            mejor=i;

    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],matriz)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++)
        cout << poblacion[mejor][i] << "  ";

    cout << endl;
    return calculafitness(poblacion[mejor],matriz); //ya que esto
}

void genetico(int num_operadores, int num_maquinas, int matriz[][5], int *maquinas_num_max) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion,matriz,maquinas_num_max, num_maquinas, num_operadores);
    for(int i=0;i<ITERACIONES;i++) {
        vector<vector<int>>padres;
        //muestrapoblacion(poblacion,paq);
        //cout << endl;
        seleccion(poblacion,padres,matriz);
        casamiento(poblacion,padres,matriz,maquinas_num_max);
        mataclon(poblacion, num_maquinas);
        mutacion((poblacion),padres,matriz,maquinas_num_max, num_maquinas+1);
        inversion(poblacion,padres,matriz, maquinas_num_max);
        regenerapoblacion(poblacion,matriz, num_maquinas+1);
        //muestrapoblacion(poblacion,matriz);
    }
    muestramejor(poblacion,matriz);
}

int main() {
    int operadores=7;
    int maquinas=5;
    int matriz[7][5]={
        {3,4,5,3,6},
        {3,2,1,2,5},
        {1,8,5,3,1},
        {3,6,4,6,3},
        {8,2,10,4,9},
        {7,6,3,2,3},
        {4,5,1,3,6}
    };
    int maquinas_num_max[5]={2,3,1,4,3};
    genetico(operadores, maquinas, matriz, maquinas_num_max);

    return 0;
}