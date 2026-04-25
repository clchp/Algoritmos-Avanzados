#include <iostream>
#include <vector>

using namespace std;

#define ATTRIBUTES 3
#define N_PRESENTATIONS 4
#define TRONCOS 10


void resolver(int data[ATTRIBUTES][N_PRESENTATIONS]) {
    //ORDENAR POR FINAL
    for (int i = 0; i < N_PRESENTATIONS; i++) {
        for(int j=0;j<N_PRESENTATIONS;j++) {
            if (data[1][i]<data[1][j]) {
                for(int k=0;k<ATTRIBUTES;k++) {
                    int temp=data[k][i];
                    data[k][i]=data[k][j];
                    data[k][j]=temp;
                }
            }
        }
    }
    //ver si esta ordenado IMPRESION
    cout<<"PRESENTACIONES ORDENADAS: "<<endl;
    for (int i = 0; i < N_PRESENTATIONS; i++) {
        cout<<"Presentacion N"<<i+1<<": ";
        for(int j=0;j<ATTRIBUTES;j++) {
            cout<<data[j][i]<<" ";
        }
        cout<<endl;
    }
    //Ahora comienza la magia
    int dp[N_PRESENTATIONS+1]; //aqui tendra la mejor ganancia teniendo la presentacion i como limite
    dp[0]=0; //nada con 0 presentaciones

    for(int i=1;i<N_PRESENTATIONS+1;i++) {
        int ganancia_actual=data[2][i-1];
        int inicio_actual=data[0][i-1];

        int ganancia_sinincluir=dp[i-1]; //eso es si no lo tomo
        int ganancia_incluyendo=ganancia_actual;

        for(int j=i-1;j>0;j--) { //ahora vamos a buscar una presentacion anterior con la que pueda estar
            int final_anterior=data[1][j-1];
            if (inicio_actual>=final_anterior) {
                ganancia_incluyendo+=dp[j]; //hasta es emomento
                break; //ya encontramos
            }
        }
        dp[i]=max(ganancia_sinincluir, ganancia_incluyendo);
    }
    cout<<"GANANCIA: S/."<<dp[N_PRESENTATIONS]*TRONCOS<<endl;
}

int main() {
    /*
Inicio (m) 5 2 6 4
Fin (m) 10 4 12 15
Beneficio (S/.) 30 40 80 100
 */
    int data[ATTRIBUTES][N_PRESENTATIONS] = {
        {5, 2, 6, 4},
        {10, 4, 12, 15},
        {30, 40, 80, 100}
    };
    resolver(data);
    return 0;
}