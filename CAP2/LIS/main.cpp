#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> dp;

int maximaCantidad(int n, int maximo, vector<int>tareas) {
    if (n==0 or maximo==0)return 0;
    if (dp[n][maximo]!=-1) return dp[n][maximo];
    if (tareas[n-1]>maximo) dp[n][maximo]=maximaCantidad(n-1,maximo,tareas);
    else dp[n][maximo]=max(maximaCantidad(n-1,maximo,tareas), tareas[n-1]+maximaCantidad(n-1,maximo-tareas[n-1],tareas));
    return dp[n][maximo];
}

int main() {
    vector<int> tareas={1, 3, 6, 10, 16};// horas que se tiene por cada tarea
    int n=tareas.size();
    int turnos;

    cout<<"Ingrese la cantidad de turnos que se desean realizar: ";
    cin>>turnos;
    int maximo=turnos*8;

    dp.assign(n+1,vector<int>(maximo+1,-1));

    cout<<"Con "<<turnos<<" se pueden realizar en "<<maximaCantidad(n, maximo, tareas)<<" horas sin sobrepasar las "<<maximo<<
        " del turno ("<<turnos<<")"<<endl;
    return 0;
}
