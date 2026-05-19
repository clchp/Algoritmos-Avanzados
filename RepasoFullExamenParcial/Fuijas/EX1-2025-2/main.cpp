#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

struct NodoMaquina {
    int numero;
    int tiempo;
};

struct Tareas {
    int numero;
    vector<NodoMaquina> maquinas;
};

struct MaquinasRespuesta {
    int numeroMaquina;
    vector<int> nombreTarea;
    vector<int>tiempoTarea;
    int tiempoAcumulado=0;
};

void tiempo_acumulado_de_maquina_seleccionada(MaquinasRespuesta &maquinita) {
    int tiempoAcumulado=0;
    for (int i = 0; i < maquinita.nombreTarea.size(); i++) {
        tiempoAcumulado+=maquinita.tiempoTarea[i];
    }
    maquinita.tiempoAcumulado=tiempoAcumulado;
}

int hallarMejorMaquina(vector<NodoMaquina>&maquinas, vector<MaquinasRespuesta>&respuesta) {
    int menorTiempoAcumulado=99999, idxMenor;
    for (int i = 0; i < maquinas.size(); i++) {
        int tiempoMaquinaAcumuladoParcial=respuesta[i].tiempoAcumulado+maquinas[i].tiempo;
        if (tiempoMaquinaAcumuladoParcial<menorTiempoAcumulado) {
            menorTiempoAcumulado=tiempoMaquinaAcumuladoParcial;
            idxMenor=i;
        }
    }
    return idxMenor;
}
void imprimir(vector<MaquinasRespuesta>&respuesta) {
    cout<<"======================================================================="<<endl;
    for (int i = 0; i < respuesta.size(); i++) {
        cout<<"Maquina N"<<respuesta[i].numeroMaquina<<" | Tiempo acumulado: "<<respuesta[i].tiempoAcumulado<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"TAREAS PROCESADAS: ";
        for (int j=0;j<respuesta[i].nombreTarea.size();j++) {
            cout<<respuesta[i].tiempoTarea[j]<<"(T"<<respuesta[i].nombreTarea[j]<<")";
            if (j+1!=respuesta[i].nombreTarea.size()) {
                cout<<"-";
            }
        }
        cout<<endl<<"======================================================================="<<endl;
    }
}

void resolviendo_problema_claudia1_tupia0(vector<Tareas>data) {
    //Vamos a recorrer por cada tarea
    vector<MaquinasRespuesta> respuesta={
        {1,{},{}},
        {2,{},{}},
        {3,{},{}},
        {4,{},{}},
    }; //aqui vamos a guardar la data
    for (int i = 0; i < data.size(); i++) {
        vector<NodoMaquina> maquinas=data[i].maquinas; //aqui tenemos las maquinas
        int idxMejor=hallarMejorMaquina(maquinas, respuesta);
        respuesta[idxMejor].nombreTarea.push_back(data[i].numero);
        respuesta[idxMejor].tiempoTarea.push_back(maquinas[idxMejor].tiempo);
        tiempo_acumulado_de_maquina_seleccionada(respuesta[idxMejor]);
    }
    int makespan=0;
    for (int i = 0; i < respuesta.size(); i++) {
        if (makespan<respuesta[i].tiempoAcumulado) {
            makespan=respuesta[i].tiempoAcumulado;
        }
    }
    imprimir(respuesta);
    cout<<"Makespan: "<<makespan<<endl;
}


int main() {
    vector<Tareas> data={
        {1,{{1,6},{2,4},{3,3},{4,2}}},
        {2,{{1,7},{2,6},{3,4},{4,3}}},
        {3,{{1,4},{2,3},{3,2},{4,2}}},
        {4,{{1,8},{2,5},{3,11},{4,4}}},
        {5,{{1,5},{2,3},{3,2},{4,3}}},
        {6,{{1,9},{2,6},{3,5},{4,4}}},
        {7,{{1,7},{2,4},{3,3},{4,3}}},
        {8,{{1,6},{2,5},{3,4},{4,3}}},
        {9,{{1,8},{2,5},{3,4},{4,4}}},
        {10,{{1,9},{2,6},{3,5},{4,3}}}
    };
    resolviendo_problema_claudia1_tupia0(data);
    return 0;
}