#include <iostream>
#include <vector>

using namespace std;

#define ATRIBUTOS 3
#define N_EVENTOS 6

void resolver_eventos(int data[ATRIBUTOS][N_EVENTOS]) {
    //como ya esta ordenado, ya no se debe hacer eso, sino el dp d1
    //lo vamos a tratar como si fuera un coin row
    int dp[N_EVENTOS+1]; //aqui se guarda la ganancia mayor en base a cuantos eventos se escoge
    dp[0]=0; //con 0 eventos no hay ganancia

    for (int i=1;i<=N_EVENTOS;i++) { //VAMOS a RECORRER TODOS LOS EVENTOS
        int inicio_actual=data[0][i-1];
        int ganancia_actual=data[2][i-1];

        //opcion A: no se incluye el producto
        int ganancia_sinincluir=dp[i-1];
        //opcion B: si se incluye el producto
        int ganancia_incluyendo=ganancia_actual;

        for (int j=i-1;j>0;j--) { //recorremos hacia atras
            int final_anterior=data[1][j-1];
            if (inicio_actual>final_anterior) { //hacemos que sea mayor para que como minimo acepte 1 y no igual
                if (inicio_actual-final_anterior==1) {
                    //cout<<"Final anterior: "<<final_anterior<<" Inicio actual: "<<inicio_actual<<endl;
                    ganancia_incluyendo+=15; //se le agrega 15 de bonificacion
                }
                ganancia_incluyendo+=dp[j]; //hasta ese evento
                break; //porque esta ordenado y con el dp se tiene la mejor solucion hasta ese momento
            }
        }
        dp[i]=max(ganancia_incluyendo,ganancia_sinincluir);
    }
    cout<<"GANANCIA MAXIMA: "<<dp[N_EVENTOS]<<endl;
}

int main() {
    //aqui guardamos la data
    int data[ATRIBUTOS][N_EVENTOS]={
        {1,4,6,6,5,8},
        {3,5,8,8,9,12},
        {30,10,60,20,50,40}
    };
    resolver_eventos(data);
    return 0;
}